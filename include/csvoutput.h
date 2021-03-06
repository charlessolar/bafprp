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

#ifndef BAFPRPCSV_H
#define BAFPRPCSV_H

#include <fstream>

#include "output.h"

namespace bafprp
{
	class CSV : public Output
	{
	public:

		void record( const BafRecord* record );
		void error( const BafRecord* record, const std::string& error );
		void log( LOG_LEVEL level, const std::string& log );
		
	protected:
		// Register the output type
		CSV() : Output( "csv" ) {}
		virtual ~CSV();

		void checkFile( property_map& props, bool start );

		std::ofstream _file;
		std::string _filename;
		std::vector<std::string> _storedFilenames;  // For different output with different filenames
		std::vector<std::string> _usedFilenames;

	private:
		void StringExplode( std::string str, const std::string& separator, std::vector<std::string>* results );
		std::string sanitize( const std::string& string, const std::string& delimeter );

		// This variable simply initializes a class that registers with the main output code
		static const CSV registerThis;
	};
}

#endif