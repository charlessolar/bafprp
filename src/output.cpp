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
	std::string Output::_recordoutput;
	std::string Output::_erroroutput;
	std::string Output::_logoutput;
	LOG_LEVEL Output::_level;

	Output::Output( const std::string name )
	{
		getReg().insert( std::make_pair( name, this ) );
	}

	Output::~Output()
	{
	}

	void Output::recordOutput( BafRecord* record )
	{
		LOG_TRACE( "Output::recordOutput" );
		output_map::iterator itr = getReg().find( _recordoutput );
		if( itr != getReg().end() )
			itr->second->record( record );
		else
			LOG_ERROR( "Output type " << _recordoutput << " does not exist." );
		LOG_TRACE( "/Output::recordOutput" );
	}

	void Output::errorOutput( BafRecord* record, const std::string error )
	{
		LOG_TRACE( "Output::errorOutput" );
		output_map::iterator itr = getReg().find( _erroroutput );
		if( itr != getReg().end() )
			itr->second->error( record, error );
		else
			LOG_ERROR( "Output type " << _erroroutput << " does not exist." );
		LOG_TRACE( "/Output::errorOutput" );
	}

	void Output::logOutput( LOG_LEVEL level, const std::string log )
	{
		if( level < _level ) return;

		output_map::iterator itr = getReg().find( _logoutput );
		if( itr != getReg().end() )
			itr->second->log( log );
		else
			getReg().begin()->second->log( "Output type " + _logoutput + " does not exist." );		// If output is set wrong, use one that works.
																								// there should always be at least one form of output
																								// unfortunently we do not know which one thanks to static init.
	}

	std::string NowTime()
	{  
		char timestamp[100];
		time_t ltime; 
		struct tm* mytm = NULL;
		ltime = time(NULL);  
		mytm=localtime( &ltime );  
		strftime( timestamp, sizeof( timestamp ), "%a, %d %b %Y %H:%M:%S", mytm );
		return std::string( timestamp );  
	}  
}