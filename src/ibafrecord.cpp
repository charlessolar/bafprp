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
#include "crc32.h"

namespace bafprp
{

	IBafRecord::IBafRecord( const BYTE* data, int length, long filePos ) : _length( length ), _filePos( filePos )
	{
		LOG_TRACE( "IBafRecord::IBafRecord" );
		_data = data;
		_fieldData = _data;

		// Module flag is 4 for some reason, and no its not the number of modules
		_modules = ( ( *data & 0xF0 ) >> 4 == 0x04 );

		CRC32::Encode( _fieldData, length, _crc );

		LOG_TRACE( "/IBafRecord::IBafRecord" );
	}


	IBafRecord::~IBafRecord()
	{
		LOG_TRACE( "IBafRecord::~IBafRecord" );
		for( field_vector::iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
			delete (*itr);

		//delete[] _data;
		LOG_TRACE( "/IBafRecord::~IBafRecord" );
	}


	IBafRecord* RecordMaker::newRecord( const BYTE* data, int length, long filePos )
	{
		LOG_TRACE( "IBafRecord::newRecord" );
		// This function will take the full record data, extract the structure type, and create a new
		// record object from that type

		data += 2; // ignore the length
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
		// We should now be standing on the structure type field and the module flag

		IField* structuretype = FieldMaker::newField( "structuretype" );
		if( !structuretype->convert( data ) )
		{
			LOG_ERROR( "Could not convert structure type" );
			return NULL;
		}
		int type = structuretype->getInt();
		delete structuretype;
		
		maker_map::iterator itr = getReg().find ( type );
		if ( itr != getReg().end() )
			return itr->second->make( data, length, filePos );


		LOG_ERROR( "Could not find record of type \"" << type << "\"" );
		LOG_TRACE( "/IBafRecord::newRecord" );
		return NULL;
	}

	const IField* IBafRecord::getField( const std::string name ) const
	{
		LOG_TRACE( "IBafRecord::getField" );
		if( _fields.empty() ) return NULL;

		for( field_vector::const_iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
		{
			if( (*itr)->getName() == name )
				return *itr;
		}
		
		LOG_WARN( "Did not find field named: " << name );
		LOG_TRACE( "/IBafRecord::getField" );
		return NULL;
	}

	const IField* IBafRecord::getNextField( DWORD lastUID ) const
	{
		LOG_TRACE( "IBafRecord::getNextField" );
		if( _fields.empty() ) return NULL;

		for( field_vector::const_iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
		{
			if( (*itr)->getUID() == lastUID )
				if( ( itr + 1 ) != _fields.end() )
					return *(++itr);
				else
					return NULL;  // end of the road
		}

		// last not found, assume they sent 0 meaning start at begining
		LOG_TRACE( "/IBafRecord::getNextField" );
		return *_fields.begin();
	}

	void IBafRecord::addField( const std::string name )
	{
		LOG_TRACE( "IBafRecord::addField" );
		IField* field = FieldMaker::newField( name );
		if( !field )
		{
			LOG_ERROR( "Could not find field name '" << name << ".'  We will continue processing this record, but the record will be corrupt" );
			_fieldData += 4;  // aprox avg length of a field
			return;
		}
		if( !field->convert( _fieldData ) )
		{
			ERROR_OUTPUT( this, "Could not convert field '" << field->getName() << "' of type '" << field->getType() << "' and size '" << field->getSize() << "'. ERROR: '" << field->getError() << "'" );
		}
		// update data position, the mod is to make the size even for nice division
		_fieldData += ( field->getSize() + ( field->getSize() % 2 ) ) / 2;
		_fields.push_back( field );
		
		if( ( _fieldData - _data ) > _length ) // overstepping our bounds here, not a good place to be
		{
			LOG_ERROR( "Record has outgrown its stated length of " << _length << ". It is now " << ( _fieldData - _data ) );
		}

		LOG_TRACE( "/IBafRecord::addField" );
	}


	// Modules are extra fields attached to the record.  Therefore we will use a giant switch
	void IBafRecord::decodeModules()
	{
		if( !_modules ) return;
		LOG_TRACE( "IBafRecord::decodeModules" );

		int count = 0;
		// Just to be safe
		while( count < 20 )
		{
			count++;

			addField( "modulenumber" );
		
			// Will be the mudule number
			switch( _fields.back()->getInt() )
			{
			case 0:
				// All done here
				return;
			case 21:
				addField( "icincindicator" );
				addField( "carrierconnectdate" );
				addField( "carrierconnecttime" );
				addField( "carrierelapsedtime" );
				addField( "icinccalleventstatus" );
				addField( "trunkgroupnumber" );
				addField( "icincroutingindicator" );
				addField( "dialingpresubindicator" );
				addField( "anicpnindicator" );
				break;
			case 22:
				addField( "presentdate" );
				addField( "presenttime" );
				break;
			case 25:
				addField( "date" );
				addField( "time" );
				break;
			case 27:
				addField( "businessid" );
				break;
			case 29:
				addField( "altbillnumber" );
				break;
			case 30:
				addField( "contextid" );
				addField( "transsetfield" );
				break;
			case 40:
				addField( "digitsid" );
				addField( "significantdigits" );
				addField( "digits" );
				addField( "digitslong" );
				break;
			case 49:
				addField( "callcountnameonly" );
				addField( "callcountnumonly" );
				break;
			case 68:
				addField( "calleddndescription" );
				break;
			case 70:
				addField( "bearercaps" );
				addField( "networkinterworking" );
				addField( "sigsuppservusage" );
				addField( "releasecauseind" );
				break;
			case 71:
				addField( "bearercaps" );
				addField( "networkinterworking" );
				addField( "releasecauseindicator" );
				break;
			case 74:
				addField( "bbg" );
				addField( "chargeablenpa" );
				addField( "chargeableepn" );
				addField( "trunkgroupnumber" );
				break;
			case 102:
				addField( "significantdigits" );
				addField( "number" );
				break;
			case 103:
				addField( "significantdigits" );
				addField( "number" );
				break;
			case 104:
				addField( "trunkidentification" );
				break;
			case 109:
				addField( "classfeaturecode" );
				addField( "classfunctions" );
				addField( "screenlistsizegen" );
				break;
			case 119:
				addField( "trunkgroupinfo" );
				addField( "carrierinterface" );
				addField( "networkidentifier" );
				break;
			case 164:
				addField( "numberidentity" );
				addField( "countrycode" );
				addField( "significantdigits" );
				addField( "number" );
				break;
			case 203:
				addField( "contextid" );
				addField( "servproviderid" );
				addField( "amasequencenumber" );
				break;
			case 204:
				addField( "indicatorid" );
				break;
			case 306:
				addField( "callinglineinfo" );
				break;
			case 307:
				addField( "linenumbertype" );
				addField( "linenumber" );
				break;
			case 611:
				addField( "genericcontextid" );
				addField( "number" );
				break;
			case 719:
				addField( "partyid" );
				addField( "lrn" );
				addField( "supportinginfo" );
				break;
			case 720:
				addField( "partyid" );
				addField( "lrn" );
				addField( "serviceproviderid" );
				addField( "location" );
				addField( "supportinginfo" );
				break;
			default:
				LOG_ERROR( "Unknown modules id: " << _fields.back()->getInt() << " at " << _filePos << "." << (DWORD)( _fieldData - _data ) << " record type " << getType() );
			}
		}

		LOG_TRACE( "/IBafRecord::decodeModules" );
	}

}