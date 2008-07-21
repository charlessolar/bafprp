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

#include "trunkidentification.h"
#include "output.h"

namespace bafprp
{
	const TrunkIdentificationFieldMaker TrunkIdentificationFieldMaker::registerThis;

	IField* TrunkIdentificationFieldMaker::make() const
	{
		LOG_TRACE( "TrunkIdentificationFieldMaker::make" );
		LOG_TRACE( "/TrunkIdentificationFieldMaker::make" );
		return new TrunkIdentification;
		
	}

	TrunkIdentification::TrunkIdentification() : IField()
	{
		LOG_TRACE( "TrunkIdentification::TrunkIdentificationFieldConverter" );
		LOG_TRACE( "/TrunkIdentification::TrunkIdentificationFieldConverter" );
	}


	TrunkIdentification::~TrunkIdentification()
	{
		LOG_TRACE( "TrunkIdentification::~TrunkIdentificationFieldConverter" );
		LOG_TRACE( "/TrunkIdentification::~TrunkIdentificationFieldConverter" );
	}

	bool TrunkIdentification::convert ( const BYTE* data )
	{
		LOG_TRACE( "TrunkIdentification::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/TrunkIdentification::convert" );
		return _converted;
	}

	std::string TrunkIdentification::getString() const
	{
		LOG_TRACE( "TrunkIdentification::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			ret = "Routing Indicator = ";
			switch( _return[0] )
			{
			case '1':
				ret += "Direct - Incoming Different network";
				break;
			case '2':
				ret += "Direct - Outgoing Different network";
				break;
			case '3':
				ret += "Direct - Incoming Same network";
				break;
			case '4':
				ret += "Direct - Outgoing Same network";
				break;
			case '5':
				ret += "Tandem - Incoming Different network";
				break;
			case '6':
				ret += "Tandem - Outgoing Different network";
				break;
			case '7':
				ret += "Tandem - Incoming Same network";
				break;
			case '8':
				ret += "Tandem - Outgoing Same network";
				break;
			default:
				ret += "Unknown " + _return[0];
			}
			ret += " Trunk Group Number: " + _return.substr(1,4);
			ret += " Trunk Member Number: " + _return.substr(5,4);
		}

		LOG_TRACE( "/TrunkIdentification::getString" );
		return ret;
	}
}
