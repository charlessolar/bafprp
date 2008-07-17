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
		if( _return[3] != 'C' )
		{
			_lastError = "Badly formated field";
			_converted = false;
		}		

		LOG_TRACE( "/CallingNumber::convert" );
		return _converted;
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
		{
			ret = _return.substr(0,3) + "-" + _return.substr(4,3) + "-" + _return.substr(7,4);
		}

		LOG_TRACE( "/CallingNumber::getString" );
		return ret;
	}
}
