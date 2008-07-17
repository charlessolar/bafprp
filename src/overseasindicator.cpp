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

#include "overseasindicator.h"
#include "output.h"

namespace bafprp
{
	const OverseasIndicatorFieldMaker OverseasIndicatorFieldMaker::registerThis;

	IField* OverseasIndicatorFieldMaker::make() const
	{
		LOG_TRACE( "OverseasIndicatorFieldMaker::make" );
		LOG_TRACE( "/OverseasIndicatorFieldMaker::make" );
		return new OverseasIndicator;
		
	}

	OverseasIndicator::OverseasIndicator() : IField()
	{
		LOG_TRACE( "OverseasIndicator::OverseasIndicatorFieldConverter" );
		LOG_TRACE( "/OverseasIndicator::OverseasIndicatorFieldConverter" );
	}


	OverseasIndicator::~OverseasIndicator()
	{
		LOG_TRACE( "OverseasIndicator::~OverseasIndicatorFieldConverter" );
		LOG_TRACE( "/OverseasIndicator::~OverseasIndicatorFieldConverter" );
	}

	bool OverseasIndicator::convert ( const BYTE* data )
	{
		LOG_TRACE( "OverseasIndicator::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/OverseasIndicator::convert" );
		return _converted;
	}

	int OverseasIndicator::getInt()
	{
		LOG_TRACE( "OverseasIndicator::getInt" );

		int ret;
		if( !_converted )
		{
			_lastError = "Tried to get int before field was converted";
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/OverseasIndicator::getInt" );
		return ret;
	}

	long OverseasIndicator::getLong()
	{
		LOG_TRACE( "OverseasIndicator::getLong" );

		long ret;
		if( !_converted )
		{
			_lastError = "Tried to get long before field was converted";
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/OverseasIndicator::getLong" );
		return ret;
	}

	std::string OverseasIndicator::getString()
	{
		LOG_TRACE( "OverseasIndicator::getString" );

		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
		{
			switch( _return[0] )
			{
			case '0':
				ret = "NPA dialed by customer";
				break;
			case '1':
				ret = "NPA determined by the network element";
				break;
			case '2':
				ret = "Non-NANP number dialed (non-international)";
				break;
			case '3':
				ret = "7-digits international number";
				break;
			case '4':
				ret = "8-digits international number";
				break;
			case '5':
				ret = "9-digits international number";
				break;
			case '6':
				ret = "10-digits international number";
				break;
			case '7':
				ret = "11-digits international number";
				break;
			case '8':
				ret = "12-digits international number";
				break;
			case '9':
				ret = "Operator inward dialed-code";
				break;
			}
		}

		LOG_TRACE( "/OverseasIndicator::getString" );
		return ret;
	}
}
