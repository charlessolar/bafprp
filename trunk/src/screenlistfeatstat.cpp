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

#include "screenlistfeatstat.h"
#include "output.h"

namespace bafprp
{
	const ScreenListFeatStatFieldMaker ScreenListFeatStatFieldMaker::registerThis;

	IField* ScreenListFeatStatFieldMaker::make() const
	{
		LOG_TRACE( "ScreenListFeatStatFieldMaker::make" );
		LOG_TRACE( "/ScreenListFeatStatFieldMaker::make" );
		return new ScreenListFeatStat;
		
	}

	ScreenListFeatStat::ScreenListFeatStat() : IField()
	{
		LOG_TRACE( "ScreenListFeatStat::ScreenListFeatStatFieldConverter" );
		LOG_TRACE( "/ScreenListFeatStat::ScreenListFeatStatFieldConverter" );
	}


	ScreenListFeatStat::~ScreenListFeatStat()
	{
		LOG_TRACE( "ScreenListFeatStat::~ScreenListFeatStatFieldConverter" );
		LOG_TRACE( "/ScreenListFeatStat::~ScreenListFeatStatFieldConverter" );
	}

	bool ScreenListFeatStat::convert ( const BYTE* data )
	{
		LOG_TRACE( "ScreenListFeatStat::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ScreenListFeatStat::convert" );
		return _converted;
	}

	int ScreenListFeatStat::getInt() const
	{
		LOG_TRACE( "ScreenListFeatStat::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ScreenListFeatStat::getInt" );
		return ret;
	}

	long ScreenListFeatStat::getLong() const
	{
		LOG_TRACE( "ScreenListFeatStat::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ScreenListFeatStat::getLong" );
		return ret;
	}

	std::string ScreenListFeatStat::getString() const
	{
		LOG_TRACE( "ScreenListFeatStat::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( getInt() )
			{
			case 0:
				ret = "None";
				break;
			case 1:
				ret = "SCF active";
				break;
			case 2:
				ret = "SCR active";
				break;
			case 3:
				ret = "SCF and SCR active";
				break;
			case 4:
				ret = "DRCW active";
				break;
			case 5:
				ret = "SCF and DRCW active";
				break;
			case 6:
				ret = "SCR and DRCW active";
				break;
			case 7:
				ret = "SCF, SCR, and DRCW active";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/ScreenListFeatStat::getString" );
		return ret;
	}
}
