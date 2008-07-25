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

#include "classfeaturecode.h"
#include "output.h"

namespace bafprp
{
	const ClassFeatureCodeFieldMaker ClassFeatureCodeFieldMaker::registerThis;

	IField* ClassFeatureCodeFieldMaker::make() const
	{
		LOG_TRACE( "ClassFeatureCodeFieldMaker::make" );
		LOG_TRACE( "/ClassFeatureCodeFieldMaker::make" );
		return new ClassFeatureCode;
		
	}

	ClassFeatureCode::ClassFeatureCode() : IField()
	{
		LOG_TRACE( "ClassFeatureCode::ClassFeatureCodeFieldConverter" );
		LOG_TRACE( "/ClassFeatureCode::ClassFeatureCodeFieldConverter" );
	}


	ClassFeatureCode::~ClassFeatureCode()
	{
		LOG_TRACE( "ClassFeatureCode::~ClassFeatureCodeFieldConverter" );
		LOG_TRACE( "/ClassFeatureCode::~ClassFeatureCodeFieldConverter" );
	}

	bool ClassFeatureCode::convert ( const BYTE* data )
	{
		LOG_TRACE( "ClassFeatureCode::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/ClassFeatureCode::convert" );
		return _converted;
	}

	int ClassFeatureCode::getInt() const
	{
		LOG_TRACE( "ClassFeatureCode::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/ClassFeatureCode::getInt" );
		return ret;
	}

	long ClassFeatureCode::getLong() const
	{
		LOG_TRACE( "ClassFeatureCode::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/ClassFeatureCode::getLong" );
		return ret;
	}

	std::string ClassFeatureCode::getString() const
	{
		LOG_TRACE( "ClassFeatureCode::getString" );

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
			case 1:
				ret = "Outgoingcallbarringdailycontination";
				break;
			case 2:
				ret = "Outgoingcallbarringactivation";
				break;
			case 3:
				ret = "Outgoingcallbarringdeactivation";
				break;
			case 32:
				ret = "ARreactivation,delayedprocessing,setup";
				break;
			case 33:
				ret = "ACreactivation,delayedprocessing,setup";
				break;
			case 34:
				ret = "ARreactivation,busyringback,noscanning";
				break;
			case 35:
				ret = "ACreactivation,busyringback,noscanning";
				break;
			case 36:
				ret = "ARreactivation,delayedprocessing,timeout";
				break;
			case 37:
				ret = "ACreactivation,delayedprocessing,timeout";
				break;
			case 38:
				ret = "ARreactivation,delayedprocessing,de/react";
				break;
			case 39:
				ret = "ACreactivation,delayedprocessing,de/react";
				break;
			case 52:
				ret = "Selectivecallforwarding";
				break;
			case 57:
				ret = "Anonymouscallrejectionactivation";
				break;
			case 58:
				ret = "Anonymouscallrejectiondeactivation";
				break;
			case 59:
				ret = "Anonymouscallrejectioncontinuation";
				break;
			case 60:
				ret = "ARactivation,immediateprocessing,setup";
				break;
			case 61:
				ret = "ACactivation,immediateprocessing,setup";
				break;
			case 62:
				ret = "ARactivation,delayedprocessing,setup";
				break;
			case 63:
				ret = "ACactivation,delayedprocessing,setup";
				break;
			case 64:
				ret = "ARactivation,busyringback,noscanning";
				break;
			case 65:
				ret = "ACactivation,busyringback,noscanning";
				break;
			case 66:
				ret = "ARactivation,delayedprocessing,timeout";
				break;
			case 67:
				ret = "ACactivation,delayedprocessing,timeout";
				break;
			case 68:
				ret = "ARactivation,delayedprocessing,de/react";
				break;
			case 69:
				ret = "ACactivation,delayedprocessing,de/react";
				break;
			case 70:
				ret = "Customeroriginatedtraceactivation";
				break;
			case 72:
				ret = "Selectivecallrejection";
				break;
			case 73:
				ret = "DistinctiveRinging/CallWaiting";
				break;
			case 74:
				ret = "ScreenListeditingdailycontination";
				break;
			case 75:
				ret = "Callingnumberdeliveryblockingactivation";
				break;
			case 79:
				ret = "Selectivecallacceptance";
				break;
			case 80:
				ret = "Callingnumberdelivery";
				break;
			case 82:
				ret = "Callingnamedelivery";
				break;
			case 85:
				ret = "Callingidentitydeliveryandsuppression";
				break;
			case 95:
				ret = "ARtwo-levelactivation";
				break;
			default:
				ret = "Unknown " + _return;
				break;
			}
		}

		LOG_TRACE( "/ClassFeatureCode::getString" );
		return ret;
	}
}
