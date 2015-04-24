# Command Line Options #

Bafprp can be completely controlled using the supplied command line options, so users who do not want to mess with the code can run the program.  These options follow a general format which is described below.

## Switching Output Forms ##

To switch forms of output for each output type, you use the -r, -e, or -l options followed by the form name.  For example, if you want to have logs print in the console, and records recorded to files, you would use

```
bafprp -rfile -lconsole
```

## Supplying Properties ##

Some more complicated output forms require certain properties to be supplied.  To see what options are available for each for please refer to the OutputTypes output types page.  To set these properties you use the following syntax

```
-p(type)(property):(value)
```

Type should be the 1 letter abbreviation for the output type, either r, e, or l for records, errors, or logs respectively.

Example:
To set the filename property for file output
```
bafprp -rfile -prfilename:myrecords.log
```

To set a destination email for email output
```
bafprp -remail -prto:me@test.net -prfrom:bafprp -prserver:mail.test.net
```

It should be noted that properties only exist for their specific output type.  You cannot share properties amongst the different output types.  If you wish to email both logs and records, you must supply the to, from, and server for both.
It should also be noted that supplying extra properties will not hurt the programs operation.  Say for instance you want to switch from file output to email output, this command works just fine
```
bafprp -remail -prfilename:records.log -prto:me@test.net -prfrom:bafprp -prserver:mail.test.net
```
Notice the extra filename property.

# Advanced Properties #

In Bafprp v1.2 and greater, we introduced the ability to supply program altering properties.  These properties can do everything from defining a completely new field for immediate use in the program, to removing the hyphens from phone numbers.

To use these properties two new property types were created, **t** and **f**.  These types refer to field type and field name respectively.  When setting properties the user has two choices.  They can choose to add a property to a single exact field type ( ex. originatingnumber ), by using **f**.  They can also set a property on the entire phone number field type by using **t**.  Here is how this process works.

We will construct some simple examples

To remove hyphens from all originating numbers
` -pforiginatingnumber:hyphens:false `

To remove hyphens from ALL phone numbers
` -ptphonenumber:hyphens:false `

To filter a specific field type
` -pfsensorid:filter:true `

To filter all number type fields
` -ptnumber:filter:true `

To change the format of all dates in the program
` -ptdate:format:M-Y-D `
In this string only D, M, and Y are significant, these will be replaced by the appropriate data at runtime.

For a more detailed view on all properties and field types please refer to [the complete field guide](fields.md)