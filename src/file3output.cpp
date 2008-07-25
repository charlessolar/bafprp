/*
Copyright (C) 2008 by Charles Solar
charlessolar@gmail.com

This File3 is part of bafprp.

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

#include "File3output.h"

#include <iomanip>
#include <ios>
#include <stdio.h>

namespace bafprp
{
	const File3 File3::registerThis;

	File3::File3() : Output( "file3" )
	{
		// Not sure if its a good idea to lock a File3 for the duration of the program,
		// but I cannot find a way to unlock the File3.
		if( fopen_s( &_fp, "bafprp3.log", "w" ) != 0 )
		{
			Output::setOutputLog( "console" );
			LOG_ERROR( "Could not open log File3, falling back to console log" );
		}
	}

	File3::~File3()
	{
		if( _fp ) fclose( _fp );
	}

	// Best to avert your eyes.
	void File3::error( const IBafRecord* record, const std::string error )
	{
		if( !_fp )
		{
			Output::setOutputLog( "console" );
			LOG_ERROR( "File3 pointer no longer valid, falling back to console output" );
		}
		LOG_TRACE( "File3::error" );

		fprintf_s( _fp, "* Record Error *********************************************\n" );
		fprintf_s( _fp, "*                                                          *\n" );
		fprintf_s( _fp, "*    %s                             *\n", NowTime().c_str() );

		std::ostringstream os;
		os.setf( std::ios::left );

		fprintf_s( _fp, "*                                                          *\n" );

		std::string rest = "";
		int space = 0;

		space = error.substr( 0, 48 ).find_last_of( " " );
		if( space == std::string::npos )
				space = 48;

		os << "* Report: " << std::setw( 48 ) << error.substr( 0, space ) << " *" << std::endl;
		fprintf_s( _fp, os.str().c_str() );
		os.str("");

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
			fprintf_s( _fp, os.str().c_str() );
			os.str("");

			if( rest.length() > 49 )	
				rest = rest.substr( space + 1 );
			else
				rest = "";
		}

		fprintf_s( _fp, "*                                                          *\n" );
		os << "* Details: Type: " << std::setw(41) << record->getType() << " *" << std::endl;
		fprintf_s( _fp, os.str().c_str() );
		os.str("");
		os << "*          Length: " << std::setw(39) << record->getSize() << " *" << std::endl;
		fprintf_s( _fp, os.str().c_str() );
		os.str("");
		os << "*          Position: " << std::setw(37) << record->getFilePosition() << " *" << std::endl;	
		fprintf_s( _fp, os.str().c_str() );
		os.str("");

		fprintf_s( _fp, "*                                                          *\n" );
		std::string bytes = record->getData();
		os << "* BYTES: " << std::setw(49) << bytes.substr( 0, 48 ) << " *" << std::endl;
		fprintf_s( _fp, os.str().c_str() );
		os.str("");

		const IField* structtype = record->getField( "structuretype" );
		if( structtype ) os << "*          Structure Type: " << std::setw(30) << structtype->getString() << " *" << std::endl;
		fprintf_s( _fp, os.str().c_str() );
		os.str("");

		rest = "";

		if( bytes.length() > 48 )
			rest = bytes.substr( 48 );
		
		while( rest != "" )
		{
			os << "*        " << std::setw(49) << rest.substr( 0, 48 ) << " *" << std::endl;
			fprintf_s( _fp, os.str().c_str() );
			os.str("");

			if( rest.length() > 48 )
				rest = rest.substr( 48 );
			else
				rest = "";
		}
		fprintf_s( _fp, "*                                                          *\n" );
		fprintf_s( _fp, "************************************************************\n" );
	
		LOG_TRACE( "/File3::error" );
	}

	void File3::log( const std::string log )
	{
		if( !_fp )
		{
			Output::setOutputLog( "console" );
			LOG_ERROR( "File3 pointer no longer valid, falling back to console output" );
		}
		fprintf_s( _fp, "%s\n", log.c_str() );
	}

	void File3::record( const IBafRecord* record )
	{
		if( !_fp )
		{
			Output::setOutputLog( "console" );
			LOG_ERROR( "File3 pointer no longer valid, falling back to console output" );
		}
		LOG_TRACE( "File3::record" );

		const IField* field;
		DWORD lastUID = 0;
		
		fprintf_s( _fp, "---------------------------------------\n" );
		fprintf_s( _fp, "%s\n", record->getType().c_str() );
		fprintf_s( _fp, "---------------------------------------\n" );
		fprintf_s( _fp, "Length of record: %d, CRC32: %u\n", record->getSize(), record->getCRC() );
		fprintf_s( _fp, "---------------------------------------\n" );

		// sending a last name of "" effectively returns us the begining, getting the ball rolling.
		while( ( field = record->getNextField( lastUID ) ) != NULL )
		{
			lastUID = field->getUID();
			fprintf_s( _fp, "%s: %s\n", field->getName().c_str(), field->getString().c_str() );
		}

		fprintf_s( _fp, "\n" );

		LOG_TRACE( "/File3::record" );
	}
}