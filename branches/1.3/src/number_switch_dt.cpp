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

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = "0";
		}
		else
		{
			bool only_number = ( getProperty( "number_only", true ) == "true" );
			std::vector<std::string> numbers = getProperty( "number" );
			if( only_number )
			{
				for( std::vector<std::string>::iterator itr = numbers.begin(); itr != numbers.end(); itr++ )
				{
				
					// Subtract 48 because '0' is 48 in ascii.  We are cheating to convert a char to an int
					ret += _return.substr( (*itr)[0] - 48, (*itr)[1] - 48 ).c_str();
				}	
			}
			else
				ret += _return.c_str();
		}

		LOG_TRACE( "/NumberSwitchField::getInt" );
		return atoi( ret.c_str() );
	}

	long NumberSwitchField::getLong() const
	{
		LOG_TRACE( "NumberSwitchField::getLong" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = "0";
		}
		else
		{
			bool only_number = ( getProperty( "number_only", true ) == "true" );
			std::vector<std::string> numbers = getProperty( "number" );
			if( only_number )
			{
				for( std::vector<std::string>::iterator itr = numbers.begin(); itr != numbers.end(); itr++ )
				{
				
					// Subtract 48 because '0' is 48 in ascii.  We are cheating to convert a char to an int
					ret += _return.substr( (*itr)[0] - 48, (*itr)[1] - 48 ).c_str();
				}	
			}
			else
				ret += _return.c_str();
		}

		LOG_TRACE( "/NumberSwitchField::getLong" );
		return atol( ret.c_str() );
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
			std::vector<std::string> switches = getProperty( "switch" );
			std::string sw;
			if( switches.empty() )
			{
				// No "switch" property so assume we switch on character 0
				sw = "0" + _return;
				sw.resize( 2 );
				std::string string = getProperty( sw, true );
				if( string != "" )
					ret = string + " ";
				else
					ret = "Unknown: " + sw.substr(1);
			}
			else
			{
				for( std::vector<std::string>::iterator pos = switches.begin(); pos != switches.end(); pos++ )
				{
					sw = (*pos) + (char*)&_return[ atoi( (*pos).c_str() ) ];
					sw.resize(2);
					std::string string = getProperty( sw, true );
					std::string desc = getProperty( *pos, true );
					if( string != "" )
					{
						if( desc != "" ) 
							ret += desc + " = " + string + " : ";
						else
							ret += string + " : ";
					}
					else
						ret += "Unknown: " + sw.substr(1) + " : ";
				}
				
			}

			std::vector<std::string> numbers = getProperty( "number" );
			if( !numbers.empty() )
			{
				for( std::vector<std::string>::iterator number = numbers.begin(); number != numbers.end(); number++ )
				{
					ret += _return.substr( (*number)[0] - 48, (*number)[1] - 48 ) + " : ";
				}
			}
			else
			{
				LOG_WARN( "No 'number' property found in this numberswitch data type: " << getID() );
			}
			ret.resize( ret.length() - 3 ); // Trim off last ':'
		}

		LOG_TRACE( "/NumberSwitchField::getString" );
		return ret;
	}
}
