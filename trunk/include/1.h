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

#ifndef BAFPRP1_H
#define BAFPRP1_H

#include "ibafrecord.h"

namespace bafprp
{
	class r1 : public IBafRecord
	{
		friend class r1Maker;
	public:
		std::string getType() const;

		~r1();
	protected:
		r1( const BYTE* data, int length, long filePos );
	};

	class r1Maker : public RecordMaker
	{
	public:
		r1Maker() : RecordMaker( 1 ) {}
	protected:
		IBafRecord* make( const BYTE* data, int length, long filePos ) const;
	private:
		static const r1Maker registerThis;
	};
}

#endif