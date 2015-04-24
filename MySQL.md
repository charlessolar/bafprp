# MySQL Server #

Will send data to a mysql server specified by the user.


## Properties ##
  * table - table for inserting records
  * dsn - the database dsn
or for string connections
  * database - the destination database
  * server - the server
  * user - user name with INSERT and SELECT privileges
  * password - password for user
  * table - table for inserting records

**NOTE** Only one database, server, user, and password will be used for all 3 types of output.  If you specify different values, the first one connected will be used throughout the duration of the program.

**CLARIFICATION** This does not mean that using mysql for one output type will override the output forms of the other two types.  Only that if you are output both logs and records to mysql, the first database it connects to will be the one it uses for both types of output.

In linux you must install unixODBC and myodbc.  You must then edit your odbcinst.ini to include myodbc as a driver.  After that bafprp will handle the connection details.

## Tables ##

### Log Table ###

```
create table logs
(
id int unsigned auto_increment primary key,
ts datetime,
loglevel int,
msg text,
index( loglevel )
)
```

### Error Table ###

```
create table errors
(
id int unsigned auto_increment primary key,
ts datetime not null,
error text not null,
filename varchar(255),
filepos int,
type varchar(255),
length int,
bytes text
)
```


### Records ###

The record table operates a little differently.  It has no specific structure like log or error, instead when it comes time to insert a record bafprp will first query the table for a list of the column names.  It will then match those column names to elements that are in the current record.

For example, if we wanted to record the calling number, the called number, and the elapsed time we would make a table like this

```
create table records
(
id int unsigned auto_increment primary key,
originatingnpa varchar(6) not null,
originatingnumber varchar(8) not null,
terminatingnpa varchar(6) not null,
terminatingnumber varchar(8) not null,
elapsedtime int unsigned not null,
index( originatingnpa ),
index( originatingnumber ),
index( terminatingnpa ),
index( terminatingnumber ),
index( elapsedtime )
)
```

The function will automatically match those columns and insert the data accordingly.  There are a couple of things to note while using this behavior.  Firstly, if a record has no data in common with the sql table, it will not be recorded.  Secondly, if there is a n error inserting the record an error message will be created through the error output type.  These should be checked often.

For a complete list of the different field types in a record, see [fields](fields.md)

In addition to these field types there are also special fields recognized by the output function.
  * type - the type of record
  * size - the size of the record
  * crc - the crc32 hash
  * filename - the filename of the baf file
  * filepos - the position of this record in the baf file

You may add these columns to your records table for extra data.