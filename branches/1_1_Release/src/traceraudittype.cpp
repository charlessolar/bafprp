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

#include "traceraudittype.h"
#include "output.h"

namespace bafprp
{
	const TracerAuditTypeFieldMaker TracerAuditTypeFieldMaker::registerThis;

	IField* TracerAuditTypeFieldMaker::make() const
	{
		LOG_TRACE( "TracerAuditTypeFieldMaker::make" );
		return new TracerAuditType();
		LOG_TRACE( "TracerAuditTypeFieldMaker::make" );
	}

	TracerAuditType::TracerAuditType() : IField()
	{
		LOG_TRACE( "TracerAuditType::TracerAuditType" );
		LOG_TRACE( "/TracerAuditType::TracerAuditType" );
	}


	TracerAuditType::~TracerAuditType()
	{
		LOG_TRACE( "TracerAuditType::~TracerAuditType" );
		LOG_TRACE( "/TracerAuditType::~TracerAuditType" );
	}

	bool TracerAuditType::convert ( const BYTE* data )
	{
		LOG_TRACE( "TracerAuditType::convert" );
		
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/TracerAuditType::convert" );
		return _converted;
	}

	long TracerAuditType::getLong() const
	{
		LOG_TRACE( "TracerAuditType::getLong" );
		
		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/TracerAuditType::getLong" );
		return ret;
	}

	int TracerAuditType::getInt() const
	{
		LOG_TRACE( "TracerAuditType::getInt" );
		
		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/TracerAuditType::getInt" );
		return ret;
	}

	std::string TracerAuditType::getString() const
	{
		LOG_TRACE( "TracerAuditType::getString" );
		
		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			int type = getInt();
			std::string sType;
			switch( type )
			{
			case 7:
				ret = "Transfer in";
				break;
			case 8:
				ret = "End of recording";
				break;
			case 52:
				ret = "Hourly AMA audit";
				break;
			default:
				ret = "Unknown Type " + type;
			}
		}

		LOG_TRACE( "/TracerAuditType::getString" );
		return ret;
	}
}