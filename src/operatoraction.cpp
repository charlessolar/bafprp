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

#include "operatoraction.h"
#include "output.h"

namespace bafprp
{
	const OperatorActionFieldMaker OperatorActionFieldMaker::registerThis;

	IField* OperatorActionFieldMaker::make() const
	{
		LOG_TRACE( "OperatorActionFieldMaker::make" );
		LOG_TRACE( "/OperatorActionFieldMaker::make" );
		return new OperatorAction;
		
	}

	OperatorAction::OperatorAction() : IField()
	{
		LOG_TRACE( "OperatorAction::OperatorActionFieldConverter" );
		LOG_TRACE( "/OperatorAction::OperatorActionFieldConverter" );
	}


	OperatorAction::~OperatorAction()
	{
		LOG_TRACE( "OperatorAction::~OperatorActionFieldConverter" );
		LOG_TRACE( "/OperatorAction::~OperatorActionFieldConverter" );
	}

	bool OperatorAction::convert ( const BYTE* data )
	{
		LOG_TRACE( "OperatorAction::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/OperatorAction::convert" );
		return _converted;
	}

	std::string OperatorAction::getString()
	{
		LOG_TRACE( "OperatorAction::getString" );

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
				ret = "Automatically identified, customer dialed";
				break;
			case '1':
				ret = "Automatically identified, customer dialed with OSS";
				break;
			case '2':
				ret = "Operator identified, customer dialed";
				break;
			case '3':
				ret = "Operator identified, customer dialed with OSS";
				break;
			default:
				ret = "Unknown " + _return;
			}
		}

		LOG_TRACE( "/OperatorAction::getString" );
		return ret;
	}
}
