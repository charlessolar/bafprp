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

#include "callslostdata.h"
#include "output.h"

namespace bafprp
{
	const CallsLostDataFieldMaker CallsLostDataFieldMaker::registerThis;

	IField* CallsLostDataFieldMaker::make() const
	{
		LOG_TRACE( "CallsLostDataFieldMaker::make" );
		LOG_TRACE( "/CallsLostDataFieldMaker::make" );
		return new CallsLostData;
		
	}

	CallsLostData::CallsLostData() : IField()
	{
		LOG_TRACE( "CallsLostData::CallsLostDataFieldConverter" );
		LOG_TRACE( "/CallsLostData::CallsLostDataFieldConverter" );
	}


	CallsLostData::~CallsLostData()
	{
		LOG_TRACE( "CallsLostData::~CallsLostDataFieldConverter" );
		LOG_TRACE( "/CallsLostData::~CallsLostDataFieldConverter" );
	}

	bool CallsLostData::convert ( const BYTE* data )
	{
		LOG_TRACE( "CallsLostData::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CallsLostData::convert" );
		return _converted;
	}

	int CallsLostData::getInt() const
	{
		LOG_TRACE( "CallsLostData::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/CallsLostData::getInt" );
		return ret;
	}

	long CallsLostData::getLong() const
	{
		LOG_TRACE( "CallsLostData::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/CallsLostData::getLong" );
		return ret;
	}

	std::string CallsLostData::getString() const
	{
		LOG_TRACE( "CallsLostData::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/CallsLostData::getString" );
		return ret;
	}
}
