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

#ifndef BAFPRPBAFRECORD_H
#define BAFPRPBAFRECORD_H

#include <map>

#include "bafdefines.h"
#include "ifieldconverter.h"


namespace bafprp
{
	class IBafRecord
	{
	public:
		virtual IFieldConverter* getField( std::string name ) = 0;
		virtual IFieldConverter* getNextField() = 0;
		
		virtual ~IBafRecord();	
	protected:
		IBafRecord( const BYTE* data, int length );
			
		typedef std::map<std::string, IFieldConverter*> field_map;
		field_map _fields;

		int _length;
		BYTE* _data;
	};

	class RecordMaker
	{
	private:
		typedef std::map<int, RecordMaker*> maker_map;

		static maker_map& getReg()
		{
			static maker_map registry;
			return registry;
		}
		RecordMaker() {}
	public:
		static IBafRecord* newRecord( const BYTE* data, int length );
	protected:
		RecordMaker( int type )
		{
			getReg().insert ( std::make_pair ( type, this ) );
		}
		virtual IBafRecord* make( const BYTE* data, int length ) const = 0;
	};
}

#endif