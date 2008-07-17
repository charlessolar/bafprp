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

#include "timingindicator.h"
#include "output.h"

namespace bafprp
{
	const TimingIndicatorFieldMaker TimingIndicatorFieldMaker::registerThis;

	IField* TimingIndicatorFieldMaker::make() const
	{
		LOG_TRACE( "TimingIndicatorFieldMaker::make" );
		LOG_TRACE( "/TimingIndicatorFieldMaker::make" );
		return new TimingIndicator;
		
	}

	TimingIndicator::TimingIndicator() : IField()
	{
		LOG_TRACE( "TimingIndicator::TimingIndicatorFieldConverter" );
		LOG_TRACE( "/TimingIndicator::TimingIndicatorFieldConverter" );
	}


	TimingIndicator::~TimingIndicator()
	{
		LOG_TRACE( "TimingIndicator::~TimingIndicatorFieldConverter" );
		LOG_TRACE( "/TimingIndicator::~TimingIndicatorFieldConverter" );
	}

	bool TimingIndicator::convert ( const BYTE* data )
	{
		LOG_TRACE( "TimingIndicator::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/TimingIndicator::convert" );
		return _converted;
	}

	std::string TimingIndicator::getString() const
	{
		LOG_TRACE( "TimingIndicator::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			ret = "";
			switch( _return[1] )
			{
			case '0':
				ret += "Default";
				break;
			case '2':
				ret += "Timing guard condition";
				break;
			case '4':
				ret += "Unanswered call release";
				break;
			default:
				ret += "Unknown " + _return;
			}
			ret += " : ";
			switch( _return[2] )
			{
			case '0':
				ret += "Default";
				break;
			case '1':
				ret += "Short called party off hook";
				break;
			default:
				ret += "Unknown " + _return;
			}
			ret += " : ";
			switch( _return[3] )
			{
			case '0':
				ret += "Default";
				break;
			case '1':
				ret += "Start of long duration call";
				break;
			case '2':
				ret += "Continuation of long duration call";
				break;
			case '3':
				ret += "Service capability series: deactivation";
				break;
			default:
				ret += "Unknown " + _return;
			}
		}

		LOG_TRACE( "/TimingIndicator::getString" );
		return ret;
	}
}
