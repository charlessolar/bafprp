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

#ifndef BAFPRPNumberSwitch_H
#define BAFPRPNumberSwitch_H

#include "ifield.h"

/*
Generic class for converting NumberSwitch fields
A NumberSwitch field is any field that contains both a switch and a set of digits.
A good example would be the ic inc indicator, which containcs the call CIC and a switch digit
*/

namespace bafprp
{
	class NumberSwitchField : public IField
	{
		friend class NumberSwitchFieldMaker;
	public:
		int getInt() const;
		long getLong() const;
		std::string getString() const;

		bool convert ( const BYTE* data );

		std::string getType() const { return "numberswitch"; }

		~NumberSwitchField();
	private:
		NumberSwitchField();
	};

	class NumberSwitchFieldMaker : public FieldMaker
	{
	public:
		NumberSwitchFieldMaker() : FieldMaker ( "numberswitch" ) {}
	protected:
		IField* make() const;
	private:
		static const NumberSwitchFieldMaker registerThis;
	};

}

#endif
