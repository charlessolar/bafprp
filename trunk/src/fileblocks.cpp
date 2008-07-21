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

#include "fileblocks.h"
#include "output.h"

namespace bafprp
{
	const FileBlocksFieldMaker FileBlocksFieldMaker::registerThis;

	IField* FileBlocksFieldMaker::make() const
	{
		LOG_TRACE( "FileBlocksFieldMaker::make" );
		LOG_TRACE( "/FileBlocksFieldMaker::make" );
		return new FileBlocks;
		
	}

	FileBlocks::FileBlocks() : IField()
	{
		LOG_TRACE( "FileBlocks::FileBlocksFieldConverter" );
		LOG_TRACE( "/FileBlocks::FileBlocksFieldConverter" );
	}


	FileBlocks::~FileBlocks()
	{
		LOG_TRACE( "FileBlocks::~FileBlocksFieldConverter" );
		LOG_TRACE( "/FileBlocks::~FileBlocksFieldConverter" );
	}

	bool FileBlocks::convert ( const BYTE* data )
	{
		LOG_TRACE( "FileBlocks::convert" );
		_return = getChars( data, getSize() );
		_converted = true;

		if( _return.length() != getSize() ) 
		{
			_lastError = "Data read is not the correct size";
			_converted = false;
		}

		LOG_TRACE( "/FileBlocks::convert" );
		return _converted;
	}

	int FileBlocks::getInt() const
	{
		LOG_TRACE( "FileBlocks::getInt" );

		int ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get int before field was converted" );
			ret = 0;
		}
		else
			ret = atoi( _return.c_str() );

		LOG_TRACE( "/FileBlocks::getInt" );
		return ret;
	}

	long FileBlocks::getLong() const
	{
		LOG_TRACE( "FileBlocks::getLong" );

		long ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get long before field was converted" );
			ret = 0;
		}
		else
			ret = atol( _return.c_str() );

		LOG_TRACE( "/FileBlocks::getLong" );
		return ret;
	}

	std::string FileBlocks::getString() const
	{
		LOG_TRACE( "FileBlocks::getString" );

		std::string ret;
		if( !_converted )
		{
			LOG_WARN( "Tried to get string before field was converted" );
			ret = "";
		}
		else
			ret = _return;

		LOG_TRACE( "/FileBlocks::getString" );
		return ret;
	}
}
