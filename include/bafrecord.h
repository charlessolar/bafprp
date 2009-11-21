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

#ifndef BAFPRPBAFRECORD_H
#define BAFPRPBAFRECORD_H

#include "ifield.h"

namespace bafprp
{
	class BafRecord
	{
		friend class RecordMaker;
	protected:
		typedef std::multimap<std::string, std::string> property_map;
		typedef std::pair<property_map::const_iterator, property_map::const_iterator> props_pair;

	public:
		bool hasField( const std::string& name ) const;
		const IField* getField( const std::string& name ) const;
		const IField* getNextField( DWORD last = 0 ) const;

		std::string getType() const;
		int getTypeCode() const { return _type; }

		int getSize() const { return _length; }

		std::string getData() const { return getChars( _data, _length  * 2   ); }
		long getFilePosition() const { return _filePos; }

		DWORD getCRC() const { return _crc; }
		std::string getFilename() const { return _filename; }

		virtual ~BafRecord() {}
	private:
		BafRecord( const BYTE* data, int length, const std::string& filename, long filePos );

		void addField( const std::string& field_type );
		void setProperties( property_map& props ) { _properties = &props; }

		void decodeModules();

		typedef std::vector<IField*> field_vector;
		// To perform queries on field types we need to keep a second vector around
		// using a map will cause the record output to be alphabetized which is not
		// desired.
		typedef std::vector<std::string> field_type_vector;
		field_vector _fields;
		field_type_vector _field_types;

		int _type;
		int _length;
		bool _modules;
		DWORD _crc;
		std::string _filename;
		long _filePos;

		property_map* _properties;
				
		const BYTE* _fieldData;  // The data pointer we are allowed to modify
		const BYTE* _data;  // This one needs to stay constant since we have to delete it later
	};

	class RecordMaker
	{
	private:
		typedef std::map<int, std::multimap<std::string, std::string> > property_map;
		typedef std::pair<property_map::const_iterator, property_map::const_iterator> props_pair;
		typedef std::map<int, std::vector<std::string> > field_map;

		RecordMaker() {}
		
		static property_map _recordProps;
		static field_map _recordFields;
	public:
		static BafRecord* newRecord( const BYTE* data, int length, const std::string& filename, long filePos );
		static void setRecordField( int record, const std::string& fieldName );
		static void setRecordProp( int record, const std::string& prop );
	};

	void define_default_records();
}

#endif