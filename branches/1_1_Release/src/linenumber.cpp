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

#include "linenumber.h"
#include "output.h"

namespace bafprp
{
	const LineNumberFieldMaker LineNumberFieldMaker::registerThis;

	IField* LineNumberFieldMaker::make() const
	{
		LOG_TRACE( "LineNumberFieldMaker::make" );
		LOG_TRACE( "/LineNumberFieldMaker::make" );
		return new LineNumber;
		
	}

	LineNumber::LineNumber() : IField()
	{
		LOG_TRACE( "LineNumber::LineNumberFieldConverter" );
		LOG_TRACE( "/LineNumber::LineNumberFieldConverter" );
	}


	LineNumber::~LineNumber()
	{
		LOG_TRACE( "LineNumber::~LineNumberFieldConverter" );
		LOG_TRACE( "/LineNumber::~LineNumberFieldConverter" );
	}

	bool LineNumber::convert ( const BYTE* data )
	{
		LOG_TRACE( "LineNumber::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/LineNumber::convert" );
		return _converted;
	}

	std::string LineNumber::getString() const
	{
		LOG_TRACE( "LineNumber::getString" );

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

		LOG_TRACE( "/LineNumber::getString" );
		return ret;
	}
}
