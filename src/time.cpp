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

#include "time.h"
#include "output.h"

namespace bafprp
{
	const TimeFieldMaker TimeFieldMaker::registerThis;

	IField* TimeFieldMaker::make() const
	{
		LOG_TRACE( "TimeFieldMaker::make" );
		return new Time();
		LOG_TRACE( "TimeFieldMaker::make" );
	}

	Time::Time() : IField()
	{
		LOG_TRACE( "Time::Time" );
		LOG_TRACE( "/Time::Time" );
	}


	Time::~Time()
	{
		LOG_TRACE( "Time::~Time" );
		LOG_TRACE( "/Time::~Time" );
	}

	bool Time::convert ( const BYTE* data )
	{
		LOG_TRACE( "Time::convert" );
		_return = getChars( data, getSize() );
		LOG_TRACE( "/Time::convert" );
		return true;
	}

	long Time::getLong()
	{
		LOG_TRACE( "Time::getLong" );
		LOG_TRACE( "/Time::getLong" );
		return atol( _return.c_str() );
	}

	int Time::getInt()
	{
		LOG_TRACE( "Time::getInt" );
		LOG_TRACE( "/Time::getInt" );
		return atoi( _return.c_str() );
	}

	std::string Time::getString()
	{
		LOG_TRACE( "Time::getString" );
		LOG_TRACE( "/Time::getString" );
		return _return;
	}
}