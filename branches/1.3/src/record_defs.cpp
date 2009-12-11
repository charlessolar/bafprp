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

#include "bafrecord.h"

namespace bafprp
{
	void define_default_records()
	{
		// Only setup types once.
		static bool first = true;
		if( !first ) return;
		first = false;

		RecordMaker::setRecordField( 1, "structurecode" );
		RecordMaker::setRecordField( 1, "calltype" ); 
		RecordMaker::setRecordField( 1, "sensortype" ); 
		RecordMaker::setRecordField( 1, "sensorid" ); 
		RecordMaker::setRecordField( 1, "recordofficetype" );
		RecordMaker::setRecordField( 1, "recordofficeid" );
		RecordMaker::setRecordField( 1, "date" );
		RecordMaker::setRecordField( 1, "timingindicator" );
		RecordMaker::setRecordField( 1, "studyindicator" );
		RecordMaker::setRecordField( 1, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 1, "servicetrafficind" );
		RecordMaker::setRecordField( 1, "operatoraction" );
		RecordMaker::setRecordField( 1, "servicefeaturecode" );
		RecordMaker::setRecordField( 1, "originatingnpa" );
		RecordMaker::setRecordField( 1, "originatingnumber" );
		RecordMaker::setRecordField( 1, "overseasindicator" );
		RecordMaker::setRecordField( 1, "terminatingnpa" );
		RecordMaker::setRecordField( 1, "terminatingnumber" );
		RecordMaker::setRecordField( 1, "time" );
		RecordMaker::setRecordField( 1, "elapsedtime" );

		RecordMaker::setRecordField( 20, "structurecode" ); 
		RecordMaker::setRecordField( 20, "calltype" ); 
		RecordMaker::setRecordField( 20, "sensortype" ); 
		RecordMaker::setRecordField( 20, "sensorid" ); 
		RecordMaker::setRecordField( 20, "recordofficetype" );
		RecordMaker::setRecordField( 20, "recordofficeid" );
		RecordMaker::setRecordField( 20, "date" );
		RecordMaker::setRecordField( 20, "timingindicator" );
		RecordMaker::setRecordField( 20, "studyindicator" );
		RecordMaker::setRecordField( 20, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 20, "servicetrafficind" );
		RecordMaker::setRecordField( 20, "operatoraction" );
		RecordMaker::setRecordField( 20, "servicefeaturecode" );
		RecordMaker::setRecordField( 20, "originatingnpa" );
		RecordMaker::setRecordField( 20, "originatingnumber" );
		RecordMaker::setRecordField( 20, "overseasindicator" );
		RecordMaker::setRecordField( 20, "terminatingnpa" );
		RecordMaker::setRecordField( 20, "terminatingnumber" );
		RecordMaker::setRecordField( 20, "time" );
		RecordMaker::setRecordField( 20, "elapsedtime" );
		RecordMaker::setRecordField( 20, "watsindicator" );
		RecordMaker::setRecordField( 20, "msgbillingindex" );

		RecordMaker::setRecordField( 28, "structurecode" ); 
		RecordMaker::setRecordField( 28, "calltype" ); 
		RecordMaker::setRecordField( 28, "sensortype" ); 
		RecordMaker::setRecordField( 28, "sensorid" ); 
		RecordMaker::setRecordField( 28, "recordofficetype" );
		RecordMaker::setRecordField( 28, "recordofficeid" );
		RecordMaker::setRecordField( 28, "date" );
		RecordMaker::setRecordField( 28, "timingindicator" );
		RecordMaker::setRecordField( 28, "studyindicator" );
		RecordMaker::setRecordField( 28, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 28, "servicetrafficind" );
		RecordMaker::setRecordField( 28, "operatoraction" );
		RecordMaker::setRecordField( 28, "servicefeaturecode" );
		RecordMaker::setRecordField( 28, "originatingnpa" );
		RecordMaker::setRecordField( 28, "originatingnumber" );
		RecordMaker::setRecordField( 28, "time" );

		RecordMaker::setRecordField( 76, "structurecode" ); 
		RecordMaker::setRecordField( 76, "calltype" ); 
		RecordMaker::setRecordField( 76, "sensortype" ); 
		RecordMaker::setRecordField( 76, "sensorid" ); 
		RecordMaker::setRecordField( 76, "recordofficetype" );
		RecordMaker::setRecordField( 76, "recordofficeid" );
		RecordMaker::setRecordField( 76, "date" );
		RecordMaker::setRecordField( 76, "timingindicator" );
		RecordMaker::setRecordField( 76, "studyindicator" );
		RecordMaker::setRecordField( 76, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 76, "servicetrafficind" );
		RecordMaker::setRecordField( 76, "operatoraction" );
		RecordMaker::setRecordField( 76, "servicefeaturecode" );
		RecordMaker::setRecordField( 76, "originatingnpa" );
		RecordMaker::setRecordField( 76, "originatingnumber" );
		RecordMaker::setRecordField( 76, "time" );
		RecordMaker::setRecordField( 76, "elapsedtime" );
		RecordMaker::setRecordField( 76, "numtrunklegsused" );

		RecordMaker::setRecordField( 79, "structurecode" ); 
		RecordMaker::setRecordField( 79, "calltype" ); 
		RecordMaker::setRecordField( 79, "sensortype" ); 
		RecordMaker::setRecordField( 79, "sensorid" ); 
		RecordMaker::setRecordField( 79, "recordofficetype" );
		RecordMaker::setRecordField( 79, "recordofficeid" );
		RecordMaker::setRecordField( 79, "date" );
		RecordMaker::setRecordField( 79, "timingindicator" );
		RecordMaker::setRecordField( 79, "studyindicator" );
		RecordMaker::setRecordField( 79, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 79, "servicetrafficind" );
		RecordMaker::setRecordField( 79, "operatoraction" );
		RecordMaker::setRecordField( 79, "servicefeaturecode" );
		RecordMaker::setRecordField( 79, "terminatingnpa" );
		RecordMaker::setRecordField( 79, "terminatingnumber" );
		RecordMaker::setRecordField( 79, "time" );
		RecordMaker::setRecordField( 79, "elapsedtime" );

		RecordMaker::setRecordField( 96, "structurecode" ); 
		RecordMaker::setRecordField( 96, "calltype" ); 
		RecordMaker::setRecordField( 96, "sensortype" ); 
		RecordMaker::setRecordField( 96, "sensorid" ); 
		RecordMaker::setRecordField( 96, "recordofficetype" );
		RecordMaker::setRecordField( 96, "recordofficeid" );
		RecordMaker::setRecordField( 96, "activationdate" );
		RecordMaker::setRecordField( 96, "timingindicator" );
		RecordMaker::setRecordField( 96, "studyindicator" );
		RecordMaker::setRecordField( 96, "servicefeaturecode" );
		RecordMaker::setRecordField( 96, "originatingnpa" );
		RecordMaker::setRecordField( 96, "originatingnumber" );
		RecordMaker::setRecordField( 96, "overseasindicator" );
		RecordMaker::setRecordField( 96, "forwardtonumber" );
		RecordMaker::setRecordField( 96, "activationtime" );
		RecordMaker::setRecordField( 96, "elapsedtime" );
		RecordMaker::setRecordField( 96, "presentdate" );
		RecordMaker::setRecordField( 96, "presenttime" );

		RecordMaker::setRecordField( 110, "structurecode" ); 
		RecordMaker::setRecordField( 110, "calltype" ); 
		RecordMaker::setRecordField( 110, "sensortype" ); 
		RecordMaker::setRecordField( 110, "sensorid" ); 
		RecordMaker::setRecordField( 110, "recordofficetype" );
		RecordMaker::setRecordField( 110, "recordofficeid" );
		RecordMaker::setRecordField( 110, "classfeaturecode" );
		RecordMaker::setRecordField( 110, "date" );
		RecordMaker::setRecordField( 110, "time" );
		RecordMaker::setRecordField( 110, "originatingnpa" );
		RecordMaker::setRecordField( 110, "originatingnumber" );
		RecordMaker::setRecordField( 110, "callcountinfodeliv" );
		RecordMaker::setRecordField( 110, "callcountinfoanon" );

		RecordMaker::setRecordField( 220, "structurecode" ); 
		RecordMaker::setRecordField( 220, "calltype" ); 
		RecordMaker::setRecordField( 220, "sensortype" ); 
		RecordMaker::setRecordField( 220, "sensorid" ); 
		RecordMaker::setRecordField( 220, "recordofficetype" );
		RecordMaker::setRecordField( 220, "recordofficeid" );
		RecordMaker::setRecordField( 220, "date" );
		RecordMaker::setRecordField( 220, "timingindicator" );
		RecordMaker::setRecordField( 220, "studyindicator" );
		RecordMaker::setRecordField( 220, "completionindicator" );
		RecordMaker::setRecordField( 220, "operatoraction" );
		RecordMaker::setRecordField( 220, "servicefeaturecode" );
		RecordMaker::setRecordField( 220, "originatingnpa" );
		RecordMaker::setRecordField( 220, "originatingnumber" );
		RecordMaker::setRecordField( 220, "overseasindicator" );
		RecordMaker::setRecordField( 220, "terminatingnpa" );
		RecordMaker::setRecordField( 220, "terminatingnumber" );
		RecordMaker::setRecordField( 220, "time" );
		RecordMaker::setRecordField( 220, "elapsedtime" );
		RecordMaker::setRecordField( 220, "servicelogicid" );

		RecordMaker::setRecordField( 221, "structurecode" ); 
		RecordMaker::setRecordField( 221, "calltype" ); 
		RecordMaker::setRecordField( 221, "sensortype" ); 
		RecordMaker::setRecordField( 221, "sensorid" ); 
		RecordMaker::setRecordField( 221, "recordofficetype" );
		RecordMaker::setRecordField( 221, "recordofficeid" );
		RecordMaker::setRecordField( 221, "date" );
		RecordMaker::setRecordField( 221, "timingindicator" );
		RecordMaker::setRecordField( 221, "studyindicator" );
		RecordMaker::setRecordField( 221, "completionindicator" );
		RecordMaker::setRecordField( 221, "servicefeaturecode" );
		RecordMaker::setRecordField( 221, "terminatingnpa" );
		RecordMaker::setRecordField( 221, "terminatingnumber" );
		RecordMaker::setRecordField( 221, "time" );
		RecordMaker::setRecordField( 221, "elapsedtime" );
		RecordMaker::setRecordField( 221, "servicelogicid" );

		RecordMaker::setRecordField( 360, "structurecode" ); 
		RecordMaker::setRecordField( 360, "calltype" ); 
		RecordMaker::setRecordField( 360, "sensortype" ); 
		RecordMaker::setRecordField( 360, "sensorid" ); 
		RecordMaker::setRecordField( 360, "recordofficetype" );
		RecordMaker::setRecordField( 360, "recordofficeid" );
		RecordMaker::setRecordField( 360, "date" );
		RecordMaker::setRecordField( 360, "timingindicator" );
		RecordMaker::setRecordField( 360, "studyindicator" );
		RecordMaker::setRecordField( 360, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 360, "servicetrafficind" );
		RecordMaker::setRecordField( 360, "operatoraction" );
		RecordMaker::setRecordField( 360, "servicefeaturecode" );
		RecordMaker::setRecordField( 360, "originatingnpa" );
		RecordMaker::setRecordField( 360, "originatingnumber" );
		RecordMaker::setRecordField( 360, "dialednpa" );
		RecordMaker::setRecordField( 360, "dialednumber" );
		RecordMaker::setRecordField( 360, "overseasindicator" );
		RecordMaker::setRecordField( 360, "terminatingnpa" );
		RecordMaker::setRecordField( 360, "terminatingnumber" );
		RecordMaker::setRecordField( 360, "time" );
		RecordMaker::setRecordField( 360, "elapsedtime" );
		RecordMaker::setRecordField( 360, "icincprefix" );
		RecordMaker::setRecordField( 360, "carrierconnectdate" );
		RecordMaker::setRecordField( 360, "carrierconnecttime" );
		RecordMaker::setRecordField( 360, "carrierelapsedtime" );
		RecordMaker::setRecordField( 360, "icinceventstatus" );
		RecordMaker::setRecordField( 360, "trunkgroupnumber" );
		RecordMaker::setRecordField( 360, "icincroutingind" );
		RecordMaker::setRecordField( 360, "anicpnindicator" );
		RecordMaker::setRecordField( 360, "rao" );
		RecordMaker::setRecordField( 360, "lata" );

		RecordMaker::setRecordField( 364, "structurecode" ); 
		RecordMaker::setRecordField( 364, "calltype" ); 
		RecordMaker::setRecordField( 364, "sensortype" ); 
		RecordMaker::setRecordField( 364, "sensorid" ); 
		RecordMaker::setRecordField( 364, "recordofficetype" );
		RecordMaker::setRecordField( 364, "recordofficeid" );
		RecordMaker::setRecordField( 364, "date" );
		RecordMaker::setRecordField( 364, "timingindicator" );
		RecordMaker::setRecordField( 364, "studyindicator" );
		RecordMaker::setRecordField( 364, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 364, "servicetrafficind" );
		RecordMaker::setRecordField( 364, "operatoraction" );
		RecordMaker::setRecordField( 364, "servicefeaturecode" );
		RecordMaker::setRecordField( 364, "originatingnpa" );
		RecordMaker::setRecordField( 364, "originatingnumber" );
		RecordMaker::setRecordField( 364, "dialednumber" );
		RecordMaker::setRecordField( 364, "overseasindicator" );
		RecordMaker::setRecordField( 364, "terminatingnpa" );
		RecordMaker::setRecordField( 364, "terminatingnumber" );
		RecordMaker::setRecordField( 364, "time" );
		RecordMaker::setRecordField( 364, "elapsedtime" );
		RecordMaker::setRecordField( 364, "rao" );
		RecordMaker::setRecordField( 364, "lata" );

		RecordMaker::setRecordField( 500, "structurecode" ); 
		RecordMaker::setRecordField( 500, "calltype" ); 
		RecordMaker::setRecordField( 500, "sensortype" ); 
		RecordMaker::setRecordField( 500, "sensorid" ); 
		RecordMaker::setRecordField( 500, "recordofficetype" );
		RecordMaker::setRecordField( 500, "recordofficeid" );
		RecordMaker::setRecordField( 500, "date" );
		RecordMaker::setRecordField( 500, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 500, "servicefeaturecode" );
		RecordMaker::setRecordField( 500, "originatingnpa" );
		RecordMaker::setRecordField( 500, "originatingnumber" );
		RecordMaker::setRecordField( 500, "overseasindicator" );
		RecordMaker::setRecordField( 500, "terminatingnpa" );
		RecordMaker::setRecordField( 500, "terminatingnumber" );
		RecordMaker::setRecordField( 500, "time" );
		RecordMaker::setRecordField( 500, "elapsedtime" );

		RecordMaker::setRecordField( 614, "structurecode" ); 
		RecordMaker::setRecordField( 614, "calltype" ); 
		RecordMaker::setRecordField( 614, "sensortype" ); 
		RecordMaker::setRecordField( 614, "sensorid" ); 
		RecordMaker::setRecordField( 614, "recordofficetype" );
		RecordMaker::setRecordField( 614, "recordofficeid" );
		RecordMaker::setRecordField( 614, "date" );
		RecordMaker::setRecordField( 614, "timingindicator" );
		RecordMaker::setRecordField( 614, "studyindicator" );
		RecordMaker::setRecordField( 614, "servicefeaturecode" );
		RecordMaker::setRecordField( 614, "originatingnpa" );
		RecordMaker::setRecordField( 614, "originatingnumber" );
		RecordMaker::setRecordField( 614, "overseasindicator" );
		RecordMaker::setRecordField( 614, "forwardtonumber" );
		RecordMaker::setRecordField( 614, "activationtime" );

		RecordMaker::setRecordField( 625, "structurecode" ); 
		RecordMaker::setRecordField( 625, "calltype" ); 
		RecordMaker::setRecordField( 625, "sensortype" ); 
		RecordMaker::setRecordField( 625, "sensorid" ); 
		RecordMaker::setRecordField( 625, "recordofficetype" );
		RecordMaker::setRecordField( 625, "recordofficeid" );
		RecordMaker::setRecordField( 625, "date" );
		RecordMaker::setRecordField( 625, "timingindicator" );
		RecordMaker::setRecordField( 625, "studyindicator" );
		RecordMaker::setRecordField( 625, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 625, "servicetrafficind" );
		RecordMaker::setRecordField( 625, "operatoraction" );
		RecordMaker::setRecordField( 625, "servicefeaturecode" );
		RecordMaker::setRecordField( 625, "originatingnpa" );
		RecordMaker::setRecordField( 625, "originatingnumber" );
		RecordMaker::setRecordField( 625, "overseasindicator" );
		RecordMaker::setRecordField( 625, "terminatingnpa" );
		RecordMaker::setRecordField( 625, "terminatingnumber" );
		RecordMaker::setRecordField( 625, "time" );
		RecordMaker::setRecordField( 625, "elapsedtime" );
		RecordMaker::setRecordField( 625, "icincid" );
		RecordMaker::setRecordField( 625, "carrierconnectdate" );
		RecordMaker::setRecordField( 625, "carrierconnecttime" );
		RecordMaker::setRecordField( 625, "carrierelapsedtime" );
		RecordMaker::setRecordField( 625, "icinccalleventstatus" );
		RecordMaker::setRecordField( 625, "trunkgroupnumber" );
		RecordMaker::setRecordField( 625, "icincrouting" );
		RecordMaker::setRecordField( 625, "dialingpresubind" );
		RecordMaker::setRecordField( 625, "anicpnindicator" );

		RecordMaker::setRecordField( 653, "structurecode" ); 
		RecordMaker::setRecordField( 653, "calltype" ); 
		RecordMaker::setRecordField( 653, "sensortype" ); 
		RecordMaker::setRecordField( 653, "sensorid" ); 
		RecordMaker::setRecordField( 653, "recordofficetype" );
		RecordMaker::setRecordField( 653, "recordofficeid" );
		RecordMaker::setRecordField( 653, "date" );
		RecordMaker::setRecordField( 653, "timingindicator" );
		RecordMaker::setRecordField( 653, "studyindicator" );
		RecordMaker::setRecordField( 653, "calledpartyanswerindicator" );
		RecordMaker::setRecordField( 653, "servicetrafficind" );
		RecordMaker::setRecordField( 653, "operatoraction" );
		RecordMaker::setRecordField( 653, "servicefeaturecode" );
		RecordMaker::setRecordField( 653, "overseasindicator" );
		RecordMaker::setRecordField( 653, "terminatingnpa" );
		RecordMaker::setRecordField( 653, "terminatingnumber" );
		RecordMaker::setRecordField( 653, "time" );
		RecordMaker::setRecordField( 653, "elapsedtime" );
		RecordMaker::setRecordField( 653, "icincid" );
		RecordMaker::setRecordField( 653, "carrierconnectdate" );
		RecordMaker::setRecordField( 653, "carrierconnecttime" );
		RecordMaker::setRecordField( 653, "carrierelapsedtime" );
		RecordMaker::setRecordField( 653, "icinccalleventstatus" );
		RecordMaker::setRecordField( 653, "trunkgroupnumber" );
		RecordMaker::setRecordField( 653, "icincrouting" );

		RecordMaker::setRecordField( 1030, "structurecode" ); 
		RecordMaker::setRecordField( 1030, "calltype" ); 
		RecordMaker::setRecordField( 1030, "sensortype" ); 
		RecordMaker::setRecordField( 1030, "sensorid" ); 
		RecordMaker::setRecordField( 1030, "recordofficetype" );
		RecordMaker::setRecordField( 1030, "recordofficeid" );
		RecordMaker::setRecordField( 1030, "date" );
		RecordMaker::setRecordField( 1030, "classfeaturecode" );
		RecordMaker::setRecordField( 1030, "originatingnpa" );
		RecordMaker::setRecordField( 1030, "originatingnumber" );
		RecordMaker::setRecordField( 1030, "overseasindicator" );
		RecordMaker::setRecordField( 1030, "terminatingnpa" );
		RecordMaker::setRecordField( 1030, "terminatingnumber" );
		RecordMaker::setRecordField( 1030, "time" );
		RecordMaker::setRecordField( 1030, "elapsedtime" );
		RecordMaker::setRecordField( 1030, "classfunctions" );
		RecordMaker::setRecordField( 1030, "classfeaturestatus" );
		RecordMaker::setRecordField( 1030, "screenlistsizescf" );
		RecordMaker::setRecordField( 1030, "screenlistsizescr" );
		RecordMaker::setRecordField( 1030, "screenlistsizedrcw" );

		RecordMaker::setRecordField( 9000, "structurecode" ); 
		RecordMaker::setRecordField( 9000, "calltype" ); 
		RecordMaker::setRecordField( 9000, "sensortype" ); 
		RecordMaker::setRecordField( 9000, "sensorid" ); 
		RecordMaker::setRecordField( 9000, "recordofficetype" );
		RecordMaker::setRecordField( 9000, "recordofficeid" );
		RecordMaker::setRecordField( 9000, "timebefore" );
		RecordMaker::setRecordField( 9000, "timeafter" );
		RecordMaker::setRecordField( 9000, "datebefore" );
		RecordMaker::setRecordField( 9000, "dateafter" );

		RecordMaker::setRecordField( 9013, "structurecode" ); 
		RecordMaker::setRecordField( 9013, "calltype" ); 
		RecordMaker::setRecordField( 9013, "sensortype" ); 
		RecordMaker::setRecordField( 9013, "sensorid" ); 
		RecordMaker::setRecordField( 9013, "recordofficetype" );
		RecordMaker::setRecordField( 9013, "recordofficeid" );
		RecordMaker::setRecordField( 9013, "date" );
		RecordMaker::setRecordField( 9013, "time" );
		RecordMaker::setRecordField( 9013, "softwareid" );
		RecordMaker::setRecordField( 9013, "traceraudittype" );
		RecordMaker::setRecordField( 9013, "filesequenceno" );

		RecordMaker::setRecordField( 9014, "structurecode" ); 
		RecordMaker::setRecordField( 9014, "calltype" ); 
		RecordMaker::setRecordField( 9014, "sensortype" ); 
		RecordMaker::setRecordField( 9014, "sensorid" ); 
		RecordMaker::setRecordField( 9014, "recordofficetype" );
		RecordMaker::setRecordField( 9014, "recordofficeid" );
		RecordMaker::setRecordField( 9014, "date" );
		RecordMaker::setRecordField( 9014, "time" );
		RecordMaker::setRecordField( 9014, "softwareid" );
		RecordMaker::setRecordField( 9014, "traceraudittype" );
		RecordMaker::setRecordField( 9014, "filesequenceno" );
		RecordMaker::setRecordField( 9014, "recordcount" );
		RecordMaker::setRecordField( 9014, "blockcount" );

		RecordMaker::setRecordField( 9102, "structurecode" ); 
		RecordMaker::setRecordField( 9102, "calltype" ); 
		RecordMaker::setRecordField( 9102, "sensortype" ); 
		RecordMaker::setRecordField( 9102, "sensorid" ); 
		RecordMaker::setRecordField( 9102, "recordofficetype" );
		RecordMaker::setRecordField( 9102, "recordofficeid" );
		RecordMaker::setRecordField( 9102, "date" );
		RecordMaker::setRecordField( 9102, "time" );
		RecordMaker::setRecordField( 9102, "traceraudittype" );
		RecordMaker::setRecordField( 9102, "calls" );
		RecordMaker::setRecordField( 9102, "amacalls" );
		RecordMaker::setRecordField( 9102, "lostcalldata" );
		RecordMaker::setRecordField( 9102, "amalostcalldata" );
		RecordMaker::setRecordField( 9102, "abortedbafrecords" );
		RecordMaker::setRecordField( 9102, "bafrecords" );
		RecordMaker::setRecordField( 9102, "flaggedbafrecords" );
		RecordMaker::setRecordField( 9102, "timingerrorbafrecords" );
		RecordMaker::setRecordField( 9102, "lostbafrecords" );
		RecordMaker::setRecordField( 9102, "originatingcalls" );
		RecordMaker::setRecordField( 9102, "terminatingcalls" );
		RecordMaker::setRecordField( 9102, "outgoingcalls" );
	}
}  // namespace bafprp