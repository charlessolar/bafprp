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

#include "calltypefieldconverter.h"
#include "output.h"

namespace bafprp
{
	const CallTypeFieldMaker CallTypeFieldMaker::registerThis;

	IFieldConverter* CallTypeFieldMaker::make() const
	{
		LOG_TRACE( "CallTypeFieldMaker::make" );
		LOG_TRACE( "/CallTypeFieldMaker::make" );
		return new CallTypeFieldConverter;
		
	}

	CallTypeFieldConverter::CallTypeFieldConverter() : IFieldConverter()
	{
		LOG_TRACE( "CallTypeFieldConverter::CallTypeFieldConverter" );
		LOG_TRACE( "/CallTypeFieldConverter::CallTypeFieldConverter" );
	}


	CallTypeFieldConverter::~CallTypeFieldConverter()
	{
		LOG_TRACE( "CallTypeFieldConverter::~CallTypeFieldConverter" );
		LOG_TRACE( "/CallTypeFieldConverter::~CallTypeFieldConverter" );
	}

	bool CallTypeFieldConverter::convert ( const BYTE* data )
	{
		LOG_TRACE( "CallTypeFieldConverter::convert" );
		_return = getChars( data, getSize() );
		LOG_TRACE( "/CallTypeFieldConverter::convert" );
		return true;
	}

	int CallTypeFieldConverter::getInt()
	{
		LOG_TRACE( "CallTypeFieldConverter::getInt" );
		LOG_TRACE( "/CallTypeFieldConverter::getInt" );
		return atoi( _return.c_str() );
	}

	long CallTypeFieldConverter::getLong()
	{
		LOG_TRACE( "CallTypeFieldConverter::getLong" );
		LOG_TRACE( "/CallTypeFieldConverter::getLong" );
		return atol( _return.c_str() );
	}

	std::string CallTypeFieldConverter::getString()
	{
		LOG_TRACE( "CallTypeFieldConverter::getString" );
		LOG_TRACE( "/CallTypeFieldConverter::getString" );
		return _return;
	}
}
