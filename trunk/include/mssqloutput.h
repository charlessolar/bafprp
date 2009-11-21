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

#ifndef BAFPRPMSSQL_H
#define BAFPRPMSSQL_H

#include <sqltypes.h>

#include "output.h"

namespace bafprp
{
	class MSSQL : public Output
	{
	public:

		void record( const BafRecord* record );
		void error( const BafRecord* record, const std::string& error );
		void log( LOG_LEVEL level, const std::string& log );

	protected:
		// Register the output type
		MSSQL() : Output( "mssql" ) {}
		~MSSQL() { disconnect(); }

	private:
		void checkDB( property_map& props );
		void connect();
		void disconnect();
		std::string sanitize( const std::string& string );
		void extractError( std::ostringstream& os, char* fn, SQLHANDLE handle, SQLSMALLINT type );

		// property variables
		std::string _dsn;
		std::string _database;
		std::string _server;
		std::string _user;
		std::string _password;

		std::string _table;

		std::map<std::string,std::string> _columnCache;
		time_t _cacheAge;

		// private non-property variables
		SQLHENV _env;
		SQLHDBC _dbc;
		bool _dbConnected;
		
		// This variable simply initializes a class that registers with the main output code
		static const MSSQL registerThis;
	};
}

#endif
