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

#include "abortedbafrecords.h"
#include "output.h"

namespace bafprp
{
	const AbortedBafRecordsFieldMaker AbortedBafRecordsFieldMaker::registerThis;

	IField* AbortedBafRecordsFieldMaker::make() const
	{
		LOG_TRACE( "AbortedBafRecordsFieldMaker::make" );
		LOG_TRACE( "/AbortedBafRecordsFieldMaker::make" );
		return new AbortedBafRecords;
		
	}

	AbortedBafRecords::AbortedBafRecords() : IField()
	{
		LOG_TRACE( "AbortedBafRecords::AbortedBafRecordsFieldConverter" );
		LOG_TRACE( "/AbortedBafRecords::AbortedBafRecordsFieldConverter" );
	}


	AbortedBafRecords::~AbortedBafRecords()
	{
		LOG_TRACE( "AbortedBafRecords::~AbortedBafRecordsFieldConverter" );
		LOG_TRACE( "/AbortedBafRecords::~AbortedBafRecordsFieldConverter" );
	}

	bool AbortedBafRecords::convert ( const BYTE* data )
	{
		LOG_TRACE( "AbortedBafRecords::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/AbortedBafRecords::convert" );
		return _converted;
	}

	int AbortedBafRecords::getInt() const
	{
		LOG_TRACE( "AbortedBafRecords::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/AbortedBafRecords::getInt" );
		return ret;
	}

	long AbortedBafRecords::getLong() const
	{
		LOG_TRACE( "AbortedBafRecords::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/AbortedBafRecords::getLong" );
		return ret;
	}

	std::string AbortedBafRecords::getString() const
	{
		LOG_TRACE( "AbortedBafRecords::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/AbortedBafRecords::getString" );
		return ret;
	}
}
