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

#ifndef BAFPRP9013_H
#define BAFPRP9013_H

#include "ibafrecord.h"

namespace bafprp
{
	class r9013 : public IBafRecord
	{
		friend class r9013Maker;
	public:
		std::string getType() const;

		~r9013();
	protected:
		r9013( const BYTE* data, int length, long filePos );
	};

	class r9013Maker : public RecordMaker
	{
	public:
		r9013Maker() : RecordMaker( 9013 ) {}
	protected:
		IBafRecord* make( const BYTE* data, int length, long filePos ) const;
	private:
		static const r9013Maker registerThis;
	};
}

#endif