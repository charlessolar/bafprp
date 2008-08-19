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

#include "countrycode.h"
#include "output.h"

namespace bafprp
{
	const CountryCodeFieldMaker CountryCodeFieldMaker::registerThis;

	IField* CountryCodeFieldMaker::make() const
	{
		LOG_TRACE( "CountryCodeFieldMaker::make" );
		LOG_TRACE( "/CountryCodeFieldMaker::make" );
		return new CountryCode;
		
	}

	CountryCode::CountryCode() : IField()
	{
		LOG_TRACE( "CountryCode::CountryCodeFieldConverter" );
		LOG_TRACE( "/CountryCode::CountryCodeFieldConverter" );
	}


	CountryCode::~CountryCode()
	{
		LOG_TRACE( "CountryCode::~CountryCodeFieldConverter" );
		LOG_TRACE( "/CountryCode::~CountryCodeFieldConverter" );
	}

	bool CountryCode::convert ( const BYTE* data )
	{
		LOG_TRACE( "CountryCode::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CountryCode::convert" );
		return _converted;
	}

	int CountryCode::getInt() const
	{
		LOG_TRACE( "CountryCode::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.substr(1).c_str() );

		LOG_TRACE( "/CountryCode::getInt" );
		return ret;
	}

	long CountryCode::getLong() const
	{
		LOG_TRACE( "CountryCode::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.substr(1).c_str() );

		LOG_TRACE( "/CountryCode::getLong" );
		return ret;
	}

	std::string CountryCode::getString() const
	{
		LOG_TRACE( "CountryCode::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( _return[0] )
			{
			case '0':
				ret = "E.164 number for undeterminable country code length";
				break;
			case '1':
				ret = "E.164 number 1-digit country code";
				break;
			case '2':
				ret = "E.164 number 2-digit country code";
				break;
			case '3':
				ret = "E.164 number 3-digit country code";
				break;
			case '4':
				ret = "X.121 number";
				break;
			default:
				ret = "Unknown " + _return[0];
			}
			ret += " : ";
			ret += _return.substr(1);
		}

		LOG_TRACE( "/CountryCode::getString" );
		return ret;
	}
}
