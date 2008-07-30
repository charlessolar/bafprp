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

#include "9013.h"
#include "output.h"

namespace bafprp
{

	const r9013Maker r9013Maker::registerThis;

	IBafRecord* r9013Maker::make( const BYTE* data, int length, const std::string filename, long filePos ) const
	{
		LOG_TRACE( "r9013Maker::make" );
		LOG_TRACE( "/r9013Maker::make" );
		return new r9013( data, length, filename, filePos );
	}

	r9013::r9013( const BYTE* data, int length, const std::string filename, long filePos ) : IBafRecord( data, length, filename, filePos )
	{
		// make the real structure
		addField( "structuretype" ); 
		addField( "calltype" ); 
		addField( "sensortype" ); 
		addField( "sensorid" ); 
		addField( "recordofficetype" );
		addField( "recordofficeid" );
		addField( "date" );
		addField( "time" );
		addField( "genericid" );
		addField( "traceraudittype" );
		addField( "filesequenceno" );
		//decodeModules();
	}

	std::string r9013::getType() const
	{
		// This type of record only has 1 use
		return "Record 9013: File Start Marker";
	}

	r9013::~r9013()
	{
	}

}