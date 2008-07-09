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

#ifndef BAFPRPIFIELDCONVERTER_H
#define BAFPRPIFIELDCONVERTER_H

#include <string>
#include <map>

#include "bafdefines.h"

namespace bafprp
{
	class IFieldConverter
	{
		friend class FieldMaker;
	public:
		virtual bool getBool() { return 0; }
		virtual int getInt() { return 0; }
		virtual long getLong() { return 0; }
		virtual std::string getString() { return ""; }

		virtual bool convert ( const BYTE* data ) = 0;
		virtual std::string getError() const = 0;
		virtual int getSize() const = 0;

		~IFieldConverter() {}
	protected:
		IFieldConverter() {}
	};

	class FieldMaker
	{
	private:
		typedef std::map<std::string, FieldMaker*> maker_map;

		static maker_map& getReg()
		{
			static maker_map registry;
			return registry;
		}
		FieldMaker() {}
	public:
		static IFieldConverter* newFieldConverter ( std::string type )
		{
			maker_map::iterator itr = getReg().find ( type );
			if ( itr != getReg().end() )
				return itr->second->make();
			return NULL;
		}
	protected:
		FieldMaker ( std::string type )
		{
			getReg().insert ( std::make_pair ( type, this ) );
		}
		virtual IFieldConverter* make() const = 0;
	};
}

#endif