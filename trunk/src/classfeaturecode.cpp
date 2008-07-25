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

#include "classfeaturecode.h"
#include "output.h"

namespace bafprp
{
	const ClassFeatureCodeFieldMaker ClassFeatureCodeFieldMaker::registerThis;

	IField* ClassFeatureCodeFieldMaker::make() const
	{
		LOG_TRACE( "ClassFeatureCodeFieldMaker::make" );
		LOG_TRACE( "/ClassFeatureCodeFieldMaker::make" );
		return new ClassFeatureCode;
		
	}

	ClassFeatureCode::ClassFeatureCode() : IField()
	{
		LOG_TRACE( "ClassFeatureCode::ClassFeatureCodeFieldConverter" );
		LOG_TRACE( "/ClassFeatureCode::ClassFeatureCodeFieldConverter" );
	}


	ClassFeatureCode::~ClassFeatureCode()
	{
		LOG_TRACE( "ClassFeatureCode::~ClassFeatureCodeFieldConverter" );
		LOG_TRACE( "/ClassFeatureCode::~ClassFeatureCodeFieldConverter" );
	}

	bool ClassFeatureCode::convert ( const BYTE* data )
	{
		LOG_TRACE( "ClassFeatureCode::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ClassFeatureCode::convert" );
		return _converted;
	}

	int ClassFeatureCode::getInt() const
	{
		LOG_TRACE( "ClassFeatureCode::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ClassFeatureCode::getInt" );
		return ret;
	}

	long ClassFeatureCode::getLong() const
	{
		LOG_TRACE( "ClassFeatureCode::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ClassFeatureCode::getLong" );
		return ret;
	}

	std::string ClassFeatureCode::getString() const
	{
		LOG_TRACE( "ClassFeatureCode::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/ClassFeatureCode::getString" );
		return ret;
	}
}
