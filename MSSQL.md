# Microsoft SQL Server #

Will send data to a sql server specified by the user.


## Properties ##
  * table - table for inserting records
  * dsn - the database dsn
  * user - username with INSERT and SELECT provileges
  * password - password for user
or for string connections
  * database - the destination database
  * server - the server
  * user - user name with INSERT and SELECT privileges
  * password - password for user
  * table - table for inserting records

**NOTE** Only one database, server, user, and password will be used for all 3 types of output.  If you specify different values, the first one connected will be used throughout the duration of the program.

**CLARIFICATION** This does not mean that using ms sql for one output type will override the output forms of the other two types.  Only that if you are output both logs and records to ms sql, the first database it connects to will be the one it uses for both types of output.

In linux you must install unixODBC and FreeTDS.  You must then edit your odbcinst.ini to include freetds as a driver.  After that bafprp will handle the connection details.

## Tables ##

### Log Table ###

```
CREATE TABLE logs
(
id BIGINT IDENTITY(1,1) PRIMARY KEY,
ts DATETIME,
loglevel SMALLINT,
msg TEXT
);
CREATE NONCLUSTERED INDEX IX_loglevel on calllogs ( loglevel );
CREATE NONCLUSTERED INDEX IX_ts on calllogs ( ts );
```

### Error Table ###

```
CREATE TABLE errors
(
id BIGINT IDENTITY(1,1) PRIMARY KEY,
ts DATETIME NOT NULL,
error TEXT NOT NULL,
filename VARCHAR(255),
filepos INT,
type VARCHAR(255),
length INT,
bytes TEXT
);
CREATE NONCLUSTERED INDEX IX_ts on callerrors ( ts );
CREATE NONCLUSTERED INDEX IX_filename on callerrors ( filename );
```


### Records ###

The record table operates a little differently.  It has no specific structure like log or error, instead when it comes time to insert a record bafprp will first query the Information Schema for a list of the column names.  It will then match those column names to elements that are in the current record.

An example table for use in a production billing system would be the following

```
create table callrecords (
id bigint IDENTITY(1,1) not null primary key,
originatingnpa smallint default 0,
originatingnumber bigint default 0,
terminatingnpa int default 0,
terminatingnumber bigint default 0,
largedigits varchar(16), -- Extra long terminating npas go here
elapsedtime bigint,  -- milliseconds
calltype int not null,
type varchar(255),
overseasindicator int default 0,
icincid int default 0,
date datetime,
time datetime,
size int,
crc bigint,
filename varchar(255),
filepos bigint,
);
CREATE NONCLUSTERED INDEX IX_orignpa ON callrecords (originatingnpa);
CREATE NONCLUSTERED INDEX IX_orignum ON callrecords (originatingnumber);
-- This prevents a baf record from being uploaded twice
CREATE UNIQUE NONCLUSTERED INDEX UX_crc_filename ON callrecords (crc,filename);
CREATE NONCLUSTERED INDEX IX_termnpa ON callrecords (terminatingnpa);
CREATE NONCLUSTERED INDEX IX_termnum ON callrecords (terminatingnumber);
CREATE NONCLUSTERED INDEX IX_largedigits ON callrecords (largedigits);
CREATE NONCLUSTERED INDEX IX_calltype ON callrecords ( calltype );
CREATE NONCLUSTERED INDEX IX_elapsedtime ON callrecords ( elapsedtime );
CREATE NONCLUSTERED INDEX IX_date_time ON callrecords ( date, time );
CREATE NONCLUSTERED INDEX IX_date ON callrecords ( date );
CREATE NONCLUSTERED INDEX IX_time ON callrecords (time);
CREATE NONCLUSTERED INDEX IX_overseas ON callrecords ( overseasindicator );
CREATE NONCLUSTERED INDEX IX_icincid ON callrecords ( icincid );
```

The function will automatically match those columns and insert the data accordingly.  There are a couple of things to note while using this behavior.  Firstly, if a record has no data in common with the sql table, it will not be recorded.  Secondly, if there is an error inserting the record an error message will be created through the error output type.  These should be checked often.

For a complete list of the different field types in a record, see [fields](fields.md)

In addition to these field types there are also special fields recognized by the output function.
  * type - the type of record
  * size - the size of the record
  * crc - the crc32 hash
  * filename - the filename of the baf file
  * filepos - the position of this record in the baf file

You may add these columns to your records table for extra data.