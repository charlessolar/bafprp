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

#include "location.h"
#include "output.h"

namespace bafprp
{
	const LocationFieldMaker LocationFieldMaker::registerThis;

	IField* LocationFieldMaker::make() const
	{
		LOG_TRACE( "LocationFieldMaker::make" );
		LOG_TRACE( "/LocationFieldMaker::make" );
		return new Location;
		
	}

	Location::Location() : IField()
	{
		LOG_TRACE( "Location::LocationFieldConverter" );
		LOG_TRACE( "/Location::LocationFieldConverter" );
	}


	Location::~Location()
	{
		LOG_TRACE( "Location::~LocationFieldConverter" );
		LOG_TRACE( "/Location::~LocationFieldConverter" );
	}

	bool Location::convert ( const BYTE* data )
	{
		LOG_TRACE( "Location::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/Location::convert" );
		return _converted;
	}

	std::string Location::getString() const
	{
		LOG_TRACE( "Location::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( atoi( _return.substr(0,3).c_str() ) )
			{
			case 6:
				ret = "6 digit geographic unit building block";
				break;
			case 100:
				ret = "Signaling point code";
				break;
			default:
				ret = "Unknown " + _return.substr(0,3);
			}
			ret += " : ";
			ret += _return.substr(4,11);
		}

		LOG_TRACE( "/Location::getString" );
		return ret;
	}
}
