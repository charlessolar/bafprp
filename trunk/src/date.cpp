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

#include "date.h"
#include "output.h"

namespace bafprp
{
	const DateFieldMaker DateFieldMaker::registerThis;

	IField* DateFieldMaker::make() const
	{
		LOG_TRACE( "DateFieldMaker::make" );
		return new Date();
		LOG_TRACE( "DateFieldMaker::make" );
	}

	Date::Date() : IField()
	{
		LOG_TRACE( "Date::Date" );
		LOG_TRACE( "/Date::Date" );
	}


	Date::~Date()
	{
		LOG_TRACE( "Date::~Date" );
		LOG_TRACE( "/Date::~Date" );
	}

	bool Date::convert ( const BYTE* data )
	{
		LOG_TRACE( "Date::convert" );
		_return = getChars( data, getSize() );
		LOG_TRACE( "/Date::convert" );
		return true;
	}

	long Date::getLong()
	{
		LOG_TRACE( "Date::getLong" );
		LOG_TRACE( "/Date::getLong" );
		return atol( _return.c_str() );
	}

	int Date::getInt()
	{
		LOG_TRACE( "Date::getInt" );
		LOG_TRACE( "/Date::getInt" );
		return atoi( _return.c_str() );
	}

	std::string Date::getString()
	{
		LOG_TRACE( "Date::getString" );
		LOG_TRACE( "/Date::getString" );
		return _return;
	}
}