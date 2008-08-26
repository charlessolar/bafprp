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

#include "lrn.h"
#include "output.h"

namespace bafprp
{
	const LRNFieldMaker LRNFieldMaker::registerThis;

	IField* LRNFieldMaker::make() const
	{
		LOG_TRACE( "LRNFieldMaker::make" );
		LOG_TRACE( "/LRNFieldMaker::make" );
		return new LRN;
		
	}

	LRN::LRN() : IField()
	{
		LOG_TRACE( "LRN::LRNFieldConverter" );
		LOG_TRACE( "/LRN::LRNFieldConverter" );
	}


	LRN::~LRN()
	{
		LOG_TRACE( "LRN::~LRNFieldConverter" );
		LOG_TRACE( "/LRN::~LRNFieldConverter" );
	}

	bool LRN::convert ( const BYTE* data )
	{
		LOG_TRACE( "LRN::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/LRN::convert" );
		return _converted;
	}

	int LRN::getInt() const
	{
		LOG_TRACE( "LRN::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/LRN::getInt" );
		return ret;
	}

	long LRN::getLong() const
	{
		LOG_TRACE( "LRN::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/LRN::getLong" );
		return ret;
	}

	std::string LRN::getString() const
	{
		LOG_TRACE( "LRN::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/LRN::getString" );
		return ret;
	}
}
