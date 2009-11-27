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

#include <vector>

#include "csvoutput.h"
#include "baffile.h"

namespace bafprp
{
	const CSV CSV::registerThis;

	CSV::~CSV()
	{
		if( _file.is_open() ) _file.close();
	}

	void CSV::error( const BafRecord* record, const std::string& error )
	{
		LOG_TRACE( "CSV::error" );
		checkFile( _errorProperties, true );
		if( !_file.is_open() )
		{
			LOG_ERROR( "No valid file for error output, falling back to console output" );
			Output::setOutputError( "console" );

			// be nice
			Output::outputError( record, error );
			return;
		}

		std::string delim = ";";
		property_map::iterator itr = _recordProperties.find( "delimiter" );
		if( itr != _recordProperties.end() )
			delim = itr->second;

		_file << NowTime() << delim << error << delim << record->getType() << delim << record->getSize() << delim << record->getFilePosition() << delim << record->getFilename() << delim << record->getData() << std::endl; 
		_file.flush();
	
		checkFile( _errorProperties, false );
		LOG_TRACE( "/CSV::error" );
	}

	void CSV::log( LOG_LEVEL level, const std::string& log )
	{
		checkFile( _logProperties, true );
		if( !_file.is_open() )
		{
			Output::setOutputLog( "console" );
			LOG_ERROR( "No valid file for log output, falling back to console output" );

			// be nice
			Output::outputLog( level, log );
			return;
		}

		std::string delim = ";";
		property_map::iterator itr = _recordProperties.find( "delimiter" );
		if( itr != _recordProperties.end() )
			delim = itr->second;

		_file << NowTime() << delim << getStrLogLevel( level ) << delim << log << std::endl;
		_file.flush();
		checkFile( _logProperties, false );
	}

	void CSV::record( const BafRecord* record )
	{
		LOG_TRACE( "CSV::record" );
		checkFile( _recordProperties, true );
		if( !_file.is_open() )
		{
			LOG_ERROR( "No valid file for record output, falling back to console output" );
			Output::setOutputRecord( "console" );

			// be nice
			Output::outputRecord( record );
			return;
		}

		// Pull the field property
		std::string fieldStr;
		property_map::iterator itr = _recordProperties.find( "fields" );
		if( itr != _recordProperties.end() )
			fieldStr = itr->second;
		else
		{
			LOG_ERROR( "No 'fields' property defined for CSV record output, falling back to file output" );
			Output::setOutputRecord( "file" );
			Output::outputRecord( record );
			return;
		}

		// Some people might want to push all fields into the csv file
		// this setup will only allow the user to output a fixed set
		// of fields.
		// Allowing all fields to be printed per line is no simple task.
		// Each record differs in the number of fields and the type of field
		// therefore if you want to print the entire record each line, each
		// line will end up different and there would be no defined columns 
		// in your output. :(

		std::string delim = ";";
		itr = _recordProperties.find( "delimiter" );
		if( itr != _recordProperties.end() )
			delim = itr->second;

		// For each element in field property, print the respective field
		std::vector<std::string> fields;
		StringExplode( fieldStr, ",", &fields );

		if( fields.size() <= 0 )
		{
			LOG_ERROR( "The 'fields' property for CSV output is invalid, falling back to file output" );
			Output::setOutputRecord( "file" );
			Output::outputRecord( record );
			return;
		}

		for( std::vector<std::string>::iterator itr = fields.begin(); itr != fields.end(); itr++ )
		{
			// Check for 'special' columns
			if( *itr == "filename" )
			{
				_file << record->getFilename() << delim;
				continue;
			}
			if( *itr == "filepos" )
			{
				_file << record->getFilePosition() << delim;
				continue;
			}
			if( *itr == "type" )
			{
				_file << record->getType() << delim;
				continue;
			}
			if( *itr == "size" )
			{
				_file << record->getSize() << delim;
				continue;
			}
			if( *itr == "crc" )
			{
				_file << record->getCRC() << delim;
				continue;
			}

			if( !record->hasField( *itr ) ) 
			{
				_file << delim;  // So the columns do not get misaligned just because 1 record was missing a field
				continue; // Skip fields the record does not have
			}

			// Find field in record (if it exists)
			const IField* field = record->getField( *itr );

			if( !field ) 
			{
				LOG_WARN( "Failed to retreive field " << *itr << " from record for CSV output" );
				continue;
			}
			if( field->filter() ) 
			{
				_file << delim;
				continue;
			}

			_file << field->getString() << delim;
		}

		// Trim off last delimiter
		_file.seekp( -1, std::ios_base::cur );
		_file << std::endl;
		_file.flush();

		checkFile( _recordProperties, false );
		LOG_TRACE( "/CSV::record" );
	}

	// http://www.infernodevelopment.com/perfect-c-string-explode-split
	void CSV::StringExplode( std::string str, const std::string& separator, std::vector<std::string>* results )
	{
    int found;
    found = str.find_first_of(separator);
		while(found != std::string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
	}

	void CSV::checkFile( property_map& props, bool start )
	{
		// The property should have a filename parameter
		property_map::iterator filename = props.find( "filename" );
		if( filename == props.end() )
		{
			printf( "Error: no 'filename' property for output\n" );
			return;	
		}

		// If the function is at the begining, we need to make sure the right file is open
		if( start )
		{
			if( _file.is_open() ) 
			{
				if( _filename != filename->second )  // Is the RIGHT file open?
				{
					// If not, we need to store the current file's name, and open the correct file
					_storedFilenames.push_back( _filename );
					_filename = "";
					_file.close();

					// If the filename we are opening has been used before we need to open it to APPEND, however
					// if it has NOT been used before, open it normally, wiping out the previous contents.
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
						_file.open( filename->second.c_str() );  // Clear original file
					else
						_file.open( filename->second.c_str(), std::ios::app );  // Append

					// does not matter if file opened or not, individual functions check and make better errors then
					// we could dream of making

					_filename = filename->second;
					_usedFilenames.push_back( _filename );  // Make sure we open it for APPENDING next time
				}
				// current open file matches desired file.
			}
			else // No file is open, need to open a new file for output
			{
				// Since there should ALWAYS been one file open, we can assume this is the first time this
				// file is being opened and not check for appending.
				// If you encounter a bug where your files are being cleared in the middle of the program,
				// you are probably doing some very weird things to your output, but if need be, we can copy 
				// the used file check here.
				_file.open( filename->second.c_str() );

				// does not matter if file opened or not, individual functions check and make better errors then
				// we could dream of making

				_filename = filename->second;
				_usedFilenames.push_back( _filename );  // Open for appending next time
			}
		}
		else  // end of function file check
		{
			// The function is ending, we need to restore the previous open file, if there was one.
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