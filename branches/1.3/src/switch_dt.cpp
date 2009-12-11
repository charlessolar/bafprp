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

#include <algorithm>

#include "switch_dt.h"
#include "output.h"

namespace bafprp
{
	const SwitchFieldMaker SwitchFieldMaker::registerThis;

	IField* SwitchFieldMaker::make() const
	{
		return new SwitchField;
	}

	SwitchField::SwitchField() : IField()
	{
		LOG_TRACE( "SwitchField::Switch" );
		LOG_TRACE( "/SwitchField::Switch" );
	}


	SwitchField::~SwitchField()
	{
		LOG_TRACE( "SwitchField::~Switch" );
		LOG_TRACE( "/SwitchField::~Switch" );
	}

	bool SwitchField::convert ( const BYTE* data )
	{
		LOG_TRACE( "SwitchField::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/SwitchField::convert" );
		return _converted;
	}

	int SwitchField::getInt() const
	{
		LOG_TRACE( "SwitchField::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/SwitchField::getInt" );
		return ret;
	}

	long SwitchField::getLong() const
	{
		LOG_TRACE( "SwitchField::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/SwitchField::getLong" );
		return ret;
	}
	
	std::string SwitchField::getString() const
	{
		LOG_TRACE( "SwitchField::getString" );

		std::string ret = "";
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
				ret.resize( ret.length() - 3 ); // remove last ':'
			}
		}
		LOG_TRACE( "/SwitchField::getString" );
		return ret;
	}
}
