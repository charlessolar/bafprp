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

#include "flaggedbafrecords.h"
#include "output.h"

namespace bafprp
{
	const FlaggedBafRecordsFieldMaker FlaggedBafRecordsFieldMaker::registerThis;

	IField* FlaggedBafRecordsFieldMaker::make() const
	{
		LOG_TRACE( "FlaggedBafRecordsFieldMaker::make" );
		LOG_TRACE( "/FlaggedBafRecordsFieldMaker::make" );
		return new FlaggedBafRecords;
		
	}

	FlaggedBafRecords::FlaggedBafRecords() : IField()
	{
		LOG_TRACE( "FlaggedBafRecords::FlaggedBafRecordsFieldConverter" );
		LOG_TRACE( "/FlaggedBafRecords::FlaggedBafRecordsFieldConverter" );
	}


	FlaggedBafRecords::~FlaggedBafRecords()
	{
		LOG_TRACE( "FlaggedBafRecords::~FlaggedBafRecordsFieldConverter" );
		LOG_TRACE( "/FlaggedBafRecords::~FlaggedBafRecordsFieldConverter" );
	}

	bool FlaggedBafRecords::convert ( const BYTE* data )
	{
		LOG_TRACE( "FlaggedBafRecords::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/FlaggedBafRecords::convert" );
		return _converted;
	}

	int FlaggedBafRecords::getInt() const
	{
		LOG_TRACE( "FlaggedBafRecords::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/FlaggedBafRecords::getInt" );
		return ret;
	}

	long FlaggedBafRecords::getLong() const
	{
		LOG_TRACE( "FlaggedBafRecords::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/FlaggedBafRecords::getLong" );
		return ret;
	}

	std::string FlaggedBafRecords::getString() const
	{
		LOG_TRACE( "FlaggedBafRecords::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/FlaggedBafRecords::getString" );
		return ret;
	}
}
