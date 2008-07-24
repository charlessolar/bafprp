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

#include "callcountinfodeliv.h"
#include "output.h"

namespace bafprp
{
	const CallCountInfoDelivFieldMaker CallCountInfoDelivFieldMaker::registerThis;

	IField* CallCountInfoDelivFieldMaker::make() const
	{
		LOG_TRACE( "CallCountInfoDelivFieldMaker::make" );
		LOG_TRACE( "/CallCountInfoDelivFieldMaker::make" );
		return new CallCountInfoDeliv;
		
	}

	CallCountInfoDeliv::CallCountInfoDeliv() : IField()
	{
		LOG_TRACE( "CallCountInfoDeliv::CallCountInfoDelivFieldConverter" );
		LOG_TRACE( "/CallCountInfoDeliv::CallCountInfoDelivFieldConverter" );
	}


	CallCountInfoDeliv::~CallCountInfoDeliv()
	{
		LOG_TRACE( "CallCountInfoDeliv::~CallCountInfoDelivFieldConverter" );
		LOG_TRACE( "/CallCountInfoDeliv::~CallCountInfoDelivFieldConverter" );
	}

	bool CallCountInfoDeliv::convert ( const BYTE* data )
	{
		LOG_TRACE( "CallCountInfoDeliv::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CallCountInfoDeliv::convert" );
		return _converted;
	}

	int CallCountInfoDeliv::getInt() const
	{
		LOG_TRACE( "CallCountInfoDeliv::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/CallCountInfoDeliv::getInt" );
		return ret;
	}

	long CallCountInfoDeliv::getLong() const
	{
		LOG_TRACE( "CallCountInfoDeliv::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/CallCountInfoDeliv::getLong" );
		return ret;
	}

	std::string CallCountInfoDeliv::getString() const
	{
		LOG_TRACE( "CallCountInfoDeliv::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/CallCountInfoDeliv::getString" );
		return ret;
	}
}
