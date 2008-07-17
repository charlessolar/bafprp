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

	IBafRecord* r625Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r625Maker::make" );
		LOG_TRACE( "/r625Maker::make" );
		return new r625( data, length, filePos );
	}

	r625::r625( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
	{
		// make the real structure
		addField( "structuretype" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "date" );
		addField( "timingindicator" );
		addField( "studyindicator" );
		addField( "calledpartyoffhook" );
		addField( "servicetraffic" );
		addField( "operatoraction" );
		addField( "servicefeature" );
		addField( "callingnumber" );
		addField( "overseasindicator" );
		addField( "callednumber" );
		addField( "time" );
		addField( "duration" );
		addField( "icincindicator" );
		addField( "carrierconnectdate" );
		addField( "carrierconnecttime" );
		addField( "carrierelapsedtime" );
		addField( "icinccalleventstatus" );
		addField( "trunkgroupnumber" );
		addField( "icincroutingindicator" );
		addField( "dialingpresubindicator" );
		addField( "anicpnindicator" );
	}

	std::string r625::getType()
	{
		// Need to look at the call type field
		std::string ret;
		IField* field = getField( "Call Type" );
		if( !field ) 
		{
			LOG_ERROR( "No 'calltype' field in record 625" );
			return "";
		}

		switch( field->getInt() )
		{
		case 119:
			ret = "Incomming CDR";
			break;
		default:
			ret = "Unknown";
		}
		return ret;
	}

	r625::~r625()
	{
	}

}