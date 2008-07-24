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

#include "96.h"
#include "output.h"

namespace bafprp
{

	const r96Maker r96Maker::registerThis;

	IBafRecord* r96Maker::make( const BYTE* data, int length, long filePos ) const
	{
		LOG_TRACE( "r96Maker::make" );
		LOG_TRACE( "/r96Maker::make" );
		return new r96( data, length, filePos );
	}

	r96::r96( const BYTE* data, int length, long filePos ) : IBafRecord( data, length, filePos )
	{
		// make the real structure
		addField( "structuretype" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "activationdate" );
		addField( "timingindicator" );
		addField( "studyindicator" );
		addField( "servicefeature" );
		addField( "callingnumber" );
		addField( "overseasindicator" );
		addField( "forwardtonumber" );
		addField( "activationtime" );
		addField( "duration" );
		addField( "presentdate" );
		addField( "presenttime" );
		decodeModules();
		addField( "endofrecord" );
	}

	std::string r96::getType() const
	{
		// This type of record only has 1 use
		return "Unknown";
	}

	r96::~r96()
	{
	}

}