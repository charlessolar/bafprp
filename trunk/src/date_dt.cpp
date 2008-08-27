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

#include <time.h>

#include "date_dt.h"
#include "output.h"

namespace bafprp
{
	const DateFieldMaker DateFieldMaker::registerThis;

	IField* DateFieldMaker::make() const
	{
		return new DateField;
	}

	DateField::DateField() : IField()
	{
		LOG_TRACE( "DateField::Date" );
		_replaceProperties.push_back( "format" );
		LOG_TRACE( "/DateField::Date" );
	}


	DateField::~DateField()
	{
		LOG_TRACE( "DateField::~Date" );
		LOG_TRACE( "/DateField::~Date" );
	}

	bool DateField::convert ( const BYTE* data )
	{
		LOG_TRACE( "DateField::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/DateField::convert" );
		return _converted;
	}

	std::string DateField::getString() const
	{
		LOG_TRACE( "DateField::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			char year[5] = "";
			time_t ltime; 
			struct tm* mytm;
			ltime = time( NULL );  
			mytm = localtime( &ltime );  
			strftime( year, sizeof( year ), "%Y", mytm );
			year[3] = _return[0];

			
			property_map::const_iterator itr = _properties.find( "format" );
			if( itr != _properties.end() && itr->second.find( "Y" ) != std::string::npos && itr->second.find( "M" ) != std::string::npos && itr->second.find( "D" ) != std::string::npos )
			{
				ret = itr->second;
				ret.replace( ret.find("Y"), strlen( year ), year );
				ret.replace( ret.find("M"), 1, _return.substr(1,2) );
				ret.replace( ret.find("D"), 1, _return.substr(3,2) );
			}
			else
			{
				std::ostringstream os;
				os << year << "-" << _return[1] << _return[2] << "-" << _return[3] << _return[4];
				ret = os.str();
			}
		}

		LOG_TRACE( "/DateField::getString" );
		return ret;
	}
}
