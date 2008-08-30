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
		field_map::iterator datatype = _fields.find ( type );
		if ( datatype != _fields.end() )
		{
			maker_map::iterator maker = getReg().find( datatype->second );
			if( maker != getReg().end() )
			{
				IField* ret = maker->second->make();
				ret->setProperty( "id", type );
				props_pair props;
				// Set data type global properties
				props = _typeProps.equal_range( datatype->second );
				for( property_map::const_iterator prop = props.first; prop != props.second; prop++ )
				{
					int pos = prop->second.find( ":" );
					if( pos == std::string::npos ) 
					{
						LOG_WARN( "Tried to set an invalid property: " << prop->second << " for field type: " << type );
					}
					else
						ret->setProperty( prop->second.substr( 0, pos ), prop->second.substr( pos + 1 ) );
				}
				// Set field type specific properties
				props = _fieldProps.equal_range( type );
				for( property_map::const_iterator prop = props.first; prop != props.second; prop++ )
				{
					int pos = prop->second.find( ":" );
					if( pos == std::string::npos ) 
					{
						LOG_WARN( "Tried to set an invalid property: " << prop->second << " for field type: " << type );
					}
					else
						ret->setProperty( prop->second.substr( 0, pos ), prop->second.substr( pos + 1 ) );
				}
				return ret;
			}
			else
			{
				LOG_ERROR( "Field of type '" << type << "' does not have a registered data type" );
			}	
		}

		LOG_ERROR( "Field of type \"" << type << "\" could not be made" );
		return NULL;
	}

	void FieldMaker::setFieldProperty( const std::string& fieldtype, const std::string& prop )
	{
		// 'ndatatype' property is special, we use it to associate data types and field names
		std::string object = prop.substr( 0, prop.find( ":" ) );
		std::string value = prop.substr( prop.find( ":" ) + 1 );
		if( object == "datatype" )
		{
			_fields.insert( std::make_pair( fieldtype, value ) ) );

			//Make sure global type properties are created with new field type
			props_pair props = _typeProps.equal_range( value );
			for( property_map::const_iterator prop = props.first; prop != props.second; prop++ )
			{
				int pos = prop->second.find( ":" );
				if( pos == std::string::npos ) 
				{
					LOG_WARN( "Tried to set an invalid property: " << prop->second << " for field type: " << type );
				}
				else
					_fieldProps.insert( fieldtype, std::make_pair( prop->second.substr( 0, pos ), prop->second.substr( pos + 1 ) ) );
			}
		}
		else
			_fieldProps.insert( std::make_pair( fieldtype, std::make_pair( object, value ) ) );
	}

	void FieldMaker::setTypeProperty( const std::string& fieldtype, const std::string& prop )
	{
			_typeProps.insert( std::make_pair( fieldtype, prop ) );
	}

	void IField::setProperties( props_pair props )
	{
		_props = props;
		if( prop == "id" ) 
			_id = value;
		else if( prop == "desc" )
			_desc= value;
		else if( prop == "size" )
			_size = atoi( value.c_str() );
		else if( prop == "filter" )
		{
			if( value == "yes" || value == "true" || value == "y" || value == "t" || value == "1" )
				_filter = true;
			else
				_filter = false;
		}
		else
		{
			std::vector<std::string>::iterator itr = std::find( _replaceProperties.begin(), _replaceProperties.end(), prop );
			property_map::iterator theProp = _properties.find( prop );
			// To be REPLACED instead of added when set, the property must be in the _replaceProperties vector
			// or by less then 3 characters long.
			// The 3 character this is for overriding switch properties, we do not want to add them all to the replace vector
			// but we might want to over ride their strings
			if( ( itr != _replaceProperties.end() || prop.length() < 3 ) && theProp != _properties.end() )
			{
				// Replace the variable do not simply insert it
				theProp->second = value;				
			}
			else
			_properties.insert( std::make_pair( prop, value ) );		
		}
	}

	int getSize() const
	{
		std::find_end( _props.first, _props.end, 
	}

	std::string getID() const
	{
	}

	std::string getDesc() const
	{
	}

	bool filter() const
	{
	}
}