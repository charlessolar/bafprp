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

#include "icincindicator.h"
#include "output.h"

namespace bafprp
{
	const ICINCIndicatorFieldMaker ICINCIndicatorFieldMaker::registerThis;

	IField* ICINCIndicatorFieldMaker::make() const
	{
		LOG_TRACE( "ICINCIndicatorFieldMaker::make" );
		LOG_TRACE( "/ICINCIndicatorFieldMaker::make" );
		return new ICINCIndicator;
		
	}

	ICINCIndicator::ICINCIndicator() : IField()
	{
		LOG_TRACE( "ICINCIndicator::ICINCIndicatorFieldConverter" );
		LOG_TRACE( "/ICINCIndicator::ICINCIndicatorFieldConverter" );
	}


	ICINCIndicator::~ICINCIndicator()
	{
		LOG_TRACE( "ICINCIndicator::~ICINCIndicatorFieldConverter" );
		LOG_TRACE( "/ICINCIndicator::~ICINCIndicatorFieldConverter" );
	}

	bool ICINCIndicator::convert ( const BYTE* data )
	{
		LOG_TRACE( "ICINCIndicator::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ICINCIndicator::convert" );
		return _converted;
	}

	int ICINCIndicator::getInt()
	{
		LOG_TRACE( "ICINCIndicator::getInt" );

		int ret;
		if( !_converted )
		{
			_lastError = "Tried to get int before field was converted";
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ICINCIndicator::getInt" );
		return ret;
	}

	long ICINCIndicator::getLong()
	{
		LOG_TRACE( "ICINCIndicator::getLong" );

		long ret;
		if( !_converted )
		{
			_lastError = "Tried to get long before field was converted";
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ICINCIndicator::getLong" );
		return ret;
	}

	std::string ICINCIndicator::getString()
	{
		LOG_TRACE( "ICINCIndicator::getString" );

		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/ICINCIndicator::getString" );
		return ret;
	}
}
