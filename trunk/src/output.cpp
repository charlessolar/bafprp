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

#include "output.h"

namespace bafprp
{
	std::string Output::_output;

	Output::Output( const std::string name )
	{
		getReg().insert( std::make_pair( name, this ) );
	}

	Output::~Output()
	{
	}

	void Output::recordOutput( BafRecord* record )
	{
	}

	void Output::errorOutput( BafRecord* record, const std::string error )
	{
	}

	void Output::logOutput( LOG_LEVEL level, const std::string log )
	{
		std::ostringstream op;

		output_map::iterator itr = getReg().find( _output );
		if( itr != getReg().end() )
			itr->second->log( log );
		else
			getReg().begin()->second->log( "Output type " + _output + " does not exist." );  // If output is set wrong, use one that works.
	}


}