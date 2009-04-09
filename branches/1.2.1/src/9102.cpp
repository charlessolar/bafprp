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

#include "9102.h"
#include "output.h"

namespace bafprp
{

	const r9102Maker r9102Maker::registerThis;

	IBafRecord* r9102Maker::make( const BYTE* data, int length, const std::string& filename, long filePos ) const
	{
		LOG_TRACE( "r9102Maker::make" );
		LOG_TRACE( "/r9102Maker::make" );
		return new r9102( data, length, filename, filePos );
	}

	r9102::r9102( const BYTE* data, int length, const std::string& filename, long filePos ) : IBafRecord( data, length, filename, filePos )
	{
		// make the real structure
		addField( "structurecode" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "date" );
		addField( "time" );
		addField( "traceraudittype" );
		addField( "calls" );
		addField( "amacalls" );
		addField( "lostcalldata" );
		addField( "amalostcalldata" );
		addField( "abortedbafrecords" );
		addField( "bafrecords" );
		addField( "flaggedbafrecords" );
		addField( "timingerrorbafrecords" );
		addField( "lostbafrecords" );
		addField( "originatingcalls" );
		addField( "terminatingcalls" );
		addField( "outgoingcalls" );
		decodeModules();
	}

	std::string r9102::getType() const
	{
		// Need to look at the call type field
		std::string ret;
		const IField* field = getField( "calltype" );
		if( !field ) 
		{
			LOG_ERROR( "No 'calltype' field in record 9102" );
			return "";
		}

		switch( field->getInt() )
		{
		case 90:
			ret = "Record 9102: Sensor Audit Record";
			break;
		default:
			ret = "Record 9102: Unknown";
		}
		return ret;
	}

	r9102::~r9102()
	{
	}

}
