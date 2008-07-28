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

#include <iomanip>
#include <ios>

#include "fileoutput.h"
#include "baffile.h"


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
		checkFile( _errorProperties, true );

		_file.setf( std::ios::left );

		_file << "* Record Error *********************************************" << std::endl;
		_file << "*                                                          *" << std::endl;
		_file << "*    " << std::setw(53) << NowTime() << " *" << std::endl;

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
		_file << "*          Filename: " << std::setw(37) << BafFile::getFilename() << " *" << std::endl;

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
	
		checkFile( _errorProperties, false );
		LOG_TRACE( "/File::error" );
	}

	void File::log( const std::string log )
	{
		checkFile( _logProperties, true );
		_file << log << std::endl;
		_file.flush();
		checkFile( _logProperties, false );
	}

	void File::record( const IBafRecord* record )
	{
		LOG_TRACE( "File::record" );
		checkFile( _recordProperties, true );

		const IField* field;
		DWORD lastUID = 0;
		
		_file << "--------------------------------------------------------------------------" << std::endl;
		_file << record->getType() << std::endl;
		_file << "--------------------------------------------------------------------------" << std::endl;
		_file << "Length of record: " << record->getSize() << ", CRC32: " << record->getCRC() << std::endl;
		_file << "--------------------------------------------------------------------------" << std::endl;
		_file << "File: " << BafFile::getFilename() << std::endl;
		_file << "--------------------------------------------------------------------------" << std::endl;
		_file << "Position: " << record->getFilePosition() << std::endl;
		_file << "--------------------------------------------------------------------------" << std::endl;

		// sending a last name of "" effectively returns us the begining, getting the ball rolling.
		while( ( field = record->getNextField( lastUID ) ) != NULL )
		{
			lastUID = field->getUID();
			_file << field->getName() << ": " << field->getString() << std::endl;
		}

		_file << std::endl;
		_file.flush();

		checkFile( _recordProperties, false );
		LOG_TRACE( "/File::record" );
	}


	// This function is in dire need of some cleaning...
	void File::checkFile( property_map& props, bool start )
	{
		// We must use printf here because if log output is set to file we could get outselves
		// into a nice infinite loop here.


		property_map::iterator filename = props.find( "filename" );
		// add check for filename == props.end()

		if( start )
		{
			if( _file.is_open() )
			{
				if( _filename != filename->second )
				{
					_storedFilenames.push_back( _filename );
					_filename = "";
					_file.close();

					bool bFound = false;
					for( std::vector<std::string>::iterator itr = _usedFilenames.begin(); itr != _usedFilenames.end(); itr++ )
					{
						if( (*itr) == filename->second )
						{
							bFound = true;
							break;
						}
					}

					if( !bFound )
						_file.open( filename->second.c_str() );
					else
						_file.open( filename->second.c_str(), std::ios::app );

					// add checks to see if file is actually open

					_filename = filename->second;
					_usedFilenames.push_back( _filename );
				}
				// current open file matches desired file.
			}
			else // Need to open a new file for output
			{
				_file.open( filename->second.c_str() );

				// add file open check

				_filename = filename->second;
				_usedFilenames.push_back( _filename );
			}
		}
		else  // end of function file check
		{
			if( _storedFilenames.size() > 0 )  // we had to push off another file to output
			{
				// restore that file
				_file.close();
				_file.open( _storedFilenames.back().c_str(), std::ios::app );
				_filename = _storedFilenames.back();
				_storedFilenames.pop_back();
			}
		}
	}
}