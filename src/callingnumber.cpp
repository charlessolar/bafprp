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

#include "callingnumber.h"
#include "output.h"

namespace bafprp
{
	const CallingNumberFieldMaker CallingNumberFieldMaker::registerThis;

	IField* CallingNumberFieldMaker::make() const
	{
		LOG_TRACE( "CallingNumberFieldMaker::make" );
		LOG_TRACE( "/CallingNumberFieldMaker::make" );
		return new CallingNumber;
		
	}

	CallingNumber::CallingNumber() : IField()
	{
		LOG_TRACE( "CallingNumber::CallingNumberFieldConverter" );
		LOG_TRACE( "/CallingNumber::CallingNumberFieldConverter" );
	}


	CallingNumber::~CallingNumber()
	{
		LOG_TRACE( "CallingNumber::~CallingNumberFieldConverter" );
		LOG_TRACE( "/CallingNumber::~CallingNumberFieldConverter" );
	}

	bool CallingNumber::convert ( const BYTE* data )
	{
		LOG_TRACE( "CallingNumber::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CallingNumber::convert" );
		return _converted;
	}

	int CallingNumber::getInt()
	{
		LOG_TRACE( "CallingNumber::getInt" );

		int ret;
		if( !_converted )
		{
			_lastError = "Tried to get int before field was converted";
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/CallingNumber::getInt" );
		return ret;
	}

	long CallingNumber::getLong()
	{
		LOG_TRACE( "CallingNumber::getLong" );

		long ret;
		if( !_converted )
		{
			_lastError = "Tried to get long before field was converted";
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/CallingNumber::getLong" );
		return ret;
	}

	std::string CallingNumber::getString()
	{
		LOG_TRACE( "CallingNumber::getString" );

		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/CallingNumber::getString" );
		return ret;
	}
}
