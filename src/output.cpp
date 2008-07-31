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

#include "output.h"

namespace bafprp
{
	std::string Output::_outputRecord;
	std::string Output::_outputError;
	std::string Output::_outputLog;
	Output::property_map Output::_errorProperties;
	Output::property_map Output::_recordProperties;
	Output::property_map Output::_logProperties;
	LOG_LEVEL Output::_level;

	Output::Output( const std::string name )
	{
		getReg().insert( std::make_pair( name, this ) );
	}

	Output::~Output()
	{
	}

	void Output::outputRecord( const IBafRecord* record )
	{
		LOG_TRACE( "Output::outputRecord" );
		output_map::iterator itr = getReg().find( _outputRecord );
		if( itr != getReg().end() )
			itr->second->record( record );
		else
			LOG_ERROR( "Output type " << _outputRecord << " does not exist." );
		LOG_TRACE( "/Output::outputRecord" );
	}

	void Output::outputError( const IBafRecord* record, const std::string error )
	{
		LOG_TRACE( "Output::outputError" );
		output_map::iterator itr = getReg().find( _outputError );
		if( itr != getReg().end() )
			itr->second->error( record, error );
		else
			LOG_ERROR( "Output type " << _outputError << " does not exist." );
		LOG_TRACE( "/Output::outputError" );
	}

	void Output::outputLog( LOG_LEVEL level, const std::string log )
	{
		if( _level < level ) return;

		output_map::iterator itr = getReg().find( _outputLog );
		if( itr != getReg().end() )
			itr->second->log( level, log );
		else
		{
			Output::setOutputLog( "file" );
			LOG_ERROR( "Output type " + _outputLog + " does not exist." );		// If output is set wrong, use one that works.
		}
																								
	}

	void Output::setLogLevel( int level )
	{
		switch( level )
		{
		default:
		case 0:
			_level = LOG_LEVEL_FATAL;
			break;
		case 1:
			_level = LOG_LEVEL_ERROR;
			break;
		case 2:
			_level = LOG_LEVEL_WARN;
			break;
		case 3:
			_level = LOG_LEVEL_INFO;
			break;
		case 4:
			_level = LOG_LEVEL_DEBUG;
			break;
		case 5:
			_level = LOG_LEVEL_TRACE;
			break;
		}
	}

	std::string Output::getStrLogLevel( LOG_LEVEL level )
	{
		switch( level )
		{
		case 0:
			return "FATAL";
		case 1:
			return "ERROR";
		case 2:
			return "WARN";
		case 3:
			return "INFO";
		case 4:
			return "DEBUG";
		case 5:
			return "TRACE";
		default:
			return "UNKNOWN";
		}
	}

	void Output::setErrorProperty( const std::string name, const std::string value )
	{
		property_map::iterator itr = _errorProperties.find( name );
		if( itr != _errorProperties.end() )
			itr->second = value;
		else
			_errorProperties.insert( std::make_pair( name, value ) );
	}

	void Output::setRecordProperty( const std::string name, const std::string value )
	{
		property_map::iterator itr = _recordProperties.find( name );
		if( itr != _recordProperties.end() )
			itr->second = value;
		else
			_recordProperties.insert( std::make_pair( name, value ) );
	}

	void Output::setLogProperty( const std::string name, const std::string value )
	{
		property_map::iterator itr = _logProperties.find( name );
		if( itr != _logProperties.end() )
			itr->second = value;
		else
			_logProperties.insert( std::make_pair( name, value ) );
	}

	void Output::setOutputRecord( const std::string name )
	{
		output_map::iterator itr = getReg().find( name );
		if( itr != getReg().end() )
			_outputRecord = name;
		else
			printf( "Output type %s does not exist\n", name.c_str() );
	}

	void Output::setOutputError( const std::string name )
	{
		output_map::iterator itr = getReg().find( name );
		if( itr != getReg().end() )
			_outputError = name;
		else
			printf( "Output type %s does not exist\n", name.c_str() );
	}

	void Output::setOutputLog( const std::string name )
	{
		output_map::iterator itr = getReg().find( name );
		if( itr != getReg().end() )
			_outputLog = name;
		else
			printf( "Output type %s does not exist\n", name.c_str() );
	}

	std::string NowTime()
	{  
		char timestamp[100] = "";
		time_t ltime; 
		struct tm mytm;
		ltime = time( NULL );  
		localtime_s( &mytm, &ltime );  
		strftime( timestamp, sizeof( timestamp ), "%m/%d/%y %H:%M:%S", &mytm );
		return std::string( timestamp );  
	}  

	
}