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

// Class to detect and remove duplicates from the record list
// Ask me to explain why I made these processing functions seperate classes
// and I will give you a new answer every day.

#ifndef BAFPRPDUPLICATE_H
#define BAFPRPDUPLICATE_H

#include "ibafrecord.h"

namespace bafprp
{
	class Duplicate
	{
	public:
		// remove all duplicates
		static void remove( std::vector<IBafRecord*>& records );
		// list duplicates in info log
		static void list( std::vector<IBafRecord*>& records );
	};

	bool recordcrcequal( const IBafRecord* record, DWORD value );
}
#endif