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
				ret = "Outgoing call barring daily contination";
				break;
			case 2:
				ret = "Outgoing call barring activation";
				break;
			case 3:
				ret = "Outgoing call barring deactivation";
				break;
			case 32:
				ret = "AR reactivation, delayed processing, setup";
				break;
			case 33:
				ret = "AC reactivation, delayed processing, setup";
				break;
			case 34:
				ret = "AR reactivation, busy ringback, no scanning";
				break;
			case 35:
				ret = "AC reactivation, busy ringback, noscanning";
				break;
			case 36:
				ret = "AR reactivation, delayed processing, timeout";
				break;
			case 37:
				ret = "AC reactivation, delayed processing, timeout";
				break;
			case 38:
				ret = "AR reactivation, delayed processing, de/react";
				break;
			case 39:
				ret = "AC reactivation, delayed processing, de/react";
				break;
			case 52:
				ret = "Selective call forwarding";
				break;
			case 57:
				ret = "Anonymous call rejection activation";
				break;
			case 58:
				ret = "Anonymous call rejection deactivation";
				break;
			case 59:
				ret = "Anonymous call rejection continuation";
				break;
			case 60:
				ret = "AR activation, immediate processing, setup";
				break;
			case 61:
				ret = "AC activation, immediate processing, setup";
				break;
			case 62:
				ret = "AR activation, delayed processing, setup";
				break;
			case 63:
				ret = "AC activation, delayed processing, setup";
				break;
			case 64:
				ret = "AR activation, busy ring back, no scanning";
				break;
			case 65:
				ret = "AC activation, busy ringback, no scanning";
				break;
			case 66:
				ret = "AR activation, delayed processing, timeout";
				break;
			case 67:
				ret = "AC activation, delayed processing, timeout";
				break;
			case 68:
				ret = "AR activation, delayed processing, de/react";
				break;
			case 69:
				ret = "AC activation, delayed processing, de/react";
				break;
			case 70:
				ret = "Customer originated trace activation";
				break;
			case 72:
				ret = "Selective call rejection";
				break;
			case 73:
				ret = "Distinctive Ringing / Call Waiting";
				break;
			case 74:
				ret = "Screen List editing daily contination";
				break;
			case 75:
				ret = "Calling number delivery blocking activation";
				break;
			case 79:
				ret = "Selective call acceptance";
				break;
			case 80:
				ret = "Calling number delivery";
				break;
			case 82:
				ret = "Calling name delivery";
				break;
			case 85:
				ret = "Calling identity delivery and suppression";
				break;
			case 95:
				ret = "AR two-level activation";
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
