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

#include "releasecauseindicator.h"
#include "output.h"

namespace bafprp
{
	const ReleaseCauseIndicatorFieldMaker ReleaseCauseIndicatorFieldMaker::registerThis;

	IField* ReleaseCauseIndicatorFieldMaker::make() const
	{
		LOG_TRACE( "ReleaseCauseIndicatorFieldMaker::make" );
		LOG_TRACE( "/ReleaseCauseIndicatorFieldMaker::make" );
		return new ReleaseCauseIndicator;
		
	}

	ReleaseCauseIndicator::ReleaseCauseIndicator() : IField()
	{
		LOG_TRACE( "ReleaseCauseIndicator::ReleaseCauseIndicatorFieldConverter" );
		LOG_TRACE( "/ReleaseCauseIndicator::ReleaseCauseIndicatorFieldConverter" );
	}


	ReleaseCauseIndicator::~ReleaseCauseIndicator()
	{
		LOG_TRACE( "ReleaseCauseIndicator::~ReleaseCauseIndicatorFieldConverter" );
		LOG_TRACE( "/ReleaseCauseIndicator::~ReleaseCauseIndicatorFieldConverter" );
	}

	bool ReleaseCauseIndicator::convert ( const BYTE* data )
	{
		LOG_TRACE( "ReleaseCauseIndicator::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ReleaseCauseIndicator::convert" );
		return _converted;
	}

	std::string ReleaseCauseIndicator::getString() const
	{
		LOG_TRACE( "ReleaseCauseIndicator::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( _return[1] )
			{
			case '0':
				ret = "ITU standard";
				break;
			case '2':
				ret = "National";
				break;
			case '3':
				ret = "Network specific";
				break;
			}
			ret += " : Cause Indicator: ";
			ret += _return.substr( 2, 2 );
		}

		LOG_TRACE( "/ReleaseCauseIndicator::getString" );
		return ret;
	}
}
