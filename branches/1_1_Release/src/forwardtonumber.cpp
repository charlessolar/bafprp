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

#include "forwardtonumber.h"
#include "output.h"

namespace bafprp
{
	const ForwardToNumberFieldMaker ForwardToNumberFieldMaker::registerThis;

	IField* ForwardToNumberFieldMaker::make() const
	{
		LOG_TRACE( "ForwardToNumberFieldMaker::make" );
		LOG_TRACE( "/ForwardToNumberFieldMaker::make" );
		return new ForwardToNumber;
		
	}

	ForwardToNumber::ForwardToNumber() : IField()
	{
		LOG_TRACE( "ForwardToNumber::ForwardToNumberFieldConverter" );
		LOG_TRACE( "/ForwardToNumber::ForwardToNumberFieldConverter" );
	}


	ForwardToNumber::~ForwardToNumber()
	{
		LOG_TRACE( "ForwardToNumber::~ForwardToNumberFieldConverter" );
		LOG_TRACE( "/ForwardToNumber::~ForwardToNumberFieldConverter" );
	}

	bool ForwardToNumber::convert ( const BYTE* data )
	{
		LOG_TRACE( "ForwardToNumber::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}
		if( _return[5] != 'C' )
		{
			_lastError = "Badly formated field";
			_converted = false;
		}

		LOG_TRACE( "/ForwardToNumber::convert" );
		return _converted;
	}

	std::string ForwardToNumber::getString() const
	{
		LOG_TRACE( "ForwardToNumber::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			ret = "";
			if( _return[0] != '0' || _return[1] != '0' )
				ret += _return.substr(0,2) + "-";
			ret += _return.substr(2,3) + "-" + _return.substr(6,3) + "-" + _return.substr(9,4);
		}


		LOG_TRACE( "/ForwardToNumber::getString" );
		return ret;
	}
}
