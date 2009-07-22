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

	void CSV::record( const IBafRecord* record )
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

		std::string delim = ",";
		itr = _recordProperties.find( "delimeter" );
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

			if( !record->hasField( *itr ) ) continue; // Skip fields the record does not have

			// Find field in record (if it exists)
			const IField* field = record->getField( *itr );

			if( !field ) 
			{
				LOG_WARN( "Failed to retreive field " << *itr << " from record for CSV output" );
				continue;
			}
			if( field->filter() ) continue;

			_file << field->getString() << delim;
		}
				
		// I thought about trimming off the last delim but its not that big of a deal imo
		// There is no way to trim of a character once its written to fstream so if you really want to
		// get rid of that extra delim write all fields to a string then trim the string and THEN write the string to 
		// _file.

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
}