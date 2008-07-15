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

#include "structuretypefieldconverter.h"

#include "output.h"

namespace bafprp
{
	const StructureTypeFieldMaker StructureTypeFieldMaker::registerThis;

	IFieldConverter* StructureTypeFieldMaker::make() const
	{
		LOG_TRACE( "StructureTypeFieldMaker::make" );
		return new StructureTypeFieldConverter();
		LOG_TRACE( "StructureTypeFieldMaker::make" );
	}

	StructureTypeFieldConverter::StructureTypeFieldConverter()
			: IFieldConverter()
	{
		LOG_TRACE( "StructureTypeFieldConverter::StructureTypeFieldConverter" );
		LOG_TRACE( "/StructureTypeFieldConverter::StructureTypeFieldConverter" );
	}


	StructureTypeFieldConverter::~StructureTypeFieldConverter()
	{
		LOG_TRACE( "StructureTypeFieldConverter::~StructureTypeFieldConverter" );
		LOG_TRACE( "/StructureTypeFieldConverter::~StructureTypeFieldConverter" );
	}

	bool StructureTypeFieldConverter::convert ( const BYTE* data )
	{
		LOG_TRACE( "StructureTypeFieldConverter::convert" );
		_return = getChars( data, getSize() );

		LOG_TRACE( "/StructureTypeFieldConverter::convert" );
		return true;
	}

	long StructureTypeFieldConverter::getLong()
	{
		LOG_TRACE( "StructureTypeFieldConverter::getLong" );
		LOG_TRACE( "/StructureTypeFieldConverter::getLong" );
		return atol( _return.c_str() );
	}

	int StructureTypeFieldConverter::getInt()
	{
		LOG_TRACE( "StructureTypeFieldConverter::getInt" );
		LOG_TRACE( "/StructureTypeFieldConverter::getInt" );
		return atoi( _return.c_str() );
	}

	std::string StructureTypeFieldConverter::getString()
	{
		LOG_TRACE( "StructureTypeFieldConverter::getString" );
		LOG_TRACE( "/StructureTypeFieldConverter::getString" );
		return _return;
	}
}
