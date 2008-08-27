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

#include "625.h"
#include "output.h"

namespace bafprp
{

	const r625Maker r625Maker::registerThis;

	IBafRecord* r625Maker::make( const BYTE* data, int length, const std::string& filename, long filePos ) const
	{
		LOG_TRACE( "r625Maker::make" );
		LOG_TRACE( "/r625Maker::make" );
		return new r625( data, length, filename, filePos );
	}

	r625::r625( const BYTE* data, int length, const std::string& filename, long filePos ) : IBafRecord( data, length, filename, filePos )
	{
		// make the real structure
		addField( "structurecode" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "date" );
		addField( "timingindicator" );
		addField( "studyindicator" );
		addField( "calledpartyanswerindicator" );
		addField( "servicetrafficind" );
		addField( "operatoraction" );
		addField( "servicefeaturecode" );
		addField( "originatingnpa" );
		addField( "originatingnumber" );
		addField( "overseasindicator" );
		addField( "terminatingnpa" );
		addField( "terminatingnumber" );
		addField( "time" );
		addField( "elapsedtime" );
		addField( "icincid" );
		addField( "carrierconnectdate" );
		addField( "carrierconnecttime" );
		addField( "carrierelapsedtime" );
		addField( "icinccalleventstatus" );
		addField( "trunkgroupnumber" );
		addField( "icincrouting" );
		addField( "dialingpresubind" );
		addField( "anicpnindicator" );
		decodeModules();
	}

	std::string r625::getType() const
	{
		// Need to look at the call type field
		std::string ret;
		const IField* field = getField( "calltype" );
		if( !field ) 
		{
			LOG_ERROR( "No 'calltype' field in record 625" );
			return "";
		}

		switch( field->getInt() )
		{
		case 119:
			ret = "Record 625: Incoming CDR";
			break;
		case 110:
			ret = "Record 625: Interlata call";
			break;
		default:
			ret = "Record 625: Unknown";
		}
		return ret;
	}

	r625::~r625()
	{
	}

}
