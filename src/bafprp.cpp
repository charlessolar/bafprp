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


// General purpose testing while building converters.



#include <iostream>
#include <cstdio>

#include "baffile.h"
#include "output.h"

using namespace bafprp;
using namespace std;

int main ( int argc, char *argv[] )
{	
	Output::setLogLevel( LOG_LEVEL_DEBUG );
	Output::setOutput( "file" );
	LOG_TRACE( "Global::main" );
	

	BafFile* file = new BafFile( "baf.pri" );
	BafRecord* record;

	while( file->isOpen() && ( record = file->getNextRecord() ) != NULL )
	{
		delete record;
	}

	file->close();

	/*
	IFieldConverter* tool = FieldMaker::newFieldConverter( "structuretype" );
	BYTE* test = (BYTE*)"\x12\x34\x56\x78";
	cout << "Converting: " << test << endl;
	tool->convert( test );
	cout << "Here you go: " << tool->getLong() << " and " << tool->getString() << endl;
	delete tool;
	*/

	LOG_TRACE( "/Global::main" );
	cout << "Press any key to exit..." << endl;
	getchar();

	
	return EXIT_SUCCESS;
}