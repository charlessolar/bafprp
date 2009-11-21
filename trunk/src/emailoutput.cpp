/*
Copyright (C) 2008 by Charles Solar
charlessolar@gmail.com

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

#include <ios>
#include <iomanip>

#include "jwsmtp.h"

#include "emailoutput.h"
#include "baffile.h"


namespace bafprp
{
	const Email Email::registerThis;

	void Email::error( const BafRecord* record, const std::string& error )
	{
		LOG_TRACE( "Email::error" );
		checkProperties( _errorProperties );
		if( _to == "" || _from == "" ) 
		{
			LOG_ERROR( "To or From property of email output is wrong" );
			return;
		}

		std::ostringstream os;

		jwsmtp::mailer m( _to.c_str(), _from.c_str(), "Error Report from BAFPRP", "Report:\n\n", "localhost", jwsmtp::mailer::SMTP_PORT, false);

		os.setf( std::ios::left );

		os << "* Record Error *********************************************" << std::endl;
		os << "*                                                          *" << std::endl;
		os << "*    " << std::setw(53) << NowTime() << " *" << std::endl;

		os << "*                                                          *" << std::endl;

		std::string rest = "";
		int space = 0;

		if( error.length() > 48 )
		{
			space = error.substr( 0, 48 ).find_last_of( " " );
			if( space == std::string::npos )
					space = 48;
		}
		else
			space = 48;

		os << "* Report: " << std::setw( 48 ) << error.substr( 0, space ) << " *" << std::endl;

		// Avoid the out_of_range exception
		if( error.length() > 48 )
			rest = error.substr( space + 1 );		
		
		// I like neatly formated messages.
		while( rest != "" )
		{
			if( rest.length() > 49 ) 
			{
				space = rest.substr( 0, 48 ).find_last_of( " " );
				if( space == std::string::npos )
					space = 48;
			}
			

			os << "*         " << std::setw( 48 ) << rest.substr( 0, space ) << " *" << std::endl;

			if( rest.length() > 49 )	
				rest = rest.substr( space + 1 );
			else
				rest = "";
		}

		os << "*                                                          *" << std::endl;
		os << "* Details: Type: " << std::setw(41) << record->getType() << " *" << std::endl;
		os << "*          Length: " << std::setw(39) << record->getSize() << " *" << std::endl;
		os << "*          Position: " << std::setw(37) << record->getFilePosition() << " *" << std::endl;
		os << "*          Filename: " << std::setw(37) << record->getFilename() << " *" << std::endl;

		os << "*                                                          *" << std::endl;
		std::string bytes = record->getData();
		os << "* BYTES: " << std::setw(49) << bytes.substr( 0, 48 ) << " *" << std::endl;

		rest = "";

		if( bytes.length() > 48 )
			rest = bytes.substr( 48 );
		
		while( rest != "" )
		{
			os << "*        " << std::setw(49) << rest.substr( 0, 48 ) << " *" << std::endl;

			if( rest.length() > 48 )
				rest = rest.substr( 48 );
			else
				rest = "";
		}
		os << "*                                                          *" << std::endl;
		os << "************************************************************" << std::endl;

		m.setmessage( os.str() );
		m.send();
		if( m.response().find( "OK" ) == std::string::npos )
		{
			LOG_ERROR( "Could not send email error, falling back to file output" );
			Output::setOutputError( "file" );

			Output::outputError( record, error );
		}

		LOG_TRACE( "/Email::error" );
	}

	void Email::log( LOG_LEVEL level, const std::string& log )
	{
		static int cache = 0;

		// We need to clear the cache when being destroyed.  However there is a problem,
		// there is a chance that out output class has already been destroyed.  In fact, this
		// is very likely to be the case.  As such _logProperties will be null and we will
		// crash in a firey ball of error messages if we try to get any data from it.
		// Obviously we do not want this to happen so we must check before using it.
		// HOWEVER, this is annoying because if for whatever reason the email properties
		// changed since the last cache empty these changes will not show up in this final
		// email.  Unfortunetly I can not think of a better solution for this at the moment
		if( log != "" ) checkProperties( _logProperties );
		
		if( cache >= _iCache || log == "" )
		{
			if( cache == 0 ) return; // Dont clear an empty cache


			if( _to == "" || _from == "" ) 
			{
				Output::setOutputLog( "file" );
				LOG_ERROR( "To or From property of email output is wrong, falling back to file output" );
				return;
			}

			jwsmtp::mailer m( _to.c_str(), _from.c_str(), "Log from BAFPRP", "Log:\n\n", _server.c_str(), _serverPort, false);
			
			std::string message = "";
			for( std::vector<std::string>::iterator itr = _cachedLogs.begin(); itr != _cachedLogs.end(); itr++ )
			{
				message += (*itr) + "\n";
			}
			m.setmessage( message.c_str() );
			
			m.send();
			if( m.response().find( "OK" ) == std::string::npos )
			{
				LOG_ERROR( "Could not send email log, falling back to file output" );
				Output::setOutputLog( "file" );

				for( std::vector<std::string>::iterator itr = _cachedLogs.begin(); itr != _cachedLogs.end(); itr++ )
				{
					// Can't really pick out the real log level at this point, oh well.
					Output::outputLog( LOG_LEVEL_WARN, *itr );
				}
				// Current log has not bee recorded yet.
				Output::outputLog( level, log );
			}
			_cachedLogs.clear();
			cache = 0;

			if( log == "" ) return;
		}

		std::string logstr = NowTime() + " " + getStrLogLevel( level ) + ": " + log;

		_cachedLogs.push_back( logstr );
		cache++;
	}

	void Email::record( const BafRecord* record )
	{
		LOG_TRACE( "Email::record" );
		// We need to clear the cache when being destroyed.  However there is a problem,
		// there is a chance that out output class has already been destroyed.  In fact, this
		// is very likely to be the case.  As such _recordProperties will be null and we will
		// crash in a firey ball of error messages if we try to get any data from it.
		// Obviously we do not want this to happen so we must check before using it.
		// HOWEVER, this is annoying because if for whatever reason the email properties
		// changed since the last cache empty these changes will not show up in this final
		// email.  Unfortunetly I can not think of a better solution for this at the moment
		if( record != NULL ) checkProperties( _recordProperties );

		static int cache = 0;

		// sending null will clear out the cache (for use at the end of the program)
		if( cache >= _iCache || record == NULL )
		{
			if( cache == 0 ) return; // Dont clear an empty cache

			if( _to == "" || _from == "" ) 
			{
				LOG_ERROR( "To or From property of email output is wrong" );
				return;
			}

			jwsmtp::mailer m( _to.c_str(), _from.c_str(), "Records from BAFPRP", "Record:\n\n", _server.c_str(), _serverPort, false);
			
			std::string message = "";
			for( std::vector<std::string>::iterator itr = _cachedRecords.begin(); itr != _cachedRecords.end(); itr++ )
			{
				message += (*itr) + "\n";
			}
			m.setmessage( message.c_str() );
			
			m.send();
			if( m.response().find( "OK" ) == std::string::npos )
			{
				LOG_ERROR( "Could not send email log, falling back to file output" );
				Output::setOutputLog( "file" );

				// Current log has not bee recorded yet.
				Output::outputRecord( record );
			}
			_cachedRecords.clear();
			cache = 0;

			// Obviously there is no actual record to log
			if( record == NULL ) return;
		}


		const IField* field;
		std::string value = "";
		DWORD lastUID = 0;

		std::ostringstream os;

		os << "--------------------------------------------------------------------------" << std::endl;
		os << record->getType() << std::endl;
		os << "--------------------------------------------------------------------------" << std::endl;
		os << "Length of record: " << record->getSize() << std::endl;
		os << "--------------------------------------------------------------------------" << std::endl;
		os << "File: " << record->getFilename() << std::endl;
		os << "--------------------------------------------------------------------------" << std::endl;
		os << "Position: " << record->getFilePosition() << std::endl;
		os << "--------------------------------------------------------------------------" << std::endl;

		// sending a last name of "" effectively returns us the begining, getting the ball rolling.
		while( ( field = record->getNextField( lastUID ) ) != NULL )
		{
			lastUID = field->getUID();
			if( !field->filter() ) os << field->getDesc() << ": " << field->getString() << std::endl;
		}

		_cachedRecords.push_back( os.str() );
		cache++;

		LOG_TRACE( "/Email::record" );
	}

	void Email::checkProperties( property_map& props )
	{
		LOG_TRACE( "Email::checkProperties" );

		property_map::iterator itr = props.find( "to" );
		if( itr != props.end() )
			_to = itr->second;
		else
			_to = "";

		itr = props.find( "from" );
		if( itr != props.end() )
			_from = itr->second;
		else
			_from = "";

		itr = props.find( "cache" );
		if( itr != props.end() )
		{
			// maybe add tolower here later
			if( itr->second != "true" && itr->second != "1" )
				_bCache = false;
			else
				_bCache = true;
		}
		else
			_bCache = true;

		
		itr = props.find( "cachesize" );
		if( itr != props.end() )
			_iCache = atoi( itr->second.c_str() );
		else
			_iCache = 100;

		itr = props.find( "server" );
		if( itr != props.end() )
			_server = itr->second;
		else
			_server = "localhost";

		itr = props.find( "port" );
		if( itr != props.end() )
			_serverPort = atoi( itr->second.c_str() );
		else
			_serverPort = jwsmtp::mailer::SMTP_PORT;

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
		
		LOG_TRACE( "/Email::checkProperties" );
	}

}
