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

#include "220.h"
#include "output.h"

namespace bafprp
{

	const r220Maker r220Maker::registerThis;

	IBafRecord* r220Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r220Maker::make" );
		LOG_TRACE( "/r220Maker::make" );
		return new r220( data, length, filePos );
	}

	r220::r220( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
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
		addField( "completionindicator" );
		addField( "servicefeature" );
		addField( "callingnumber" );
		addField( "overseasindicator" );
		addField( "callednumber" );
		addField( "time" );
		addField( "duration" );
		addField( "servicelogicid" );
		decodeModules();
		addField( "endofrecord" );
	}

	std::string r220::getType() const
	{
		// Need to look at the call type field
		std::string ret;
		const IField* field = getField( "Call Type" );
		if( !field ) 
		{
			LOG_ERROR( "No 'calltype' field in record 220" );
			return "";
		}

		switch( field->getInt() )
		{
		case 119:
			ret = "Incoming CDR";
			break;
		case 110:
			ret = "Interlata call";
			break;
		default:
			ret = "Unknown";
		}
		return ret;
	}

	r220::~r220()
	{
	}

}