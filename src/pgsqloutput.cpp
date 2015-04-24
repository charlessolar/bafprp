/*
Copyright (C) 2011 by Stephane Garneau
sgarneau1220@gmail.com

This file is part of bafprp.

bafprp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

bafprp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with bafprp.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _WIN32
#include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>
#include <ostream>

#include "pgsqloutput.h"
#include "baffile.h"

#include <ios>
#include <cstring>
#include <iostream>
#include <cstdio>

namespace bafprp
{
	const POSTGRESQL POSTGRESQL::registerThis;

	void POSTGRESQL::error( const BafRecord* record, const std::string& error )
	{
		LOG_TRACE( "POSTGRESQL::error" );
		checkDB( _errorProperties );
		if( !_dbConnected || _table == "" ) 
		{
			Output::setOutputError( "file" );
			LOG_ERROR( "Failed to connect to the database, or you failed to supply a table, check your properties, falling back to file output" );

			// Play nice
			Output::outputError( record, error );
			return;
		}

		SQLHSTMT stmt;
		SQLAllocHandle(SQL_HANDLE_STMT, _dbc, &stmt);

		std::ostringstream os;

		os << "INSERT INTO " << _table << " ( ts, error, filename, filepos, type, length, bytes ) VALUES ( ";
		os << "'" << sanitize( NowTime() ) << "', ";
		os << "'" << sanitize( error ) << "', ";
		os << "'" << sanitize( record->getFilename() ) << "', ";
		os << "'" << record->getFilePosition() << "', ";
		os << "'" << sanitize( record->getType() ) << "', ";
		os << "'" << record->getSize() << "', ";
		os << "'" << sanitize( record->getData() ) << "' ";
		os << ")";

		if( SQLExecDirectA(stmt, (SQLCHAR*)os.str().c_str(), SQL_NTS) == SQL_ERROR )
		{
			os << "Error: ";
			extractError( os, (char *)"SQLExecDirectA", stmt, SQL_HANDLE_STMT );
			Output::setOutputError( "file" );
			LOG_ERROR( "Failed to insert error message into database, falling back to file output. Query: " << os.str() );

			Output::outputError( record, error );
		}

		SQLFreeHandle( SQL_HANDLE_STMT, stmt );

		LOG_TRACE( "/POSTGRESQL::error" );
	}

	void POSTGRESQL::log( LOG_LEVEL level, const std::string& log )
	{
		checkDB( _logProperties );

		if( !_dbConnected || _table == "" ) 
		{
			Output::setOutputLog( "file" );
			LOG_ERROR( "Failed to connect to the database, or you failed to supply a table, check your properties\n" );

			// Play nice
			Output::outputLog( level, log );
			return;
		}

		SQLHSTMT stmt;
		SQLAllocHandle(SQL_HANDLE_STMT, _dbc, &stmt);

		std::ostringstream os;
		os << "INSERT INTO " << _table << " ( ts, loglevel, msg ) VALUES ( '" << NowTime() << "', '" << level << "', '" << sanitize( log ) << "' )";
		if( SQLExecDirectA(stmt, (SQLCHAR*)os.str().c_str(), SQL_NTS) == SQL_ERROR )
		{
			os << "Error: ";
			extractError( os, (char *)"SQLExecDirectA", stmt, SQL_HANDLE_STMT );
			Output::setOutputLog( "file" );
			LOG_ERROR( "Failed to insert log into database, falling back to file output. Query: " << os.str() );

			Output::outputLog( level, log );
		}

		SQLFreeHandle( SQL_HANDLE_STMT, stmt );
	}

	void POSTGRESQL::record( const BafRecord* record )
	{
		LOG_TRACE( "POSTGRESQL::record" );
		checkDB( _recordProperties );
		
		if( !_dbConnected || _table == "" ) 
		{
			Output::setOutputRecord( "file" );
			LOG_ERROR( "Failed to connect to the database, or you failed to supply a table, check your properties, falling back to file output" );

			// Play nice
			Output::outputRecord( record );
			return;
		}

		SQLHSTMT stmt;
		
		// We do not need to query the table info each time, cache the result for five minutes
		if( ( time( NULL ) - _cacheAge ) > 300000 )
		{
			_cacheAge = time( NULL );

			// Query table to find out what the column names are
			
			SQLAllocHandle(SQL_HANDLE_STMT, _dbc, &stmt);

			std::ostringstream os;

		        os << "SELECT column_name, data_type FROM information_schema.columns WHERE table_name='" << _table << "'";	
			if( SQLExecDirectA(stmt, (SQLCHAR*)os.str().c_str(), SQL_NTS) == SQL_ERROR )
			{
				Output::setOutputRecord( "file" );
				std::ostringstream os;
				extractError( os, (char *)"SQLExecDirectA", stmt, SQL_HANDLE_STMT );
				LOG_ERROR( "Failed to query columns in database, falling back to file output. Error: " << os.str() );
				SQLFreeHandle( SQL_HANDLE_STMT, stmt );
				return;
			}

			SQLCHAR columnName[50];
			SQLCHAR columnType[50];
			long int cbData;
			while( SQLFetch(stmt) == SQL_SUCCESS )
			{
			  SQLGetData( stmt, 1, SQL_C_CHAR, columnName, sizeof( columnName ), &cbData );
			  SQLGetData( stmt, 2, SQL_C_CHAR, columnType, sizeof( columnType ), &cbData );
			  char* space = strchr( (char*)columnType, '(' );
			  if( space ) *space = '\0'; // trim off atributes
			  _columnCache.insert( std::make_pair( (char*)columnName, (char*)columnType ) );
			}

			SQLFreeHandle( SQL_HANDLE_STMT, stmt );
		}

		// Construct an insert query from the record values corresponding to those names
		// Two part query, see below
		std::ostringstream query1; 
		std::ostringstream query2;

		query1 << "INSERT INTO " << _table << " ( ";
		query2 << "VALUES ( ";
		
		for( std::map<std::string,std::string>::iterator itr = _columnCache.begin(); itr != _columnCache.end(); itr++ )
		{
			if( itr->first == "id" ) continue;  // Skip 'id' field

			// Check for 'special' columns
			if( itr->first == "filename" )
			{
				query1 << "filename, ";
				query2 << "'" << sanitize( record->getFilename() ) << "', ";
				continue;
			}
			if( itr->first == "filepos" )
			{
				query1 << "filepos, ";
				query2 << "'" << record->getFilePosition() << "', ";
				continue;
			}
			if( itr->first == "type" )
			{
				query1 << "type, ";
				query2 << "'" << sanitize( record->getType() ) << "', ";
				continue;
			}
			if( itr->first == "size" )
			{
				query1 << "size, ";
				query2 << "'" << record->getSize() << "', ";
				continue;
			}
			if( itr->first == "crc" )
			{
				query1 << "crc, ";
				query2 << "'" << record->getCRC() << "', ";
				continue;
			}

			if( !record->hasField( itr->first ) ) continue; // Skip fields the record does not have

			// Find field in record (if it exists)
			const IField* field = record->getField( itr->first );

			if( !field ) 
			{
				LOG_WARN( "Failed to retreive field " << itr->first << " from record for sql output" );
				continue;
			}
			if( field->filter() ) continue;

			if( itr->second == "int" || itr->second == "bigint" || itr->second == "integer" )
			{
				query1 << "\"" << itr->first << "\", ";
				query2 << "'" << field->getLong() << "', ";
			}
			else if( itr->second == "decimal" || itr->second == "float" )
			{
				query1 << "\"" << itr->first << "\", ";
				query2 << "'" << field->getFloat() << "', ";
			}
			else
			{
				query1 << "\"" << itr->first << "\", ";
				query2 << "'" << sanitize( field->getString() ) << "', ";
			}
		}

		// Make the full query, trimming off the surplus commas
		std::string fullQuery = query1.str().substr( 0, query1.str().length() - 2 ) + ") " + query2.str().substr( 0, query2.str().length() - 2 ) + ")";

		// LOG_TRACE(fullQuery);

		SQLAllocHandle(SQL_HANDLE_STMT, _dbc, &stmt);

		if( SQLExecDirectA(stmt, (SQLCHAR*)fullQuery.c_str(), SQL_NTS) == SQL_ERROR )
		{
			std::ostringstream os;
			extractError( os, (char *)"SQLExecDirectA", stmt, SQL_HANDLE_STMT );
			ERROR_OUTPUT( record, "Failed to insert record: " << record->getType() << " into database.  Query: " << fullQuery << " Error: " << os.str() );
		}

		SQLFreeHandle( SQL_HANDLE_STMT, stmt );

		LOG_TRACE( "/POSTGRESQL::record" );
	}

	void POSTGRESQL::checkDB( property_map& props )
	{
		LOG_TRACE( "POSTGRESQL::checkDB" );

		// Only allow 1 database connection for the whole program.  Properties only change the table name if need be once connected.
		// Through exparimentation it seems that switching databases and/or servers produces errors on the server when connecting and disconnecting so fast.

		property_map::iterator itr = props.find( "table" );
		if( itr != props.end() )
			_table = itr->second;
		else
			_table = "";

		if( _dbConnected ) return;

		itr = props.find( "dsn" );
		if( itr != props.end() )
			_dsn = itr->second;
		else
			_dsn = "";

		itr = props.find( "database" );
		if( itr != props.end() )
			_database = itr->second;
		else
			_database = "";

		itr = props.find( "server" );
		if( itr != props.end() )
			_server = itr->second;
		else
			_server = "localhost";

		itr = props.find( "user" );
		if( itr != props.end() )
			_user = itr->second;
		else
			_user = "";

		itr = props.find( "password" );
		if( itr != props.end() )
			_password = itr->second;
		else
			_password = "";


		// No database connected, so connect
		connect();


		// Should always be connected to 1 database
		if( !_dbConnected )
		{
			printf( "Failed to connect to the database: %s, postgresql output will not be available\n", _database.c_str() );
		}

		LOG_TRACE( "/POSTGRESQL::checkDB" );
	}

	void POSTGRESQL::disconnect()
	{
		if( !_dbConnected ) return;
		SQLDisconnect( _dbc );
		SQLFreeHandle( SQL_HANDLE_DBC, _dbc );
		SQLFreeHandle( SQL_HANDLE_ENV, _env );
		_dbConnected = false;
	}

	void POSTGRESQL::connect()
	{
		// We disconnect before the check because if the information passed is invalid, we want the program to
		// not corrupt the current database.
		if( _dbConnected ) disconnect();

		if( _dsn == "" && ( _database == "" || _server == "" || _user == "" || _password == "" ) )
		{
			std::cout << "DSN:" << _dsn << "\n";
			std::cout << "Database:" << _database << "\n";
			std::cout << "Server:" << _server << "\n";
			std::cout << "User:" << _user << "\n";
			std::cout << "PWD:" << _password << "\n";
			std::cout << "Not enough information to connect to sql database\n";

			return;
		}

		SQLRETURN ret;
		SQLCHAR OutConnStr[255];
		SQLSMALLINT OutConnStrLen;


		if( (ret=SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_env )) != SQL_SUCCESS )
		{
			printf( "Could not alocate environment handle\n" );
			disconnect();
			return;
		}

		if( (ret=SQLSetEnvAttr( _env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER )) != SQL_SUCCESS )
		{
			printf( "Could not set environment variable\n" );
			disconnect();
			return;
		}

		if( (ret=SQLAllocHandle( SQL_HANDLE_DBC, _env, &_dbc )) != SQL_SUCCESS )
		{
			printf( "Could not alocate database handle\n" );
			disconnect();
			return;
		}

		std::ostringstream os;
		std::string dsn;
		if( _dsn != "" )
			dsn = "DSN=" + _dsn;
		else
		{
	#ifdef _WIN32
			dsn = "DRIVER={PostgreSQL};Server=" + _server + ";Port=5432;DATABASE=" + _database + ";User=" + _user + "; Password=" + _password;
	#else
			dsn = "DRIVER={PostgreSQL};Server=" + _server + ";Port=5432"+ ";Uid="+ _user + ";Pwd=" + _password + ";DATABASE=" + _database + ";";			
	#endif
		}

		ret = SQLDriverConnectA( _dbc, NULL, (SQLCHAR*)dsn.c_str(), SQL_NTS, OutConnStr, sizeof( OutConnStr ), &OutConnStrLen, SQL_DRIVER_COMPLETE );

		if( SQL_SUCCEEDED( ret ) )
			_dbConnected = true;
		else
		{
			std::ostringstream os;
			extractError( os, (char *)"SQLDriverConnect", _dbc, SQL_HANDLE_DBC );
			printf( "%s\n", os.str().c_str() );
			disconnect();
		}
	}

	// Sanitize a string so it works in a sql query
	std::string POSTGRESQL::sanitize( const std::string& string )
	{
		std::string retVal = string;
		int pos = 0;
		while( ( pos = retVal.find( "'" ) ) != std::string::npos )
			retVal = retVal.replace( pos, 1, "\"" );
		
		return retVal;
	}
 
		// Sanitize a string so it works in a sql query
	std::string POSTGRESQL::escapeFileName( const std::string& string )
	{
		std::string retVal = string;

		for (int i = 0; i < retVal.length(); ++i)
		{
			if (retVal[i] == '\\')
			{
				retVal.replace(i, 1, "\\\\");
				++i; // Skip inserted char
			}//if
		}//for
	
		return retVal;
	}

	void POSTGRESQL::extractError( std::ostringstream& os, char* fn, SQLHANDLE handle, SQLSMALLINT type )
	{
		SQLSMALLINT	 i = 0;
		SQLINTEGER	 native;
		SQLCHAR	 state[ 7 ];
		SQLCHAR	 text[256];
		SQLSMALLINT	 len;
		SQLRETURN	 ret;

		os << "Error while running " << fn << ": ";
		do
		{
			ret = SQLGetDiagRecA(type, handle, ++i, state, &native, text,
								sizeof(text), &len );
			if (SQL_SUCCEEDED(ret))
				os << state << ":" << i << ":" << native << ":" << text;
		}
		while( ret == SQL_SUCCESS );

	}

}

