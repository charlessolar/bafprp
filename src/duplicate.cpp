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
		if( records.size() == 0 ) return;

		std::vector<IBafRecord*> myrecords( records );  // Make a copy because we do not want to disturb the natural order 
														// Should not be a problem since the vector is just thousands of
														// pointers

		std::sort( myrecords.begin(), myrecords.end(), recordsort );

		// Notes:
		// This statement did not work for me.  I do not know if it was working but giving the wrong output,
		// or if it just was not working.  
		// What I did was unique the list and tried to find the collisions in the vector from the values after
		// the iterator returned from unique, which should be the start of the duplicates.
		// I ended up getting very poor results from this search, often finding that records after
		// the unique iterator were actually unique in the record log.  This caused me to remove this unique
		// and add my own since once the records are sorted its fairly easy (and fast) to do it myself.

		//records.erase( std::unique( records.begin(), records.end(), recordequal ), records.end() );

		for(std::vector<IBafRecord*>::iterator itr = myrecords.begin() + 1; itr != myrecords.end(); itr++ )
		{
			if( (*itr)->getCRC() == (*(itr - 1))->getCRC() )
			{
				// Probably a better way
				for( std::vector<IBafRecord*>::iterator itr2 = records.begin(); itr2 != records.end(); itr2++ )
				{
					if( (*itr2)->getCRC() == (*itr)->getCRC() )
					{
						if( *itr2 ) delete *itr2;
						records.erase( itr2 );
						break;
					}
				}
				//if( *itr ) delete *itr;
				//itr = records.erase( itr );
				//if( itr == records.end() ) break;   // We need this in case we end up deleting the iterator right before the end().  If that happens the iterator would be
													// incremented and would produce a very bad error
			}
		}
	}

	void Duplicate::list( std::vector<IBafRecord*>& records )
	{
		if( records.size() == 0 ) return;

		std::vector<IBafRecord*> myrecords( records );  // Make a copy because we do not want to disturb the natural order 
														// Should not be a problem since the vector is just thousands of
														// pointers

		std::sort( myrecords.begin(), myrecords.end(), recordsort );

		for(std::vector<IBafRecord*>::iterator itr = myrecords.begin() + 1; itr != myrecords.end(); itr++ )
		{
			if( (*itr)->getCRC() == (*(itr - 1))->getCRC() )
			{
				LOG_INFO( "* " << std::setw(30) << (*itr)->getType() << "\t" << (*itr)->getSize() << "\t" << (*itr)->getFilePosition() << "\t" << (*itr)->getCRC() << " collided with " << std::setw(30) << (*(itr - 1))->getType() << "\t" << (*(itr - 1))->getSize() << "\t" << (*(itr - 1))->getFilePosition() << "\t" << (*(itr - 1))->getCRC() );
			}
		}
	}


}
