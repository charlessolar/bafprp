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

// code modified from http://www.gamedev.net/reference/programming/features/crc32/default.asp

#ifndef BAFPRPCRC32_H
#define BAFPRPCRC32_H

#include "bafdefines.h"


namespace bafprp
{

	class CRC32 
	{
	public:
		static bool Encode( const BYTE* data, DWORD dwSize, DWORD& crc ); 

	private:
		static inline void GetCRC32( const BYTE byte, DWORD& crc );

		static DWORD CRC32Table[256];
	};

}

#endif
