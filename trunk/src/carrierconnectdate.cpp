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

#include "carrierconnectdate.h"
#include "output.h"

namespace bafprp
{
	const CarrierConnectDateFieldMaker CarrierConnectDateFieldMaker::registerThis;

	IField* CarrierConnectDateFieldMaker::make() const
	{
		LOG_TRACE( "CarrierConnectDateFieldMaker::make" );
		LOG_TRACE( "/CarrierConnectDateFieldMaker::make" );
		return new CarrierConnectDate;
		
	}

	CarrierConnectDate::CarrierConnectDate() : IField()
	{
		LOG_TRACE( "CarrierConnectDate::CarrierConnectDateFieldConverter" );
		LOG_TRACE( "/CarrierConnectDate::CarrierConnectDateFieldConverter" );
	}


	CarrierConnectDate::~CarrierConnectDate()
	{
		LOG_TRACE( "CarrierConnectDate::~CarrierConnectDateFieldConverter" );
		LOG_TRACE( "/CarrierConnectDate::~CarrierConnectDateFieldConverter" );
	}

	bool CarrierConnectDate::convert ( const BYTE* data )
	{
		LOG_TRACE( "CarrierConnectDate::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CarrierConnectDate::convert" );
		return _converted;
	}

	std::string CarrierConnectDate::getString() const
	{
		LOG_TRACE( "CarrierConnectDate::getString" );

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

			std::ostringstream os;
			os << year << "-" << _return[1] << _return[2] << "-" << _return[3] << _return[4];;
			// In case you live in europe
			// os << _return[3] << _return[4] << "/" << _return[1] << _return[2] << "/" << year;

			ret = os.str();
		}

		LOG_TRACE( "/CarrierConnectDate::getString" );
		return ret;
	}
}
