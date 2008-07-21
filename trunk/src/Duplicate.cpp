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

#include "duplicate.h"
#include "output.h"

namespace bafprp
{

	void Duplicate::remove( std::vector<IBafRecord*>& _records )
	{
		long size = _records.size();

		bool* hashTable = new bool[ size ];
		memset( hashTable, 0, sizeof(bool) * size );

		for( std::vector<IBafRecord*>::iterator itr = _records.begin(); itr != _records.end(); itr++ )
		{
			if( !hashTable[ (*itr)->getCRC() % size ] )
			{
				hashTable[ (*itr)->getCRC() % size ] = true;
			}
			else
			{
				// Colision! Duplicate!!
				_records.erase( itr );
			}
		}
	}

	void Duplicate::list( std::vector<IBafRecord*>& _records )
	{
		long size = _records.size();

		bool* hashTable = new bool[ size ];
		memset( hashTable, 0, sizeof(bool) * size );

		LOG_INFO( "Searching for duplicates..." );

		for( std::vector<IBafRecord*>::iterator itr = _records.begin(); itr != _records.end(); itr++ )
		{
			if( !hashTable[ (*itr)->getCRC() % size ] )
			{
				hashTable[ (*itr)->getCRC() % size ] = true;
			}
			else
			{
				// Colision! Duplicate!!
				LOG_INFO( "* " << (*itr)->getType() << "\t" << (*itr)->getSize() << "\t" << (*itr)->getFilePosition() )
			}
		}

		LOG_INFO( "Duplicate search done" );
	}
}