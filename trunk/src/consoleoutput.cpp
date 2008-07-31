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
#include <ios>
#include <iomanip>

#include "consoleoutput.h"
#include "baffile.h"

namespace bafprp
{
	const Console Console::registerThis;

	void Console::error( const IBafRecord* record, const std::string& error )
	{
		LOG_TRACE( "Console::error" );

		std::cout.setf( std::ios::left );

		std::cout << "* Record Error *********************************************" << std::endl;
		std::cout << "*                                                          *" << std::endl;
		std::cout << "*    " << std::setw(53) << NowTime() << " *" << std::endl;

		std::cout << "*                                                          *" << std::endl;

		std::string rest = "";
		int space = 0;

		space = error.substr( 0, 48 ).find_last_of( " " );
		if( space == std::string::npos )
				space = 48;

		std::cout << "* Report: " << std::setw( 48 ) << error.substr( 0, space ) << " *" << std::endl;

		// Avoid the out_of_range exception
		if( error.length() > 48 )
			rest = error.substr( space + 1 );		
		
		// I like neatly formated messages.
		while( rest != "" )
		{
			if( rest.length() > 49 ) 
			{
				space = rest.substr( 0, 48 ).find_last_of( " " );
				if( space == std::string::npos )
					space = 48;
			}
			

			std::cout << "*         " << std::setw( 48 ) << rest.substr( 0, space ) << " *" << std::endl;

			if( rest.length() > 49 )	
				rest = rest.substr( space + 1 );
			else
				rest = "";
		}

		std::cout << "*                                                          *" << std::endl;
		std::cout << "* Details: Type: " << std::setw(41) << record->getType() << " *" << std::endl;
		std::cout << "*          Length: " << std::setw(39) << record->getSize() << " *" << std::endl;
		std::cout << "*          Position: " << std::setw(37) << record->getFilePosition() << " *" << std::endl;
		std::cout << "*          Filename: " << std::setw(37) << record->getFilename() << " *" << std::endl;

		std::cout << "*                                                          *" << std::endl;
		std::string bytes = record->getData();
		std::cout << "* BYTES: " << std::setw(49) << bytes.substr( 0, 48 ) << " *" << std::endl;

		rest = "";

		if( bytes.length() > 48 )
			rest = bytes.substr( 48 );
		
		while( rest != "" )
		{
			std::cout << "*        " << std::setw(49) << rest.substr( 0, 48 ) << " *" << std::endl;

			if( rest.length() > 48 )
				rest = rest.substr( 48 );
			else
				rest = "";
		}
		std::cout << "*                                                          *" << std::endl;
		std::cout << "************************************************************" << std::endl;

		LOG_TRACE( "/Console::error" );
	}

	void Console::log( LOG_LEVEL level, const std::string& log )
	{
		std::cout << "- " << NowTime() << " " << getStrLogLevel( level ) << ": " << log << std::endl;
	}

	void Console::record( const IBafRecord* record )
	{
		LOG_TRACE( "Console::record" );

		const IField* field;
		std::string value = "";
		DWORD lastUID = 0;

		std::cout << "--------------------------------------------------------------------------" << std::endl;
		std::cout << record->getType() << std::endl;
		std::cout << "--------------------------------------------------------------------------" << std::endl;
		std::cout << "Length of record: " << record->getSize() << std::endl;
		std::cout << "--------------------------------------------------------------------------" << std::endl;
		std::cout << "File: " << record->getFilename() << std::endl;
		std::cout << "--------------------------------------------------------------------------" << std::endl;
		std::cout << "Position: " << record->getFilePosition() << std::endl;
		std::cout << "--------------------------------------------------------------------------" << std::endl;

		// sending a last name of "" effectively returns us the begining, getting the ball rolling.
		while( ( field = record->getNextField( lastUID ) ) != NULL )
		{
			lastUID = field->getUID();
			std::cout << field->getName() << ": " << field->getString() << std::endl;
		}

		LOG_TRACE( "/Console::record" );
	}

}
