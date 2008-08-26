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

#include "linenumbertype.h"
#include "output.h"

namespace bafprp
{
	const LineNumberTypeFieldMaker LineNumberTypeFieldMaker::registerThis;

	IField* LineNumberTypeFieldMaker::make() const
	{
		LOG_TRACE( "LineNumberTypeFieldMaker::make" );
		LOG_TRACE( "/LineNumberTypeFieldMaker::make" );
		return new LineNumberType;
		
	}

	LineNumberType::LineNumberType() : IField()
	{
		LOG_TRACE( "LineNumberType::LineNumberTypeFieldConverter" );
		LOG_TRACE( "/LineNumberType::LineNumberTypeFieldConverter" );
	}


	LineNumberType::~LineNumberType()
	{
		LOG_TRACE( "LineNumberType::~LineNumberTypeFieldConverter" );
		LOG_TRACE( "/LineNumberType::~LineNumberTypeFieldConverter" );
	}

	bool LineNumberType::convert ( const BYTE* data )
	{
		LOG_TRACE( "LineNumberType::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/LineNumberType::convert" );
		return _converted;
	}

	int LineNumberType::getInt() const
	{
		LOG_TRACE( "LineNumberType::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/LineNumberType::getInt" );
		return ret;
	}

	long LineNumberType::getLong() const
	{
		LOG_TRACE( "LineNumberType::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/LineNumberType::getLong" );
		return ret;
	}

	std::string LineNumberType::getString() const
	{
		LOG_TRACE( "LineNumberType::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( getInt() )
			{
			case 4:
				ret = "Incomming terminating number";
				break;
			case 5:
				ret = "Calling party identification";
				break;
			case 6:
				ret = "Automatic number identification delivered";
				break;
			default:
				if( getInt() > 800 && getInt() < 999 )
					ret = "LEC assigned";
				else
					ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/LineNumberType::getString" );
		return ret;
	}
}
