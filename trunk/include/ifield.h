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

#ifndef BAFPRPIFIELD_H
#define BAFPRPIFIELD_H

#include <cstdlib>
#include <string>
#include <map>
#include <vector>

#include "bafdefines.h"


namespace bafprp
{
	class IField
	{
		friend class FieldMaker;
	protected:
		typedef std::multimap<std::string, std::string> property_map;
		typedef std::pair<property_map::const_iterator, property_map::const_iterator> props_pair;

	public:
		virtual bool getBool() const { return 0; }
		virtual int getInt() const { return 0; }
		virtual long getLong() const { return 0; }
		virtual float getFloat() const { return 0.0f; }
		virtual std::string getString() const { return ""; }

		std::string getError() const { return _lastError; }
		DWORD getUID() const { return _uid; }
		
		virtual bool convert ( const BYTE* data ) = 0;
		
		// returns a generic type that would most easily be asociated with the type of data
		// useful for sql output
		virtual std::string getType() const = 0;
		
		int getSize() const;
		std::string getID() const;
		std::string getDesc() const;
		bool filter() const;
		void setProperties( property_map& props );

		~IField() {}
	protected:
		IField() : _converted(false), _return(""), _lastError(""), _filter( false ), _id("[NO ID]"), _desc("[NO DESC]"), _size(0)
		{
			// each field needs a unique id so we can safely list them with a 'getNext' in the record class.
			static DWORD uid_counter = 0;
			_uid = uid_counter++;
		}

		std::vector<std::string> getProperty( const std::string& name ) const;
		std::string getProperty( const std::string& name, bool one ) const;

		bool _converted;
		std::string _return;
		std::string _lastError;

		// Global properties
		std::string _id;
		std::string _desc;
		int _size;
		bool _filter;  // Will not return data if true
		
		property_map* _properties; // For individual field type properties
	private:
		DWORD _uid;
	};

	class FieldMaker
	{
	private:
		typedef std::map<std::string, FieldMaker*> maker_map;
		typedef std::map<std::string, std::multimap<std::string, std::string> > property_map;
		typedef std::pair<property_map::const_iterator, property_map::const_iterator> props_pair;
		typedef std::map<std::string, std::string> field_map;
		typedef std::multimap<std::string, std::string> field_props;

		static maker_map& getReg()
		{
			static maker_map registry;
			return registry;
		}
		FieldMaker() {}

		static field_map _fields;
		static property_map _fieldProps;
		static property_map _typeProps;
	public:
		static IField* newField( const std::string& type );
		static void setFieldProperty( const std::string& fieldType, const std::string& prop );
		static void setTypeProperty( const std::string& dataType, const std::string& prop );
	protected:
		FieldMaker( const std::string& type )
		{
			getReg().insert( std::make_pair ( type, this ) );
		}
		virtual IField* make() const = 0;
	};

	void define_default_fields();
}

#endif
