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

#include "bearercaps.h"
#include "output.h"

namespace bafprp
{
	const BearerCapsFieldMaker BearerCapsFieldMaker::registerThis;

	IField* BearerCapsFieldMaker::make() const
	{
		LOG_TRACE( "BearerCapsFieldMaker::make" );
		LOG_TRACE( "/BearerCapsFieldMaker::make" );
		return new BearerCaps;
		
	}

	BearerCaps::BearerCaps() : IField()
	{
		LOG_TRACE( "BearerCaps::BearerCapsFieldConverter" );
		LOG_TRACE( "/BearerCaps::BearerCapsFieldConverter" );
	}


	BearerCaps::~BearerCaps()
	{
		LOG_TRACE( "BearerCaps::~BearerCapsFieldConverter" );
		LOG_TRACE( "/BearerCaps::~BearerCapsFieldConverter" );
	}

	bool BearerCaps::convert ( const BYTE* data )
	{
		LOG_TRACE( "BearerCaps::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/BearerCaps::convert" );
		return _converted;
	}

	std::string BearerCaps::getString() const
	{
		LOG_TRACE( "BearerCaps::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( _return[0] )
			{
			case '1':
				ret = "Voice/voiceband data";
				break;
			case '2':
				ret = "Circuit-mode data";
				break;
			case '3':
				ret = "Packet-mode data";
				break;
			default:
				ret = "Unknown " + _return[0];
			}
			ret += " : ";
			switch( atoi( _return.substr(1,2).c_str() ) )
			{
			case 1:
				ret += "Speech";
				break;
			case 2:
				ret += "3.1 KHz audio";
				break;
			case 3:
				ret += "64-kbps transfer";
				break;
			case 4:
				ret += "64-kbps transfer rate adapted from 56-kbps";
				break;
			case 5:
				ret += "Digital information transfer";
				break;
			case 7:
				ret += "Transfer at a rate greater than 64-kbps";
				break;
			default:
				ret += "Unknown " + _return.substr(1,2);
			}
		}

		LOG_TRACE( "/BearerCaps::getString" );
		return ret;
	}
}
