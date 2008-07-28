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

#include "110.h"
#include "output.h"

namespace bafprp
{

	const r110Maker r110Maker::registerThis;

	IBafRecord* r110Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r110Maker::make" );
		LOG_TRACE( "/r110Maker::make" );
		return new r110( data, length, filePos );
	}

	r110::r110( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
	{
		// make the real structure
		addField( "structuretype" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "classfeaturecode" );
		addField( "date" );
		addField( "time" );
		addField( "callingnumber" );
		addField( "callcountinfodeliv" );
		addField( "callcountinfoanon" );
		decodeModules();
	}

	std::string r110::getType() const
	{
		// Need to look at the call type field
		std::string ret;
		const IField* field = getField( "Call Type" );
		if( !field ) 
		{
			LOG_ERROR( "No 'calltype' field in record 110" );
			return "Record 110: Error";
		}
		const IField* field2 = getField( "CLASS Feature code" );
		if( !field2 ) 
		{
			LOG_ERROR( "No 'classfeaturecode' field in record 110" );
			return "Record 110: Unknown";
		}


		switch( field->getInt() )
		{
		case 330:
			if( field2->getInt() == 1 || field2->getInt() == 2 || field2->getInt() == 3 )
				ret = "Record 110: CLASS feature: Outgoing Call Barring";
			else
				ret = "Record 110: CLASS feature: Anonymous call rejection";
			break;
		default:
			ret = "Record 110: Unknown";
		}
		return ret;
	}

	r110::~r110()
	{
	}

}