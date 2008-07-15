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

#include "structuretype.h"

#include "output.h"

namespace bafprp
{
	const StructureTypeFieldMaker StructureTypeFieldMaker::registerThis;

	IField* StructureTypeFieldMaker::make() const
	{
		LOG_TRACE( "StructureTypeFieldMaker::make" );
		return new StructureType();
		LOG_TRACE( "StructureTypeFieldMaker::make" );
	}

	StructureType::StructureType() : IField()
	{
		LOG_TRACE( "StructureType::StructureTyper" );
		LOG_TRACE( "/StructureType::StructureType" );
	}


	StructureType::~StructureType()
	{
		LOG_TRACE( "StructureType::~StructureType" );
		LOG_TRACE( "/StructureType::~StructureType" );
	}

	bool StructureType::convert ( const BYTE* data )
	{
		LOG_TRACE( "StructureType::convert" );
		_return = getChars( data, getSize() );
		LOG_TRACE( "/StructureType::convert" );
		return true;
	}

	long StructureType::getLong()
	{
		LOG_TRACE( "StructureType::getLong" );
		LOG_TRACE( "/StructureType::getLong" );
		return atol( _return.c_str() );
	}

	int StructureType::getInt()
	{
		LOG_TRACE( "StructureType::getInt" );
		LOG_TRACE( "/StructureType::getInt" );
		return atoi( _return.c_str() );
	}

	std::string StructureType::getString()
	{
		LOG_TRACE( "StructureType::getString" );
		LOG_TRACE( "/StructureType::getString" );
		return _return;
	}
}
