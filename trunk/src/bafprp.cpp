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

#ifdef _WIN32
# include <windows.h>
#endif

#include "baffile.h"
#include "output.h"

using namespace std;
using namespace bafprp;

void print_usage();

int main( int argc, char* argv[] ) 
{	
	Output::setLogLevel( LOG_LEVEL_INFO );

	bool usage_error = true;
	if( argc > 1 )
	{
		usage_error = false;

		for( int ii = 1; ii < argc; ii++ )
		{
			if ( argv[ii][0] == '-' )
			{
				int i = 1;
				switch ( argv[ii][i] )
				{
				case 'v':
				case 'V':
					while( argv[ii][i] == 'v' || argv[ii][i] == 'V' )
						Output::setLogLevel( i++ );
					printf( "Log level set to %d\n\n", i-1 );
					break;
				case 'l':
				case 'L':
					BafFile::listDups = true;
				case 's':
				case 'S':
					Output::setLogLevel( LOG_LEVEL_FATAL );
				default:
					printf( "Invalid option selected: %s\n", argv[ii] );
					usage_error = TRUE;
				}
			}
		}
	}

	if( usage_error )
	{
		print_usage();
		return 1;
	}

	Output::setOutputRecord( "no" );
	Output::setOutputError( "file" );
	Output::setOutputLog( "file" );

	LOG_TRACE( "Global::main" );
	
	cout << "Press return to start process" << endl;
	getchar();

#ifdef _WIN32
	WIN32_FIND_DATAA fdata;
	HANDLE findh = INVALID_HANDLE_VALUE;	
#endif

	for( int ii = 1; ii < argc; ii++ )
	{
		if( argv[ii][0] != '-' )
		{
		#ifdef _WIN32
			findh = FindFirstFileA( argv[ii], &fdata );
			if (findh == INVALID_HANDLE_VALUE)
			{
				cout << "Could not emumerate files of pattern " << argv[ii] << endl;
				LOG_ERROR( "Could not emumerate files of pattern " << argv[ii] );
				return 0;
			}
			do
			{
		#endif
				cout << "Parsing " << fdata.cFileName << " started at " << NowTime() << endl;
				LOG_INFO( "Parsing " << fdata.cFileName << " started" );
				BafFile* file = new BafFile( fdata.cFileName );
				cout << "Parsing " << fdata.cFileName << " ended at " << NowTime() << endl;
				LOG_INFO( "Parsing " << fdata.cFileName << " ended" );
				cout << "Processing " << fdata.cFileName << " started at " << NowTime() << endl;
				LOG_INFO( "Processing " << fdata.cFileName << " started" );
				file->process();
				cout << "Processing " << fdata.cFileName << " ended at " << NowTime() << endl;
				LOG_INFO( "Processing " << fdata.cFileName << " ended" );
				cout << "Cleanup started at " << NowTime() << endl;
				LOG_INFO( "Cleanup started" );
				delete file;
				cout << "Cleanup ended at " << NowTime() << endl;
				LOG_INFO( "Cleanup ended" );
		#ifdef _WIN32
			} while( FindNextFileA( findh, &fdata ) != 0);
		#endif
		}
	}

	
	LOG_TRACE( "/Global::main" );
	cout << "Press any key to exit..." << endl;
	getchar();

	
	return EXIT_SUCCESS;
}

void print_usage()
{
	printf( 
		"Usage: bafprp [-v+] file[s]\n"
		"\n"
		"-v+   Set log level to the number of consecutive v's\n"
		"      Example: -vvvvv means log level 5\n"
		"\n"
		"-l    List duplicates as an info log message before removal\n"
		"\n"
		"-s    Only log FATAL messages\n"
		"\n"
		"file  Any number of files with wildcards such as * and ?\n"
		"\n"
		);
}