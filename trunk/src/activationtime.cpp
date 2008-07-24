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

#include "ActivationTime.h"
#include "output.h"

namespace bafprp
{
	const ActivationTimeFieldMaker ActivationTimeFieldMaker::registerThis;

	IField* ActivationTimeFieldMaker::make() const
	{
		LOG_TRACE( "ActivationTimeFieldMaker::make" );
		LOG_TRACE( "/ActivationTimeFieldMaker::make" );
		return new ActivationTime;
		
	}

	ActivationTime::ActivationTime() : IField()
	{
		LOG_TRACE( "ActivationTime::ActivationTimeFieldConverter" );
		LOG_TRACE( "/ActivationTime::ActivationTimeFieldConverter" );
	}


	ActivationTime::~ActivationTime()
	{
		LOG_TRACE( "ActivationTime::~ActivationTimeFieldConverter" );
		LOG_TRACE( "/ActivationTime::~ActivationTimeFieldConverter" );
	}

	bool ActivationTime::convert ( const BYTE* data )
	{
		LOG_TRACE( "ActivationTime::convert" );
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

		LOG_TRACE( "/ActivationTime::convert" );
		return _converted;
	}

	int ActivationTime::getInt() const
	{
		LOG_TRACE( "ActivationTime::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ActivationTime::getInt" );
		return ret;
	}

	long ActivationTime::getLong() const
	{
		LOG_TRACE( "ActivationTime::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ActivationTime::getLong" );
		return ret;
	}

	float ActivationTime::getFloat() const
	{
		// Return time in seconds
		LOG_TRACE( "ActivationTime::getFloat" );

		float ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get float before field was converted" );
			ret = 0.0f;
		}
		else
			ret = getInt() / 1000.0f;

		LOG_TRACE( "/ActivationTime::getFloat" );
		return ret;
	}

	std::string ActivationTime::getString() const
	{
		LOG_TRACE( "ActivationTime::getString" );

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

			int ActivationTime = getInt();

			int milli = ( ActivationTime % 1000 ) / 100;  // divide by 100 since our ms will always be 1 digit ( we dont need a 3 digit float )
			int seconds = ( ActivationTime / 1000 ) % 60;
			int minutes = ( ActivationTime / 1000 / 60 ) % 60;
			int hours = ( ActivationTime / 1000 / 60 / 60);

			
			os << hours << ":" <<  ( ( minutes < 10 ) ? "0" : "" ) << minutes << ":" << ( ( seconds < 10 ) ? "0" : "" ) << seconds << "." << milli;
			ret = os.str();
			
		}

		LOG_TRACE( "/ActivationTime::getString" );
		return ret;
	}
}
