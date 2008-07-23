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

#include <fstream>

#include "baffile.h"
#include "output.h"

#include "Duplicate.h"

namespace bafprp
{
	bool BafFile::listDups = false;

	BafFile::BafFile( const std::string filename ) : _filename( filename )
	{
		LOG_TRACE( "BafFile::BafFile" );
		if( !open( _filename ) ) return;
		LOG_TRACE( "/BafFile::BafFile" );
	}

	BafFile::BafFile(const char *filename) : _filename( filename )
	{
		LOG_TRACE( "BafFile::BafFile" );
		if( !open( _filename ) ) return;
		LOG_TRACE( "/BafFile::BafFile" );
	}

	BafFile::~BafFile()
	{
		LOG_TRACE( "BafFile::~BafFile" );

		_filename.clear();
		
		// Clean up records
		for( std::vector<IBafRecord*>::iterator itr = _records.begin(); itr != _records.end(); itr++ )
		{
			delete *itr;
		}

		delete[] _fileData;

		LOG_TRACE( "/BafFile::~BafFile" );
	}

	bool BafFile::readRecord()
	{
		LOG_TRACE( "BafFile::getNextRecord" );
		
		_length_of_record = ( _fileData[_offset] * 256 ) + _fileData[_offset + 1];

		IBafRecord* record = RecordMaker::newRecord( _fileData + _offset, _length_of_record, _offset ); 
		if( record )
		{
			Output::outputRecord( record );	
			_records.push_back( record );
		}
		
		_offset += _length_of_record;

		LOG_TRACE( "/BafFile::getNextRecord" );
		return true;
	}

	bool BafFile::open( const std::string filename )
	{
		LOG_TRACE( "BafFile::open" );


		std::ifstream file( filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate );
		int size;
		if( file.is_open() )
		{
			size = file.tellg();
			_fileData = new BYTE[size];
			file.seekg( 0, std::ios::beg );
			file.read( (char*)_fileData, size );
			file.close();
		}
		else
		{
			LOG_ERROR( "Could not open file: " << filename );
			return false;
		}

		//std::string string = getChars( _fileData, 41 );
		//printf( string.c_str() );

		_offset = 0;
		// This needs a redesign
		while( _offset < size )
		{
			readRecord();
		}
		LOG_INFO( "Read and Parsed " << _records.size() << " records" );

		LOG_TRACE( "/BafFile::open" );
		return true;
	}

	void BafFile::process()
	{
		LOG_TRACE( "BafFile::process" );
		LOG_INFO( "Records: " << _records.size() );
		if( listDups ) Duplicate::list( _records );
		Duplicate::remove( _records );
		LOG_INFO( "Records: " << _records.size() );
		LOG_TRACE( "/BafFile::process" );
	}
}