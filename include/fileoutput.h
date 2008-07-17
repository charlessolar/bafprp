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

#ifndef BAFPRPFILE_H
#define BAFPRPFILE_H

#include "output.h"

namespace bafprp
{
	class File : public Output
	{
	public:
		// Register the output type
		File();
		~File();

		void record( const IBafRecord* record );
		void error( const IBafRecord* record, const std::string error );
		void log( const std::string log );

	private:
		FILE* _fp;
		// This variable simply initializes a class that registers with the main output code
		static const File registerThis;
	};
}


#endif