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

#include "number.h"
#include "output.h"

namespace bafprp
{
	const NumberFieldMaker NumberFieldMaker::registerThis;

	IField* NumberFieldMaker::make() const
	{
		LOG_TRACE( "NumberFieldMaker::make" );
		LOG_TRACE( "/NumberFieldMaker::make" );
		return new Number;
		
	}

	Number::Number() : IField()
	{
		LOG_TRACE( "Number::NumberFieldConverter" );
		LOG_TRACE( "/Number::NumberFieldConverter" );
	}


	Number::~Number()
	{
		LOG_TRACE( "Number::~NumberFieldConverter" );
		LOG_TRACE( "/Number::~NumberFieldConverter" );
	}

	bool Number::convert ( const BYTE* data )
	{
		LOG_TRACE( "Number::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/Number::convert" );
		return _converted;
	}

	int Number::getInt() const
	{
		LOG_TRACE( "Number::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/Number::getInt" );
		return ret;
	}

	long Number::getLong() const
	{
		LOG_TRACE( "Number::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/Number::getLong" );
		return ret;
	}

	std::string Number::getString() const
	{
		LOG_TRACE( "Number::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/Number::getString" );
		return ret;
	}
}
