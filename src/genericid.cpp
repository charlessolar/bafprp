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
		LOG_TRACE( "/GenericID::convert" );
		return true;
	}

	long GenericID::getLong()
	{
		LOG_TRACE( "GenericID::getLong" );
		LOG_TRACE( "/GenericID::getLong" );
		return atol( _return.c_str() );
	}

	int GenericID::getInt()
	{
		LOG_TRACE( "GenericID::getInt" );
		LOG_TRACE( "/GenericID::getInt" );
		return atoi( _return.c_str() );
	}

	std::string GenericID::getString()
	{
		LOG_TRACE( "GenericID::getString" );
		LOG_TRACE( "/GenericID::getString" );
		return _return;
	}
}