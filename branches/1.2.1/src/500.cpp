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

#include "500.h"
#include "output.h"

namespace bafprp
{

	const r500Maker r500Maker::registerThis;

	IBafRecord* r500Maker::make( const BYTE* data, int length, const std::string& filename, long filePos ) const
	{
		LOG_TRACE( "r500Maker::make" );
		LOG_TRACE( "/r500Maker::make" );
		return new r500( data, length, filename, filePos );
	}

	r500::r500( const BYTE* data, int length, const std::string& filename, long filePos ) : IBafRecord( data, length, filename, filePos )
	{
		// make the real structure
		addField( "structurecode" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "date" );
		addField( "calledpartyanswerindicator" );
		addField( "servicefeaturecode" );
		addField( "originatingnpa" );
		addField( "originatingnumber" );
		addField( "overseasindicator" );
		addField( "terminatingnpa" );
		addField( "terminatingnumber" );
		addField( "time" );
		addField( "elapsedtime" );
		decodeModules();
	}

	std::string r500::getType() const
	{
		// This type of record only has 1 use
		return "Record 500: Unknown";
	}

	r500::~r500()
	{
	}

}
