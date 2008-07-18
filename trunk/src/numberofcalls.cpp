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

#include "numberofcalls.h"
#include "output.h"

namespace bafprp
{
	const NumberOfCallsFieldMaker NumberOfCallsFieldMaker::registerThis;

	IField* NumberOfCallsFieldMaker::make() const
	{
		LOG_TRACE( "NumberOfCallsFieldMaker::make" );
		LOG_TRACE( "/NumberOfCallsFieldMaker::make" );
		return new NumberOfCalls;
		
	}

	NumberOfCalls::NumberOfCalls() : IField()
	{
		LOG_TRACE( "NumberOfCalls::NumberOfCallsFieldConverter" );
		LOG_TRACE( "/NumberOfCalls::NumberOfCallsFieldConverter" );
	}


	NumberOfCalls::~NumberOfCalls()
	{
		LOG_TRACE( "NumberOfCalls::~NumberOfCallsFieldConverter" );
		LOG_TRACE( "/NumberOfCalls::~NumberOfCallsFieldConverter" );
	}

	bool NumberOfCalls::convert ( const BYTE* data )
	{
		LOG_TRACE( "NumberOfCalls::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/NumberOfCalls::convert" );
		return _converted;
	}

	int NumberOfCalls::getInt() const
	{
		LOG_TRACE( "NumberOfCalls::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/NumberOfCalls::getInt" );
		return ret;
	}

	long NumberOfCalls::getLong() const
	{
		LOG_TRACE( "NumberOfCalls::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/NumberOfCalls::getLong" );
		return ret;
	}

	std::string NumberOfCalls::getString() const
	{
		LOG_TRACE( "NumberOfCalls::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/NumberOfCalls::getString" );
		return ret;
	}
}
