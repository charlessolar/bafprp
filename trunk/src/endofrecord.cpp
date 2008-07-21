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

#include "endofrecord.h"
#include "output.h"

namespace bafprp
{
	const EndOfRecordFieldMaker EndOfRecordFieldMaker::registerThis;

	IField* EndOfRecordFieldMaker::make() const
	{
		LOG_TRACE( "EndOfRecordFieldMaker::make" );
		LOG_TRACE( "/EndOfRecordFieldMaker::make" );
		return new EndOfRecord;
		
	}

	EndOfRecord::EndOfRecord() : IField()
	{
		LOG_TRACE( "EndOfRecord::EndOfRecordFieldConverter" );
		LOG_TRACE( "/EndOfRecord::EndOfRecordFieldConverter" );
	}


	EndOfRecord::~EndOfRecord()
	{
		LOG_TRACE( "EndOfRecord::~EndOfRecordFieldConverter" );
		LOG_TRACE( "/EndOfRecord::~EndOfRecordFieldConverter" );
	}

	bool EndOfRecord::convert ( const BYTE* data )
	{
		LOG_TRACE( "EndOfRecord::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/EndOfRecord::convert" );
		return _converted;
	}

	int EndOfRecord::getInt() const
	{
		LOG_TRACE( "EndOfRecord::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/EndOfRecord::getInt" );
		return ret;
	}

	long EndOfRecord::getLong() const
	{
		LOG_TRACE( "EndOfRecord::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/EndOfRecord::getLong" );
		return ret;
	}

	std::string EndOfRecord::getString() const
	{
		LOG_TRACE( "EndOfRecord::getString" );

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
			case 5:
				ret = "Normal";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/EndOfRecord::getString" );
		return ret;
	}
}
