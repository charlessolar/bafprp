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

#include "9000.h"
#include "output.h"

namespace bafprp
{

	const r9000Maker r9000Maker::registerThis;

	IBafRecord* r9000Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r9000Maker::make" );
		LOG_TRACE( "/r9000Maker::make" );
		return new r9000( data, length, filePos );
	}

	r9000::r9000( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
	{
		// make the real structure
		addField( "structuretype" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "timebefore" );
		addField( "timeafter" );
		addField( "datebefore" );
		addField( "dateafter" );
		decodeModules();
		addField( "endofrecord" );

	}

	std::string r9000::getType() const
	{
		// This type of record only has 1 use
		return "Record 9000: Unknown";
	}

	r9000::~r9000()
	{
	}

}