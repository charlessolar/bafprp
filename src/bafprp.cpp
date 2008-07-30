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
	bool listDups = false;
	Output::setLogLevel( LOG_LEVEL_INFO );

	Output::setOutputRecord( "file" );
	Output::setRecordProperty( "filename", "record.log" );
	Output::setOutputError( "file" );
	Output::setErrorProperty( "filename", "error.log" );
	Output::setOutputLog( "file" );
	Output::setLogProperty( "filename", "log.log" );


	bool usage_error = true;

	std::string prop = "";

	if( argc > 1 )
	{
		usage_error = false;

		for( int ii = 1; ii < argc; ii++ )
		{
			if ( argv[ii][0] == '-' )
			{
				int i = 1;
				int size = strlen( argv[ii] );
				switch ( argv[ii][i] )
				{
				case 'v':
				case 'V':
					while( argv[ii][i] == 'v' || argv[ii][i] == 'V' )
						Output::setLogLevel( i++ );
					printf( "Log level set to %d\n\n", i-1 );
					break;
				case 'd':
				case 'D':
					listDups = true;
					break;
				case 's':
				case 'S':
					Output::setLogLevel( LOG_LEVEL_FATAL );
					break;
				case 'r':
				case 'R':
					Output::setOutputRecord( argv[ii] + 2 );
					break;
				case 'e':
				case 'E':
					Output::setOutputError( argv[ii] + 2 );
					break;
				case 'l':
				case 'L':
					Output::setOutputLog( argv[ii] + 2 );
					break;
				case 'p':
				case 'P':
					int j;
					prop.clear();
					for( j = 3; j < size; j++ )
					{
						if( argv[ii][j] == ':' ) break;
					}
					prop.append( argv[ii], 3, j - 3 );
					j++;
					switch( argv[ii][2] )
					{
					case 'r':
					case 'R':
						Output::setRecordProperty( prop, argv[ii] + j );
						break;
					case 'e':
					case 'E':
						Output::setErrorProperty( prop, argv[ii] + j );
						break;
					case 'l':
					case 'L':
						Output::setLogProperty( prop, argv[ii] + j );
						break;
					default:
						printf( "Invalid output type while setting property: %s\n", argv[ii] );
					}
					break;
				default:
					printf( "Invalid option selected: %s\n", argv[ii] );
					usage_error = true;
				}
			}
		}
	}

	if( usage_error )
	{
		print_usage();
		return 1;
	}

	

	LOG_TRACE( "Global::main" );

#ifdef _WIN32
	WIN32_FIND_DATAA fdata;
	HANDLE findh = INVALID_HANDLE_VALUE;	
#endif

	BafFile* file = new BafFile();

	LOG_INFO( "Running Program" );

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
				std::string dir = std::string( argv[ii] ).substr( 0, std::string( argv[ii] ).find_last_of( "\\" ) + 1 );
				LOG_INFO( "Processing " << fdata.cFileName << " started" );
				if ( !file->process( dir + string( fdata.cFileName ), listDups ) )
				{
					LOG_ERROR( "Error processing " << dir << fdata.cFileName );
				}
				LOG_INFO( "Processing " << dir << fdata.cFileName << " ended" );
				
				LOG_INFO( "Cleanup started" );
				if( !file->clear() )
				{
					LOG_ERROR( "Error clearing " << dir << fdata.cFileName << " record data" );
				}
				LOG_INFO( "Cleanup ended" );

		#ifdef _WIN32
			} while( FindNextFileA( findh, &fdata ) != 0);
		#endif
		}
	}
	if( file ) delete file;
	LOG_INFO( "Program Terminated" );
	
	LOG_TRACE( "/Global::main" );

	return 0;
}

void print_usage()
{
	printf( 
		"Usage: bafprp [-v+] [-rTYPE] [-lTYPE] [-eTYPE] file[s]\n"
		"\n"
		"-r    Set the record output type\n"
		"\n"
		"-l    Set the log output type\n"
		"\n"
		"-e    Set the error output type\n" 
		"\n"
		"-v+   Set log level to the number of consecutive v's\n"
		"      Example: -vvvvv means log level 5\n"
		"\n"
		"-d    List duplicates as an info log message before removal\n"
		"\n"
		"-s    Only log FATAL messages, not recomended\n"
		"\n"
		"file  Any number of files with wildcards such as * and ?\n"
		"\n"
		);
}