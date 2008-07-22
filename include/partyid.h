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

#ifndef BAFPRPPARTYID_H
#define BAFPRPPARTYID_H

#include "ifield.h"

namespace bafprp
{
	class PartyID : public IField
	{
		friend class PartyIDFieldMaker;
	public:
		int getInt() const;
		long getLong() const;
		std::string getString() const;

		bool convert ( const BYTE* data );

		int getSize() const { return 3; }
		std::string getType() const { return "string"; }
		std::string getName() const { return "Party Identifier"; }

		~PartyID();
	private:
		PartyID();
	};

	class PartyIDFieldMaker : public FieldMaker
	{
	public:
		PartyIDFieldMaker() : FieldMaker( "partyid" ) {}
	protected:
		IField* make() const;
	private:
		static const PartyIDFieldMaker registerThis;
	};

}

#endif