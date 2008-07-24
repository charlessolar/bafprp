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

#include "1030.h"
#include "output.h"

namespace bafprp
{

	const r1030Maker r1030Maker::registerThis;

	IBafRecord* r1030Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r1030Maker::make" );
		LOG_TRACE( "/r1030Maker::make" );
		return new r1030( data, length, filePos );
	}

	r1030::r1030( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
	{
		// make the real structure
		addField( "structuretype" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "date" );
		addField( "classfeaturecode" );
		addField( "callingnumber" );
		addField( "overseasindicator" );
		addField( "callednumber" );
		addField( "time" );
		addField( "duration" );
		addField( "classfunctions" );
		addField( "screenlistfeatstat" );
		addField( "screenlistsizescfa" );
		addField( "screenlistsizescr" );
		addField( "screenlistsizedrcw" );
		decodeModules();
		addField( "endofrecord" );
	}

	std::string r1030::getType() const
	{
		// This type of record only has 1 use
		return "Unknown";
	}

	r1030::~r1030()
	{
	}

}