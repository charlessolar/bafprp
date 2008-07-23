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

#include <algorithm>
#include <iomanip>

#include "duplicate.h"
#include "output.h"


namespace bafprp
{

	void Duplicate::remove( std::vector<IBafRecord*>& records )
	{
		std::sort( records.begin(), records.end(), recordsort );

		// Notes:
		// This statement did not work for me.  I do not know if it was working but giving the wrong output,
		// or if it just was not working.  
		// What I did was unique the list and tried to find the collisions in the vector from the values after
		// the iterator returned from unique, which should be the start of the duplicates.
		// I ended up getting very poor results from this search, often finding that records after
		// the unique iterator were actually unique in the record log.  This caused me to remove this unique
		// and add my own since once the records are sorted its fairly easy (and fast) to do it myself.

		//records.erase( std::unique( records.begin(), records.end(), recordequal ), records.end() );

		for(std::vector<IBafRecord*>::iterator itr = records.begin() + 1; itr != records.end(); itr++ )
		{
			if( (*itr)->getCRC() == (*(itr - 1))->getCRC() )
			{
				itr = records.erase( itr );
			}
		}
	}

	void Duplicate::list( std::vector<IBafRecord*>& records )
	{
		std::sort( records.begin(), records.end(), recordsort );
		//std::vector<IBafRecord*>::iterator itr = std::unique( records.begin(), records.end(), recordequal );

		for(std::vector<IBafRecord*>::iterator itr = records.begin() + 1; itr != records.end(); itr++ )
		{
			if( (*itr)->getCRC() == (*(itr - 1))->getCRC() )
			{
				LOG_INFO( "* " << std::setw(30) << (*itr)->getType() << "\t" << (*itr)->getSize() << "\t" << (*itr)->getFilePosition() << "\t" << (*itr)->getCRC() << " collided with " << std::setw(30) << (*(itr - 1))->getType() << "\t" << (*(itr - 1))->getSize() << "\t" << (*(itr - 1))->getFilePosition() << "\t" << (*(itr - 1))->getCRC() );
			}
		}
	}


}