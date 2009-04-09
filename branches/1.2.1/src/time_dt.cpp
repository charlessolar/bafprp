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

#include "time_dt.h"
#include "output.h"

namespace bafprp
{
	const TimeFieldMaker TimeFieldMaker::registerThis;

	IField* TimeFieldMaker::make() const
	{
		return new TimeField;
	}

	TimeField::TimeField() : IField()
	{
		LOG_TRACE( "TimeField::Time" );
		LOG_TRACE( "/TimeField::Time" );
	}


	TimeField::~TimeField()
	{
		LOG_TRACE( "TimeField::~Time" );
		LOG_TRACE( "/TimeField::~Time" );
	}

	bool TimeField::convert ( const BYTE* data )
	{
		LOG_TRACE( "TimeField::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/TimeField::convert" );
		return _converted;
	}

	std::string TimeField::getString() const
	{
		LOG_TRACE( "TimeField::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			std::ostringstream os;
			os << _return[0] << _return[1] << ":" << _return[2] << _return[3] << ":" << _return[4] << _return[5];
			ret = os.str();
		}

		LOG_TRACE( "/TimeField::getString" );
		return ret;
	}
}
