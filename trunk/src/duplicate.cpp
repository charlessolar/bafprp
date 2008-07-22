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
		// algorithm.h <3
		std::sort( records.begin(), records.end(), recordsort );
		records.erase( std::unique( records.begin(), records.end(), recordequal ), records.end() );
	}

	void Duplicate::list( std::vector<IBafRecord*>& records )
	{
		std::sort( records.begin(), records.end(), recordsort );
		std::vector<IBafRecord*>::iterator itr = std::unique( records.begin(), records.end(), recordequal );
		for(; itr != records.end(); itr++ )
		{
			std::vector<IBafRecord*>::iterator itr2;
			for( itr2 = records.begin(); itr2 != itr; itr2++ )
				if( (*itr2)->getCRC() == (*itr)->getCRC() ) break;
			if( itr2 == itr )
			{
				LOG_ERROR( "Could not find collision record for " << (*itr)->getType() << "\t" << (*itr)->getSize() << "\t" << (*itr)->getFilePosition() << "\t" << (*itr)->getCRC() );
			}
			else
			{
				LOG_INFO( "* " << std::setw(30) << (*itr)->getType() << "\t" << (*itr)->getSize() << "\t" << (*itr)->getFilePosition() << "\t" << (*itr)->getCRC() << " collided with " << std::setw(30) << (*itr2)->getType() << "\t" << (*itr2)->getSize() << "\t" << (*itr2)->getFilePosition() << "\t" << (*itr2)->getCRC() );
			}
		}
	}


}