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

#include "icinccalleventstatus.h"
#include "output.h"

namespace bafprp
{
	const ICINCCallEventStatusFieldMaker ICINCCallEventStatusFieldMaker::registerThis;

	IField* ICINCCallEventStatusFieldMaker::make() const
	{
		LOG_TRACE( "ICINCCallEventStatusFieldMaker::make" );
		LOG_TRACE( "/ICINCCallEventStatusFieldMaker::make" );
		return new ICINCCallEventStatus;
		
	}

	ICINCCallEventStatus::ICINCCallEventStatus() : IField()
	{
		LOG_TRACE( "ICINCCallEventStatus::ICINCCallEventStatusFieldConverter" );
		LOG_TRACE( "/ICINCCallEventStatus::ICINCCallEventStatusFieldConverter" );
	}


	ICINCCallEventStatus::~ICINCCallEventStatus()
	{
		LOG_TRACE( "ICINCCallEventStatus::~ICINCCallEventStatusFieldConverter" );
		LOG_TRACE( "/ICINCCallEventStatus::~ICINCCallEventStatusFieldConverter" );
	}

	bool ICINCCallEventStatus::convert ( const BYTE* data )
	{
		LOG_TRACE( "ICINCCallEventStatus::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ICINCCallEventStatus::convert" );
		return _converted;
	}

	int ICINCCallEventStatus::getInt()
	{
		LOG_TRACE( "ICINCCallEventStatus::getInt" );

		int ret;
		if( !_converted )
		{
			_lastError = "Tried to get int before field was converted";
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ICINCCallEventStatus::getInt" );
		return ret;
	}

	long ICINCCallEventStatus::getLong()
	{
		LOG_TRACE( "ICINCCallEventStatus::getLong" );

		long ret;
		if( !_converted )
		{
			_lastError = "Tried to get long before field was converted";
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ICINCCallEventStatus::getLong" );
		return ret;
	}

	std::string ICINCCallEventStatus::getString()
	{
		LOG_TRACE( "ICINCCallEventStatus::getString" );

		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/ICINCCallEventStatus::getString" );
		return ret;
	}
}
