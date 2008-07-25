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

#include "bafdefines.h"

#include <assert.h>

#include "output.h"

namespace bafprp
{

	/*
	This is the most confusing function in this entire program.
	Heres the basic idea, our baf file has a string os text packed in nibbles (4 bits)
	Usually a character such as 9 is stored as 0x39 (ascii code) in a file, but it is different
	here.
	Since this document contains no real 'strings' they opted to store numbers as 4 bits instead of 8.
	Meaning their alphabet only consists of 1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
	Example:
		Regular storage of "92"
			- 3932
		Baf file storage of "92"
			- 092C
	To decode a number we must read each nibble one by one.
	This function steps over each nibble and appends the character to a string which we then return.
	*/
	std::string getChars( const BYTE* data, int length )
	{
		assert( data );

		static const unsigned char hex[] = 
		{
			'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
		};

		std::string ret;
		ret.resize( length );

		// Increase the data pointer because we will be reading the data backwards.
		data += ( length + length % 2 ) / 2;

		if( hex[( *data & 0x0F )] != 'C' )
			LOG_DEBUG( "Decoding a record without a terminating 'C'  This is usually a sign of an incorrect field size. Length of field: " << length );

		// We are reading the data backwards to be more compatable with varying field sizes.
		// The old way was to read starting at the beginning of a byte and continue 
		// however there are fields that start in the middle of a byte, so the only accurate
		// starting position we can count on in the end.  In our case, the end of a field is marked by
		// a 0x0C
		// which is fortunate for us since that gives us a valid byte alignment to start reading from
		for( int i = length; i > 0; i-- )
		{
			// When reading a field of even length, length % 2 will be 1 the first time
			// and then the data pointer will be decremented.
			// When reading a field of odd length, length % 2 will be 0 the first time
			// and we also need to decrement the pointer since the next character will
			// just be 0x0C
			if( i % 2 == ( length % 2 ) ) 
			{
				ret[i-1] = hex[ ( ( *data & 0xF0 ) >> 4 ) ];
				data--;
			}
			else
				ret[i-1] = hex[ ( *data & 0x0F ) ];
		}
		
		return ret;
	}
}