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

#include "ifield.h"

namespace bafprp
{
	// A function to make defining fields easier
	void makeField( const std::string& id, const std::string& datatype, const std::string& size, const std::string& desc ) 
	{
		FieldMaker::setFieldProperty( id, "datatype:" + datatype ); 
		FieldMaker::setFieldProperty( id, "size:" + size ); 
		FieldMaker::setFieldProperty( id, "desc:" + desc );
	}

	void define_default_fields()
	{
		// Only setup types once.
		static bool first = true;
		if( !first ) return;
		first = false;

		// AMADNS tables
		makeField( "sourcecomponentid", "amadns", "1", "Source Component ID" );
		FieldMaker::setFieldProperty( "sourcecomponentid", "bytes:2" );
		FieldMaker::setFieldProperty( "sourcecomponentid", "high:4" );
		FieldMaker::setFieldProperty( "sourcecomponentid", "low:7" );
		makeField( "sourcecomponenttype", "amadns", "1", "Source Component Type" );
		FieldMaker::setFieldProperty( "sourcecomponenttype", "bytes:1" );
		FieldMaker::setFieldProperty( "sourcecomponenttype", "high:0" );
		FieldMaker::setFieldProperty( "sourcecomponenttype", "low:3" );
		makeField( "destinationcomponentid", "amadns", "1", "Destination Component ID" );
		FieldMaker::setFieldProperty( "destinationcomponentid", "bytes:2" );
		FieldMaker::setFieldProperty( "destinationcomponentid", "high:4" );
		FieldMaker::setFieldProperty( "destinationcomponentid", "low:7" );
		makeField( "destinationcomponenttype", "amadns", "1", "Destination Component Type" );
		FieldMaker::setFieldProperty( "destinationcomponenttype", "bytes:1" );
		FieldMaker::setFieldProperty( "destinationcomponenttype", "high:0" );
		FieldMaker::setFieldProperty( "destinationcomponenttype", "low:3" );
		makeField( "filetype", "amadns", "0", "File Type" );
		FieldMaker::setFieldProperty( "filetype", "bytes:1" );
		FieldMaker::setFieldProperty( "filetype", "high:0" );
		FieldMaker::setFieldProperty( "filetype", "low:4" );
		makeField( "dateformattype", "amadns", "1", "Date Format Type" );
		FieldMaker::setFieldProperty( "dateformattype", "bytes:1" );
		FieldMaker::setFieldProperty( "dateformattype", "high:5" );
		FieldMaker::setFieldProperty( "dateformattype", "low:7" );
		makeField( "fieldsuppressiontype", "amadns", "0", "Field Suppression Type" );
		FieldMaker::setFieldProperty( "fieldsuppressiontype", "bytes:1" );
		FieldMaker::setFieldProperty( "fieldsuppressiontype", "high:0" );
		FieldMaker::setFieldProperty( "fieldsuppressiontype", "low:1" );
		makeField( "fileprioritylevel", "amadns", "0", "File Priority Level" );
		FieldMaker::setFieldProperty( "fileprioritylevel", "bytes:1" );
		FieldMaker::setFieldProperty( "fileprioritylevel", "high:2" );
		FieldMaker::setFieldProperty( "fileprioritylevel", "low:4" );
		makeField( "restartstatus", "amadns", "0", "Restart Status" );
		FieldMaker::setFieldProperty( "restartstatus", "bytes:1" );
		FieldMaker::setFieldProperty( "restartstatus", "high:5" );
		FieldMaker::setFieldProperty( "restartstatus", "low:5" );
		makeField( "primarysecondarystatus", "amadns", "0", "Primary/Secondary Status" );
		FieldMaker::setFieldProperty( "primarysecondarystatus", "bytes:1" );
		FieldMaker::setFieldProperty( "primarysecondarystatus", "high:6" );
		FieldMaker::setFieldProperty( "primarysecondarystatus", "low:6" );
		makeField( "recordsourceinfotype", "amadns", "1", "Record Source Info Type" );
		FieldMaker::setFieldProperty( "recordsourceinfotype", "bytes:1" );
		FieldMaker::setFieldProperty( "recordsourceinfotype", "high:7" );
		FieldMaker::setFieldProperty( "recordsourceinfotype", "low:7" );
		makeField( "filesequencenumber", "amadns", "3", "File Sequence Number" );
		FieldMaker::setFieldProperty( "filesequencenumber", "bytes:2" );
		FieldMaker::setFieldProperty( "filesequencenumber", "high:0" );
		FieldMaker::setFieldProperty( "filesequencenumber", "low:7" );
		makeField( "filecreationtime", "amadns", "1", "File Creation Time" );
		FieldMaker::setFieldProperty( "filecreationtime", "bytes:2" );
		FieldMaker::setFieldProperty( "filecreationtime", "high:4" );
		FieldMaker::setFieldProperty( "filecreationtime", "low:7" );
		makeField( "filecreationdate", "amadns", "5", "File Creation Date" );
		FieldMaker::setFieldProperty( "filecreationdate", "bytes:3" );
		FieldMaker::setFieldProperty( "filecreationdate", "high:0" );
		FieldMaker::setFieldProperty( "filecreationdate", "low:3" );
		makeField( "filelastmodtime", "amadns", "2", "File Last Modification Time" );
		FieldMaker::setFieldProperty( "filelastmodtime", "bytes:2" );
		FieldMaker::setFieldProperty( "filelastmodtime", "high:4" );
		FieldMaker::setFieldProperty( "filelastmodtime", "low:7" );
		makeField( "filelastmoddate", "amadns", "5", "File Last Modification Date" );
		FieldMaker::setFieldProperty( "filelastmoddate", "bytes:3" );
		FieldMaker::setFieldProperty( "filelastmoddate", "high:0" );
		FieldMaker::setFieldProperty( "filelastmoddate", "low:3" );
		makeField( "filelength", "amadns", "7", "File Length" );
		FieldMaker::setFieldProperty( "filelength", "bytes:4" );
		FieldMaker::setFieldProperty( "filelength", "high:0" );
		FieldMaker::setFieldProperty( "filelength", "low:7" );
		makeField( "recordsinfile", "amadns", "5", "Number of Records in File" );
		FieldMaker::setFieldProperty( "recordsinfile", "bytes:3" );
		FieldMaker::setFieldProperty( "recordsinfile", "high:0" );
		FieldMaker::setFieldProperty( "recordsinfile", "low:7" );
		makeField( "recordsourcetype", "amadns", "1", "Record Source Type" );
		FieldMaker::setFieldProperty( "recordsourcetype", "bytes:2" );
		FieldMaker::setFieldProperty( "recordsourcetype", "high:4" );
		FieldMaker::setFieldProperty( "recordsourcetype", "low:7" );
		makeField( "recordsourceid", "amadns", "3", "Record Source Identification Number" );
		FieldMaker::setFieldProperty( "recordsourceid", "bytes:3" );
		FieldMaker::setFieldProperty( "recordsourceid", "high:0" );
		FieldMaker::setFieldProperty( "recordsourceid", "low:3" );



		// Table 0
		makeField( "structurecode", "numberswitch", "5", "Structure Code" );
		FieldMaker::setFieldProperty( "structurecode", "switch:0" );
		FieldMaker::setFieldProperty( "structurecode", "00:No Modules Attached" );
		FieldMaker::setFieldProperty( "structurecode", "04:Modules Attached" );
		FieldMaker::setFieldProperty( "structurecode", "number:14" );
		FieldMaker::setFieldProperty( "structurecode", "number_only:true" );
		// Table 1
		makeField( "calltype", "number", "3", "Call Type" );
		// Table 2
		makeField( "sensortype", "number", "3", "Sensor Type" );
		// Table 3
		makeField( "sensorid", "numberswitch", "7", "Sensor Identification" );
		FieldMaker::setFieldProperty( "sensorid", "switch:0" );
		FieldMaker::setFieldProperty( "sensorid", "00:Default" );
		FieldMaker::setFieldProperty( "sensorid", "01:Previously-Output Record" );
		FieldMaker::setFieldProperty( "sensorid", "02:Potential Duplicate Record" );
		FieldMaker::setFieldProperty( "sensorid", "number:16" );
		// Table 4
		makeField( "recordofficetype", "number", "3", "Record Office Type" );
		// Table 5
		makeField( "recordofficeid", "numberswitch", "7", "Record Office Identification" );
		FieldMaker::setFieldProperty( "recordofficeid", "switch:0" );
		FieldMaker::setFieldProperty( "recordofficeid", "00:Default" );
		FieldMaker::setFieldProperty( "recordofficeid", "01:Record is From a Sensor Undergoing Validation Testing" );
		FieldMaker::setFieldProperty( "recordofficeid", "number:16" );
		// Table 6
		makeField( "date", "date", "5", "Date" );
		// Table 6
		makeField( "carrierconnectdate", "date", "5", "Carrier Connect Date" );
		// Table 6
		makeField( "presentdate", "date", "5", "Present or Deactivation Date" );
		// Table 6
		makeField( "datebefore", "date", "5", "Date Before Change" );
		// Table 6
		makeField( "dateafter", "date", "5", "Date After Change" );
		// Table 6
		makeField( "dateheaderrecorded", "date", "5", "Date Header Recorded" );
		// Table 6
		makeField( "datetrailerrecorded", "date", "5", "Date Trailer Recorded" );
		// Table 6
		makeField( "datefirstblock", "date", "5", "Date First Block was Written" );
		// Table 6
		makeField( "datelastblock", "date", "5", "Date Last Block was Written" );
		// Table 6
		makeField( "datetransmitted", "date", "5", "Date Data was Transmitted to Collector" );
		// Table 6
		makeField( "activationdate", "date", "5", "Activation Date" );
		// Table 6
		makeField( "circuitdate", "date", "5", "Circuit Date" ); 
		// Table 7
		makeField( "timingindicator", "switch", "5", "Timing Indicator" );
		FieldMaker::setFieldProperty( "timingindicator", "switch:0" );
		FieldMaker::setFieldProperty( "timingindicator", "00:Default" );
		FieldMaker::setFieldProperty( "timingindicator", "01:Time Release Disconnect" );
		FieldMaker::setFieldProperty( "timingindicator", "02:Timing Guard Condition" );
		FieldMaker::setFieldProperty( "timingindicator", "03:Single Time Line" );
		FieldMaker::setFieldProperty( "timingindicator", "04:Unanswered Call Release" );
		FieldMaker::setFieldProperty( "timingindicator", "05:Connection Acknowledgement Not Received" );
		FieldMaker::setFieldProperty( "timingindicator", "06:Call is forcibly released" );
		FieldMaker::setFieldProperty( "timingindicator", "switch:1" );
		FieldMaker::setFieldProperty( "timingindicator", "10:Default" );
		FieldMaker::setFieldProperty( "timingindicator", "11:Short called party off-hook detected" );
		FieldMaker::setFieldProperty( "timingindicator", "12:Under minimum chargeable" );
		FieldMaker::setFieldProperty( "timingindicator", "13:SST&UMCD" );
		FieldMaker::setFieldProperty( "timingindicator", "14:SST" );
		FieldMaker::setFieldProperty( "timingindicator", "switch:2" );
		FieldMaker::setFieldProperty( "timingindicator", "20:Default" );
		FieldMaker::setFieldProperty( "timingindicator", "21:Start of long duration call" );
		FieldMaker::setFieldProperty( "timingindicator", "22:Continuation of long duration call" );
		FieldMaker::setFieldProperty( "timingindicator", "23:Service capability status: Deactivation" );
		FieldMaker::setFieldProperty( "timingindicator", "24:Old type long duration call" );
		FieldMaker::setFieldProperty( "timingindicator", "25:Complete long duration call record" );
		FieldMaker::setFieldProperty( "timingindicator", "switch:3" );
		FieldMaker::setFieldProperty( "timingindicator", "30:Default" );
		FieldMaker::setFieldProperty( "timingindicator", "31:Charge Guard (conversation elapsed time)" );
		FieldMaker::setFieldProperty( "timingindicator", "32:Message Register Not Stroked Or Trunk Not Seized" );
		FieldMaker::setFieldProperty( "timingindicator", "33:Charge Guard And Mess Reg Not Stroked" );
		FieldMaker::setFieldProperty( "timingindicator", "34:Charge Guard (elapsed time from carrier connect)" );
		FieldMaker::setFieldProperty( "timingindicator", "35:Charge Guard (elapsed time and elapsed time from carrier connect)" );
		FieldMaker::setFieldProperty( "timingindicator", "switch:4" );
		FieldMaker::setFieldProperty( "timingindicator", "40:Default" );
		FieldMaker::setFieldProperty( "timingindicator", "41:Possible Time Stamp Error (conversation connect)" );
		FieldMaker::setFieldProperty( "timingindicator", "42:Possible Time Stamp Error (carrier connect)" );
		FieldMaker::setFieldProperty( "timingindicator", "43:Possible Time Stamp Error (carrier and carrier connect)" );
		FieldMaker::setFieldProperty( "timingindicator", "44:Time Change Rating Discrepancy" );
		// Table 8
		makeField( "studyindicator", "switch", "7", "Study Indicator" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:0" );
		FieldMaker::setFieldProperty( "studyindicator", "00:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "01:Point to Point" );
		FieldMaker::setFieldProperty( "studyindicator", "02:Subscriber Line Usage Study" );
		FieldMaker::setFieldProperty( "studyindicator", "03:Point-to-Point and SLUS" );
		FieldMaker::setFieldProperty( "studyindicator", "04:Study Dependant ID 4" );
		FieldMaker::setFieldProperty( "studyindicator", "05:Study Dependant ID 5" );
		FieldMaker::setFieldProperty( "studyindicator", "06:Study Dependant ID 6" );
		FieldMaker::setFieldProperty( "studyindicator", "07:Study Dependant ID 7" );
		FieldMaker::setFieldProperty( "studyindicator", "08:Study Dependant ID 8" );
		FieldMaker::setFieldProperty( "studyindicator", "09:Study Dependant ID 9" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:1" );
		FieldMaker::setFieldProperty( "studyindicator", "10:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "11:Complaint Observed" );
		FieldMaker::setFieldProperty( "studyindicator", "12:Network Completion" );
		FieldMaker::setFieldProperty( "studyindicator", "13:Complaint Observed and Network Completion" );
		FieldMaker::setFieldProperty( "studyindicator", "14:Study Dependant ID 4" );
		FieldMaker::setFieldProperty( "studyindicator", "15:Study Dependant ID 5" );
		FieldMaker::setFieldProperty( "studyindicator", "16:Study Dependant ID 6" );
		FieldMaker::setFieldProperty( "studyindicator", "17:Study Dependant ID 7" );
		FieldMaker::setFieldProperty( "studyindicator", "18:Study Dependant ID 8" );
		FieldMaker::setFieldProperty( "studyindicator", "19:Study Dependant ID 9" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:2" );
		FieldMaker::setFieldProperty( "studyindicator", "20:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "21:Validation Test" );
		FieldMaker::setFieldProperty( "studyindicator", "22:Study Generated Record" );
		FieldMaker::setFieldProperty( "studyindicator", "23:Validation Test And Study Generated Record" );
		FieldMaker::setFieldProperty( "studyindicator", "24:Study Dependant ID 4" );
		FieldMaker::setFieldProperty( "studyindicator", "25:Study Dependant ID 5" );
		FieldMaker::setFieldProperty( "studyindicator", "26:Study Dependant ID 6" );
		FieldMaker::setFieldProperty( "studyindicator", "27:Study Dependant ID 7" );
		FieldMaker::setFieldProperty( "studyindicator", "28:Study Dependant ID 8" );
		FieldMaker::setFieldProperty( "studyindicator", "29:Study Dependant ID 9" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:3" );
		FieldMaker::setFieldProperty( "studyindicator", "30:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "31:Test Call" );
		FieldMaker::setFieldProperty( "studyindicator", "32:Network Specific Facility" );
		FieldMaker::setFieldProperty( "studyindicator", "33:NSF and Test Call" );
		FieldMaker::setFieldProperty( "studyindicator", "34:Study Dependant ID 4" );
		FieldMaker::setFieldProperty( "studyindicator", "35:Study Dependant ID 5" );
		FieldMaker::setFieldProperty( "studyindicator", "36:Study Dependant ID 6" );
		FieldMaker::setFieldProperty( "studyindicator", "37:Study Dependant ID 7" );
		FieldMaker::setFieldProperty( "studyindicator", "38:Study Dependant ID 8" );
		FieldMaker::setFieldProperty( "studyindicator", "39:Study Dependant ID 9" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:4" );
		FieldMaker::setFieldProperty( "studyindicator", "40:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "41:Called Directory Number Not Marked Anonymous" );
		FieldMaker::setFieldProperty( "studyindicator", "42:Called Directory Number Marked Anonymous" );
		FieldMaker::setFieldProperty( "studyindicator", "43:Calling Party Marked Anonymous, Called Parky Marked Not Anonymous" );
		FieldMaker::setFieldProperty( "studyindicator", "44:Calling and Called Party Marked Anonymous" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:5" );
		FieldMaker::setFieldProperty( "studyindicator", "50:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "51:No Originating Number" );
		FieldMaker::setFieldProperty( "studyindicator", "53:No Terminating Number" );
		FieldMaker::setFieldProperty( "studyindicator", "54:No originating and Terminating Numbers" );
		FieldMaker::setFieldProperty( "studyindicator", "55:No Terminating NANP Station Number" );
		FieldMaker::setFieldProperty( "studyindicator", "56:No Originating NANP Station Number" );
		FieldMaker::setFieldProperty( "studyindicator", "57:No Originating and Terminating NANP Station Numbers" );
		FieldMaker::setFieldProperty( "studyindicator", "58:Study Dependant ID 8" );
		FieldMaker::setFieldProperty( "studyindicator", "59:Studt Dependant ID 9" );
		FieldMaker::setFieldProperty( "studyindicator", "switch:6" );
		FieldMaker::setFieldProperty( "studyindicator", "60:Default" );
		FieldMaker::setFieldProperty( "studyindicator", "61:No Class of Charge" );
		FieldMaker::setFieldProperty( "studyindicator", "62:No AMA Call" );
		FieldMaker::setFieldProperty( "studyindicator", "63:Holding Time Study" );
		FieldMaker::setFieldProperty( "studyindicator", "64:Expanded 4 Digits" );
		FieldMaker::setFieldProperty( "studyindicator", "65:Expanded 5 Digits" );
		FieldMaker::setFieldProperty( "studyindicator", "66:Expanded 7 Digits" );
		FieldMaker::setFieldProperty( "studyindicator", "67:Corrected 7 Digits" );
		FieldMaker::setFieldProperty( "studyindicator", "68:Corrected Undetermined Number of Digits" );
		FieldMaker::setFieldProperty( "studyindicator", "69:More Than 7 Digits Seen" );
		// Table 9
		makeField( "calledpartyanswerindicator", "switch", "1", "Called Party Answer Indicator" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "switch:0" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "00:Called Party Answer Detected" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "01:Called Party Answer not Detected" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "02:Answered Attempt" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "03:Simulated Called Party Off-Hook Indicator" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "04:NCD, CAS, Blocked After Answer" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "05:NCD, CAS, Blocked Before Answer" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "07:Service Features Not Provided, Call Answered" );
		FieldMaker::setFieldProperty( "calledpartyanswerindicator", "08:Service Features Not Provided, Call Unanswered" );
		// Table 10
		makeField( "servicetrafficind", "switch", "1", "Service-Observed/Traffic-Sampled Indicator" );
		FieldMaker::setFieldProperty( "servicetrafficind", "switch:0" );
		FieldMaker::setFieldProperty( "servicetrafficind", "00:Default" );
		FieldMaker::setFieldProperty( "servicetrafficind", "01:Service Observed" );
		FieldMaker::setFieldProperty( "servicetrafficind", "02:Traffic Sampled" );
		FieldMaker::setFieldProperty( "servicetrafficind", "03:Service Observed and Traffic Sampled" );
		FieldMaker::setFieldProperty( "servicetrafficind", "04:Message Detailed Recorded" );
		FieldMaker::setFieldProperty( "servicetrafficind", "05:Message Detailed Recorded, Service Observed" );
		FieldMaker::setFieldProperty( "servicetrafficind", "06:Message Detailed Recorded, Traffic Sampled" );
		FieldMaker::setFieldProperty( "servicetrafficind", "07:Message Detailed Recorded, Service Observed And Traffic Sampled" );
		// Table 11
		makeField( "operatoraction", "switch", "1", "Operator Action" );
		FieldMaker::setFieldProperty( "operatoraction", "switch:0" );
		FieldMaker::setFieldProperty( "operatoraction", "00:Automatically Identified, Customer Dialed" );
		FieldMaker::setFieldProperty( "operatoraction", "01:Automatically Identified, Operator Dialed" );
		FieldMaker::setFieldProperty( "operatoraction", "02:Operator Identified, Customer Dialed" );
		FieldMaker::setFieldProperty( "operatoraction", "03:Operator Identified, Operator Dialed" );
		FieldMaker::setFieldProperty( "operatoraction", "04:Customer Dialed, Identification Failure" );
		FieldMaker::setFieldProperty( "operatoraction", "05:Operator Dialed, Identification Failure" );
		FieldMaker::setFieldProperty( "operatoraction", "06:Customer Dialed, ANI Identification Failure" );
		FieldMaker::setFieldProperty( "operatoraction", "07:Operator Dialed, ANI Identification Failure" );
		// Table 12
		makeField( "servicefeaturecode", "number", "3", "Service Feature Code" );
		// Table 13
		makeField( "originatingnpa", "number", "3", "Originating NPA" );
		// Table 13
		makeField( "activatingnpa", "number", "3", "Activating NPA" );
		// Table 13
		makeField( "destinatingnpa", "number", "3", "Destination NPA" );
		// Table 14
		makeField( "originatingnumber", "phonenumber", "7", "Originating Number" );
		// Table 14
		makeField( "activatingnumber", "phonenumber", "7", "Activating Number" );
		// Table 14
		makeField( "destinatingnumber", "phonenumber", "7", "Destination Number" );
		// Table 13
		makeField( "dialednpa", "number", "3", "Dialed NPA" );
		// Table 14
		makeField( "dialednumber", "phonenumber", "7", "Dialed Number" );
		// Table 15
		makeField( "overseasindicator", "switch", "1", "Overseas Indicator" );
		FieldMaker::setFieldProperty( "overseasindicator", "switch:0" );
		FieldMaker::setFieldProperty( "overseasindicator", "00:NPA Dialed by Customer" );
		FieldMaker::setFieldProperty( "overseasindicator", "01:NPA Determined by the Network Element" );
		FieldMaker::setFieldProperty( "overseasindicator", "02:Non-North American Numbering Plan Terminating Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "03:7-digit International Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "04:8-digit International Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "05:9-digit International Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "06:10-digit International Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "07:11-digit International Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "08:12-digit International Number" );
		FieldMaker::setFieldProperty( "overseasindicator", "09:Operator Inward-Dialed Code is in the Called Number Field" );
		// Table 16
		makeField( "terminatingnpa", "number", "5", "Terminating NPA" );
		FieldMaker::setFieldProperty( "terminatingnpa", "trim:true" );
		// Table 16
		makeField( "linenpa", "number", "5", "Line NPA" );
		FieldMaker::setFieldProperty( "linenpa", "trim:true" );
		// Table 16
		makeField( "forwardtonpa", "number", "5", "Terminating NPA" );
		FieldMaker::setFieldProperty( "forwardtonpa", "trim:true" );
		// Table 17
		makeField( "terminatingnumber", "phonenumber", "7", "Terminating Number" );
		// Table 17
		makeField( "linenumber", "phonenumber", "7", "Line Number" );
		// Table 17
		makeField( "forwardtonumber", "phonenumber", "7", "Forward to Number" );
		// Table 18
		makeField( "time", "time", "7", "Time" );
		// Table 18
		makeField( "carrierconnecttime", "time", "7", "Carrier Connect Time" );
		// Table 18
		makeField( "presenttime", "time", "7", "Present or Deactivation Time" );
		// Table 18
		makeField( "timebefore", "time", "7", "Time Before Change" );
		// Table 18
		makeField( "timeafter", "time", "7", "Time After Change" );
		// Table 18
		makeField( "timeheaderrecorded", "time", "7", "Time Header Recorded" );
		// Table 18
		makeField( "timetrailerrecorded", "time", "7", "Time Trailer Recorded" );
		// Table 18
		makeField( "timefirstblock", "time", "7", "Time First Block was Written" );
		// Table 18
		makeField( "timelastblock", "time", "7", "Time Last Block was Written" );
		// Table 18
		makeField( "timetransmitted", "time", "7", "Time Data was Transmitted to Collector" );
		// Table 18
		makeField( "activationtime", "time", "7", "Activation Time" );
		// Table 18
		makeField( "bridgeconnecttime", "time", "7", "Bridge Connect Time" );
		// Table 19
		makeField( "elapsedtime", "duration", "9", "Elapsed Time" );
		// Table 19
		makeField( "carrierelapsedtime", "duration", "9", "Carrier Elapsed Time" );
		// Table 19
		makeField( "bridgeelapsedtime", "duration", "9", "Bridge Elapsed Time" );
		// Table 20
		makeField( "trunknetworknumber", "number", "7", "Trunk Network Number" );
		// Table 21
		makeField( "cdarnumber", "number", "9", "Customer-Dialed Account Recording Number" );
		// Table 22
		makeField( "chargeindicator", "switch", "1", "Charge Indicator" );
		// Table 23
		makeField( "chargeamount", "money", "5", "Amount of Charge / Amount Deposited" );
		// Table 24
		// Credit Card Failure (Vendor Specific)
		// Table 25
		makeField( "billingnumber", "number", "11", "Billing Number" );
		// Table 26
		makeField( "circuittime", "time", "7", "Circuit Time" );
		// Table 28	
		makeField( "watsindicator", "switch", "1", "WATS Indicator" );
		FieldMaker::setFieldProperty( "watsindicator", "switch:0" );
		FieldMaker::setFieldProperty( "watsindicator", "00:Default" );
		FieldMaker::setFieldProperty( "watsindicator", "02:Measured Time" );
		// Table 29
		makeField( "watsband", "number", "3", "WATS Band" );
		// Table 29
		makeField( "msgbillingindex", "number", "3", "Message Billing Index" );
		// Table 30
		makeField( "watsadmin", "number", "5", "WATS Administration" );
		// Table 31
		makeField( "customeridentification", "number", "5", "Customer Identification" );
		// Table 32
		makeField( "digitsdialed1", "number", "11", "Digits Dialed (11 Digits)" );
		// Table 33
		makeField( "digitsdialed2", "number", "13", "Digits Dialed (13 Digits)" );
		// Table 34
		makeField( "screeningcode", "number", "3", "Screening Code" );
		// Table 35
		makeField( "ssas1", "number", "3", "SSAS Part 1" );
		// Table 36
		makeField( "coincreditindicator", "switch", "1", "Coin Credit Indicator" );
		FieldMaker::setFieldProperty( "coincreditindicator", "switch:0" );
		FieldMaker::setFieldProperty( "coincreditindicator", "00:No Coin Credit" );
		FieldMaker::setFieldProperty( "coincreditindicator", "01:Coin Credit" );
		// Table 37
		makeField( "ssasindicator", "switch", "1", "SSAS Indicator" );
		FieldMaker::setFieldProperty( "ssasindicator", "switch:0" );
		FieldMaker::setFieldProperty( "ssasindicator", "00:No Handled by SSAS" );
		FieldMaker::setFieldProperty( "ssasindicator", "01:Handled by SSAS" );
		// Table 38
		makeField( "wdamount", "number", "5", "Walkaway or Deposited Amount" );  // Field format DDDCC
		// Table 39
		makeField( "operatorid", "numberswitch", "11", "Operator Identification" );
		FieldMaker::setFieldProperty( "operatorid", "switch:0" );
		FieldMaker::setFieldProperty( "operatorid", "00:Not Used" );
		FieldMaker::setFieldProperty( "operatorid", "01:1 Operator Identified" );
		FieldMaker::setFieldProperty( "operatorid", "02:2 Operators on Call" );
		FieldMaker::setFieldProperty( "operatorid", "03:3 or More Operators on Call" );
		FieldMaker::setFieldProperty( "operatorid", "number:15" );
		FieldMaker::setFieldProperty( "operatorid", "number:57" );
		// Table 40
		makeField( "traceraudittype", "number", "3", "Type of Audit (Tracer) Record" );
		// Table 41
		makeField( "datacapabilitiesind", "number", "3", "Data Capabilities Indicator" );
		// Table 42
		makeField( "inftransind", "number", "3", "Information Transfer Rate Indicator" );
		// Table 44		
		makeField( "rtatype", "switch", "1", "RTA type" );
		FieldMaker::setFieldProperty( "rtatype", "switch:0" );
		FieldMaker::setFieldProperty( "rtatype", "00:Not a RTA Call" );
		FieldMaker::setFieldProperty( "rtatype", "01:RTA Call" );
		FieldMaker::setFieldProperty( "rtatype", "04:Combined Trunk" );
		FieldMaker::setFieldProperty( "rtatype", "05:RTA Call on Combinded Trunk" );
		// Table 46
		makeField( "raonumber", "number", "3", "Revenue Accounting Office Number" );
		// Table 47
		makeField( "billingnumbercontent", "switch", "1", "Billing Number Content" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "switch:0" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "00:Not Used" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "01:Third Number Billing with NPA, no ROA" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "02:Third Number Billing with RAO and NPA" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "03:ABC with RAO" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "04:ABC with NPA, no RAO" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "05:ABC with NPA and RAO" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "06:Collect with NPA and RAO" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "07:Collect with NPA, no RAO" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "08:10 Digit Special Billing Number" );
		FieldMaker::setFieldProperty( "billingnumbercontent", "09:ITU Standard Card Used" );
		// Table 48
		makeField( "billingvalidationfile", "switch", "1", "Billing Validation File" );
		FieldMaker::setFieldProperty( "billingvalidationfile", "switch:0" );
		FieldMaker::setFieldProperty( "billingvalidationfile", "00:BVF Not Accessed" );
		FieldMaker::setFieldProperty( "billingvalidationfile", "01:BVF Accessed" );
		FieldMaker::setFieldProperty( "billingvalidationfile", "02:BVF Unsuccessful Attempt" );
		FieldMaker::setFieldProperty( "billingvalidationfile", "03:LIDB Accessed" );
		// Table 49
		makeField( "dialingrate", "switch", "1", "Dialing Rate" );
		FieldMaker::setFieldProperty( "dialingrate", "00:Not Used" );
		FieldMaker::setFieldProperty( "dialingrate", "01:ABC" );
		FieldMaker::setFieldProperty( "dialingrate", "02:Operator-Assisted ABC, No Notify" );
		FieldMaker::setFieldProperty( "dialingrate", "03:Operator-Assisted ABC, With Notify" );
		FieldMaker::setFieldProperty( "dialingrate", "04:Operator-Assisted Third Number or Special Billing Number" );
		FieldMaker::setFieldProperty( "dialingrate", "05:Automatic Sequence Call" );
		// Table 55
		makeField( "sigdigs", "number", "3", "Significant Digits in Next Field" );
		// Table 56
		makeField( "terminatingcompany", "number", "3", "Terminating Company" );
		// Table 57
		makeField( "icincid", "numberswitch", "5", "IC/INC Identification" );
		FieldMaker::setFieldProperty( "icincid", "switch:4" );
		FieldMaker::setFieldProperty( "icincid", "40:FGD, IC/INC Involved" );
		FieldMaker::setFieldProperty( "icincid", "41:FGD, IC/INC Not Involved" );
		FieldMaker::setFieldProperty( "icincid", "42:FGD, IC/INC Involvement Unknown" );
		FieldMaker::setFieldProperty( "icincid", "43:FGB, IC/INC Involved" );
		FieldMaker::setFieldProperty( "icincid", "44:FGB, IC/INC Not Involved" );
		FieldMaker::setFieldProperty( "icincid", "45:FGB, IC/INC Involvement Unknown" );
		FieldMaker::setFieldProperty( "icincid", "47:CIC Unknown, IC/INC Involved" );
		FieldMaker::setFieldProperty( "icincid", "48:CIC Unknown, IC/INC Not Involved" );
		FieldMaker::setFieldProperty( "icincid", "49:CIC Unknown, IC/INC Involvement Unknown" );
		FieldMaker::setFieldProperty( "icincid", "4F:Error" );
		FieldMaker::setFieldProperty( "icincid", "number:04" );
		FieldMaker::setFieldProperty( "icincid", "number_only:true" );
		// Table 58
		makeField( "icinccalleventstatus", "number", "3", "IC/INC Call Event Status" );
		// Table 59
		makeField( "icincrouting", "switch", "1", "IC/INC Routing Indicator" );
		FieldMaker::setFieldProperty( "icincrouting", "switch:0" );
		FieldMaker::setFieldProperty( "icincrouting", "00:Direct" );
		FieldMaker::setFieldProperty( "icincrouting", "01:Tandem" );
		FieldMaker::setFieldProperty( "icincrouting", "02:CAP" );
		FieldMaker::setFieldProperty( "icincrouting", "03:CAP from AP Tandem" );
		FieldMaker::setFieldProperty( "icincrouting", "04:Tandem Signaling to TSP - CAP Trunks" );
		FieldMaker::setFieldProperty( "icincrouting", "05:Tandem from Another LEC" );
		// Table 60
		makeField( "anicpnindicator", "switch", "1", "ANI/CPN Indicator" );
		FieldMaker::setFieldProperty( "anicpnindicator", "00:Neither ANI or CPN Info Provided" );
		FieldMaker::setFieldProperty( "anicpnindicator", "01:ANI Info" );
		FieldMaker::setFieldProperty( "anicpnindicator", "02:CPN Info" );
		FieldMaker::setFieldProperty( "anicpnindicator", "03:Both ANI and CPN" );
		// Table 62
		makeField( "dnicode", "number", "5", "Data Network Identification Code" );
		// Table 64
		makeField( "chargepacketind", "switch", "3", "Charging and Packet Indicator" );
		FieldMaker::setFieldProperty( "chargepacketind", "switch:0" );
		FieldMaker::setFieldProperty( "chargepacketind", "00:Unused" );
		FieldMaker::setFieldProperty( "chargepacketind", "01:Intranetwork Call" );
		FieldMaker::setFieldProperty( "chargepacketind", "02:Outgoing Internetwork Call" );
		FieldMaker::setFieldProperty( "chargepacketind", "03:Incoming Internetwork Call" );
		FieldMaker::setFieldProperty( "chargepacketind", "04:Transit Network Call" );
		FieldMaker::setFieldProperty( "chargepacketind", "switch:1" );
		FieldMaker::setFieldProperty( "chargepacketind", "10:Unused" );
		FieldMaker::setFieldProperty( "chargepacketind", "11:Correct Segment Count" );
		FieldMaker::setFieldProperty( "chargepacketind", "12:Incorrect Segment Count" );
		FieldMaker::setFieldProperty( "chargepacketind", "switch:2" );
		FieldMaker::setFieldProperty( "chargepacketind", "20:Unused" );
		FieldMaker::setFieldProperty( "chargepacketind", "21:Orginating User" );
		FieldMaker::setFieldProperty( "chargepacketind", "22:Terminating User" );
		FieldMaker::setFieldProperty( "chargepacketind", "23:Third Party" );
		FieldMaker::setFieldProperty( "chargepacketind", "24:Originating NUI" );
		FieldMaker::setFieldProperty( "chargepacketind", "25:terminating NUI" );
		// Table 70
		makeField( "callednumberdesc", "number", "3", "Called Directory Number Description" );
		// Table 72
		makeField( "altroutenumber", "number", "3", "Alternate Route Number" );
		// Table 73
		makeField( "intntlsvcdiff", "switch", "3", "International Service Difficulty" );
		FieldMaker::setFieldProperty( "intntlsvcdiff", "switch:1" );
		FieldMaker::setFieldProperty( "intntlsvcdiff", "11:Wrong Number" );
		FieldMaker::setFieldProperty( "intntlsvcdiff", "12:Cut Off" );
		FieldMaker::setFieldProperty( "intntlsvcdiff", "13:Poor Transmission" );
		// Table 74
		makeField( "creditmultiplierfactor", "number", "5", "Credit Multiplier Factor" );
		// Table 75
		makeField( "chargeamount", "number", "5", "Charge Amount" );
		// Table 76
		makeField( "numberidentity", "switch", "1", "Number Identity" );
		FieldMaker::setFieldProperty( "numberidentity", "switch:0" );
		FieldMaker::setFieldProperty( "numberidentity", "01:Originating ANI" );
		FieldMaker::setFieldProperty( "numberidentity", "02:Terminating" );
		FieldMaker::setFieldProperty( "numberidentity", "03:Originating CPN" );
		FieldMaker::setFieldProperty( "numberidentity", "04:Private ANI" );
		FieldMaker::setFieldProperty( "numberidentity", "05:Private CPN" );
		FieldMaker::setFieldProperty( "numberidentity", "06:RN" );
		FieldMaker::setFieldProperty( "numberidentity", "07:OCN" );
		FieldMaker::setFieldProperty( "numberidentity", "08:Provisioned Billing Number" );
		// Table 77
		makeField( "servicelogicid", "number", "9", "Service Logic ID" );
		// Table 78
		makeField( "digitsid", "number", "3", "Digits Identifier" );
		// Table 81
		makeField( "npanxxid", "numberswitch", "7", "NPA-NXX Identifier" );
		FieldMaker::setFieldProperty( "npanxxid", "switch:0" );
		FieldMaker::setFieldProperty( "npanxxid", "00:Combined Query Counts" );
		FieldMaker::setFieldProperty( "npanxxid", "01:800" );
		FieldMaker::setFieldProperty( "npanxxid", "02:888" );
		FieldMaker::setFieldProperty( "npanxxid", "03:877" );
		FieldMaker::setFieldProperty( "npanxxid", "04:866" );
		FieldMaker::setFieldProperty( "npanxxid", "05:855" );
		FieldMaker::setFieldProperty( "npanxxid", "06:844" );
		FieldMaker::setFieldProperty( "npanxxid", "07:833" );
		FieldMaker::setFieldProperty( "npanxxid", "08:822" );
		FieldMaker::setFieldProperty( "npanxxid", "09:Reserved" );
		FieldMaker::setFieldProperty( "npanxxid", "number:16" );
		// Table 83
		makeField( "trunkgroupnumber", "numberswitch", "5", "Trunk Group Number" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "switch:0" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "01:SS7 Direct" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "02:Non-SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "03:SS7 Direct Trunk Group Number" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "04:SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "05:Non-SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "06:SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "09:Signal Type Not Specified" );
		FieldMaker::setFieldProperty( "trunkgroupnumber", "number:15" );
		// Table 83
		makeField( "simfacgroup", "numberswitch", "5", "Simulated Facility Group" );
		FieldMaker::setFieldProperty( "simfacgroup", "switch:0" );
		FieldMaker::setFieldProperty( "simfacgroup", "01:SS7 Direct" );
		FieldMaker::setFieldProperty( "simfacgroup", "02:Non-SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "simfacgroup", "03:SS7 Direct Trunk Group Number" );
		FieldMaker::setFieldProperty( "simfacgroup", "04:SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "simfacgroup", "05:Non-SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "simfacgroup", "06:SS7 from IC to AT" );
		FieldMaker::setFieldProperty( "simfacgroup", "09:Signal Type Not Specified" );
		FieldMaker::setFieldProperty( "simfacgroup", "number:15" );
		// Table 85
		makeField( "dialingpresubind", "switch", "1", "Dialing and Presubscription Indicator" );
		FieldMaker::setFieldProperty( "dialingpresubind", "00:Dialed Digits Cannot Be Determined" );
		FieldMaker::setFieldProperty( "dialingpresubind", "01:CAC not dialed, cust presub, no presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "02:CAC dialed, cust not presub, no presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "03:950-XXXX Dialed" );
		FieldMaker::setFieldProperty( "dialingpresubind", "04:CAC not dialed, cust not presub, presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "05:CAC dialed, cust not presub, presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "06:CAC dialed, cust presub, presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "07:CAC dialed, cust presub, no presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "08:CAC not dialed, station not presub, no presub ind" );
		FieldMaker::setFieldProperty( "dialingpresubind", "09:CAC dialed unknown, station presub, presub ind" );

		// Table 87
		makeField( "customerid", "numberswitch", "11", "Customer Identification" );
		FieldMaker::setFieldProperty( "customerid", "switch:0" );
		FieldMaker::setFieldProperty( "customerid", "00:Default" );
		FieldMaker::setFieldProperty( "customerid", "01:Originating" );
		FieldMaker::setFieldProperty( "customerid", "02:Terminating" );
		FieldMaker::setFieldProperty( "customerid", "03:Originating and Terminating" );
		FieldMaker::setFieldProperty( "customerid", "number:15" );
		FieldMaker::setFieldProperty( "customerid", "number:55" );
		// Table 88
		makeField( "modulecode", "number", "3", "Module Code" );
		// Table 89
		makeField( "transfield", "number", "3", "Translation-Settable Field" );
		// Table 91
		makeField( "servicedifficulty", "switch", "1", "Service Difficulty" );
		FieldMaker::setFieldProperty( "servicedifficulty", "switch:0" );
		FieldMaker::setFieldProperty( "servicedifficulty", "00:Not Used" );
		FieldMaker::setFieldProperty( "servicedifficulty", "01:Wrong Number" );
		FieldMaker::setFieldProperty( "servicedifficulty", "02:Cut off" );
		FieldMaker::setFieldProperty( "servicedifficulty", "03:Poor Transmition" );
		// Table 92
		makeField( "numbermin", "number", "3", "Number of Occurrences/Minutes" );
		// Table 95
		makeField( "credit", "money", "5", "Amount of Credit" );
		// Table 105
		makeField( "identificationcode", "number", "5", "5-Digit ID Number" );
		// Table 117
		makeField( "billingid", "switch", "1", "Billing type Identification" );
		FieldMaker::setFieldProperty( "billingid", "switch:0" );
		FieldMaker::setFieldProperty( "billingid", "00:Not Used" );
		FieldMaker::setFieldProperty( "billingid", "01:Calling Card" );
		FieldMaker::setFieldProperty( "billingid", "02:Special Billing Number" );
		FieldMaker::setFieldProperty( "billingid", "03:Third Number" );
		FieldMaker::setFieldProperty( "billingid", "04:Collect" );
		// Table 120
		makeField( "softwareid", "number", "5", "Software Release Identification" );
		// Table 120
		makeField( "collectorid", "number", "5", "Collector Program Generic Number" );
		// Table 120
		makeField( "genericissue", "number", "5", "Generic Issue" );

		// Table 126
		makeField( "digits", "number", "15", "Digits" );
		FieldMaker::setFieldProperty( "digits", "trim:true" );
		// Table 126
		makeField( "largedigits", "number", "15", "Large Digits" );
		FieldMaker::setFieldProperty( "largedigits", "trim:true" );
		// Table 126
		makeField( "pincodedigits", "number", "15", "PIN Code Digits" );
		FieldMaker::setFieldProperty( "largedigits", "trim:true" );

		// Table 140
		makeField( "amasequencenum", "number", "5", "AMA Sequence Number" );

		// Table 165
		makeField( "countrycode", "numberswitch", "5", "Country Code or Data Network ID Code" );
		FieldMaker::setFieldProperty( "countrycode", "switch:0" );
		FieldMaker::setFieldProperty( "countrycode", "00:E.164 Number, Code Length Unknown" );
		FieldMaker::setFieldProperty( "countrycode", "01:E.164 Number, 1 Digit Code" );
		FieldMaker::setFieldProperty( "countrycode", "02:E.164 Number, 2 Digit Code" );
		FieldMaker::setFieldProperty( "countrycode", "03:E.164 Number, 3 Digit Code" );
		FieldMaker::setFieldProperty( "countrycode", "04:X.121 Number" );
		FieldMaker::setFieldProperty( "countrycode", "09:E.164 Number, LIDB Cannot Determine Code Length" );
		FieldMaker::setFieldProperty( "countrycode", "number:14" );

		// Table 188
		makeField( "bbgbillingnpa", "number", "3", "BBG Billing NPA" );
		// Table 189
		makeField( "bbgbillingcoend", "number", "7", "BBG Billing CO-End Point Number" );

		// Table 197
		makeField( "lata", "number", "3", "Local Access and Transport Area" );

		// Table 206
		makeField( "directorynumdesc", "number", "3", "Directory Number Description" );

		// Table 244
		makeField( "trunkid", "numberswitch", "9", "Trunk Identification" );
		FieldMaker::setFieldProperty( "trunkid", "switch:0" );
		FieldMaker::setFieldProperty( "trunkid", "0:Routing Indicator" );
		FieldMaker::setFieldProperty( "trunkid", "01:Direct - Incoming, Different Network" );
		FieldMaker::setFieldProperty( "trunkid", "02:Direct - Outgoing, Difference Network" );
		FieldMaker::setFieldProperty( "trunkid", "03:Direct - Incoming, Same Network" );
		FieldMaker::setFieldProperty( "trunkid", "04:Direct - Outgoing, Same Network" );
		FieldMaker::setFieldProperty( "trunkid", "05:Tandem - Incoming, Different Network" );
		FieldMaker::setFieldProperty( "trunkid", "06:Tandem - Outgoing, Different Network" );
		FieldMaker::setFieldProperty( "trunkid", "07:Tandem - Incoming, Same Network" );
		FieldMaker::setFieldProperty( "trunkid", "08:Tandem - Outgoing, Same Network" );
		FieldMaker::setFieldProperty( "trunkid", "number:14" );
		FieldMaker::setFieldProperty( "trunkid", "number:54" );

		// Table 272
		makeField( "trunkgroupinfo", "number", "13", "Trunk Group Information" );

		// Table 273
		makeField( "carrierinterface", "switch", "3", "Carrier Interface" );
		FieldMaker::setFieldProperty( "carrierinterface", "switch:2" );
		FieldMaker::setFieldProperty( "carrierinterface", "21:Feature Group D" );
		FieldMaker::setFieldProperty( "carrierinterface", "22:Feature Group D with Tandem Signaling" );
		FieldMaker::setFieldProperty( "carrierinterface", "23:Telecommunications Relay Service" );
		FieldMaker::setFieldProperty( "carrierinterface", "24:Type 2A" );
		FieldMaker::setFieldProperty( "carrierinterface", "25:Type 2B" );
		FieldMaker::setFieldProperty( "carrierinterface", "26:Type 2D" );

		// Table 280
		makeField( "completionindicator", "number", "3", "Completion Indicator" );

		// Table 330
		makeField( "classfunctions", "switch", "3", "CLASS Functions" );
		FieldMaker::setFieldProperty( "classfunctions", "switch:2" );
		FieldMaker::setFieldProperty( "classfunctions", "20:None" );
		FieldMaker::setFieldProperty( "classfunctions", "21:Active" );
		FieldMaker::setFieldProperty( "classfunctions", "22:Inactive" );
		FieldMaker::setFieldProperty( "classfunctions", "23:Delete" );
		FieldMaker::setFieldProperty( "classfunctions", "24:Create Active" );
		FieldMaker::setFieldProperty( "classfunctions", "25:Create Inactive" );
		FieldMaker::setFieldProperty( "classfunctions", "26:Session Aborted" );
		// Table 331
		makeField( "classfeaturestatus", "number", "3", "Class Feature Status" );

		// Table 403
		makeField( "chargeableopholding", "shortduration", "5", "Chargeable Operator Holding Time" );

		// Table 407
		makeField( "bbgcalltype", "switch", "3", "BBG Call Type" );
		FieldMaker::setFieldProperty( "bbgcalltype", "switch:1" );
		FieldMaker::setFieldProperty( "bbgcalltype", "1:BBG Call Type" );
		FieldMaker::setFieldProperty( "bbgcalltype", "10:Unused ( Vendor Specific )" );
		FieldMaker::setFieldProperty( "bbgcalltype", "11:Intercom use" );
		FieldMaker::setFieldProperty( "bbgcalltype", "12:Public network access: Originating outgoing" );
		FieldMaker::setFieldProperty( "bbgcalltype", "13:Public network access: Incoming terminating" );
		FieldMaker::setFieldProperty( "bbgcalltype", "14:Private network access: Originating outgoing" );
		FieldMaker::setFieldProperty( "bbgcalltype", "15:Private network access: Incoming terminating" );
		FieldMaker::setFieldProperty( "bbgcalltype", "16:Miscellaneous internal connection" );
		FieldMaker::setFieldProperty( "bbgcalltype", "17:Reserved ( Vendor Specific )" );
		FieldMaker::setFieldProperty( "bbgcalltype", "18:Reserved ( Vendor Specific )" );
		FieldMaker::setFieldProperty( "bbgcalltype", "19:Reserved ( Vendor Specific )" );
		FieldMaker::setFieldProperty( "bbgcalltype", "switch:2" );
		FieldMaker::setFieldProperty( "bbgcalltype", "2:Control Status" );
		FieldMaker::setFieldProperty( "bbgcalltype", "20:Not applicable" );
		FieldMaker::setFieldProperty( "bbgcalltype", "21:Within control limit" );
		FieldMaker::setFieldProperty( "bbgcalltype", "22:Control overflow, routed" );

		//Table 408
		makeField( "ektscapabilities", "switch", "7", "Activation of Electronic Key Telephone Service Capabilities" );
		FieldMaker::setFieldProperty( "ektscapabilities", "switch:1" );
		FieldMaker::setFieldProperty( "ektscapabilities", "11:Activation of User Bridging - Not Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "12:Activation of User Bridging - Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "switch:2" );
		FieldMaker::setFieldProperty( "ektscapabilities", "21:Activation of Directory Number Bridging - Not Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "22:Activation of Directory Number Bridging - Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "switch:3" );
		FieldMaker::setFieldProperty( "ektscapabilities", "31:Intercom Calling - Not Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "32:Intercom Calling - Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "switch:4" );
		FieldMaker::setFieldProperty( "ektscapabilities", "41:Deactivation of Automatic Bridging Call Exclusion - Not Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "42:Deactivation of Automatic Bridging Call Exclusion - Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "switch:5" );
		FieldMaker::setFieldProperty( "ektscapabilities", "51:Activation of Manual Bridging Call Exclusion - Not Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "52:Activation of Manual Bridging Call Exclusion - Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "switch:6" );
		FieldMaker::setFieldProperty( "ektscapabilities", "61:Station Ringing Transfer - Not Used" );
		FieldMaker::setFieldProperty( "ektscapabilities", "62:Station Ringing Transfer - Used" );

		// Table 410
		makeField( "networkinterworking", "switch", "1", "Network Interworking" );
		FieldMaker::setFieldProperty( "networkinterworking", "switch:0" );
		FieldMaker::setFieldProperty( "networkinterworking", "00:No Interworking" );
		FieldMaker::setFieldProperty( "networkinterworking", "01:Interworking Unknown" );
		FieldMaker::setFieldProperty( "networkinterworking", "02:Interworking Encountered" );
		FieldMaker::setFieldProperty( "networkinterworking", "03:Terminating Interworking Encountered for Alerting" );
		FieldMaker::setFieldProperty( "networkinterworking", "04:Terminating Interworking Encountered for Connection" );
		FieldMaker::setFieldProperty( "networkinterworking", "05:Originating Interworking Encountered" );
		// Table 411
		makeField( "releasecauseind", "numberswitch", "5", "Release Cause Indicator" );
		FieldMaker::setFieldProperty( "releasecauseind", "switch:1" );
		FieldMaker::setFieldProperty( "releasecauseind", "1:Cause Category" );
		FieldMaker::setFieldProperty( "releasecauseind", "10:ITU Standard" );
		FieldMaker::setFieldProperty( "releasecauseind", "11:National" );
		FieldMaker::setFieldProperty( "releasecauseind", "12:Network Specific" );
		FieldMaker::setFieldProperty( "releasecauseind", "number:23" );
		// Table 412
		makeField( "bearercaps", "switch", "3", "Bearer Capability / Call Type" );
		FieldMaker::setFieldProperty( "bearercaps", "switch:0" );
		FieldMaker::setFieldProperty( "bearercaps", "01:Voice / Voiceband Data" );
		FieldMaker::setFieldProperty( "bearercaps", "02:Circuit-Mode Data" );
		FieldMaker::setFieldProperty( "bearercaps", "03:Packet-Mode Data" );
		FieldMaker::setFieldProperty( "bearercaps", "switch:2" );
		FieldMaker::setFieldProperty( "bearercaps", "21:Curcuit Mode: Speech" );
		FieldMaker::setFieldProperty( "bearercaps", "22:Circuit Mode: 3.1-kHz Audio" );
		FieldMaker::setFieldProperty( "bearercaps", "23:Circuit Mode: Unrestricted 64-kbps Info Transfer" );
		FieldMaker::setFieldProperty( "bearercaps", "24:Circuit Mode: Unrestricted 64-kbps Info Transfer Adapted from 56-kbps" );
		FieldMaker::setFieldProperty( "bearercaps", "25:Packet Mode: Unrestricted Info Transfer" );
		FieldMaker::setFieldProperty( "bearercaps", "27:Circuit Mode: Unresitrcted Info Transfer Greater Than 64-kbps" );
		// Table 413
		makeField( "sigsuppservusage", "switch", "15", "Signaling or supplementary Service Capabilities Usage" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:1" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "1:Calling Party Subaddress Delivery" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "11:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "12:Feature Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:2" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "2:Called Party Subaddress Delivery" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "21:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "22:Feature Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:3" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "3:Low-Layer Compatibility Info Delivery" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "31:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "32:Feature Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:4" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "4:High-Layer Compatibility Information Delivery" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "41:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "42:Feature Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:5" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "5:User-to-User Info / Fast Select" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "51:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "52:Feature Used, Delivered" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "53:Feature Used, not Delivered" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:8" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "8:ISDN Flexible Calling" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "81:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "82:Feature Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "switch:9" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "9:Call Waiting Originating" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "91:Feature not Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "92:Feature Used" );
		FieldMaker::setFieldProperty( "sigsuppservusage", "number:96" ); // Cheat a little bit because switch does not support 2 digits, yet.

		// Table 415
		makeField( "classfeaturecode", "number", "3", "CLASS Feature Code" );

		// Table 421
		makeField( "originatinglineinfo", "number", "3", "Originating Line Information Parameter (OLIP)" );

		// Table 423
		makeField( "linenumbertype", "number", "3", "Line Number Type" );

		// Table 480
		makeField( "headertype", "switch", "1", "Header Type" );
		FieldMaker::setFieldProperty( "headertype", "switch:0" );
		FieldMaker::setFieldProperty( "headertype", "00:Start of a LDS not associated with a hardware state change" );
		FieldMaker::setFieldProperty( "headertype", "01:LDS's records occurred after a sending unit input transfer" );
		FieldMaker::setFieldProperty( "headertype", "02:Ending of an LDS not associated with a hardware state change at the switch" );
		FieldMaker::setFieldProperty( "headertype", "03:LDS's records occurred before a sending unit output transfer" );

		// Table 488
		makeField( "networkidentifier", "number", "7", "Carrier / Network Identifier" );

		// Table 490
		makeField( "sendingunitnumber", "number", "3", "Sending Unit Number" );

		// Table 608
		makeField( "resourcetype", "number", "3", "Resource Type" );

		// Table 610
		makeField( "indicatorid", "number", "3", "Indicator ID" );

		// Table 730
		makeField( "partyid", "number", "3", "Party Identifier" );

		// Table 731
		makeField( "lrn", "number", "11", "Location Routing Number" );

		// Table 732
		makeField( "serviceproviderid", "number", "9", "Service Provider Identity (NDGR)" );

		// Table 733
		makeField( "location", "number", "15", "Location" );

		// Table 734
		makeField( "supportinginfo", "numberswitch", "7", "Supporting Information" );
		FieldMaker::setFieldProperty( "supportinginfo", "switch:0" );
		FieldMaker::setFieldProperty( "supportinginfo", "01:LNP Database" );
		FieldMaker::setFieldProperty( "supportinginfo", "02:Switching System Data" );
		FieldMaker::setFieldProperty( "supportinginfo", "03:Incoming Signalling" );
		FieldMaker::setFieldProperty( "supportinginfo", "04:Switch LRN/GUBB LNP Database" );
		FieldMaker::setFieldProperty( "supportinginfo", "number:12" );

		// Table 801
		makeField( "numtrunklegsused", "number", "1", "Number of trunk Legs Used" );
		// Table 801
		makeField( "originatingshelf", "number", "1", "Originating Shelf" );
		// Table 801
		makeField( "originatingmodule", "number", "1", "Originating Module" );
		// Table 801
		makeField( "terminatingshelf", "number", "1", "Terminating Shelf" );
		// Table 801
		makeField( "terminatingmodule", "number", "1", "Terminating Module" );
		// Table 802
		makeField( "filesequenceno", "number", "3", "File Sequence Number" );
		// Table 802
		makeField( "triggerseqnum", "number", "3", "Trigger Sequence Number" );
		// Table 802
		makeField( "screenlistsizescf", "number", "3", "Screening List Size for Selective Call Forwarding" );
		// Table 802
		makeField( "screenlistsizescr", "number", "3", "Screening List Size for Selective Call Rejection" );
		// Table 802
		makeField( "screenlistsizedrcw", "number", "3", "Screening List Size for Distinctive Call Waiting" );
		// Table 802
		makeField( "originatingcard", "number", "3", "Originating Card" );
		// Table 802
		makeField( "originatingds1", "number", "3", "Originating DS-1" );
		// Table 802
		makeField( "originatingds0", "number", "3", "Originating DS-0" );
		// Table 802
		makeField( "terminatingcard", "number", "3", "Terminating Card" );
		// Table 802
		makeField( "terminatingds1", "number", "3", "Terminating DS-1" );
		// Table 802
		makeField( "terminatingds0", "number", "3", "Terminating DS-0" );
		// Table 802
		makeField( "speeddialingcode", "number", "3", "Speed Dialing Code" );
		// Table 802
		makeField( "codectype", "number", "3", "Codec Type" );
		// Table 802
		makeField( "percentlostpackets", "number", "3", "Percentage of Lost Packets" );
		// Table 803
		makeField( "blockcount", "number", "5", "Block Count" );
		// Table 803
		makeField( "callcountinfodeliv", "number", "5", "Call Count - Information Delivered" );
		// Table 803
		makeField( "callcountinfoanon", "number", "5", "Call Count - Information Anonymous" );
		// Table 804
		makeField( "recordcount", "number", "7", "Record Count" );
		// Table 804
		makeField( "lostcalldata", "number", "7", "Calls with Lost Call Data" );
		// Table 804
		makeField( "amalostcalldata", "number", "7", "AMA Calls with Lost Call Data" );
		// Table 804
		makeField( "abortedbafrecords", "number", "7", "Aborted BAF Records" );
		// Table 804
		makeField( "flaggedbafrecords", "number", "7", "Flagged BAF Records" );
		// Table 804
		makeField( "timingerrorbafrecords", "number", "7", "BAF Records with Timing Errors" );
		// Table 804
		makeField( "lostbafrecords", "number", "7", "Lost BAF Records on Block Writes" );
		// Table 804
		makeField( "firstblocknumber", "number", "7", "First Block Sequence Number" );
		// Table 804
		makeField( "lastblocknumber", "number", "7", "Last Block Sequence Number" );
		// Table 804
		makeField( "recordid", "number", "7", "Record ID" );
		// Table 804
		makeField( "jitterdelay", "number", "7", "Jitter Delay" );
		// Table 804
		makeField( "lostpackets", "number", "7", "Lost Packets" );
		// Table 804
		makeField( "rcvedpackets", "number", "7", "Number of Received Packets" );
		// Table 805
		makeField( "bafrecords", "number", "9", "BAF Records" );
		// Table 805
		makeField( "originatingcalls", "number", "9", "Originating Calls" );
		// Table 805
		makeField( "terminatingcalls", "number", "9", "Terminating Calls" );
		// Table 805
		makeField( "outgoingcalls", "number", "9", "Outgoing Calls" );
		// Table 805
		makeField( "calls", "number", "9", "Calls" );
		// Table 805
		makeField( "amacalls", "number", "9", "AMA Calls" );
		
		// Table 807
        makeField( "thirteendigitnumber", "number", "13", "13 Digit Number" );
		// Table 808
		makeField("callcorrelator", "number", "15", "Call Correlator");

		// Table 901
		makeField( "switchid", "number", "20", "Switch Identifier" );
		// Table 902
		makeField( "sipuri", "number", "128", "Uniform Resource Identifier" );
		// Table 903
		makeField( "peerfacid", "number", "5", "Peer Facility Group Identifier" );
		// Table 904
		makeField( "registrationtype", "switch", "1", "Registration Type" );
		FieldMaker::setFieldProperty( "registrationtype", "switch:0" );
		FieldMaker::setFieldProperty( "registrationtype", "00:Registration" );
		FieldMaker::setFieldProperty( "registrationtype", "01:Deregistration" );
		
		// Table 911
		makeField( "cpinternalcausecode", "number", "7", "Super-sized digits (Cedar Point proprietary table)" );

		// Table 926
		makeField( "cpsupersizedigits", "number", "25", "Super-sized digits (Cedar Point proprietary table)" );

		// Table 933
		makeField( "cplocation", "switch", "5", "Location (Cedar Point proprietary table)" );
		FieldMaker::setFieldProperty( "cplocation", "switch:2" );
		FieldMaker::setFieldProperty( "cplocation", "20:user" );
		FieldMaker::setFieldProperty( "cplocation", "21:private network serving the local user" );
		FieldMaker::setFieldProperty( "cplocation", "22:public network serving the local user" );
		FieldMaker::setFieldProperty( "cplocation", "23:transit network" );
		FieldMaker::setFieldProperty( "cplocation", "24:public network serving the remote user" );
		FieldMaker::setFieldProperty( "cplocation", "25:private network serving the remote user" );
		FieldMaker::setFieldProperty( "cplocation", "27:international network" );
		FieldMaker::setFieldProperty( "cplocation", "switch:3" );
		FieldMaker::setFieldProperty( "cplocation", "30:beyond" );

		// Table 934
		makeField( "cppartyname", "number", "31", "Super-sized digits (Cedar Point proprietary table)" );

		// Table 935
		makeField( "cpcorrelationid", "number", "33", "Correlation ID (Cedar Point proprietary table)" );

		// Table 936
		makeField( "cpboolean", "number", "1", "boolean (Cedar Point proprietary table)" );

		// Table 950
		makeField( "cpcallparkeddisp", "numberswitch", "3", "Call Parked disposition (Cedar Point proprietary table)" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "switch:0" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "00:Call Parked Disposition" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "01:Picked up" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "02:Timeout forwarded" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "03:Park Retrieved" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "04:Retrieved" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "05:Call Terminated" );
		FieldMaker::setFieldProperty( "cpcallparkeddisp", "06:Call answered on re-ring" );

		// Table 976
		makeField( "cptypeofname", "numberswitch", "1", "Type of Name (Cedar Point proprietary table)" );
		FieldMaker::setFieldProperty( "cptypeofname", "switch:0" );
		FieldMaker::setFieldProperty( "cptypeofname", "01:Originating Number (ANI)" );
		FieldMaker::setFieldProperty( "cptypeofname", "02:Terminating or Destination Number" );
		FieldMaker::setFieldProperty( "cptypeofname", "03:Originating Calling Party Number (CPN)" );
		FieldMaker::setFieldProperty( "cptypeofname", "04:Private Number Originating (ANI)" );
		FieldMaker::setFieldProperty( "cptypeofname", "05:Private Number Originating (CPN)" );
		FieldMaker::setFieldProperty( "cptypeofname", "06:Redirecting Number" );
		FieldMaker::setFieldProperty( "cptypeofname", "07:Original Called Number" );
		FieldMaker::setFieldProperty( "cptypeofname", "08:Provisioned Billing Number" );
		FieldMaker::setFieldProperty( "cptypeofname", "09:Name from CNAM query" );

	}
} // namespace