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
#include "ibafrecord.h"

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


	/*
		The output class functions as a gateway to output implentations and an interface to those implementations.
		Subclasses of output must define the three types of program output, record, error, and log.  Record and error
		are both in regards to BafRecords which  are passed through the system.  
		Subclasses can output this data however they want, be it console, file, sql, xml, as long as its defined as a concrete class.
		To register a new type of output, the class needs to call the Output constructor with the name of the format
		for example see consoleoutput.h
		Each class also needs to self instantiate themselves so they exist.  They can do this by creating a static variable of 
		themselves.  Again see consoleoutput.h for an example.

		The output class keeps a static list of all registered outputs and the user can switch between then with setOutput.  
	*/

	class Output
	{
	protected:
		// For registering subclasses
		Output( const std::string name );
		
		// virtual methods for processing data
		virtual void record( IBafRecord* record ) = 0;
		virtual void error( IBafRecord* record, const std::string error ) = 0;
		virtual void log( const std::string log ) = 0;
	public:
		virtual ~Output();

		static void setLogLevel( LOG_LEVEL level ) { _level = level; }

		static void setRecordOutput( const std::string name ) { _recordoutput = name; }
		static void setErrorOutput( const std::string name ) { _erroroutput = name; }
		static void setLogOutput( const std::string name ) { _logoutput = name; }

		static void recordOutput( IBafRecord* record );
		static void errorOutput( IBafRecord* record, const std::string error );
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

		static std::string _recordoutput;
		static std::string _erroroutput;
		static std::string _logoutput;

	};
	
	std::string NowTime();


	// Macros for easier logging
	#define LOG_TRACE( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - TRACE: " << logEvent << "\n"; \
		Output::logOutput( LOG_LEVEL_TRACE, ssOutput.str() ); \
	} while(0);
	#define LOG_DEBUG( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - DEBUG: " << logEvent << "\n"; \
		Output::logOutput( LOG_LEVEL_DEBUG, ssOutput.str() ); \
	} while(0);
	#define LOG_WARN( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - WARN: " << logEvent << "\n"; \
		Output::logOutput( LOG_LEVEL_WARN, ssOutput.str() ); \
	} while(0);
	#define LOG_ERROR( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - ERROR: " << logEvent << "\n"; \
		Output::logOutput( LOG_LEVEL_ERROR, ssOutput.str() ); \
	} while(0);
	#define LOG_FATAL( logEvent ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - FATAL: " << logEvent << "\n"; \
		Output::logOutput( LOG_LEVEL_FATAL, ssOutput.str() ); \
	} while(0);
 
}

#endif