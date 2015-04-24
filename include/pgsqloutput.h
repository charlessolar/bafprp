#ifndef BAFPRPPOSTGRESQL_H
#define BAFPRPPOSTGRESQL_H

#include <sqltypes.h>

#include "output.h"

namespace bafprp
{
        class POSTGRESQL : public Output
        {
        public:

                void record( const BafRecord* record );
                void error( const BafRecord* record, const std::string& error );
                void log( LOG_LEVEL level, const std::string& log );

        protected:
                // Register the output type
                POSTGRESQL() : Output( "postgresql" ) {}
                ~POSTGRESQL() { disconnect(); }

        private:
                void checkDB( property_map& props );
                void connect();
                void disconnect();
                std::string sanitize( const std::string& string );
                std::string escapeFileName( const std::string& string );
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
                static const POSTGRESQL registerThis;
        };
}

#endif
