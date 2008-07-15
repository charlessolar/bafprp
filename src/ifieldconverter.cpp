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

#include "ifieldconverter.h"
#include "output.h"

namespace bafprp
{

	IFieldConverter* FieldMaker::newFieldConverter( std::string type )
	{
		maker_map::iterator itr = getReg().find ( type );
		if ( itr != getReg().end() )
			return itr->second->make();

		LOG_ERROR( "Field Converter of type \"" << type << "\" could not be found" );
		return NULL;
	}

}