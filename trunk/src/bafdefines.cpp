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
	Heres the basic idea, our baf file has a string of text packed in nibbles (4 bits)
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

		for( int i = 0; i < length; i++ )
		{
			if( i % 2 == 1 )
			{
				ret[i] = hex[ ( *data & 0x0F ) ];
				data++;
			}
			else
				ret[i] = hex[ ( ( *data & 0xF0 ) >> 4 ) ];

		}

		// If length is even, we need to decrement the data pointer
		// Since all valid fields end with a 'C' all fields will be odd.
		// The only time we should get an even length is when they also want the C
		// When this happens we of course give them the C, but in order to pass this
		// upcomming check we have to backtrack 1 space so the next space WILL be
		// a C instead of 00's from the next field or record.
		if( length % 2 == 0 ) data--;

		if( hex[( *data & 0x0F )] != 'C' && hex[( *data & 0x0F )] != 'F' )
			LOG_DEBUG( "Decoded a field without a terminating 'C'  This is usually a sign of an incorrect field size. Length of field: " << length );

/*
		I used to read the data backwards since structure type is a field that sits in the middle of a byte.
		However this caused some other issues that I fixed after some tinkering with these systems
		In case I ever need to read backwards again I am keeping this code here.

		**************************************************************************************

		// Increase the data pointer because we will be reading the data backwards.
		data += ( length + length % 2 ) / 2;

		if( hex[( *data & 0x0F )] != 'C' && hex[( *data & 0x0F )] != 'F' )
			LOG_DEBUG( "Decoding a field without a terminating 'C'  This is usually a sign of an incorrect field size. Length of field: " << length );

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
		*/
		return ret;
	}

	std::string decodeBytes( const BYTE* data, int length, int high, int low )
	{
		assert( data );

		std::ostringstream os;

		static const int masks[] = { 0xFF, 0x7F, 0x3F, 0x1F, 0xF, 0x7, 0x3, 0x1 };

		int total = 0;
		for( int i = 0; i < length; i++ )
		{
			int tempLow = 7;
			int tempHigh = 0;
			if( i == 0 ) tempLow = low;
			if( i == (length-1) ) tempHigh = high;
			total += ( ( *data >> ( 7 - tempLow ) & masks[ ( 7 - ( tempLow - tempHigh ) ) ] ) << ( i == 0 ? 0 : ( ( 8 * i ) - ( 7 - low ) ) ) );
			if( i % 2 == 0 )
				data++;
		}

		os << total;

		return os.str();
	}
}
