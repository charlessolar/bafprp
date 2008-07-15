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

#include <stdio.h>
#include <memory.h>

#include "ibafrecord.h"
#include "output.h"

namespace bafprp
{

	IBafRecord::IBafRecord( const BYTE* data, int length ) : _length( length )
	{
		LOG_TRACE( "IBafRecord::IBafRecord" );
		_data = new BYTE[ _length + 1 ];
		memcpy_s( _data, _length, data, _length );

		//for( int i = 0; i < _length; i++ )
		//{
		//	printf( " %X ", _data[i] );
		//}
		//printf( "\n" );

		LOG_TRACE( "/IBafRecord::IBafRecord" );
	}


	IBafRecord::~IBafRecord()
	{
		LOG_TRACE( "IBafRecord::~IBafRecord" );
		delete[] _data;

		for( field_vector::iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
			delete (*itr);

		LOG_TRACE( "/IBafRecord::~IBafRecord" );
	}


	IBafRecord* RecordMaker::newRecord( const BYTE* data, int length )
	{
		// This function will take the full record data, extract the structure type, and create a new
		// record object from that type
		if( *data == 0x0 )
		{
			data += 2;  // Record is usually prefixed by x0000
			length -= 2;
		}
		if( *data != 0xAA ) 
		{
			// No matter what AA always starts a valid record
			LOG_WARN( "Record did not have 0xAA prefix, or we failed to find it" );
			return NULL; 
		}
		data++;
		length -= 1;
		// We should no be standing on the structure type field
		IFieldConverter* structuretype = FieldMaker::newFieldConverter( "structuretype" );
		if( !structuretype->convert( data ) )
		{
			LOG_ERROR( "Could not convert structure type" );
			return NULL;
		}
		int type = structuretype->getInt();
		delete structuretype;
		
		maker_map::iterator itr = getReg().find ( type );
		if ( itr != getReg().end() )
			return itr->second->make( data, length );

		LOG_ERROR( "Could not find record of type \"" << type << "\"" );
		return NULL;
	}

	IFieldConverter* IBafRecord::getField( const std::string name )
	{
		if( _fields.empty() ) return NULL;

		for( field_vector::iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
		{
			if( (*itr)->getName() == name )
				return *itr;
		}
		
		LOG_WARN( "Did not find field named: " << name );
		return NULL;
	}

	IFieldConverter* IBafRecord::getNextField( const std::string last )
	{
		if( _fields.empty() ) return NULL;

		for( field_vector::iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
		{
			if( (*itr)->getName() == last )
				if( ( itr + 1 ) != _fields.end() )
					return *(++itr);
				else
					return NULL;  // end of the road
		}

		// last not found, assume they sent "" meaning start at begining
		return *_fields.begin();
	}

}