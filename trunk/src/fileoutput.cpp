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

#include "fileoutput.h"

#include <stdio.h>

namespace bafprp
{
	const File File::registerThis;

	File::File() : Output( "file" )
	{
		// Not sure if its a good idea to lock a file for the duration of the program,
		// but I cannot find a way to unlock the file.
		if( fopen_s( &_fp, "bafprp.log", "a" ) != 0 )
		{
			Output::setLogOutput( "console" );
			LOG_ERROR( "Could not open log file, falling back to console log" );
		}
	}

	File::~File()
	{
		if( _fp ) fclose( _fp );
	}

	void File::error( IBafRecord* record, const std::string error )
	{
		if( !_fp )
		{
			Output::setLogOutput( "console" );
			LOG_ERROR( "File pointer no longer valid, falling back to console output" );
		}

		LOG_TRACE( "File::error" );
		LOG_TRACE( "/File::error" );
	}

	void File::log( const std::string log )
	{
		if( !_fp )
		{
			Output::setLogOutput( "console" );
			LOG_ERROR( "File pointer no longer valid, falling back to console output" );
		}
		fwrite( log.c_str(), 1, log.length(), _fp );
	}

	void File::record( IBafRecord* record )
	{
		if( !_fp )
		{
			Output::setLogOutput( "console" );
			LOG_ERROR( "File pointer no longer valid, falling back to console output" );
		}
		LOG_TRACE( "File::record" );

		IField* field;
		std::string value = "";
		std::string name = "";
		std::string output = "";

		// sending a last name of "" effectively returns us the begining, getting the ball rolling.
		while( ( field = record->getNextField( name ) ) != NULL )
		{
			value = field->getString();
			name = field->getName();
			output = name + ": " + value + "\n";
			fwrite( output.c_str(), 1, output.length(), _fp );
		}

		LOG_TRACE( "/File::record" );
	}
}