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

#include "phonenumber_dt.h"
#include "output.h"

namespace bafprp
{
	const PhoneNumberFieldMaker PhoneNumberFieldMaker::registerThis;

	IField* PhoneNumberFieldMaker::make() const
	{
		return new PhoneNumberField;
	}

	PhoneNumberField::PhoneNumberField() : IField()
	{
		LOG_TRACE( "PhoneNumberField::PhoneNumber" );
		LOG_TRACE( "/PhoneNumberField::PhoneNumber" );
	}


	PhoneNumberField::~PhoneNumberField()
	{
		LOG_TRACE( "PhoneNumberField::~PhoneNumber" );
		LOG_TRACE( "/PhoneNumberField::~PhoneNumber" );
	}

	bool PhoneNumberField::convert ( const BYTE* data )
	{
		LOG_TRACE( "PhoneNumberField::convert" );

		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/PhoneNumberField::convert" );
		return _converted;
	}

	int PhoneNumberField::getInt() const
	{
		LOG_TRACE( "PhoneNumberField::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/PhoneNumberField::getInt" );
		return ret;
	}

	long PhoneNumberField::getLong() const
	{
		LOG_TRACE( "PhoneNumberField::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/PhoneNumberField::getLong" );
		return ret;
	}
	
	std::string PhoneNumberField::getString() const
	{
		LOG_TRACE( "PhoneNumberField::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			bool nohyphen = ( getProperty( "hyphens", true ) == "false" );
			if( nohyphen )
			{
				ret = _return;
			}
			else
				ret = _return.substr(0,3) + "-" + _return.substr(3,4);
		}

		LOG_TRACE( "/PhoneNumberField::getString" );
		return ret;
	}
}
