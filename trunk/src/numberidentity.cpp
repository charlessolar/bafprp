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

#include "NumberIdentity.h"
#include "output.h"

namespace bafprp
{
	const NumberIdentityFieldMaker NumberIdentityFieldMaker::registerThis;

	IField* NumberIdentityFieldMaker::make() const
	{
		LOG_TRACE( "NumberIdentityFieldMaker::make" );
		LOG_TRACE( "/NumberIdentityFieldMaker::make" );
		return new NumberIdentity;
		
	}

	NumberIdentity::NumberIdentity() : IField()
	{
		LOG_TRACE( "NumberIdentity::NumberIdentityFieldConverter" );
		LOG_TRACE( "/NumberIdentity::NumberIdentityFieldConverter" );
	}


	NumberIdentity::~NumberIdentity()
	{
		LOG_TRACE( "NumberIdentity::~NumberIdentityFieldConverter" );
		LOG_TRACE( "/NumberIdentity::~NumberIdentityFieldConverter" );
	}

	bool NumberIdentity::convert ( const BYTE* data )
	{
		LOG_TRACE( "NumberIdentity::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/NumberIdentity::convert" );
		return _converted;
	}

	int NumberIdentity::getInt() const
	{
		LOG_TRACE( "NumberIdentity::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/NumberIdentity::getInt" );
		return ret;
	}

	long NumberIdentity::getLong() const
	{
		LOG_TRACE( "NumberIdentity::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/NumberIdentity::getLong" );
		return ret;
	}

	std::string NumberIdentity::getString() const
	{
		LOG_TRACE( "NumberIdentity::getString" );

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
			case 1:
				ret = "Originating ANI";
				break;
			case 2:
				ret = "Terminating";
				break;
			case 3:
				ret = "Originating CPN";
				break;
			case 4:
				ret = "Private Originating ANI";
				break;
			case 5:
				ret = "Private Originating CPN";
				break;
			case 6:
				ret = "Redirecting Number";
				break;
			case 7:
				ret = "Original Called Number";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/NumberIdentity::getString" );
		return ret;
	}
}
