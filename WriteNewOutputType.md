# Introduction #
This document should help developers write their own output type for use in a specific system currently unsupported by bafprp.

# The Skeleton #
For starters lets look at the skeletal structure of an output type.

header
```
#ifndef BAFPRPSKEL_H
#define BAFPRPSKEL_H

#include "output.h"

namespace bafprp
{
	class Skel : public Output
	{
	public:

		void record( const IBafRecord* record );
		void error( const IBafRecord* record, const std::string& error );
		void log( LOG_LEVEL level, const std::string& log );

	protected:		
		Skel() : Output( "skel" ) {}

	private:
		// This variable simply initializes a class that registers with the main output code
		static const Skel registerThis;
	};
}


#endif
```

source
```
#include "skeloutput.h"

namespace bafprp
{
	const Skel Skel::registerThis;

	void Skel::error( const IBafRecord* record, const std::string& error )
	{

	}

	void Skel::log( LOG_LEVEL level, const std::string& log )
	{

	}

	void Skel::record( const IBafRecord* record )
	{

	}
}
```

This is all that is required to create a new output type in bafprp.  You can add these files to your project as is, recompile, and use -rskel to use it.  Of course this file does not print anything yet so you will not see anything, but its good to know the basics.

There are three important parts to this skeleton file.

The first thing is the record, error, and log overrides.  These functions are overriding pure virtuals in the output class and need to be defined in all output classes.

The second thing is the constructor.  Notice that we call the parents constructor with the string argument "skel."  This is what registers the output type so we can use it in bafprp.  You can of course change the string, but you must register like this in order for bafprp to recognize your output class.

The final important piece is the static registerThis variable.  This variable creates the output instance and registers that instance with the main output system.

This brings up an important point you will need to understand before writing your own type.  Each output type has only one instance of itself that is used by the main output system.  Meaning if you have logs and records printing to a file, there is only one instance of the file output type handling both files.

The 'gotcha' in this design is that each of the output functions can be called at any random place in the program, so they should be viewed as mutually exclusive.

In each output type you have three worlds, error, log, and record and these three can have no relationship with each other otherwise you risk creating memory leaks or worse, a program crash.

## The Functions ##

Now lets look at each function.  The record and error output functions provide you with a pointer to the record in question.  You can use pointer to pull all relevant information from the record including fields, size, crc, filename to name a few.
For error output you are also provided a string that contains a description of the error.

For log output you are provided the log level and the log string.  This function will not be called if the log level of the request is above the current log level so checking the log level is not required.

# Conclusion #
That should cover just about everything to get you started.  If you still have questions it might be a good idea to look at some of the provided output types for guidance.