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

#include "number_switch_dt.h"
#include "output.h"

namespace bafprp
{
	const NumberSwitchFieldMaker NumberSwitchFieldMaker::registerThis;

	IField* NumberSwitchFieldMaker::make() const
	{
		return new NumberSwitchField;
	}

	NumberSwitchField::NumberSwitchField() : IField()
	{
		LOG_TRACE( "NumberSwitchField::NumberSwitch" );
		_replaceProperties.push_back( "number_only" );

		LOG_TRACE( "/NumberSwitchField::NumberSwitch" );
	}


	NumberSwitchField::~NumberSwitchField()
	{
		LOG_TRACE( "NumberSwitchField::~NumberSwitch" );
		LOG_TRACE( "/NumberSwitchField::~NumberSwitch" );
	}

	bool NumberSwitchField::convert ( const BYTE* data )
	{
		LOG_TRACE( "NumberSwitchField::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/NumberSwitchField::convert" );
		return _converted;
	}

	int NumberSwitchField::getInt() const
	{
		LOG_TRACE( "NumberSwitchField::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
		{
			property_map::const_iterator only_number = _properties.find( "number_only" );
			property_map::const_iterator number = _properties.find( "number" );
			if( only_number != _properties.end() && ( only_number->second == "true" || only_number->second == "yes" ) && number != _properties.end() )
			{
				// Subtract 48 because '0' is 48 in ascii.  We are cheating to convert a char to an int
				ret = atoi( _return.substr( number->second[0] - 48, number->second[1] - 48 ).c_str() );
			}
			else
				ret = atoi( _return.c_str() );
		}

		LOG_TRACE( "/NumberSwitchField::getInt" );
		return ret;
	}

	long NumberSwitchField::getLong() const
	{
		LOG_TRACE( "NumberSwitchField::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
		{
			property_map::const_iterator only_number = _properties.find( "number_only" );
			property_map::const_iterator number = _properties.find( "number" );
			if( only_number != _properties.end() && ( only_number->second == "true" || only_number->second == "yes" ) && number != _properties.end() )
			{
				ret = atol(  _return.substr( number->second[0] - 48, number->second[1] - 48 ).c_str() );
			}
			else
				ret = atol( _return.c_str() );
		}

		LOG_TRACE( "/NumberSwitchField::getLong" );
		return ret;
	}
	
	std::string NumberSwitchField::getString() const
	{
		LOG_TRACE( "NumberSwitchField::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			props_pair switches = _properties.equal_range( "switch" );
			std::string sw;
			if( switches.first == switches.second )
			{
				// No "switch" property so assume we switch on character 0
				sw = "0" + _return;
				sw.resize( 2 );
				property_map::const_iterator string = _properties.find( sw );
				if( string != _properties.end() )
					ret = string->second + " ";
				else
					ret = "Unknown: " + sw;
			}
			else
			{
				for( property_map::const_iterator pos = switches.first; pos != switches.second; pos++ )
				{
					sw = pos->second + (char*)&_return[ atoi( pos->second.c_str() ) ];
					sw.resize(2);
					property_map::const_iterator string = _properties.find( sw );
					if( string != _properties.end() )
						ret += string->second + " : ";
					else
						ret += "Unknown: " + sw.substr(1) + " : ";
				}
			}

			props_pair numbers = _properties.equal_range( "number" );
			if( numbers.first != numbers.second )
			{
				for( property_map::const_iterator number = numbers.first; number != numbers.second; number++ )
				{
					ret += _return.substr( number->second[0] - 48, number->second[1] - 48 ) + " : ";
				}
			}
			else
			{
				LOG_WARN( "No 'number' property found in this numberswitch data type" );
			}
			ret.resize( ret.length() - 3 ); // Trim off last ':'
		}

		LOG_TRACE( "/NumberSwitchField::getString" );
		return ret;
	}
}
