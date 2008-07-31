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

#include "bafdefines.h"
#include "ibafrecord.h"

namespace bafprp
{
	class BafFile
	{
	public:
		BafFile();
		~BafFile();

		bool read( const std::string& filename );
		bool parse( const std::string& filename );
		bool process( const std::string& filename, bool listDups = false );
		bool clear();  // reset 

		std::string getFilename() { return _filename; }

	private:
		bool readRecord();

		std::string _filename;
		long _fileSize;
		BYTE* _fileData;
		long _offset;
		int _length_of_record;

		std::vector<IBafRecord*> _records;
	};
} 
#endif