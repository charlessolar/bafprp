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

#ifndef BAFPRPEMAIL_H
#define BAFPRPEMAIL_H

#include "output.h"

namespace bafprp
{
	class Email : public Output
	{
	public:

		void record( const IBafRecord* record );
		void error( const IBafRecord* record, const std::string& error );
		void log( LOG_LEVEL level, const std::string& log );

	protected:
		// Register the output type
		Email() : Output( "email" ) {}
		~Email()
		{
			// Sending empty data will make the functions clear the cache.
			// This makes it so that when the program ends records or logs
			// that are still in the cache will not be lost.
			record( NULL );
			log( LOG_LEVEL_FATAL, "" );
		}

	private:
		void checkProperties( property_map& props );

		std::string _to;
		std::string _from;
		std::string _server;
		int _serverPort;
		std::string _user;
		std::string _password;

		bool _bCache;
		int _iCache;

		std::vector<std::string> _cachedRecords;
		std::vector<std::string> _cachedLogs;
		// This variable simply initializes a class that registers with the main output code
		static const Email registerThis;
	};
}

#endif
