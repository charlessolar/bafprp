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

#include "shortduration_dt.h"
#include "output.h"

namespace bafprp
{
	const ShortDurationFieldMaker ShortDurationFieldMaker::registerThis;

	IField* ShortDurationFieldMaker::make() const
	{
		return new ShortDurationField;
	}

	ShortDurationField::ShortDurationField() : IField()
	{
		LOG_TRACE( "ShortDurationField::ShortDuration" );
		LOG_TRACE( "/ShortDurationField::ShortDuration" );
	}


	ShortDurationField::~ShortDurationField()
	{
		LOG_TRACE( "ShortDurationField::~ShortDuration" );
		LOG_TRACE( "/ShortDurationField::~ShortDuration" );
	}

	bool ShortDurationField::convert ( const BYTE* data )
	{
		LOG_TRACE( "ShortDurationField::convert" );
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

		std::ostringstream os;
		os << milli;
		_return = os.str();

		LOG_TRACE( "/ShortDurationField::convert" );
		return _converted;
	}

	int ShortDurationField::getInt() const
	{
		LOG_TRACE( "ShortDurationField::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ShortDurationField::getInt" );
		return ret;
	}

	long ShortDurationField::getLong() const
	{
		LOG_TRACE( "ShortDurationField::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ShortDurationField::getLong" );
		return ret;
	}

	float ShortDurationField::getFloat() const
	{
		// Return time in seconds
		LOG_TRACE( "ShortDurationField::getFloat" );

		float ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get float before field was converted" );
			ret = 0.0f;
		}
		else
			ret = getInt() / 1000.0f;

		LOG_TRACE( "/ShortDurationField::getFloat" );
		return ret;
	}
	
	std::string ShortDurationField::getString() const
	{
		LOG_TRACE( "ShortDurationField::getString" );

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
			int hours = ( duration / 1000 / 60 / 60 );

			// This is confusing only because I wanted to format it corectly
			// Basically it prefixes a '0' if the value is 1 digit
			os << hours << ":" <<  ( ( minutes < 10 ) ? "0" : "" ) << minutes << ":" << ( ( seconds < 10 ) ? "0" : "" ) << seconds << "." << milli;
			ret = os.str();
			
		}

		LOG_TRACE( "/ShortDurationField::getString" );
		return ret;
	}
}
