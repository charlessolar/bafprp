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

#ifndef BAFPRPSwitch_H
#define BAFPRPSwitch_H

#include "ifield.h"

/*
Generic class for converting Switch fields
A Switch field is a field that is usually 1 digit and stands for a specific string designated by that digit.
Like an enumeration.

However there are some very complex switches in the BAF format, such as multiple switch digits, or a switch and some numbers,
through some very complex property management this class will need to handle these types as well.
*/

namespace bafprp
{
	class SwitchField : public IField
	{
		friend class SwitchFieldMaker;
	public:
		int getInt() const;
		long getLong() const;
		std::string getString() const;

		bool convert ( const BYTE* data );

		std::string getType() const { return "switch"; }

		~SwitchField();
	private:
		SwitchField();
	};

	class SwitchFieldMaker : public FieldMaker
	{
	public:
		SwitchFieldMaker() : FieldMaker ( "switch" ) {}
	protected:
		IField* make() const;
	private:
		static const SwitchFieldMaker registerThis;
	};

}

#endif
