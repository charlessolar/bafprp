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

#include "filesequenceno.h"
#include "output.h"

namespace bafprp
{
	const FileSequenceNoFieldMaker FileSequenceNoFieldMaker::registerThis;

	IField* FileSequenceNoFieldMaker::make() const
	{
		LOG_TRACE( "FileSequenceNoFieldMaker::make" );
		return new FileSequenceNo();
		LOG_TRACE( "FileSequenceNoFieldMaker::make" );
	}

	FileSequenceNo::FileSequenceNo() : IField()
	{
		LOG_TRACE( "FileSequenceNo::FileSequenceNo" );
		LOG_TRACE( "/FileSequenceNo::FileSequenceNo" );
	}


	FileSequenceNo::~FileSequenceNo()
	{
		LOG_TRACE( "FileSequenceNo::~FileSequenceNo" );
		LOG_TRACE( "/FileSequenceNo::~FileSequenceNo" );
	}

	bool FileSequenceNo::convert ( const BYTE* data )
	{
		LOG_TRACE( "FileSequenceNo::convert" );
		_return = getChars( data, getSize() );
		LOG_TRACE( "/FileSequenceNo::convert" );
		return true;
	}

	long FileSequenceNo::getLong()
	{
		LOG_TRACE( "FileSequenceNo::getLong" );
		LOG_TRACE( "/FileSequenceNo::getLong" );
		return atol( _return.c_str() );
	}

	int FileSequenceNo::getInt()
	{
		LOG_TRACE( "FileSequenceNo::getInt" );
		LOG_TRACE( "/FileSequenceNo::getInt" );
		return atoi( _return.c_str() );
	}

	std::string FileSequenceNo::getString()
	{
		LOG_TRACE( "FileSequenceNo::getString" );
		LOG_TRACE( "/FileSequenceNo::getString" );
		return _return;
	}
}