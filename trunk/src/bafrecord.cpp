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

#include "bafrecord.h"
#include "crc32.h"
#include "output.h"

namespace bafprp
{
	RecordMaker::field_map RecordMaker::_recordFields;
	RecordMaker::property_map RecordMaker::_recordProps;

	BafRecord* RecordMaker::newRecord( const BYTE* data, int length, const std::string& filename, long filePos )
	{
		define_default_records();

		BafRecord* ret = new BafRecord( data, length, filename, filePos );
		if( !ret || ret->getTypeCode() == -1 )
			return NULL;

		field_map::const_iterator fields = _recordFields.find( ret->getTypeCode() );
		if( fields == _recordFields.end() )
		{
			LOG_ERROR( "Could not find record of type '" << ret->getTypeCode() << "'" );
			delete ret;
			return NULL;
		}

		if( fields->second.empty() )
		{
			LOG_ERROR( "Record type " << ret->getTypeCode() << " has no defined fields!" );
			delete ret;
			return NULL;
		}

		for( std::vector<std::string>::const_iterator itr = fields->second.begin(); itr != fields->second.end(); itr++ )
			ret->addField( *itr );
		ret->decodeModules();
		
		property_map::iterator props = _recordProps.find( ret->getTypeCode() );
		if( props != _recordProps.end() )
			ret->setProperties( props->second );

		return ret;		
	}

	void RecordMaker::setRecordField( int record, const std::string& fieldName )
	{
		field_map::iterator itr = _recordFields.find( record );
		if( itr == _recordFields.end() )
		{
			std::vector<std::string> temp;
			_recordFields.insert( std::make_pair( record, temp ) );
			itr = _recordFields.find( record );
			itr->second.push_back( fieldName );
		}
		else
			itr->second.push_back( fieldName );
	}

	void RecordMaker::setRecordProp( int record, const std::string& prop )
	{
		std::string object = prop.substr( 0, prop.find( ":" ) );
		std::string value = prop.substr( prop.find( ":" ) + 1 );
		property_map::iterator itr = _recordProps.find( record );
		if( itr != _recordProps.end() )
			itr->second.insert( std::make_pair( object, value ) );
		else
		{
			LOG_DEBUG( "First property for record " << record );
			std::multimap<std::string,std::string> temp;
			_recordProps.insert( std::make_pair( record, temp ) );
			itr = _recordProps.find( record );
			itr->second.insert( std::make_pair( object, value ) );
		}
	}

	BafRecord::BafRecord( const BYTE* data, int length, const std::string& filename, long filePos )
	{
		// Need to peel off the structure code type
		_type = -1;

		// If AMADNS header
		if( data[0] == 0x1C )
		{		
			_type = 0;
			data++;
		}
		else
		{
			int padding = 0;
			// Do some simple scanning to the start of the record
			while( *data != 0xAB && *data != 0xAA )
			{
				data++;
				length--;
				padding++;
			}

			LOG_DEBUG( "Found " << padding << " bytes of padding on the record" );
			if( padding > 4 )
				LOG_WARN( "Found " << padding << " bytes of padding on the record" );

			if( *data == 0xAB )
			{
				LOG_WARN( "This record has indicated that it contains errors" );
			}
			else if( *data != 0xAA ) 
			{
				// No matter what AA always starts a valid record
				LOG_WARN( "Record did not have 0xAA prefix, or we failed to find it" );
			}
			data++;
			length--;
			// We should now be standing on the structure type field

			IField* structurecode = FieldMaker::newField( "structurecode" );
			if( !structurecode ) 
			{
				LOG_FATAL( "Could not retrieve 'structurecode' field" );
				return;
			}
			if( !structurecode->convert( data ) )
			{
				LOG_FATAL( "Could not convert structure type" );
				delete structurecode;
				return;
			}
			_type = structurecode->getInt();
			delete structurecode;

			// Module flag is 4 for some reason, and no its not the number of modules
			_modules = ( ( *data & 0xF0 ) >> 4 == 0x04 );
		}

		_data = _fieldData = data;
		_filename = filename;
		_length = length;
		_filePos = filePos;
		_crc = 0;


		CRC32::Encode( _fieldData, _length, _crc );
	}

	BafRecord::~BafRecord()
	{
		for( field_vector::iterator itr = _fields.begin(); itr != _fields.end(); itr++ )
			delete *itr;
	}


	bool BafRecord::hasField( const std::string& name ) const
	{
		LOG_TRACE( "BafRecord::hasField" );
		if( _fields.empty() ) return false;

		bool bFound = false;
		for( field_type_vector::const_iterator itr = _field_types.begin(); itr != _field_types.end(); itr++ )
		{
			if( *itr == name )
			{
				bFound = true;
				break;
			}
		}

		LOG_TRACE( "/BafRecord::hasField" );
		return bFound;
	}


	const IField* BafRecord::getField( const std::string& name ) const
	{
		LOG_TRACE( "BafRecord::getField" );
		if( _fields.empty() ) 
		{
			LOG_WARN( "Tried to pull a field from a record with no fields" );
			return NULL;
		}

		// This is gross
		field_vector::const_iterator itr2 = _fields.begin();
		for( field_type_vector::const_iterator itr = _field_types.begin();
			itr != _field_types.end() && itr2 != _fields.end();
			itr++, itr2++ )
		{
			if( *itr == name )
				return *itr2;
		}
		
		LOG_WARN( "Did not find field named: " << name );
		LOG_TRACE( "/BafRecord::getField" );
		return NULL;
	}

	const IField* BafRecord::getNextField( DWORD lastUID ) const
	{
		LOG_TRACE( "BafRecord::getNextField" );
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
		LOG_TRACE( "/BafRecord::getNextField" );
		return *_fields.begin();
	}

	void BafRecord::addField( const std::string& field_type )
	{
		LOG_TRACE( "BafRecord::addField" );
		IField* field = FieldMaker::newField( field_type );
		if( !field )
		{
			LOG_ERROR( "Could not find field name '" << field_type << ".'  We will continue processing this record, but the record will be corrupt" );
			_fieldData += 4;  // aprox avg length of a field
			return;
		}
		if( *( _fieldData ) != 0xFF )  // If field is used, else data will be just FFFFFFFF
		{
			field->setID( field_type );
			if( !field->convert( _fieldData ) )
			{
				ERROR_OUTPUT( this, "Could not convert field '" << field->getID() << "' of type '" << field->getType() << "' and size '" << field->getSize() << "'. ERROR: '" << field->getError() << "'" );
			}
			_fields.push_back( field );
			_field_types.push_back( field_type );
			// update data position, the mod is to make the size even for nice division
			_fieldData += ( field->getSize() + ( field->getSize() % 2 ) ) / 2;
		}
		else
		{
			// update data position, the mod is to make the size even for nice division
			_fieldData += ( field->getSize() + ( field->getSize() % 2 ) ) / 2;
			delete field;
		}
		
				
		if( ( _fieldData - _data ) > _length ) // overstepping our bounds here, not a good place to be
		{
			LOG_ERROR( "Record has outgrown its stated length of " << _length << ". It is now " << ( _fieldData - _data ) );
		}

		LOG_TRACE( "/BafRecord::addField" );
	}

	void BafRecord::addModuleField( unsigned int module, const std::string& field_type )
	{
		LOG_TRACE( "BafRecord::addModuleField" );
		IField* field = FieldMaker::newField( field_type );
		if( !field )
		{
			LOG_ERROR( "Could not find field name '" << field_type << ".'  We will continue processing this record, but the record will be corrupt" );
			_fieldData += 4;  // aprox avg length of a field
			return;
		}
		if( *( _fieldData ) != 0xFF )  // If field is used, else data will be just FFFFFFFF
		{
			// This is a module field, so append the module number to the field name so names do not overlap
			std::ostringstream os;
			os << "m" << module << "." << field_type;

			// WHen 2 of the same modules are attached, names can conflict, so suffix conflicting names with an incrementing number
			int count = 0;
			bool found = false;
			do
			{
				found = false;
				for( field_type_vector::iterator itr = _field_types.begin(); itr != _field_types.end(); ++itr )
					if( (*itr) == os.str() )
					{
						found = true;
						os.str("");
						count++;
						os << "m" << module << "." << field_type << "." << count;
						break;
					}
			} while( found );

			field->setID( os.str() );

			if( !field->convert( _fieldData ) )
			{
				ERROR_OUTPUT( this, "Could not convert field '" << field->getID() << "' of type '" << field->getType() << "' and size '" << field->getSize() << "'. ERROR: '" << field->getError() << "'" );
			}
			_fields.push_back( field );
			
			_field_types.push_back( os.str() );
			// update data position, the mod is to make the size even for nice division
			_fieldData += ( field->getSize() + ( field->getSize() % 2 ) ) / 2;
		}
		else
		{
			// update data position, the mod is to make the size even for nice division
			_fieldData += ( field->getSize() + ( field->getSize() % 2 ) ) / 2;
			delete field;
		}
		if( ( _fieldData - _data ) > _length ) // overstepping our bounds here, not a good place to be
		{
			LOG_ERROR( "Record has outgrown its stated length of " << _length << ". It is now " << ( _fieldData - _data ) );
		}
		LOG_TRACE( "/BafRecord::addModuleField" );
	}

	std::string BafRecord::getType() const
	{
		// get type id field
		// match type id to description
		std::ostringstream os;

		const IField* field = getField( "calltype" );
		if( !field ) 
		{
			if( _type != 0 )
				LOG_ERROR( "No 'calltype' field in record " << _type );
			return "";
		}

		os << "Record " << _type << ": ";

		switch( field->getInt() )
		{
		case 1:
			os << "Detailed Message Rate, Timed, with Message Billing Index";
			break;
		case 2:
			os << "Message Rate, Timed, with MBI";
			break;
		case 3:
			os << "Detailed Message Rate, Untimed, with MBI";
			break;
		case 4:
			os << "Message Rate, Untimed, with MBI";
			break;
		case 5:
			os << "Local message rate call";
			break;
		case 6:
			os << "Toll call or non-US";
			break;
		case 9:
			os << "411 Directory Assistance";
			break;
		case 11:
			os << "Foreign Exchange, Automatic Flexible Routing";
			break;
		case 13:
			os << "Default release to Pivot";
			break;
		case 21:
			os << "Common Control Switching Arrangement Sampling";
			break;
		case 25:
			os << "Station Coin Zone";
			break;
		case 26:
			os << "Conference Trunk Usage";
			break;
		case 31:
			os << "Call Forwarding";
			break;
		case 32:
			os << "Tandem Tie Trunk";
			break;
		case 33:
			os << "555 Directory Assistance";
			break;
		case 34:
			os << "Signaling Irregularities";
			break;
		case 41:
			os << "Local Coin";
			break;
		case 42:
			os << "Time change marker";
			break;
		case 45:
			os << "ISDN User Service";
			break;
		case 47:
			os << "Default AIN";
			break;
		case 48:
			os << "Usage-Sensative Feature Call";
			break;
		case 49:
			os << "Usage-Sensative Feature-Activation Record";
			break;
		case 63:
			os << "Cellular Mobile Carrier Type-1 or -2B (Originating)";
			break;
		case 64:
			os << "Cellular Mobile Carrier Type-2A (Originating)";
			break;
		case 65:
			os << "Cellular Mobile Carrier Type-1 or -2B (Terminating)";
			break;
		case 66:
			os << "Cellular Mobile Carrier Type-2A (Terminating)";
			break;
		case 67:
			os << "Originating Study Record";
			break;
		case 74:
			os << "Free call";
			break;
		case 83:
			os << "Inward Call Extended to a Centrex Station";
			break;
		case 84:
			os << "Inward Call Extended to a Tie Trunk";
			break;
		case 88:
			os << "Non-Directory Assistance 555 Call";
			break;
		case 90:
			os << "Sensor Audit Record";
			break;
		case 98:
			os << "Collector Audit Record";
			break;
		case 99:
			os << "ETS Call Vis CCSA";
			break;
		case 110:
			os << "Interlata call";
			break;
		case 119:
			os << "Incoming CDR";
			break;
		case 126:
			os << "Originating Interconnection";
			break;
		case 127:
			os << "Transiting Interconnection";
			break;
		case 128:
			os << "Terminating Interconnection";
			break;
		case 132:
			os << "Feature Group A - Terminating";
			break;
		case 134:
			os << "Feature Group B Origination";
			break;
		case 141:
			os << "Interexchange Carrier Number Services";
			break;
		case 142:
			os << "LEC Number Services";
			break;
		case 159:
			os << "Message Detail Recording Data";
			break;
		case 160:
			os << "On-Network PVN Calls";
			break;
		case 161:
			os << "PVC On-Network IC Overflow Calls";
			break;
		case 162:
			os << "Off-Network PVN Call";
			break;
		case 163:
			os << "Off-Network PVN Overflow Calls";
			break;
		case 164:
			os << "PVN Call Using Feature Group A";
			break;
		case 165:
			os << "PVN Call Using Foreign Exchange";
			break;
		case 166:
			os << "PVN Call Using OUTWATS";
			break;
		case 167:
			os << "PVN Call Using Tie Trunk";
			break;
		case 184:
			os << "ISDN Terminating User Service Record";
			break;
		case 264:
			os << "Calling Identify Delivery Record";
			break;
		case 330:
			{
				const IField* featurecode = getField( "classfeaturecode" );
				if( !featurecode ) 
				{
					LOG_ERROR( "No 'classfeaturecode' field in record " << _type );
					os << "Unknown";
					break;
				}
				if( featurecode->getInt() == 1 || featurecode->getInt() == 2 || featurecode->getInt() == 3 )
					os << "CLASS feature: Outgoing Call Barring";
				else
					os << "CLASS feature: Anonymous call rejection";
				break;
			}
		case 331:
			os << "Bulk Calling Line Identification (BCLID)";
			break;
		case 381:
			os << "Inter-vendor Handoff Back";
			break;
		case 721:
			os << "Default Local Number Portability";
			break;
		case 900:
			os << "SIP Registration";
			break;
		case 9013:
			os << "File start marker";
			break;
		case 9014:
			os << "File end marker";
			break;
		default:
			os << "Unknown";
		}

		return os.str();
	}

	// Modules are extra fields attached to the record.  Therefore we will use a giant switch
	void BafRecord::decodeModules()
	{
		if( !_modules ) return;
		LOG_TRACE( "BafRecord::decodeModules" );

		int count = 0;
		// Just to be safe
		while( count < 20 )
		{
			count++;

			addField( "modulecode" );
		
			// Will be the mudule number
			LOG_DEBUG( "Decoding module number " << _fields.back()->getInt() );
			switch( _fields.back()->getInt() )
			{
			case 0:
				// All done here
				return;
			case 21:
				addModuleField( 21, "icincid" );
				addModuleField( 21, "carrierconnectdate" );
				addModuleField( 21, "carrierconnecttime" );
				addModuleField( 21, "carrierelapsedtime" );
				addModuleField( 21, "icinccalleventstatus" );
				addModuleField( 21, "trunkgroupnumber" );
				addModuleField( 21, "icincrouting" );
				addModuleField( 21, "dialingpresubind" );
				addModuleField( 21, "anicpnindicator" );
				break;
			case 22:
				addModuleField( 22, "presentdate" );
				addModuleField( 22, "presenttime" );
				break;
			case 25:
				addModuleField( 25, "date" );
				addModuleField( 25, "time" );
				break;
			case 27:
				addModuleField( 27, "businessid" );
				break;
			case 29:
				addModuleField( 29, "altbillnumber" );
				break;
			case 30:
				addModuleField( 30, "contextid" );
				addModuleField( 30, "transsetfield" );
				break;
			case 40:
				addModuleField( 40, "digitsid" );
				addModuleField( 40, "sigdigs" );
				addModuleField( 40, "digitsdialed1" );
				addModuleField( 40, "digitsdialed2" );
				break;
			case 42:
				addModuleField( 42, "recordcount" );
				break;
			case 49:
				addModuleField( 49, "callcountnameonly" );
				addModuleField( 49, "callcountnumonly" );
				break;
			case 50:
				addModuleField( 50, "chargeableopholding" );
				break;
			case 68:
				addModuleField( 68, "calleddndescription" );
				break;
			case 70:
				addModuleField( 70, "bearercaps" );
				addModuleField( 70, "networkinterworking" );
				addModuleField( 70, "sigsuppservusage" );
				addModuleField( 70, "releasecauseind" );
				break;
			case 71:
				addModuleField( 71, "bearercaps" );
				addModuleField( 71, "networkinterworking" );
				addModuleField( 71, "releasecauseind" );
				break;
			case 74:
				addModuleField( 74, "bbgcalltype" );
				addModuleField( 74, "bbgbillingnpa" );
				addModuleField( 74, "bbgbillingcoend" );
				addModuleField( 74, "simfacgroup" );
				break;
			case 75:
				addModuleField( 75, "ektscapabilities" );
				addModuleField( 75, "bridgeconnecttime" );
				addModuleField( 75, "bridgeelapsedtime" );
				break;
			case 87:
				addModuleField( 87, "directorynumdesc" );
				break;
			case 102:
				addModuleField( 102, "sigdigs" );
				addModuleField( 102, "digits" );
				break;
			case 103:
				addModuleField( 103,"sigdigs" );
				addModuleField( 103, "digits" );
				break;
			case 104:
				addModuleField( 104, "trunkid" );
				break;
			case 109:
				addModuleField( 109, "classfeaturecode" );
				addModuleField( 109, "classfunctions" );
				addModuleField( 109, "screenlistsizegen" );
				break;
			case 119:
				addModuleField( 119, "trunkgroupinfo" );
				addModuleField( 119, "carrierinterface" );
				addModuleField( 119, "networkidentifier" );
				break;
			case 164:
				addModuleField( 164, "numberidentity" );
				addModuleField( 164, "countrycode" );
				addModuleField( 164, "sigdigs" );
				addModuleField( 164, "largedigits" );
				break;
			case 203:
				addModuleField( 203, "contextid" );
				addModuleField( 203, "servproviderid" );
				addModuleField( 203, "amasequencenumber" );
				break;
			case 204:
				addModuleField( 204, "indicatorid" );
				break;
			case 207:
				addModuleField( 207, "triggerseqnumber" );
				addModuleField( 207, "linenumbertype" );
				addModuleField( 207, "linenpa" );
				addModuleField( 207, "linenumber" );
				addModuleField( 207, "directorynumdesc" );
				break;
			case 290:
				addModuleField( 290, "servicelogicid" );
				addModuleField( 290, "triggerseqnum" );
				addModuleField( 290, "date" );
				addModuleField( 290, "timingindicator" );
				addModuleField( 290, "time" );
				addModuleField( 290, "elapsedtime" );
				addModuleField( 290, "resourcetype" );
				addModuleField( 290, "destinatingnpa" );
				addModuleField( 290, "destinatingnumber" );
				break;
			case 300:
				addModuleField( 300, "sigdigs" );
				addModuleField( 300, "digitsdialed1" );
				addModuleField( 300, "digitsdialed2" );
				break;
			case 301:
				addModuleField( 301, "subaccountbillingindicator" );
				addModuleField( 301, "subaccountbillingnumber" );
				break;
			case 306:
				addModuleField( 306, "originatinglineinfo" );
				break;
			case 307:
				addModuleField( 307, "linenumbertype" );
				addModuleField( 307, "linenpa" );
				addModuleField( 307, "linenumber" );
				break;
			case 611:
				addModuleField( 611, "genericcontextid" );
				addModuleField( 611, "digits" );
				break;
			case 719:
				addModuleField( 719, "partyid" );
				addModuleField( 719, "lrn" );
				addModuleField( 719, "supportinginfo" );
				break;
			case 720:
				addModuleField( 720, "partyid" );
				addModuleField( 720, "lrn" );
				addModuleField( 720, "serviceproviderid" );
				addModuleField( 720, "location" );
				addModuleField( 720, "supportinginfo" );
				break;
			case 901:
				// Coppercom specific module
				addModuleField( 901, "recordid" );
				addModuleField( 901, "originatingshelf" );
				addModuleField( 901, "originatingcard" );
				addModuleField( 901, "originatingmodule" );
				addModuleField( 901, "originatingds1" );
				addModuleField( 901, "originatingds0" );
				addModuleField( 901, "terminatingshelf" );
				addModuleField( 901, "terminatingcard" );
				addModuleField( 901, "terminatingmodule" );
				addModuleField( 901, "terminatingds1" );
				addModuleField( 901, "terminatingds0" );
				break;
			case 902:
				// Coppercom specific module
				addModuleField( 902, "sigdigs" );
				addModuleField( 902, "pincodedigits" );
				break;
			case 903:
				// Coppercom specific module
				addModuleField( 903, "speeddialingcode" );
				addModuleField( 903, "sigdigs" );
				addModuleField( 903, "digits" );
				addModuleField( 903, "digits" );
				break;
			case 904:
				// Coppercom specific module
				addModuleField( 904, "codectype" );
				addModuleField( 904, "jitterdelay" );
				addModuleField( 904, "lostpackets" );
				addModuleField( 904, "percentlostpackets" );
				addModuleField( 904, "rcvedpackets" );
				break;
			case 905:
				// Coppercom specific module
				addModuleField( 905, "partyid" );
				addModuleField( 905, "uniformid" );
				addModuleField( 905, "peerfacgroup" );
				break;
			case 941:
				addModuleField( 941, "releasecauseind" );
				addModuleField( 941, "cpinternalcausecode" );
				addModuleField( 941, "cplocation" );
				break;
			default:
				LOG_ERROR( "Unknown modules id: " << _fields.back()->getInt() << " at " << _filePos << "." << (DWORD)( _fieldData - _data ) << " record type " << getType() );
			}
		}
		if( ( _fieldData - _data ) != _length )
			LOG_WARN( "The record " << getType() << " was not the correct length to fit the data.  There were " << ( _fieldData - _data ) << " bytes left" );

		LOG_TRACE( "/BafRecord::decodeModules" );
	}
}