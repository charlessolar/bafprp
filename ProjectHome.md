BAFPRP is a program for parsing call data records in BAF format.  The format of a BAF file is documented by Telcordia document GR-1100 - available [here](http://telecom-info.telcordia.com/site-cgi/ido/docs.cgi?ID=SEARCH&DOCUMENT=GR-1100&).

Similar programs like bafview http://www.xach.com/misc/bafview/ were created to help us decode some of the baf data, however it has many short comings.  Bafprp allows a more thorough and deep analysis of baf records and has many different modes of output, with the ability to make more based on plugable modules.

# v 1.3.1 #
Version 1.3.1 of bafprp is available for download, please report any bugs or problems.

## Changelog ##

1.3 to 1.3.1 (July 11, 2010)
  * Win32 build now requires latest vc redistributable, make sure to update your machines!
  * File output will now print the field id next to the description
  * Conflicting field type names will be properly handled so that users can uniquely identify each field
  * Fixed a bug in duration calculation that would cause exceptionally long calls to be reported incorectly
  * Added record ids 500, 501, and 502, and a bunch of new call type descriptions
  * Fixed a couple typos

1.2.1 to 1.3 (December 10, 2009)
  * Added csv output format
  * New record design to make creating records easy
  * New makefiles to build with or without SQL output
  * New BSD specific makefile that does not require gmake (thanks thowe!)
  * Significantly reduced memory footprint yet again
  * Added date auto adjusting code to minimize any problems the new decade might bring
  * Minor house cleaning, typo fixes, etc

1.2 to 1.2.1
  * Fixed MS SQL DSN Bug
  * Added getInt and getLong to Phone Number data type
  * Added more field definitions
  * Fixed a bug that caused the program to crash on quad core cpus
  * Improved MS SQL and MySql error reporting
