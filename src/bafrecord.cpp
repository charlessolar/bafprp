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

#include <stdio.h>
#include <memory.h>

#include "bafrecord.h"

namespace bafprp
{

	BafRecord::BafRecord( const BYTE* data, int length ) : _length( length )
	{
		_data = new BYTE[ _length + 1 ];
		memcpy_s( _data, _length, data, _length );

		for( int i = 0; i < _length; i++ )
		{
			printf( " %X ", _data[i] );
		}
		printf( "\n" );
	}


	BafRecord::~BafRecord()
	{
		delete[] _data;
	}




}