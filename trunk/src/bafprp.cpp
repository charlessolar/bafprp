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


#include <iostream>
#include <string>
#include <cstdlib>

//#include "ifieldconverter.h"

//using namespace baftouch;
using namespace std;

int main ( int argc, char *argv[] )
{
	unsigned char input[10];
	cout << "Try it out: ";
	cin >> input;
	
	//IFieldConverter* tool = FieldMaker::newFieldConverter( "structuretype" );
	cout << "Converting: " << input << endl;
	//tool->convert( (BYTE*)0x13377 );
	//cout << "Here you go: " << tool->getLong() << " and " << tool->getString() << endl;
	//delete tool;

	int temp;
	cin >> temp;

	return EXIT_SUCCESS;
}