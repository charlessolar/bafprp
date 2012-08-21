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

#include "amadns_dt.h"
#include "output.h"

namespace bafprp
{
	const AmaDnsFieldMaker AmaDnsFieldMaker::registerThis;

	IField* AmaDnsFieldMaker::make() const
	{
		return new AmaDnsField;
	}

	AmaDnsField::AmaDnsField() : IField()
	{
		LOG_TRACE( "AmaDnsField::AmaDns" );
		LOG_TRACE( "/AmaDnsField::AmaDns" );
	}


	AmaDnsField::~AmaDnsField()
	{
		LOG_TRACE( "AmaDnsField::~AmaDns" );
		LOG_TRACE( "/AmaDnsField::~AmaDns" );
	}

	bool AmaDnsField::convert( const BYTE* data )
	{
		LOG_TRACE( "AmaDnsField::convert" );

		int low = atoi( getProperty( "low", true ).c_str() );
		int high = atoi( getProperty( "high", true ).c_str() );
		int bytes = atoi( getProperty( "bytes", true ).c_str() );

		_return = decodeBytes( data, bytes, high, low );
		_converted = true;

		LOG_TRACE( "/AmaDnsField::convert" );
		return _converted;
	}

	int AmaDnsField::getInt() const
	{
		LOG_TRACE( "AmaDnsField::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/AmaDnsField::getInt" );
		return ret;
	}

	long AmaDnsField::getLong() const
	{
		LOG_TRACE( "AmaDnsField::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/AmaDnsField::getLong" );
		return ret;
	}
	
	std::string AmaDnsField::getString() const
	{
		LOG_TRACE( "AmaDnsField::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			// Trim leading zeros?
			bool trim = ( getProperty( "trim", true ) == "true" );
			if( !trim )	ret = _return;
			else
			{
				ret = _return;
				std::string::size_type pos = ret.find_first_not_of('0');
				if(pos != std::string::npos) 
					ret.erase(0, pos);
				else 
					ret.erase(ret.begin(), ret.end());
			}
		}

		LOG_TRACE( "/AmaDnsField::getString" );
		return ret;
	}
}
