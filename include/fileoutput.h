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


/* NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES
// 
// It is very important that this class does not change
// Do not edit it, copy it, or in the worst case, delete it
// When output encounters a problem it will default to this
// form of output, and if this class is changed you will encounter
// unexpected results.
//
NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES */




#ifndef BAFPRPFILE_H
#define BAFPRPFILE_H

#include <fstream>

#include "output.h"

// Some functions are virtual because the csv output type derives from this class

namespace bafprp
{
	class File : public Output
	{
	public:
	
		void record( const IBafRecord* record );
		void error( const IBafRecord* record, const std::string& error );
		void log( LOG_LEVEL level, const std::string& log );

	protected:
		// Register the output type
		File() : Output( "file" ) {}
		virtual ~File();

		void checkFile( property_map& props, bool start );

		std::ofstream _file;
		std::string _filename;
		std::vector<std::string> _storedFilenames;  // For different output with different filenames
		std::vector<std::string> _usedFilenames;

		// This variable simply initializes a class that registers with the main output code
		static const File registerThis;
	};
}


#endif
