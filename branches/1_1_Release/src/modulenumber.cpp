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

#include "modulenumber.h"
#include "output.h"

namespace bafprp
{
	const ModuleNumberFieldMaker ModuleNumberFieldMaker::registerThis;

	IField* ModuleNumberFieldMaker::make() const
	{
		LOG_TRACE( "ModuleNumberFieldMaker::make" );
		LOG_TRACE( "/ModuleNumberFieldMaker::make" );
		return new ModuleNumber;
		
	}

	ModuleNumber::ModuleNumber() : IField()
	{
		LOG_TRACE( "ModuleNumber::ModuleNumberFieldConverter" );
		LOG_TRACE( "/ModuleNumber::ModuleNumberFieldConverter" );
	}


	ModuleNumber::~ModuleNumber()
	{
		LOG_TRACE( "ModuleNumber::~ModuleNumberFieldConverter" );
		LOG_TRACE( "/ModuleNumber::~ModuleNumberFieldConverter" );
	}

	bool ModuleNumber::convert ( const BYTE* data )
	{
		LOG_TRACE( "ModuleNumber::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ModuleNumber::convert" );
		return _converted;
	}

	int ModuleNumber::getInt() const
	{
		LOG_TRACE( "ModuleNumber::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ModuleNumber::getInt" );
		return ret;
	}

	long ModuleNumber::getLong() const
	{
		LOG_TRACE( "ModuleNumber::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ModuleNumber::getLong" );
		return ret;
	}

	std::string ModuleNumber::getString() const
	{
		LOG_TRACE( "ModuleNumber::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/ModuleNumber::getString" );
		return ret;
	}
}
