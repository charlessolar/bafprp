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

#include "classfunctions.h"
#include "output.h"

namespace bafprp
{
	const ClassFunctionsFieldMaker ClassFunctionsFieldMaker::registerThis;

	IField* ClassFunctionsFieldMaker::make() const
	{
		LOG_TRACE( "ClassFunctionsFieldMaker::make" );
		LOG_TRACE( "/ClassFunctionsFieldMaker::make" );
		return new ClassFunctions;
		
	}

	ClassFunctions::ClassFunctions() : IField()
	{
		LOG_TRACE( "ClassFunctions::ClassFunctionsFieldConverter" );
		LOG_TRACE( "/ClassFunctions::ClassFunctionsFieldConverter" );
	}


	ClassFunctions::~ClassFunctions()
	{
		LOG_TRACE( "ClassFunctions::~ClassFunctionsFieldConverter" );
		LOG_TRACE( "/ClassFunctions::~ClassFunctionsFieldConverter" );
	}

	bool ClassFunctions::convert ( const BYTE* data )
	{
		LOG_TRACE( "ClassFunctions::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ClassFunctions::convert" );
		return _converted;
	}

	int ClassFunctions::getInt() const
	{
		LOG_TRACE( "ClassFunctions::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ClassFunctions::getInt" );
		return ret;
	}

	long ClassFunctions::getLong() const
	{
		LOG_TRACE( "ClassFunctions::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ClassFunctions::getLong" );
		return ret;
	}

	std::string ClassFunctions::getString() const
	{
		LOG_TRACE( "ClassFunctions::getString" );

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
			case 0:
				ret = "None";
				break;
			case 1:
				ret = "Active";
				break;
			case 2:
				ret = "Inactive";
				break;
			case 3:
				ret = "Delete";
				break;
			case 4:
				ret = "Create active";
				break;
			case 5:
				ret = "Create inactive";
				break;
			case 6:
				ret = "Session aborted";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/ClassFunctions::getString" );
		return ret;
	}
}
