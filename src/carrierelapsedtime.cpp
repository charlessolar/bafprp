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

#include "carrierelapsedtime.h"
#include "output.h"

namespace bafprp
{
	const CarrierElapsedTimeFieldMaker CarrierElapsedTimeFieldMaker::registerThis;

	IField* CarrierElapsedTimeFieldMaker::make() const
	{
		LOG_TRACE( "CarrierElapsedTimeFieldMaker::make" );
		LOG_TRACE( "/CarrierElapsedTimeFieldMaker::make" );
		return new CarrierElapsedTime;
		
	}

	CarrierElapsedTime::CarrierElapsedTime() : IField()
	{
		LOG_TRACE( "CarrierElapsedTime::CarrierElapsedTimeFieldConverter" );
		LOG_TRACE( "/CarrierElapsedTime::CarrierElapsedTimeFieldConverter" );
	}


	CarrierElapsedTime::~CarrierElapsedTime()
	{
		LOG_TRACE( "CarrierElapsedTime::~CarrierElapsedTimeFieldConverter" );
		LOG_TRACE( "/CarrierElapsedTime::~CarrierElapsedTimeFieldConverter" );
	}

	bool CarrierElapsedTime::convert ( const BYTE* data )
	{
		LOG_TRACE( "CarrierElapsedTime::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CarrierElapsedTime::convert" );
		return _converted;
	}

	int CarrierElapsedTime::getInt()
	{
		LOG_TRACE( "CarrierElapsedTime::getInt" );

		int ret;
		if( !_converted )
		{
			_lastError = "Tried to get int before field was converted";
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/CarrierElapsedTime::getInt" );
		return ret;
	}

	long CarrierElapsedTime::getLong()
	{
		LOG_TRACE( "CarrierElapsedTime::getLong" );

		long ret;
		if( !_converted )
		{
			_lastError = "Tried to get long before field was converted";
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/CarrierElapsedTime::getLong" );
		return ret;
	}

	std::string CarrierElapsedTime::getString()
	{
		LOG_TRACE( "CarrierElapsedTime::getString" );

		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/CarrierElapsedTime::getString" );
		return ret;
	}
}
