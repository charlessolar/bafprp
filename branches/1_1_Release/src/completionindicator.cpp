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

#include "completionindicator.h"
#include "output.h"

namespace bafprp
{
	const CompletionIndicatorFieldMaker CompletionIndicatorFieldMaker::registerThis;

	IField* CompletionIndicatorFieldMaker::make() const
	{
		LOG_TRACE( "CompletionIndicatorFieldMaker::make" );
		LOG_TRACE( "/CompletionIndicatorFieldMaker::make" );
		return new CompletionIndicator;
		
	}

	CompletionIndicator::CompletionIndicator() : IField()
	{
		LOG_TRACE( "CompletionIndicator::CompletionIndicatorFieldConverter" );
		LOG_TRACE( "/CompletionIndicator::CompletionIndicatorFieldConverter" );
	}


	CompletionIndicator::~CompletionIndicator()
	{
		LOG_TRACE( "CompletionIndicator::~CompletionIndicatorFieldConverter" );
		LOG_TRACE( "/CompletionIndicator::~CompletionIndicatorFieldConverter" );
	}

	bool CompletionIndicator::convert ( const BYTE* data )
	{
		LOG_TRACE( "CompletionIndicator::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CompletionIndicator::convert" );
		return _converted;
	}

	int CompletionIndicator::getInt() const
	{
		LOG_TRACE( "CompletionIndicator::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/CompletionIndicator::getInt" );
		return ret;
	}

	long CompletionIndicator::getLong() const
	{
		LOG_TRACE( "CompletionIndicator::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/CompletionIndicator::getLong" );
		return ret;
	}

	std::string CompletionIndicator::getString() const
	{
		LOG_TRACE( "CompletionIndicator::getString" );

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
			case 1:
				ret = "Connect";
				break;
			case 2:
				ret = "Billing Failure";
				break;
			case 3:
				ret = "Setup restrictions table";
				break;
			case 4:
				ret = "Person requested call not available";
				break;
			case 5:
				ret = "No circuits";
				break;
			case 6:
				ret = "Ringing";
				break;
			case 7:
				ret = "Busy";
				break;
			case 8:
				ret = "No answer supervision returned";
				break;
			case 9:
				ret = "AIN pre-final route record - completed";
				break;
			case 10:
				ret = "AIN pre-final route record - not completed";
				break;
			case 11:
				ret = "AIN SCP requested release time";
				break;
			case 12:
				ret = "Network failure";
				break;
			case 13:
				ret = "Caller aborted";
				break;
			case 14:
				ret = "AIN pre-final route - NEL follows";
				break;
			case 15:
				ret = "Call sent to treatment";
				break;
			case 16:
				ret = "RTP OSS redirected";
				break;
			case 60:
				ret = "Record closed - subsequent SDS record";
				break;
			case 999:
				ret = "Not Used";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}
    
		LOG_TRACE( "/CompletionIndicator::getString" );
		return ret;
	}
}
