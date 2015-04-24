# Windows #

The solution file for Microsoft Visual Studio 2010 is located in the scripts folder.  If you have visual studio 2010 open that file and you can compile the project like normally.

Because some of the solution settings are not stored on the svn to run the program in visual studio you need to first set bafprp as the start up project, then go into Project->bafprp Properties
select configuration properties -> Debugging
and put this text in the Command field: `$(TargetPath)`
and put this text in the working directory path: `$(SolutionDir)../bin/$(ConfigurationName)`

For your reference the build objects are stored in the build directory, and the exe will be in the `bin/${ConfigurationName`} directory.

If you are using a different compiler, eg, codeblocks, eclipse, nmake, then I am afraid you are on your own.  You should know how to build a new project in codeblocks and eclipse.

Note:
In order to use (and compile with) the SQL output methods you must install the Windows SDK available at http://msdn.microsoft.com/en-us/windows/bb980924.aspx


# Linux #

Bafprp comes with three different Makefiles.

### Makefile (default) ###
  * Requires unixodbc-dev and freetds-dev packages
  * Includes MSSQL and MySQL output support

### Makefile\_NoMSSQL ###
  * Requires unixodbc-dev
  * Includes only MySQL output support

### Makefile\_NoSQL ###
  * Requires no extra packages
  * Has NO SQL output support

### Makefile\_BSD\_NoSQL ###
  * No gmake syntax, should be safe with generic linux make
  * Has NO SQL output support


Choose whichever one suits your desire and rename it to Makefile or use `make -f 'filename'`