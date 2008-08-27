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

#include "614.h"
#include "output.h"

namespace bafprp
{

	const r614Maker r614Maker::registerThis;

	IBafRecord* r614Maker::make( const BYTE* data, int length, const std::string& filename, long filePos ) const
	{
		LOG_TRACE( "r614Maker::make" );
		LOG_TRACE( "/r614Maker::make" );
		return new r614( data, length, filename, filePos );
	}

	r614::r614( const BYTE* data, int length, const std::string& filename, long filePos ) : IBafRecord( data, length, filename, filePos )
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
		addField( "servicefeaturecode" );
		addField( "originatingnpa" );
		addField( "originatingnumber" );
		addField( "overseasindicator" );
		addField( "forwardtonumber" );
		addField( "activationtime" );
		decodeModules();
	}

	std::string r614::getType() const
	{
		// This type of record only has 1 use
		return "Record 614: Unknown";
	}

	r614::~r614()
	{
	}

}
