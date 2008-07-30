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

#include "28.h"
#include "output.h"

namespace bafprp
{

	const r28Maker r28Maker::registerThis;

	IBafRecord* r28Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r28Maker::make" );
		LOG_TRACE( "/r28Maker::make" );
		return new r28( data, length, filePos );
	}

	r28::r28( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
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
		addField( "time" );
		decodeModules();
	}

	std::string r28::getType() const
	{
		// Need to look at the call type field
		std::string ret;
		const IField* field = getField( "calltype" );
		if( !field ) 
		{
			LOG_ERROR( "No 'calltype' field in record 28" );
			return "";
		}

		switch( field->getInt() )
		{
		case 9:
			ret = "Record 28: 411 Directory Assistance";
			break;
		default:
			ret = "Record 28: Unknown";
		}
		return ret;
	}

	r28::~r28()
	{
	}

}