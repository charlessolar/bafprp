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

#ifndef BAFPRPBAFFILE_H
#define BAFPRPBAFFILE_H

#include <string>
#include <stdio.h>

#include "bafdefines.h"

namespace bafprp
{
	class BafFile
	{
	public:
		BafFile();
		BafFile( const std::string filename );
		BafFile( const char* filename );
		~BafFile();

		void open( const std::string filename );
		void open( const char* filename );

		BYTE* getNextRecord();
		BYTE* getCurrentRecord();

	private:
		std::string _filename;
		FILE* _fp;
		long _offset;
	};
} 
#endif