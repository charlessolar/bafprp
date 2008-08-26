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

#include "sensortype.h"
#include "output.h"

namespace bafprp
{
	const SensorTypeFieldMaker SensorTypeFieldMaker::registerThis;

	IField* SensorTypeFieldMaker::make() const
	{
		LOG_TRACE( "SensorTypeFieldMaker::make" );
		return new SensorType();
		LOG_TRACE( "SensorTypeFieldMaker::make" );
	}

	SensorType::SensorType() : IField()
	{
		LOG_TRACE( "SensorType::SensorType" );
		LOG_TRACE( "/SensorType::SensorType" );
	}


	SensorType::~SensorType()
	{
		LOG_TRACE( "SensorType::~SensorType" );
		LOG_TRACE( "/SensorType::~SensorType" );
	}

	bool SensorType::convert ( const BYTE* data )
	{
		LOG_TRACE( "SensorType::convert" );
		
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/SensorType::convert" );
		return _converted;
	}

	long SensorType::getLong() const
	{
		LOG_TRACE( "SensorType::getLong" );
		
		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/SensorType::getLong" );
		return ret;
	}

	int SensorType::getInt() const
	{
		LOG_TRACE( "SensorType::getInt" );
		
		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/SensorType::getInt" );
		return ret;
	}

	std::string SensorType::getString() const
	{
		LOG_TRACE( "SensorType::getString" );
		
		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/SensorType::getString" );
		return ret;
	}
}