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

#include "genericid.h"
#include "output.h"

namespace bafprp
{
	const GenericIDFieldMaker GenericIDFieldMaker::registerThis;

	IField* GenericIDFieldMaker::make() const
	{
		LOG_TRACE( "GenericIDFieldMaker::make" );
		return new GenericID();
		LOG_TRACE( "GenericIDFieldMaker::make" );
	}

	GenericID::GenericID() : IField()
	{
		LOG_TRACE( "GenericID::GenericID" );
		LOG_TRACE( "/GenericID::GenericID" );
	}


	GenericID::~GenericID()
	{
		LOG_TRACE( "GenericID::~GenericID" );
		LOG_TRACE( "/GenericID::~GenericID" );
	}

	bool GenericID::convert ( const BYTE* data )
	{
		LOG_TRACE( "GenericID::convert" );

		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/GenericID::convert" );
		return _converted;
	}

	std::string GenericID::getString()
	{
		LOG_TRACE( "GenericID::getString" );
		
		std::string ret;
		if( !_converted )
		{
			_lastError = "Tried to get string before field was converted";
			ret = "";
		}
		else
		{		
			std::ostringstream os;
			os << "Software Release ID : " << "Generic issue number = " << _return[0] << _return[1] << " : Point issue level = " << _return[2] << _return[3] << " : Overwrite level = " << _return[4];
			ret = os.str();
		}
		LOG_TRACE( "/GenericID::getString" );
		return ret;
	}
}