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

#include <iomanip>
#include <ios>


namespace bafprp
{
	const File File::registerThis;

	File::File() : Output( "file" )
	{
		//_file.setf( std::ios::left );
	}

	File::~File()
	{
		if( _file.is_open() ) _file.close();
	}

	// Best to avert your eyes.
	void File::error( const IBafRecord* record, const std::string error )
	{
		LOG_TRACE( "File::error" );
		checkFile( _errorProperties );

		_file << "* Record Error *********************************************" << std::endl;
		_file << "*                                                          *" << std::endl;
		_file << "*    " << std::setw(28) << NowTime << " *" << std::endl;

		_file << "*                                                          *" << std::endl;

		std::string rest = "";
		int space = 0;

		space = error.substr( 0, 48 ).find_last_of( " " );
		if( space == std::string::npos )
				space = 48;

		_file << "* Report: " << std::setw( 48 ) << error.substr( 0, space ) << " *" << std::endl;
		
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
			

			_file << "*         " << std::setw( 48 ) << rest.substr( 0, space ) << " *" << std::endl;
			
			if( rest.length() > 49 )	
				rest = rest.substr( space + 1 );
			else
				rest = "";
		}

		_file << "*                                                          *" << std::endl;
		_file << "* Details: Type: " << std::setw(41) << record->getType() << " *" << std::endl;
		_file << "*          Length: " << std::setw(39) << record->getSize() << " *" << std::endl;
		_file << "*          Position: " << std::setw(37) << record->getFilePosition() << " *" << std::endl;	

		const IField* structtype = record->getField( "structuretype" );
		if( structtype ) 
			_file << "*          Structure Type: " << std::setw(30) << structtype->getString() << " *" << std::endl;
		else
			_file << "*          Structure Type: " << std::setw(30) << "Unknown" << " *" << std::endl;

		_file << "*                                                          *" << std::endl;
		std::string bytes = record->getData();
		_file << "* BYTES: " << std::setw(49) << bytes.substr( 0, 48 ) << " *" << std::endl;

		rest = "";

		if( bytes.length() > 48 )
			rest = bytes.substr( 48 );
		
		while( rest != "" )
		{
			_file << "*        " << std::setw(49) << rest.substr( 0, 48 ) << " *" << std::endl;

			if( rest.length() > 48 )
				rest = rest.substr( 48 );
			else
				rest = "";
		}
		_file << "*                                                          *" << std::endl;
		_file << "************************************************************" << std::endl;

		_file.flush();
	
		LOG_TRACE( "/File::error" );
	}

	void File::log( const std::string log )
	{
		checkFile( _logProperties );
		_file << log << std::endl;
		_file.flush();
	}

	void File::record( const IBafRecord* record )
	{
		LOG_TRACE( "File::record" );
		checkFile( _recordProperties );

		const IField* field;
		DWORD lastUID = 0;
		
		_file << "---------------------------------------" << std::endl;
		_file << record->getType() << std::endl;
		_file << "---------------------------------------" << std::endl;
		_file << "Length of record: " << record->getSize() << ", CRC32: " << record->getCRC() << std::endl;
		_file << "---------------------------------------" << std::endl;

		// sending a last name of "" effectively returns us the begining, getting the ball rolling.
		while( ( field = record->getNextField( lastUID ) ) != NULL )
		{
			lastUID = field->getUID();
			_file << field->getName() << ": " << field->getString() << std::endl;
		}

		_file << std::endl;
		_file.flush();

		LOG_TRACE( "/File::record" );
	}

	void File::checkFile( property_map props )
	{
		property_map::iterator filename = props.find( "filename" );
		if( filename != props.end() )
		{
			if( _filename != filename->second )
			{
				if( _file.is_open() ) _file.close();
				_file.open( filename->second.c_str() );
				if( _file.is_open() ) 
					_filename = filename->second;
				else
				{
					Output::setOutputLog( "console" );
					LOG_ERROR( "Could not open " << filename->second << " for output" );
					return;
				}
			}
		}
		
		if( !_file.is_open() )
		{
			if( _filename != "bafprp.log" )
			{
				if( _file.is_open() ) _file.close();
				_file.open( "bafprp.log" );
				if( _file.is_open() )
					_filename = "bafprp.log";
				else
				{
					Output::setOutputLog( "console" );
					LOG_ERROR( "Could not open bafprp.log for output" );
					return;
				}
			}
		}
	}
}