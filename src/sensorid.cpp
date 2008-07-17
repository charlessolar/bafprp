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

#include "sensorid.h"
#include "output.h"

namespace bafprp
{
	const SensorIDFieldMaker SensorIDFieldMaker::registerThis;

	IField* SensorIDFieldMaker::make() const
	{
		LOG_TRACE( "SensorIDFieldMaker::make" );
		return new SensorID();
		LOG_TRACE( "SensorIDFieldMaker::make" );
	}

	SensorID::SensorID() : IField()
	{
		LOG_TRACE( "SensorID::SensorID" );
		LOG_TRACE( "/SensorID::SensorID" );
	}


	SensorID::~SensorID()
	{
		LOG_TRACE( "SensorID::~SensorID" );
		LOG_TRACE( "/SensorID::~SensorID" );
	}

	bool SensorID::convert ( const BYTE* data )
	{
		LOG_TRACE( "SensorID::convert" );
		
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/SensorID::convert" );
		return _converted;
	}

	long SensorID::getLong() const
	{
		LOG_TRACE( "SensorID::getLong" );
		
		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/SensorID::getLong" );
		return ret;
	}

	int SensorID::getInt() const
	{
		LOG_TRACE( "SensorID::getInt" );
		
		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/SensorID::getInt" );
		return ret;
	}

	std::string SensorID::getString() const
	{
		LOG_TRACE( "SensorID::getString" );
		
		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/SensorID::getString" );
		return ret;
	}
}