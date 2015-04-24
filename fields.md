# Fields #

Fields in bafprp are the individual elements of records.  Each record is made of about 10-15 fields on average, these fields vary in data type and purpose, therefore a generic type system was created to accommodate all the different kinds of fields.
In addition to this type system bafprp 1.2 introduced the ability to change the behavior of fields through a property system integrated into the command line.  What follows is a description of each field type and the properties available.

**Note** Values are case sensitive

Also due to technical limitations with the argument list, properties with spaces will not work correctly.  This is a known issue but currently has no time period for a solution.

While the command line will set these properties, it is recommended that users edit the field\_defs.cpp and recompile the program to add properties just for the sake of simplicity and compatibility.

For a list of all compatible field types in bafprp refer to the field\_def.cpp file.  This file will tell you the name of the individual field as well as a brief description.
Someday a complete list of each field name may be posted but that project is not a priority at the moment.

## Date ##
This field type stores and converts date information.

**Properties**

format - change the format of the date, the property is a string where the characters Y M D are replaced with the year, month and day respectively.
The following are valid settings

  * Y-M-D
  * D/M/Y
  * M:D:Y
  * ~M~D~~Y

## Number ##
This field type is for generic numbers

**Properties**

trim - trim leading zeros, use 'true' to set

## Phone Number ##
This field holds phone numbers

**Properties**

hyphens - set to 'false' to remove hyphens from the number

## Switch ##
This field holds one or more switch data types, meaning that one number in the field corresponds to a string based on the value of the number ( switch statement )

**Properties**

switch - set the position in the field in which a switch should be used, position starting from 0

`[switch][number]` - Will set the string value of the `[switch]` switch for value `[number]`

`[switch]` and `[number]` are both 1 digit and the value is the string value for that position

Example of a switch type:

```
FieldMaker::setFieldProperty( "timingindicator", "switch:0" );
FieldMaker::setFieldProperty( "timingindicator", "00:Default" );
FieldMaker::setFieldProperty( "timingindicator", "01:Time Release Disconnect" );
FieldMaker::setFieldProperty( "timingindicator", "02:Timing Guard Condition" );
FieldMaker::setFieldProperty( "timingindicator", "03:Single Time Line" );
FieldMaker::setFieldProperty( "timingindicator", "04:Unanswered Call Release" );
FieldMaker::setFieldProperty( "timingindicator", "switch:1" );
FieldMaker::setFieldProperty( "timingindicator", "10:Default" );
FieldMaker::setFieldProperty( "timingindicator", "11:Short called party off-hook detected" );
FieldMaker::setFieldProperty( "timingindicator", "12:Under minimum chargeable" );
FieldMaker::setFieldProperty( "timingindicator", "13:SST&UMCD" );
FieldMaker::setFieldProperty( "timingindicator", "14:SST" );
```

## Number Switch ##
This field combines both a switch and a basic number.  The syntax is the same as a switch for switches, however one new property is introduced for handling numbers

**Properties**

switch - see above

number - set the position and length of a number type section of the field
The value of this property is first the potion of the number and then the length.  Both numbers must be 1 digit long, meaning numbers longer than 9 digits or more than 9 digits from the start are not supported.

number\_only - only display the number type when returning data.  Because of technical limitations, only the first number will be printed if two or more exist

Example of a number switch type:

```
FieldMaker::setFieldProperty( "structurecode", "switch:0" );
FieldMaker::setFieldProperty( "structurecode", "00:No Modules Attached" );
FieldMaker::setFieldProperty( "structurecode", "04:Modules Attached" );
FieldMaker::setFieldProperty( "structurecode", "number:14" );
FieldMaker::setFieldProperty( "structurecode", "number_only:true" );
```