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

#ifndef BAFPRPSHORTDURATION_H
#define BAFPRPSHORTDURATION_H

#include "ifield.h"

/*
Generic class for converting Short Duration fields
A Short Duration field is any field that describes a solitary Short Duration, nothing special
*/

namespace bafprp
{
	class ShortDurationField : public IField
	{
		friend class ShortDurationFieldMaker;
	public:
		int getInt() const;
		long getLong() const;
		float getFloat() const;
		std::string getString() const;

		bool convert ( const BYTE* data );

		std::string getType() const { return "shortduration"; }

		~ShortDurationField();
	private:
		ShortDurationField();
	};

	class ShortDurationFieldMaker : public FieldMaker
	{
	public:
		ShortDurationFieldMaker() : FieldMaker ( "shortduration" ) {}
	protected:
		IField* make() const;
	private:
		static const ShortDurationFieldMaker registerThis;
	};

}

#endif
