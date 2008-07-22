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

#include "supportinginfo.h"
#include "output.h"

namespace bafprp
{
	const SupportingInfoFieldMaker SupportingInfoFieldMaker::registerThis;

	IField* SupportingInfoFieldMaker::make() const
	{
		LOG_TRACE( "SupportingInfoFieldMaker::make" );
		LOG_TRACE( "/SupportingInfoFieldMaker::make" );
		return new SupportingInfo;
		
	}

	SupportingInfo::SupportingInfo() : IField()
	{
		LOG_TRACE( "SupportingInfo::SupportingInfoFieldConverter" );
		LOG_TRACE( "/SupportingInfo::SupportingInfoFieldConverter" );
	}


	SupportingInfo::~SupportingInfo()
	{
		LOG_TRACE( "SupportingInfo::~SupportingInfoFieldConverter" );
		LOG_TRACE( "/SupportingInfo::~SupportingInfoFieldConverter" );
	}

	bool SupportingInfo::convert ( const BYTE* data )
	{
		LOG_TRACE( "SupportingInfo::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/SupportingInfo::convert" );
		return _converted;
	}

	std::string SupportingInfo::getString() const
	{
		LOG_TRACE( "SupportingInfo::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
		{
			switch( _return[0] )
			{
			case '1':
				ret = "LNP database";
				break;
			case '2':
				ret = "Switching system data";
				break;
			case '3':
				ret = "Incoming signaling";
				break;
			case '4':
				ret = "Switch LRN";
				break;
			default:
				ret = "Unknown " + _return[0];
			}
			ret += " : ";
			ret += "LRN source: ";
			switch( atoi( _return.substr(1,2).c_str() ) )
			{
			case 1:
				ret += "Successful query";
				break;
			case 2:
				ret += "No response";
				break;
			case 3:
				ret += "AIN continue";
				break;
			case 4:
				ret += "Protocol error";
				break;
			case 5:
				ret += "Error detected";
				break;
			case 6:
				ret += "Query rejected";
				break;
			case 7:
				ret += "Last resort routing";
				break;
			case 9:
				ret += "No query done";
				break;
			case 11:
				ret += "Successful QoR";
				break;
			case 12:
				ret += "QoR initiated";
				break;
			case 13:
				ret +=  "QoR received";
				break;
			case 14:
				ret += "PORC last resort - donor";
				break;
			case 15:
				ret += "PORC last resort - surrogate donor";
				break;
			default:
				ret += "Unknown " + _return.substr(1,2);
			}

		}

		LOG_TRACE( "/SupportingInfo::getString" );
		return ret;
	}
}
