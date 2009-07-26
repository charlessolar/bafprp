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

#include <algorithm>

#include "ifield.h"
#include "output.h"

namespace bafprp
{
	FieldMaker::property_map FieldMaker::_fieldProps;
	FieldMaker::property_map FieldMaker::_typeProps;
	FieldMaker::field_map FieldMaker::_fields;

	IField* FieldMaker::newField( const std::string& type )
	{
		define_default_fields();
		field_map::iterator datatype = _fields.find( type );
		if ( datatype != _fields.end() )
		{
			maker_map::iterator maker = getReg().find( datatype->second );
			if( maker != getReg().end() )
			{
				IField* ret = maker->second->make();
				property_map::iterator props = _fieldProps.find( type );
				if( props != _fieldProps.end() )
					ret->setProperties( props->second );
				
				return ret;
			}
			else
			{
				LOG_ERROR( "Field of type '" << type << "' does not have a registered data type" );
			}	
		}

		LOG_ERROR( "Field of type '" << type << "' could not be made" );
		return NULL;
	}

	void FieldMaker::setFieldProperty( const std::string& fieldtype, const std::string& prop )
	{
		LOG_TRACE( "FieldMaker::setFieldProperty" );
		// 'datatype' property is special, we use it to associate data types and field names
		std::string object = prop.substr( 0, prop.find( ":" ) );
		std::string value = prop.substr( prop.find( ":" ) + 1 );
		if( object == "datatype" )
		{
			_fields.insert( std::make_pair( fieldtype, value ) );

			// Make sure global type properties are created with new field type
			property_map::iterator props = _typeProps.find( value );
			if( props != _typeProps.end() )
			{
				_fieldProps.insert( std::make_pair( fieldtype, props->second ) );
			}
		}
		else
		{
			property_map::iterator itr = _fieldProps.find( fieldtype );
			if( itr != _fieldProps.end() )
				itr->second.insert( std::make_pair( object, value ) );
			else
			{
				// I am writing this comment because at this time I am unsure why I did this
				// It looks like I create a temporary multimap to place into field props
				// so that I can in turn insert a new property object and value.
				// from what I can tell this only happens when the fieldtype is new and thus
				// does not have a multimap.
				// My issue is that it seems kind of dangerous to insert a local multimap like this
				// But I guess it works...  The program must be coping the multimap instead of using
				// the reference.
				LOG_DEBUG( "First field property for datatype " << datatype );
				std::multimap<std::string, std::string> temp;                   // This was a horible idea...
				_fieldProps.insert( std::make_pair( fieldtype, temp ) );
				itr = _fieldProps.find( fieldtype );
				itr->second.insert( std::make_pair( object, value ) );
			}
		}
		LOG_TRACE( "/FieldMaker::setFieldProperty" );
	}

	void FieldMaker::setTypeProperty( const std::string& datatype, const std::string& prop )
	{
		LOG_TRACE( "FieldMaker::setTypeProperty" );
		std::string object = prop.substr( 0, prop.find( ":" ) );
		std::string value = prop.substr( prop.find( ":" ) + 1 );
		property_map::iterator itr = _typeProps.find( datatype );
		if( itr != _typeProps.end() )
			itr->second.insert( std::make_pair( object, value ) );
		else
		{
			LOG_DEBUG( "First type property for datatype " << datatype );
			std::multimap<std::string, std::string> temp;
			_typeProps.insert( std::make_pair( datatype, temp ) );
			itr = _typeProps.find( datatype );
			itr->second.insert( std::make_pair( object, value ) );
		}
		LOG_TRACE( "/FieldMaker::setTypeProperty" );
	}

	void IField::setProperties( property_map& props )
	{
		_properties = &props;
	}

	// This function will return all properties matching name
	std::vector<std::string> IField::getProperty( const std::string& name ) const
	{
		std::vector<std::string> ret;
		props_pair props = _properties->equal_range( name );
		for( property_map::const_iterator itr = props.first; itr != props.second; itr++ )
		{
			ret.push_back( itr->second );
		}
		return ret;
	}

	// This function will return the most recent property matching name
	// This is used incase you have a property like filter which can be set
	// false at the beginging, then set true by the user later on.
	std::string IField::getProperty( const std::string& name, bool one ) const
	{
		std::string ret = "";
		props_pair props = _properties->equal_range( name );
		if( props.first == props.second ) return "";
		property_map::const_iterator prop = props.second;  // The 'second' iterator is the element right after the element we were looking for, and is NOT the element we were looking for
															// So in order to get the last element that we WERE looking for, decrement this guy.
		prop--;
		return prop->second;
	}

	int IField::getSize() const
	{
		return atoi( getProperty( "size", true ).c_str() ); 
	}

	std::string IField::getID() const
	{
		return getProperty( "id", true );
	}

	std::string IField::getDesc() const
	{
		return getProperty( "desc", true );
	}

	bool IField::filter() const
	{
		if( getProperty( "filter", true ) == "true" )
			return true;
		return false;
	}
}