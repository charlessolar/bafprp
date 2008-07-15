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

#include "calltype.h"
#include "output.h"

namespace bafprp
{
	const CallTypeFieldMaker CallTypeFieldMaker::registerThis;

	IField* CallTypeFieldMaker::make() const
	{
		LOG_TRACE( "CallTypeFieldMaker::make" );
		LOG_TRACE( "/CallTypeFieldMaker::make" );
		return new CallType;
		
	}

	CallType::CallType() : IField()
	{
		LOG_TRACE( "CallType::CallTypeFieldConverter" );
		LOG_TRACE( "/CallType::CallTypeFieldConverter" );
	}


	CallType::~CallType()
	{
		LOG_TRACE( "CallType::~CallTypeFieldConverter" );
		LOG_TRACE( "/CallType::~CallTypeFieldConverter" );
	}

	bool CallType::convert ( const BYTE* data )
	{
		LOG_TRACE( "CallType::convert" );
		_return = getChars( data, getSize() );
		LOG_TRACE( "/CallType::convert" );
		return true;
	}

	int CallType::getInt()
	{
		LOG_TRACE( "CallType::getInt" );
		LOG_TRACE( "/CallType::getInt" );
		return atoi( _return.c_str() );
	}

	long CallType::getLong()
	{
		LOG_TRACE( "CallType::getLong" );
		LOG_TRACE( "/CallType::getLong" );
		return atol( _return.c_str() );
	}

	std::string CallType::getString()
	{
		LOG_TRACE( "CallType::getString" );
		LOG_TRACE( "/CallType::getString" );
		return _return;
	}
}
