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

#include "icincindicator.h"
#include "output.h"

namespace bafprp
{
	const ICINCIndicatorFieldMaker ICINCIndicatorFieldMaker::registerThis;

	IField* ICINCIndicatorFieldMaker::make() const
	{
		LOG_TRACE( "ICINCIndicatorFieldMaker::make" );
		LOG_TRACE( "/ICINCIndicatorFieldMaker::make" );
		return new ICINCIndicator;
		
	}

	ICINCIndicator::ICINCIndicator() : IField()
	{
		LOG_TRACE( "ICINCIndicator::ICINCIndicatorFieldConverter" );
		LOG_TRACE( "/ICINCIndicator::ICINCIndicatorFieldConverter" );
	}


	ICINCIndicator::~ICINCIndicator()
	{
		LOG_TRACE( "ICINCIndicator::~ICINCIndicatorFieldConverter" );
		LOG_TRACE( "/ICINCIndicator::~ICINCIndicatorFieldConverter" );
	}

	bool ICINCIndicator::convert ( const BYTE* data )
	{
		LOG_TRACE( "ICINCIndicator::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ICINCIndicator::convert" );
		return _converted;
	}

	std::string ICINCIndicator::getString() const
	{
		LOG_TRACE( "ICINCIndicator::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			ret = "CIC = " + _return.substr(0,4) + " : ";
			switch( _return[4] )
			{
			case '0':
				ret += "FGD, IC/INC involved";
				break;
			case '1':
				ret += "FGD, IC/INC not involved";
				break;
			case '2':
				ret += "FGD, IC/INC involvement unknown";
				break;
			case '3':
				ret += "FGB, IC/INC involved";
				break;
			case '4':
				ret += "FGB, IC/INC not involved";
				break;
			case '5':
				ret += "FGB, IC/INC involvement unknown";
				break;
			case '7':
				ret += "CIC unknown, IC/INC involved";
				break;
			case '8':
				ret += "CIC unknown, IC/INC not involved";
				break;
			case '9':
				ret += "CIC unknown, IC/INC involvement unknown";
				break;
			default:
				ret += "Unknown " + _return;
			}
		}

		LOG_TRACE( "/ICINCIndicator::getString" );
		return ret;
	}
}
