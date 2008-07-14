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

#ifndef BAFPRPOUTPUT_H
#define BAFPRPOUTPUT_H

#include <map>
#include <string>
#include <sstream>
#include <time.h>

#include "bafdefines.h"
#include "bafrecord.h"

namespace bafprp
{

	enum LOG_LEVEL
	{
		LOG_LEVEL_TRACE = 0,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_WARN,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_FATAL
	};

	class Output
	{
	protected:
		// For registering subclasses
		Output( const std::string name );
		
		// virtual methods for processing data
		virtual void record( BafRecord* record ) = 0;
		virtual void error( BafRecord* record, const std::string error ) = 0;
		virtual void log( const std::string log ) = 0;
	public:
		virtual ~Output();

		static void setLogLevel( LOG_LEVEL level ) { _level = level; }

		static void setOutput( const std::string name ) { _output = name; }

		static void recordOutput( BafRecord* record );
		static void errorOutput( BafRecord* record, const std::string error );
		static void logOutput( LOG_LEVEL level, const std::string log );

	private:
		// Allow no one to make this class
		Output() {}

		typedef std::map< std::string, Output* > output_map;

		static output_map& getReg()
		{
			static output_map registry;
			return registry;
		}

		static LOG_LEVEL _level;

		static std::string _output;

	};
	
	std::string NowTime();

	#define LOG_TRACE( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - TRACE: " << logEvent; \
		Output::logOutput( LOG_LEVEL_TRACE, ssOutput.str() ); \
	} while(0);
	#define LOG_DEBUG( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - DEBUG: " << logEvent; \
		Output::logOutput( LOG_LEVEL_DEBUG, ssOutput.str() ); \
	} while(0);
	#define LOG_WARN( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - WARN: " << logEvent; \
		Output::logOutput( LOG_LEVEL_WARN, ssOutput.str() ); \
	} while(0);
	#define LOG_ERROR( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - ERROR: " << logEvent; \
		Output::logOutput( LOG_LEVEL_ERROR, ssOutput.str() ); \
	} while(0);
	#define LOG_FATAL( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - FATAL: " << logEvent; \
		Output::logOutput( LOG_LEVEL_FATAL, ssOutput.str() ); \
	} while(0);
 
}

#endif