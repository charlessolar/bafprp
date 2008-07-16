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

#include "recordofficeid.h"
#include "output.h"

namespace bafprp
{
	const RecordOfficeIDFieldMaker RecordOfficeIDFieldMaker::registerThis;

	IField* RecordOfficeIDFieldMaker::make() const
	{
		LOG_TRACE( "RecordOfficeIDFieldMaker::make" );
		return new RecordOfficeID();
		LOG_TRACE( "RecordOfficeIDFieldMaker::make" );
	}

	RecordOfficeID::RecordOfficeID() : IField()
	{
		LOG_TRACE( "RecordOfficeID::RecordOfficeID" );
		LOG_TRACE( "/RecordOfficeID::RecordOfficeID" );
	}


	RecordOfficeID::~RecordOfficeID()
	{
		LOG_TRACE( "RecordOfficeID::~RecordOfficeID" );
		LOG_TRACE( "/RecordOfficeID::~RecordOfficeID" );
	}

	bool RecordOfficeID::convert ( const BYTE* data )
	{
		LOG_TRACE( "RecordOfficeID::convert" );

		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/RecordOfficeID::convert" );
		return _converted;
	}

	long RecordOfficeID::getLong()
	{
		LOG_TRACE( "RecordOfficeID::getLong" );
		
		long ret;
		if( !_converted )
		{
			_lastError = "Tried to get long before field was converted";
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/RecordOfficeID::getLong" );
		return ret;
	}

	int RecordOfficeID::getInt()
	{
		LOG_TRACE( "RecordOfficeID::getInt" );
		
		int ret;
		if( !_converted )
		{
			_lastError = "Tried to get int before field was converted";
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/RecordOfficeID::getInt" );
		return ret;
	}

	std::string RecordOfficeID::getString()
	{
		LOG_TRACE( "RecordOfficeID::getString" );
		
		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/RecordOfficeID::getString" );
		return ret;
	}
}