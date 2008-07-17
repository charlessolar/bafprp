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

#include "calledpartyoffhook.h"
#include "output.h"

namespace bafprp
{
	const CalledPartyOffHookFieldMaker CalledPartyOffHookFieldMaker::registerThis;

	IField* CalledPartyOffHookFieldMaker::make() const
	{
		LOG_TRACE( "CalledPartyOffHookFieldMaker::make" );
		LOG_TRACE( "/CalledPartyOffHookFieldMaker::make" );
		return new CalledPartyOffHook;
		
	}

	CalledPartyOffHook::CalledPartyOffHook() : IField()
	{
		LOG_TRACE( "CalledPartyOffHook::CalledPartyOffHookFieldConverter" );
		LOG_TRACE( "/CalledPartyOffHook::CalledPartyOffHookFieldConverter" );
	}


	CalledPartyOffHook::~CalledPartyOffHook()
	{
		LOG_TRACE( "CalledPartyOffHook::~CalledPartyOffHookFieldConverter" );
		LOG_TRACE( "/CalledPartyOffHook::~CalledPartyOffHookFieldConverter" );
	}

	bool CalledPartyOffHook::convert ( const BYTE* data )
	{
		LOG_TRACE( "CalledPartyOffHook::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/CalledPartyOffHook::convert" );
		return _converted;
	}

	std::string CalledPartyOffHook::getString()
	{
		LOG_TRACE( "CalledPartyOffHook::getString" );

		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
		{
			switch( _return[0] )
			{
			case '0':
				ret = "Called party off-hook detected";
				break;
			case '1':
				ret = "Called party off-hook not detected";
				break;
			case '2':
				ret = "Answered attempt (OSS person / collect call)";
				break;
			case '3':
				ret = "Simulated called party off-hook";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}
		LOG_TRACE( "/CalledPartyOffHook::getString" );
		return ret;
	}
}
