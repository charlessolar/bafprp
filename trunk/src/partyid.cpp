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

#include "partyid.h"
#include "output.h"

namespace bafprp
{
	const PartyIDFieldMaker PartyIDFieldMaker::registerThis;

	IField* PartyIDFieldMaker::make() const
	{
		LOG_TRACE( "PartyIDFieldMaker::make" );
		LOG_TRACE( "/PartyIDFieldMaker::make" );
		return new PartyID;
		
	}

	PartyID::PartyID() : IField()
	{
		LOG_TRACE( "PartyID::PartyIDFieldConverter" );
		LOG_TRACE( "/PartyID::PartyIDFieldConverter" );
	}


	PartyID::~PartyID()
	{
		LOG_TRACE( "PartyID::~PartyIDFieldConverter" );
		LOG_TRACE( "/PartyID::~PartyIDFieldConverter" );
	}

	bool PartyID::convert ( const BYTE* data )
	{
		LOG_TRACE( "PartyID::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/PartyID::convert" );
		return _converted;
	}

	int PartyID::getInt() const
	{
		LOG_TRACE( "PartyID::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/PartyID::getInt" );
		return ret;
	}

	long PartyID::getLong() const
	{
		LOG_TRACE( "PartyID::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/PartyID::getLong" );
		return ret;
	}

	std::string PartyID::getString() const
	{
		LOG_TRACE( "PartyID::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( getInt() )
			{
			case 1:
				ret = "Originating party DN";
				break;
			case 2:
				ret = "Terminating party DN";
				break;
			case 3:
				ret = "Billing party DN";
				break;
			case 4:
				ret = "Aggregate / feature record DN";
				break;
			case 5:
				ret = "Detailed / feature record DN";
				break;
			case 6:
				ret = "Third party verification";
				break;
			case 7:
				ret = "Busy line verification";
				break;
			case 8:
				ret = "Redirecting";
				break;
			case 9:
				ret = "Directory assistance";
				break;
			case 10:
				ret = "Incoming trunk group";
				break;
			case 11:
				ret = "Outgoing trunk group";
				break;
			case 12:
				ret = "Reserved";
				break;
			case 13:
				ret = "OSS";
				break;
			case 20:
				ret = "NECA company code";
				break;
			case 21:
				ret = "CIC";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/PartyID::getString" );
		return ret;
	}
}
