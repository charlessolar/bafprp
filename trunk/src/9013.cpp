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

#include "9013.h"
#include "output.h"

namespace bafprp
{

	const r9013Maker r9013Maker::registerThis;

	IBafRecord* r9013Maker::make( const BYTE* data, int length ) const
	{
		LOG_TRACE( "r9013Maker::make" );
		LOG_TRACE( "/r9013Maker::make" );
		return new r9013( data, length );
	}

	r9013::r9013( const BYTE* data, int length ) : IBafRecord( data, length )
	{
		// make the real structure

		// This is really messy... Fix this.
		IFieldConverter* field;
		field = FieldMaker::newFieldConverter( "structuretype" );
		field->convert( data );
		data += ( field->getSize() + 1 ) / 2;
		_fields.push_back( field );
		field = FieldMaker::newFieldConverter( "calltype" );
		field->convert( data );
		data += ( field->getSize() + 1 ) / 2;
		_fields.push_back( field );

	}

	r9013::~r9013()
	{
	}

}