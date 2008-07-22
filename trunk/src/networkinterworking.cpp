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

#include "networkinterworking.h"
#include "output.h"

namespace bafprp
{
	const NetworkInterworkingFieldMaker NetworkInterworkingFieldMaker::registerThis;

	IField* NetworkInterworkingFieldMaker::make() const
	{
		LOG_TRACE( "NetworkInterworkingFieldMaker::make" );
		LOG_TRACE( "/NetworkInterworkingFieldMaker::make" );
		return new NetworkInterworking;
		
	}

	NetworkInterworking::NetworkInterworking() : IField()
	{
		LOG_TRACE( "NetworkInterworking::NetworkInterworkingFieldConverter" );
		LOG_TRACE( "/NetworkInterworking::NetworkInterworkingFieldConverter" );
	}


	NetworkInterworking::~NetworkInterworking()
	{
		LOG_TRACE( "NetworkInterworking::~NetworkInterworkingFieldConverter" );
		LOG_TRACE( "/NetworkInterworking::~NetworkInterworkingFieldConverter" );
	}

	bool NetworkInterworking::convert ( const BYTE* data )
	{
		LOG_TRACE( "NetworkInterworking::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/NetworkInterworking::convert" );
		return _converted;
	}

	std::string NetworkInterworking::getString() const
	{
		LOG_TRACE( "NetworkInterworking::getString" );

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
			case '0':
				ret = "No interworking";
				break;
			case '1':
				ret = "Interworking unspecified";
				break;
			case '2':
				ret = "Network interworking";
				break;
			case '3':
				ret = "Terminating access interworking for alerting";
				break;
			case '4':
				ret = "Terminating access interworking not for alerting";
				break;
			case '5':
				ret = "Originating access interworking";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/NetworkInterworking::getString" );
		return ret;
	}
}
