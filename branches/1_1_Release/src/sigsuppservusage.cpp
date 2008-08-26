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

#include "sigsuppservusage.h"
#include "output.h"

namespace bafprp
{
	const SigSuppServUsageFieldMaker SigSuppServUsageFieldMaker::registerThis;

	IField* SigSuppServUsageFieldMaker::make() const
	{
		LOG_TRACE( "SigSuppServUsageFieldMaker::make" );
		LOG_TRACE( "/SigSuppServUsageFieldMaker::make" );
		return new SigSuppServUsage;
		
	}

	SigSuppServUsage::SigSuppServUsage() : IField()
	{
		LOG_TRACE( "SigSuppServUsage::SigSuppServUsageFieldConverter" );
		LOG_TRACE( "/SigSuppServUsage::SigSuppServUsageFieldConverter" );
	}


	SigSuppServUsage::~SigSuppServUsage()
	{
		LOG_TRACE( "SigSuppServUsage::~SigSuppServUsageFieldConverter" );
		LOG_TRACE( "/SigSuppServUsage::~SigSuppServUsageFieldConverter" );
	}

	bool SigSuppServUsage::convert ( const BYTE* data )
	{
		LOG_TRACE( "SigSuppServUsage::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/SigSuppServUsage::convert" );
		return _converted;
	}

	std::string SigSuppServUsage::getString() const
	{
		LOG_TRACE( "SigSuppServUsage::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			if( _return[1] == '2' ) ret = "Calling party subaddress delivery ";
			if( _return[2] == '2' ) ret += " Called party subaddress delivery ";
			if( _return[3] == '2' ) ret += " Low layer compatibility delivery ";
			if( _return[4] == '2' ) ret += " High layer compatibility delivery ";
			if( _return[5] == '2' ) ret += " User to user info/Fast select ";
			if( _return[9] == '2' ) ret += " ISDN flexible calling ";
			if( _return[9] == '2' ) ret += " Call waiting originating ";
			if( _return[10] == '2' ) ret += " Dial call waiting ";
			if( _return[11] == '2' ) ret += " Call deflection ";
		}

		LOG_TRACE( "/SigSuppServUsage::getString" );
		return ret;
	}
}
