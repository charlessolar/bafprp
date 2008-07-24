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

#include "DialedNumber.h"
#include "output.h"

namespace bafprp
{
	const DialedNumberFieldMaker DialedNumberFieldMaker::registerThis;

	IField* DialedNumberFieldMaker::make() const
	{
		LOG_TRACE( "DialedNumberFieldMaker::make" );
		LOG_TRACE( "/DialedNumberFieldMaker::make" );
		return new DialedNumber;
		
	}

	DialedNumber::DialedNumber() : IField()
	{
		LOG_TRACE( "DialedNumber::DialedNumberFieldConverter" );
		LOG_TRACE( "/DialedNumber::DialedNumberFieldConverter" );
	}


	DialedNumber::~DialedNumber()
	{
		LOG_TRACE( "DialedNumber::~DialedNumberFieldConverter" );
		LOG_TRACE( "/DialedNumber::~DialedNumberFieldConverter" );
	}

	bool DialedNumber::convert ( const BYTE* data )
	{
		LOG_TRACE( "DialedNumber::convert" );
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

		LOG_TRACE( "/DialedNumber::convert" );
		return _converted;
	}

	std::string DialedNumber::getString() const
	{
		LOG_TRACE( "DialedNumber::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			ret = _return.substr(0,3) + "-" + _return.substr(4,3) + "-" + _return.substr(7,4);
		}

		LOG_TRACE( "/DialedNumber::getString" );
		return ret;
	}
}
