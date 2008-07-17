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

//#include <iomanip>
#include <ios>

#include "duration.h"
#include "output.h"

namespace bafprp
{
	const DurationFieldMaker DurationFieldMaker::registerThis;

	IField* DurationFieldMaker::make() const
	{
		LOG_TRACE( "DurationFieldMaker::make" );
		LOG_TRACE( "/DurationFieldMaker::make" );
		return new Duration;
		
	}

	Duration::Duration() : IField()
	{
		LOG_TRACE( "Duration::DurationFieldConverter" );
		LOG_TRACE( "/Duration::DurationFieldConverter" );
	}


	Duration::~Duration()
	{
		LOG_TRACE( "Duration::~DurationFieldConverter" );
		LOG_TRACE( "/Duration::~DurationFieldConverter" );
	}

	bool Duration::convert ( const BYTE* data )
	{
		LOG_TRACE( "Duration::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}
		if( _return[0] != '0' )
		{
			_lastError = "Badly formated field";
			_converted = false;
		}

		// in milliseconds

												// Fractions of a second
		int milli = atoi( _return.substr( _return.length() - 1 ).c_str() ) * 100;
												// Seconds
		milli += atoi( _return.substr( _return.length() - 3, 2 ).c_str() ) * 1000;
												// Minutes
		milli += atoi( _return.substr( _return.length() - 5, 2 ).c_str() ) * 60 * 1000;
												// Hours  - 3 digits are reserved for hours
		milli += atoi( _return.substr( _return.length() - 8, 3 ).c_str() ) * 60 * 60 * 1000;
		std::ostringstream os;
		os << milli;
		_return = os.str();

		LOG_TRACE( "/Duration::convert" );
		return _converted;
	}

	int Duration::getInt() const
	{
		LOG_TRACE( "Duration::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/Duration::getInt" );
		return ret;
	}

	long Duration::getLong() const
	{
		LOG_TRACE( "Duration::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/Duration::getLong" );
		return ret;
	}

	float Duration::getFloat() const
	{
		// Return time in seconds
		LOG_TRACE( "Duration::getFloat" );

		float ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get float before field was converted" );
			ret = 0.0f;
		}
		else
			ret = getInt() / 1000.0f;

		LOG_TRACE( "/Duration::getFloat" );
		return ret;
	}

	std::string Duration::getString() const
	{
		LOG_TRACE( "Duration::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			std::ostringstream os;
			os.setf( std::ios::fixed, std::ios::floatfield);
			os.precision( 1 );

			int duration = getInt();

			int milli = ( duration % 1000 ) / 100;  // divide by 100 since our ms will always be 1 digit ( we dont need a 3 digit float )
			int seconds = ( duration / 1000 ) % 60;
			int minutes = ( duration / 1000 / 60 ) % 60;
			int hours = ( duration / 1000 / 60 / 60);

			
			os << hours << ":" <<  ( ( minutes < 10 ) ? "0" : "" ) << minutes << ":" << ( ( seconds < 10 ) ? "0" : "" ) << seconds << "." << milli;
			ret = os.str();
			
		}

		LOG_TRACE( "/Duration::getString" );
		return ret;
	}
}
