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
		LOG_LEVEL_FATAL = 0,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_WARN,
		LOG_LEVEL_INFO,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_TRACE
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
		virtual void record( const IBafRecord* record ) = 0;
		virtual void error( const IBafRecord* record, const std::string error ) = 0;
		virtual void log( const std::string log ) = 0;
	public:
		virtual ~Output();

		static void setLogLevel( LOG_LEVEL level ) { _level = level; }
		static void setLogLevel( int level );
		static LOG_LEVEL getLogLevel() { return _level; }

		static void setOutputRecord( const std::string name ) { _outputRecord = name; }
		static void setOutputError( const std::string name ) { _outputError = name; }
		static void setOutputLog( const std::string name ) { _outputLog = name; }

		static void outputRecord( const IBafRecord* record );
		static void outputError( const IBafRecord* record, const std::string error );
		static void outputLog( LOG_LEVEL level, const std::string log );

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

		static std::string _outputRecord;
		static std::string _outputError;
		static std::string _outputLog;

	};
	
	std::string NowTime();


	// Macros for easier logging
	#define LOG_TRACE( logEvent ) \
	if( Output::getLogLevel() >= LOG_LEVEL_TRACE ) \
	{ \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - TRACE: " << logEvent; \
		Output::outputLog( LOG_LEVEL_TRACE, ssOutput.str() ); \
	}
	#define LOG_DEBUG( logEvent ) \
	if( Output::getLogLevel() >= LOG_LEVEL_DEBUG ) \
	{ \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - DEBUG: " << logEvent; \
		Output::outputLog( LOG_LEVEL_DEBUG, ssOutput.str() ); \
	} 
	#define LOG_INFO( logEvent ) \
	if( Output::getLogLevel() >= LOG_LEVEL_INFO ) \
	{ \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - INFO: " << logEvent; \
		Output::outputLog( LOG_LEVEL_INFO, ssOutput.str() ); \
	} 
	#define LOG_WARN( logEvent ) \
	if( Output::getLogLevel() >= LOG_LEVEL_WARN ) \
	{ \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - WARN: " << logEvent; \
		Output::outputLog( LOG_LEVEL_WARN, ssOutput.str() ); \
	}
	#define LOG_ERROR( logEvent ) \
	if( Output::getLogLevel() >= LOG_LEVEL_ERROR ) \
	{ \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - ERROR: " << logEvent; \
		Output::outputLog( LOG_LEVEL_ERROR, ssOutput.str() ); \
	}
	#define LOG_FATAL( logEvent ) \
	if( Output::getLogLevel() >= LOG_LEVEL_FATAL ) \
	{ \
		std::ostringstream ssOutput; \
		ssOutput << "- " << NowTime() << " - FATAL: " << logEvent; \
		Output::outputLog( LOG_LEVEL_FATAL, ssOutput.str() ); \
	} 
 
	#define ERROR_OUTPUT( record, error ) \
	do { \
		std::ostringstream ssOutput; \
		ssOutput << error; \
		Output::outputError( record, ssOutput.str() ); \
	} while(0);

}

#endif