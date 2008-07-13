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

#ifndef BAFPRPIOUTPUT_H
#define BAFPRPIOUTPUT_H

#include <string>

#include "bafrecord.h"

namespace bafprp
{
	// Interface for defining custom output
	class IOutput
	{
	protected:
		IOutput() {}
	public:
		virtual void processRecord( BafRecord* record ) = 0;
		virtual void processError( BafRecord* record, const std::string error ) = 0;
		virtual void processLog( const std::string log ) = 0;

		enum
		{
			LOG_LEVEL_TRACE = 0,
			LOG_LEVEL_DEBUG,
			LOG_LEVEL_WARN,
			LOG_LEVEL_ERROR,
			LOG_LEVEL_FATAL
		} LOG_LEVEL;

		void setLogLevel( LOG_LEVEL level ) { _level = level; }

	private:
		LOG_LEVEL _level;
	};
}

#endif