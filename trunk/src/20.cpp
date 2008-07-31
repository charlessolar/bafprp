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

#include "20.h"
#include "output.h"

namespace bafprp
{

	const r20Maker r20Maker::registerThis;

	IBafRecord* r20Maker::make( const BYTE* data, int length, const std::string& filename, long filePos ) const
	{
		LOG_TRACE( "r20Maker::make" );
		LOG_TRACE( "/r20Maker::make" );
		return new r20( data, length, filename, filePos );
	}

	r20::r20( const BYTE* data, int length, const std::string& filename, long filePos ) : IBafRecord( data, length, filename, filePos )
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
		addField( "watsindicator" );
		addField( "msgbillingindex" );
		decodeModules();
	}

	std::string r20::getType() const
	{
		// This type of record only has 1 use
		return "Record 20: Unknown";
	}

	r20::~r20()
	{
	}

}