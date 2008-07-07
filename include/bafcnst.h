#ifndef BAFCNST_INCLUDED
#define BAFCNST_INCLUDED

/**INC+***********************************************************************/
/* Header:    bafcnst.h                                                      */
/*                                                                           */
/* Purpose:   Constants used by bafview                                      */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2005                         */
/*                                                                           */
/* $Revision::   1.27               $ $Modtime::   01 Nov 2005 11:54:12   $  */
/*                                                                           */
/* This program is free software; you can redistribute it and/or modify it   */
/* under the terms of the GNU General Public License as published by the     */
/* Free Software Foundation; either version 2 of the License, or (at your    */
/* option) any later version.                                                */
/*                                                                           */
/* This program is distributed in the hope that it will be useful, but       */
/* WITHOUT ANY WARRANTY; without even the implied warranty of                */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General */
/* Public License for more details.                                          */
/*                                                                           */
/* You should have received a copy of the GNU General Public License along   */
/* with this program; if not, write to the Free Software Foundation, Inc.,   */
/* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA               */
/*                                                                           */
/**INC-***********************************************************************/

#ifndef BAFVIEW_DEFINE_VARS
extern NBB_BOOL baf_verbose;
extern NBB_BOOL baf_dump;
extern NBB_CONST BAF_FIELD baf_field_list[];
extern NBB_CONST BAF_STRUCTURE baf_structure_descriptions[];
extern NBB_CONST BAF_MODULE baf_module_descriptions[];
#else

NBB_BOOL baf_verbose = FALSE;
NBB_BOOL baf_dump = FALSE;

/*****************************************************************************/
/* List of field names and decoders.                                         */
/*****************************************************************************/
NBB_CONST BAF_FIELD baf_field_list[BAF_NUM_FIELDS] =
{
  /***************************************************************************/
  /* BAF_F_000_STRUCTURE_TYPE                                                */
  /***************************************************************************/
  {baf_decode_structure_type, "Structure type"},

  /***************************************************************************/
  /* BAF_F_001_CALL_TYPE                                                     */
  /***************************************************************************/
  {baf_decode_call_type, "Call type"},

  /***************************************************************************/
  /* BAF_F_002_SENSOR_TYPE                                                   */
  /***************************************************************************/
  {NULL, "Sensor", 4, 1,
   {{1, 3, 0, {0}, "Type"}}},

  /***************************************************************************/
  /* BAF_F_003_SENSOR_ID                                                     */
  /***************************************************************************/
  {NULL, "Sensor", 8, 2,
   {{2, 7, 0, {0}, "ID"},
    {1, 1, 3, {{0, 0, "Default"},
               {1, 1, "Previously output"},
               {2, 2, "Potentially duplicate"}}}}},

  /***************************************************************************/
  /* BAF_F_004_REC_OFF_TYPE                                                  */
  /***************************************************************************/
  {NULL, "Recording Office", 4, 1,
   {{1, 3, 0, {0}, "Type"}}},

  /***************************************************************************/
  /* BAF_F_005_REC_OFF_ID                                                    */
  /***************************************************************************/
  {NULL, "Recording Office", 8, 2,
   {{2, 7, 0, {0}, "ID"},
    {1, 1, 2, {{0, 0, "Default"},
               {1, 1, "Undergoing testing"}}}}},

  /***************************************************************************/
  /* BAF_F_006_DATE                                                          */
  /***************************************************************************/
  {baf_decode_date, "Date"},

  /***************************************************************************/
  /* BAF_F_006_CARRIER_CONNECT_DATE                                          */
  /***************************************************************************/
  {baf_decode_date, "Carrier connect date"},

  /***************************************************************************/
  /* BAF_F_006_PRESENT_DATE                                                  */
  /***************************************************************************/
  {baf_decode_date, "Present date"},

  /***************************************************************************/
  /* BAF_F_006_ACTIVATION_DATE                                               */
  /***************************************************************************/
  {baf_decode_date, "Activation date"},

  /***************************************************************************/
  /* BAF_F_006_DATE_BEFORE                                                   */
  /***************************************************************************/
  {baf_decode_date, "Date before change"},

  /***************************************************************************/
  /* BAF_F_006_DATE_AFTER                                                    */
  /***************************************************************************/
  {baf_decode_date, "Date after change"},

  /***************************************************************************/
  /* BAF_F_007_TIMING_INDICATOR                                              */
  /***************************************************************************/
  {NULL, "Timing indicator", 6, 3,
   {{1, 1, 3, {{0, 0, "Default"},
               {2, 2, "Timing guard condition"},
               {4, 4, "Unanswered call release"}}},
    {2, 2, 2, {{0, 0, "Default"},
               {1, 1, "Short called party off hook"}}},
    {3, 3, 4, {{0, 0, "Default"},
               {1, 1, "Start of long duration call"},
               {2, 2, "Continuation of long duration call"},
               {3, 3, "Service capability series: deactivation"}}}}},

  /***************************************************************************/
  /* BAF_F_008_STUDY_INDICATOR                                               */
  /***************************************************************************/
  {NULL, "Study indicator", 8, 1,
   {{6, 6, 7, {{0, 0, "Default"},
               {1, 1, "No originating number"},
               {3, 3, "No terminating number"},
               {4, 4, "No orig. and term. numbers"},
               {5, 5, "No terminating NANP station number"},
               {6, 6, "No originating NANP station number"},
               {7, 7, "No orig. and term. NANP station numbers"}}}}},

  /***************************************************************************/
  /* BAF_F_009_CALLED_PARTY_OFF_HOOK                                         */
  /***************************************************************************/
  {NULL, "Called party off-hook", 2, 1,
   {{1, 1, 4, {{0, 0, "Called party off-hook detected"},
               {1, 1, "Called party off-hook not detected"},
               {2, 2, "Answered attempt (OSS person / collect call)"},
               {3, 3, "Simulated called party off-hook"}}}}},

  /***************************************************************************/
  /* BAF_F_010_SERV_OBS_TRAF_SAMPLED                                         */
  /***************************************************************************/
  {NULL, "Service observed / Traffic sampled", 2, 1,
   {{1, 1, 4, {{0, 0, "Default"},
               {1, 1, "Service observed"},
               {2, 2, "Traffic sampled"},
               {3, 3, "Service observed and traffic sampled"}}}}},

  /***************************************************************************/
  /* BAF_F_011_OPERATOR_ACTION                                               */
  /***************************************************************************/
  {NULL, "Operator action", 2, 1,
   {{1, 1, 4, {{0, 0, "Automatically identified, customer dialed"},
               {1, 1, "Automatically identified, customer dialed with OSS"},
               {2, 2, "Operator identified, customer dialed"},
               {3, 3, "Operator identified, customer dialed with OSS"}}}}},

  /***************************************************************************/
  /* BAF_F_012_SERVICE_FEATURE_CODE                                          */
  /***************************************************************************/
  {baf_decode_service_feature_code, "Service feature code"},

  /***************************************************************************/
  /* BAF_F_013_014_CALLING_NUMBER                                            */
  /***************************************************************************/
  {baf_decode_calling_number, "Calling number"},

  /***************************************************************************/
  /* BAF_F_013_014_DIALED_NUMBER                                             */
  /***************************************************************************/
  {baf_decode_calling_number, "Dialed number"},

  /***************************************************************************/
  /* BAF_F_015_OVERSEAS_INDICATOR                                            */
  /***************************************************************************/
  {baf_decode_overseas_ind, "Overseas indicator", 2, 1,
   {{1, 1, 10, {{0, 0, "NPA dialed by customer"},
                {1, 1, "NPA determined by the network element"},
                {2, 2, "Non-NANP number dialed (non-international)"},
                {3, 3, "7-digits international number"},
                {4, 4, "8-digits international number"},
                {5, 5, "9-digits international number"},
                {6, 6, "10-digits international number"},
                {7, 7, "11-digits international number"},
                {8, 8, "12-digits international number"},
                {9, 9, "Operator inward dialed-code"}}}}},

  /***************************************************************************/
  /* BAF_F_015_FWD_OVERSEAS_IND                                              */
  /***************************************************************************/
  {baf_decode_overseas_ind, "Forward To Overseas indicator", 2, 1,
   {{1, 1, 10, {{0, 0, "NPA dialed by customer"},
                {1, 1, "NPA determined by the network element"},
                {2, 2, "Non-NANP number dialed (non-international)"},
                {3, 3, "7-digits international number"},
                {4, 4, "8-digits international number"},
                {5, 5, "9-digits international number"},
                {6, 6, "10-digits international number"},
                {7, 7, "11-digits international number"},
                {8, 8, "12-digits international number"},
                {9, 9, "Operator inward dialed-code"}}}}},

  /***************************************************************************/
  /* BAF_F_016_017_CALLED_NUMBER                                             */
  /***************************************************************************/
  {baf_decode_called_number, "Called number"},

  /***************************************************************************/
  /* BAF_F_016_017_LINE_NUMBER                                               */
  /***************************************************************************/
  {baf_decode_called_number, "Line number"},

  /***************************************************************************/
  /* BAF_F_016_017_FORWARD_TO_NUMBER                                         */
  /***************************************************************************/
  {baf_decode_called_number, "Forwarding to number"},

  /***************************************************************************/
  /* BAF_F_018_TIME                                                          */
  /***************************************************************************/
  {baf_decode_time, "Time"},

  /***************************************************************************/
  /* BAF_F_018_CARRIER_CONNECT_TIME                                          */
  /***************************************************************************/
  {baf_decode_time, "Carrier connect time"},

  /***************************************************************************/
  /* BAF_F_018_PRESENT_TIME                                                  */
  /***************************************************************************/
  {baf_decode_time, "Present time"},

  /***************************************************************************/
  /* BAF_F_018_ACTIVATION_TIME                                               */
  /***************************************************************************/
  {baf_decode_time, "Activation time"},

  /***************************************************************************/
  /* BAF_F_018_TIME_BEFORE                                                   */
  /***************************************************************************/
  {baf_decode_time, "Time before change"},

  /***************************************************************************/
  /* BAF_F_018_TIME_AFTER                                                    */
  /***************************************************************************/
  {baf_decode_time, "Time after change"},

  /***************************************************************************/
  /* BAF_F_019_CALL_LENGTH                                                   */
  /***************************************************************************/
  {baf_decode_length, "Length of call"},

  /***************************************************************************/
  /* BAF_F_019_ELAPSED_TIME                                                  */
  /***************************************************************************/
  {baf_decode_length, "Elapsed time"},

  /***************************************************************************/
  /* BAF_F_019_CARRIER_ELAPSED_TIME                                          */
  /***************************************************************************/
  {baf_decode_length, "Carrier elapsed time"},

  /***************************************************************************/
  /* BAF_F_028_WATS_INDICATOR                                                */
  /***************************************************************************/
  {NULL, "WATS Indicator", 2, 1, {{1, 1}}},

  /***************************************************************************/
  /* BAF_F_029_MSG_BILLING_INDEX                                             */
  /***************************************************************************/
  {NULL, "Message Billing Index", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_032_DIGITS                                                        */
  /***************************************************************************/
  {NULL, "Digits dialed", 12, 1, {{1, 11}}},

  /***************************************************************************/
  /* BAF_F_033_DIGITS                                                        */
  /***************************************************************************/
  {NULL, "Digits dialed", 14, 1, {{1, 13}}},

  /***************************************************************************/
  /* BAF_F_040_TRACER_AUDIT_TYPE                                             */
  /***************************************************************************/
  {NULL, "Type of audit (tracer) record", 4, 1,
   {{1, 3, 3, {{7, 7, "Transfer in"},
               {8, 8, "End of recording"},
               {52, 52, "Hourly AMA audit"}}}}},

  /***************************************************************************/
  /* BAF_F_046_RAO                                                           */
  /***************************************************************************/
  {NULL, "Revenue Accounting Office (RAO)", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_055_SIGNIFICANT_DIGITS                                            */
  /***************************************************************************/
  {NULL, "Significant digits in next field", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_057_IC_INC_PREFIX                                                 */
  /***************************************************************************/
  {NULL, "IC / INC indicator", 6, 2,
   {{1, 4, 0, {0}, "CIC"},
    {5, 5, 10, {{0, 0, "FGD, IC/INC involved"},
                {1, 1, "FGD, IC/INC not involved"},
                {2, 2, "FGD, IC/INC involvement unknown"},
                {3, 3, "FGB, IC/INC involved"},
                {4, 4, "FGB, IC/INC not involved"},
                {5, 5, "FGB, IC/INC involvement unknown"},
                {7, 7, "CIC unknown, IC/INC involved"},
                {8, 8, "CIC unknown, IC/INC not involved"},
                {9, 9, "CIC unknown, IC/INC involvement unknown"}}}}},

  /***************************************************************************/
  /* BAF_F_058_IC_INC_EVENT_STATUS                                           */
  /***************************************************************************/
  {NULL, "IC/INC call event status", 4, 1, {{2, 3}}},

  /***************************************************************************/
  /* BAF_F_059_IC_INC_ROUTING_IND                                            */
  /***************************************************************************/
  {NULL, "IC / INC Routing Indicator", 2, 1,
   {{1, 1, 6, {{0, 0, "Direct"},
               {1, 1, "Tandem"},
               {2, 2, "CAP direct from EO"},
               {3, 3, "CAP direct from AP tandem"},
               {4, 4, "Tandem sig. to TSP - CAP trunks"},
               {5, 5, "Tandem from another LEC's EO"}}}}},

  /***************************************************************************/
  /* BAF_F_060_ANI_CPN_INDICATOR                                             */
  /***************************************************************************/
  {NULL, "ANI / CPN indicator", 2, 1,
   {{1, 1, 4, {{0, 0, "Neither ANI nor CPN provided"},
               {1, 1, "ANI provided"},
               {2, 2, "CPN provided"},
               {3, 3, "Both ANI and CPN provided"}}}}},

  /***************************************************************************/
  /* BAF_F_070_CALLED_DN_DESCRIPTION                                         */
  /***************************************************************************/
  {NULL, "Called directory number description", 4, 1,
   {{1, 3, 2, {{1, 1, "Called directory number marked anonymous"},
               {6, 6, "Called directory number not marked anonymous"}}}}},

  /***************************************************************************/
  /* BAF_F_076_NUMBER_IDENTITY                                               */
  /***************************************************************************/
  {NULL, "Number identity", 2, 1,
   {{1, 1, 7, {{1, 1, "Originating ANI"},
               {2, 2, "Terminating"},
               {3, 3, "Originating CPN"},
               {4, 4, "Private Originating ANI"},
               {5, 5, "Private Originating CPN"},
               {6, 6, "Redirecting Number"},
               {7, 7, "Original Called Number"}}}}},

  /***************************************************************************/
  /* BAF_F_077_SERV_LOGIC_ID                                                 */
  /***************************************************************************/
  {NULL, "Service Logic ID", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_078_DIGITS_ID                                                     */
  /***************************************************************************/
  {NULL, "Digits Identifier", 4, 1,
   {{1, 3, 10, {{1, 1, "Authorization code"},
                {2, 2, "Account code"},
                {3, 3, "Access code"},
                {4, 4, "Digits dialed"},
                {5, 5, "Outpulse number"},
                {6, 6, "International calling party identification"},
                {11, 11, "Non-international calling party"},
                {12, 12, "Incoming terminating number"},
                {300, 998, "LEC assigned"},
                {999, 999, "Unknown"}}}}},

  /***************************************************************************/
  /* BAF_F_083_TRUNK_GROUP_NUMBER                                            */
  /***************************************************************************/
  {NULL, "Trunk Group Number", 6, 2,
   {{1, 1, 7, {{1, 1, "Non-SS7 direct"},
               {2, 2, "Non-SS7 from IC to AT, non-SS7 to EO"},
               {3, 2, "SS7 direct"},
               {4, 4, "SS7 from IC to AT, SS7 to EO"},
               {5, 5, "None-SS7 from IC to AT, SS7 to EO"},
               {6, 6, "SS7 from IC to AT, non-SS7 to EO"},
               {9, 9, "Signaling type not specified"}}},
    {2, 5}}},

  /***************************************************************************/
  /* BAF_F_085_DIALING_PRESUB_IND                                            */
  /***************************************************************************/
  {NULL, "Dialing and presubscription indicator", 2, 1,
   {{1, 1, 10, {{0, 0, "Dialed digits cannot be determined"},
                {1, 1, "CAC not dialed, cust presub, no presub ind"},
                {2, 2, "CAC dialed, cust not presub, no presub ind"},
                {3, 3, "950-XXXX dialed"},
                {4, 4, "CAC not dialed, cust not presub, presub ind"},
                {5, 5, "CAC dialed, cust not presub, presub ind"},
                {6, 6, "CAC dialed, cust presub, presub ind"},
                {7, 7, "CAC dialed, cust presub, no presub ind"},
                {8, 8, "CAC not dialed, station not presub, no presub ind"},
                {9, 9, "CAC dialed unknown, station presub, presub ind"}}}}},

  /***************************************************************************/
  /* BAF_F_087_CUSTOMER_ID                                                   */
  /***************************************************************************/
  {NULL, "Customer Identification", 12, 2,
   {{1, 1, 4, {{0, 0, "Default"},
               {1, 1, "Originating customer's ID"},
               {2, 2, "Terminating customer's ID"},
               {3, 3, "Originating and terminating customer's ID"}}},
    {2, 11}}},

  /***************************************************************************/
  /* BAF_F_088_MODULE_CODE                                                   */
  /***************************************************************************/
  {NULL, "Module code", 4, 1,
   {{1, 3, 16, {{0, 0, "Final module"},
                {21, 21, "Carrier access - Originating"},
                {22, 22, "Long duration connection"},
                {25, 25, "Circuit release"},
                {27, 27, "Business customer ID"},
                {29, 29, "Alternate billing number"},
                {30, 30, "Translation settable"},
                {40, 40, "Digits"},
                {68, 68, "Called Directory Number Descriptor"},
                {164, 164, "E.164 / X.121 number"},
                {203, 203, "Service provider identifier"},
                {204, 204, "Indicator"},
                {307, 307, "Line number"},
                {611, 611, "Generic module"},
                {719, 719, "LNP core module"},
                {720, 720, "LNP module"}}}}},

  /***************************************************************************/
  /* BAF_F_089_TRANS_SET_FIELD                                               */
  /***************************************************************************/
  {NULL, "Translation settable field", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_120_GENERIC_ID                                                    */
  /***************************************************************************/
  {NULL, "Software Release ID", 6, 3,
   {{1, 2, 0, {0}, "Generic issue number"},
    {3, 4, 0, {0}, "Point issue level"},
    {5, 5, 0, {0}, "Overwrite level"}}},

  /***************************************************************************/
  /* BAF_F_126_NUMBER                                                        */
  /***************************************************************************/
  {NULL, "Number", 16, 1, {{1, 15}}},

  /***************************************************************************/
  /* BAF_F_138_ALT_BILL_NUMBER                                               */
  /***************************************************************************/
  {NULL, "Alternate Billing Number", 12, 2,
   {{1, 1, 3, {{0, 0, "Zero constant"},
               {1, 1, "SCP based"},
               {2, 2, "Switch based"}}},
    {2, 11}}},

  /***************************************************************************/
  /* BAF_F_140_AMA_SEQUENCE_NUMBER                                           */
  /***************************************************************************/
  {NULL, "AMA Sequence Number", 6, 1, {{1, 5}}},

  /***************************************************************************/
  /* BAF_F_152_CONTEXT_ID                                                    */
  /***************************************************************************/
  {NULL, "Context identifier", 4, 1,
   {{1, 3, 10, {{1, 1, "Call type code in SCP response"},
                {2, 2, "Service feature code in SCP response"},
                {3, 3, "Message billing index"},
                {4, 4, "Call type code in SCP response (limited)"},
                {5, 5, "Service feature code in SCP response (limited)"},
                {6, 6, "RAO number"},
                {7, 7, "LATA number"},
                {8, 8, "Add. orig. billing / services indicator"},
                {17, 17, "RTP OSS service identification"},
                {800, 998, "LEC assigned"}}}}},

  /***************************************************************************/
  /* BAF_F_165_COUNTRY_CODE                                                  */
  /***************************************************************************/
  {NULL, "Country code", 6, 2,
   {{1, 1, 6, {{0, 0, "E.164 number for undeterminable country code length"},
               {1, 1, "E.164 number 1-digit country code"},
               {2, 2, "E.164 number 2-digit country code"},
               {3, 3, "E.164 number 3-digit country code"},
               {4, 4, "X.121 number"},
               {9, 9, "E.164 number, cannot determine country code length"}}},
    {2, 5}}},

  /***************************************************************************/
  /* BAF_F_188_CHARGEABLE_NPA                                                */
  /***************************************************************************/
  {NULL, "Chargeable data numbering plan area", 4, 1, {{1, 1}}},

  /***************************************************************************/
  /* BAF_F_189_CHARGEABLE_EPN                                                */
  /***************************************************************************/
  {NULL, "Chargeable data central office-end point number", 8, 1, {{1, 1}}},

  /***************************************************************************/
  /* BAF_F_197_LATA                                                          */
  /***************************************************************************/
  {NULL, "Local Access Transport Area (LATA)", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_237_GENERIC_CONTEXT_ID                                            */
  /***************************************************************************/
  {NULL, "Generic context identifier", 8, 2,
   {{1, 5, 18, {{1, 1, "Continuous digits string for MDR"},
                {2, 2, "Chargeable party ID for ATM"},
                {3, 3, "Default ATM address"},
                {4, 4, "Invalid ATM address"},
                {5, 5, "ATM E.164 address - Calling Party"},
                {6, 6, "ATM E.164 address - Called Party"},
                {7, 7, "Charge number for ATM SVC"},
                {11, 11, "ATM transit carrier info."},
                {17, 17, "DMH account code digits"},
                {18, 18, "DMH billing digits"},
                {30, 30, "Fax usage"},
                {63, 63, "Calling party number"},
                {64, 64, "SDS trigger DN"},
                {65, 65, "Alt. dialing plan ind. from previous AIN trigger"},
                {66, 66, "SDS trigger DN from previous AIN trigger"},
                {500, 500, "Caller's DN and voice mail box ID"},
                {10833, 10833, "Incoming call digits"},
                {90000, 99998, "LEC assigned"}}},
    {6, 7, 0, {0}, "Significant digits"}}},

  /***************************************************************************/
  /* BAF_F_244_TRUNK_IDENTIFICATION                                          */
  /***************************************************************************/
  {NULL, "Trunk Identification", 10, 3,
   {{1, 1, 8, {{1, 1, "Direct - Incoming Different network"},
               {2, 2, "Direct - Outgoing Different network"},
               {3, 3, "Direct - Incoming Same network"},
               {4, 4, "Direct - Outgoing Same network"},
               {5, 5, "Tandem - Incoming Different network"},
               {6, 6, "Tandem - Outgoing Different network"},
               {7, 7, "Tandem - Incoming Same network"},
               {8, 8, "Tandem - Outgoing Same network"}}, "Routing Indicator"},
    {2, 5, 0, {0}, "Trunk Group Number"},
    {6, 9, 0, {0}, "Trunk Member Number"}}},

  /***************************************************************************/
  /* BAF_F_272_TRUNK_GROUP_INFO.                                             */
  /***************************************************************************/
  {NULL, "Trunk Group", 14, 3,
   {{2, 5, 0, {0}, "Trunk Group Number - Interoffice"},
    {6, 9, 0, {0}, "Trunk Member Number - Interoffice"},
    {10, 13, 0, {0}, "Trunk Member Number - Final"}}},

  /***************************************************************************/
  /* BAF_F_273_CARRIER_INTERFACE.                                            */
  /***************************************************************************/
  {NULL, "Carrier Interface", 4, 1,
   {{2, 3, 6, {{1, 1, "Feature Group D"},
               {2, 2, "Feature Group D with tandem signalling"},
               {3, 3, "Telecommunications Relay Service (TRS)"},
               {4, 4, "Type 2A"},
               {5, 5, "Type 2B"},
               {6, 6, "Type 2D"}}, "Network Interface Description"}}},
  /***************************************************************************/
  /* BAF_F_280_COMPLETION_IND                                                */
  /***************************************************************************/
  {NULL, "Completion indicator", 4, 1,
   {{1, 3, 17, {{1, 1, "Connect"},
                {2, 2, "Billing failure"},
                {3, 3, "Setup restrictions table"},
                {4, 4, "Person requested call not available"},
                {5, 5, "No circuits"},
                {6, 6, "Ringing"},
                {7, 7, "Busy"},
                {8, 8, "No answer supervision returned"},
                {9, 9, "AIN pre-final route record - completed"},
                {10, 10, "AIN pre-final route record - not completed"},
                {11, 11, "AIN SCP requested release time"},
                {12, 12, "Network failure"},
                {13, 13, "Caller aborted"},
                {14, 14, "AIN pre-final route - NEL follows"},
                {15, 15, "Call sent to treatment"},
                {16, 16, "RTP OSS redirected"},
                {60, 60, "Record closed - subsequent SDS record"}}}}},

  /***************************************************************************/
  /* BAF_F_330_CLASS_FUNCTIONS                                               */
  /***************************************************************************/
  {NULL, "CLASS functions", 4, 1,
   {{1, 3, 7, {{0, 0, "None"},
               {1, 1, "Active"},
               {2, 2, "Inactive"},
               {3, 3, "Delete"},
               {4, 4, "Create active"},
               {5, 5, "Create inactive"},
               {6, 6, "Session aborted"}}}}},

  /***************************************************************************/
  /* BAF_F_331_SCREEN_LIST_FEAT_STAT                                         */
  /***************************************************************************/
  {NULL, "Screening list feature status", 4, 1,
   {{1, 3, 8, {{0, 0, "None"},
               {1, 1, "SCF active"},
               {2, 2, "SCR active"},
               {3, 3, "SCF and SCR active"},
               {4, 4, "DRCW active"},
               {5, 5, "SCF and DRCW active"},
               {6, 6, "SCR and DRCW active"},
               {7, 7, "SCF, SCR, and DRCW active"}}}}},

  /***************************************************************************/
  /* BAF_F_407_BBG                                                           */
  /***************************************************************************/
  {NULL, "Basic business group", 4, 1, {{2, 2}}},

  /***************************************************************************/
  /* BAF_F_410_NETWORK_INTERWORKING                                          */
  /***************************************************************************/
  {NULL, "Network Interworking", 2, 1,
   {{1, 1, 7, {{0, 0, "No interworking"},
               {1, 1, "Interworking unspecified"},
               {2, 2, "Network interworking"},
               {3, 3, "Terminating access interworking for alerting"},
               {4, 4, "Terminating access interworking not for alerting"},
               {5, 5, "Originating access interworking"},
               {9, 9, "Unknown"}}}}},

  /***************************************************************************/
  /* BAF_F_411_RELEASE_CAUSE_IND.                                            */
  /***************************************************************************/
  {NULL, "Release Cause indicator", 6, 2,
   {{2, 2, 3, {{0, 0, "ITU standard"},
               {2, 2, "National"},
               {3, 3, "Network specific"}}},
    {3, 5, 0, {0}, "Cause indication"}}},

  /***************************************************************************/
  /* BAF_F_412_BEARER_CAPS.                                                  */
  /***************************************************************************/
  {NULL, "Bearer capability/Call type", 4, 2,
   {{1, 1, 3, {{1, 1, "Voice/voiceband data"},
               {2, 2, "Circuit-mode data"},
               {3, 3, "Packet-mode data"}}},
    {2, 3, 7, {{1, 1, "Speech"},
               {2, 2, "3.1 KHz audio"},
               {3, 3, "64-kbps transfer"},
               {4, 4, "64-kbps transfer rate adapted from 56-kbps"},
               {5, 5, "Digital information transfer"},
               {7, 7, "Transfer at a rate greater than 64-kbps"},
               {99, 99, "Not recorded"}}}}},

  /***************************************************************************/
  /* BAF_F_413_SIG_SUPP_SERV_USAGE.                                          */
  /***************************************************************************/
  {NULL, "Suppl. services", 16, 9,
   {{2, 2, 2, {{1, 1, "Feature not used or not recorded"},
               {2, 2, "Feature used"}}, "Calling party subaddress delivery"},
    {3, 3, 2, {{1, 1, "Feature not used or not recorded"},
               {2, 2, "Feature used"}}, "Called party subaddress delivery"},
    {4, 4, 2, {{1, 1, "Feature not used or not recorded"},
               {2, 2, "Feature used"}}, "Low layer compatibility delivery"},
    {5, 5, 2, {{1, 1, "Feature not used or not recorded"},
               {2, 2, "Feature used"}}, "High layer compatibility delivery"},
    {6, 6, 2, {{1, 1, "Feature not used or not recorded"},
               {2, 2, "Feature used"}}, "User to user info/Fast select"},
    {9, 9, 2, {{1, 1, "Feature not used or not recorded"},
               {2, 2, "Feature used"}}, "ISDN flexible calling"},
    {10, 10, 2, {{1, 1, "Feature not used or not recorded"},
                 {2, 2, "Feature used"}}, "Call waiting originating"},
    {11, 11, 2, {{1, 1, "Feature not used or not recorded"},
                 {2, 2, "Feature used"}}, "Dial call waiting"},
    {12, 12, 2, {{1, 1, "Feature not used or not recorded"},
                 {2, 2, "Feature used"}}, "Call deflection"}}},

  /***************************************************************************/
  /* BAF_F_415_CLASS_FEATURE_CODE                                            */
  /***************************************************************************/
  {baf_decode_class_feature_code, "CLASS Feature code"},

  /***************************************************************************/
  /* BAF_F_421_CALLING_LINE_INFO                                             */
  /***************************************************************************/
  {NULL, "Calling line Info", 4, 1, {{2, 3}}},

  /***************************************************************************/
  /* BAF_F_423_LINE_NUMBER_TYPE                                              */
  /***************************************************************************/
  {NULL, "Line number type", 4, 1,
   {{1, 3, 5, {{4, 4, "Incoming terminating number"},
               {5, 5, "Calling party identification"},
               {6, 6, "Automatic number identification delivered"},
               {800, 998, "LEC assigned"},
               {999, 999, "Unknown"}}}}},

  /***************************************************************************/
  /* BAF_F_488_NETWORK_IDENTIFIER.                                           */
  /***************************************************************************/
  {NULL, "Remote network ID", 8, 2,
   {{1, 1, 1, {{1, 1, "Locally Defined"}}, "Administrative Domain"},
    {2, 7, 0, {0}, "Network Number"}}},

  /***************************************************************************/
  /* BAF_F_610_INDICATOR_ID                                                  */
  /***************************************************************************/
  {NULL, "Indicator identification", 4, 1,
   {{1, 3, 2, {{1, 1, "Not final route AIN"},
               {2, 2, "Not final route called party busy / no answer"}}}}},

  /***************************************************************************/
  /* BAF_F_701_SERV_PROVIDER_ID                                              */
  /***************************************************************************/
  {NULL, "Service Provider Identification", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_730_PARTY_ID                                                      */
  /***************************************************************************/
  {NULL, "Party identifier", 4, 1,
   {{1, 3, 16, {{1, 1, "Originating party DN"},
                {2, 2, "Terminating party DN"},
                {3, 3, "Billing party DN"},
                {4, 4, "Aggregate / feature record DN"},
                {5, 5, "Detailed / feature record DN"},
                {6, 6, "Third party verification"},
                {7, 7, "Busy line verification"},
                {8, 8, "Redirecting"},
                {9, 9, "Directory assistance"},
                {10, 10, "Incoming trunk group"},
                {11, 11, "Outgoing trunk group"},
                {12, 12, "Reserved"},
                {13, 13, "OSS"},
                {20, 20, "NECA company code"},
                {21, 21, "CIC"},
                {999, 999, "Unknown"}}}}},

  /***************************************************************************/
  /* BAF_F_731_LRN                                                           */
  /***************************************************************************/
  {NULL, "LRN", 12, 1, {{2, 11}}},

  /***************************************************************************/
  /* BAF_F_732_SERVICE_PROVIDER_ID                                           */
  /***************************************************************************/
  {NULL, "Service Provider Identity", 10, 1, {{2, 9}}},

  /***************************************************************************/
  /* BAF_F_733_LOCATION                                                      */
  /***************************************************************************/
  {NULL, "Location", 16, 2,
   {{1, 3, 2, {{6, 6, "6 digit geographic unit building block"},
               {100, 100, "Signaling point code"}}},
    {4, 15}}},

  /***************************************************************************/
  /* BAF_F_734_SUPPORTING_INFO                                               */
  /***************************************************************************/
  {NULL, "Supporting Information", 8, 2,
   {{1, 1, 5, {{1, 1, "LNP database"},
               {2, 2, "Switching system data"},
               {3, 3, "Incoming signaling"},
               {4, 4, "Switch LRN"},
               {9, 9, "Unknown"}}, "LRN source"},
    {2, 3, 14, {{1, 1, "Successful query"},
                {2, 2, "No response"},
                {3, 3, "AIN continue"},
                {4, 4, "Protocol error"},
                {5, 5, "Error detected"},
                {6, 6, "Query rejected"},
                {7, 7, "Last resort routing"},
                {9, 9, "No query done"},
                {11, 11, "Successful QoR"},
                {12, 12, "QoR initiated"},
                {13, 13, "QoR received"},
                {14, 14, "PORC last resort - donor"},
                {15, 15, "PORC last resort - surrogate donor"},
                {99, 99, "Unsuccessful query, reason unknown"}}}}},

  /***************************************************************************/
  /* BAF_F_801_NUM_TRUNK_LEGS_USED                                           */
  /***************************************************************************/
  {NULL, "Number of trunk legs used", 2, 1, {{1, 1}}},

  /***************************************************************************/
  /* BAF_F_802_SCREEN_LIST_SIZE_SCFA                                         */
  /***************************************************************************/
  {NULL, "Screening list size for SCF / SCA", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_802_SCREEN_LIST_SIZE_SCR                                          */
  /***************************************************************************/
  {NULL, "Screening list size for SCR", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_802_SCREEN_LIST_SIZE_DRCW                                         */
  /***************************************************************************/
  {NULL, "Screening list size for DRCW", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_802_SCREEN_LIST_SIZE_GEN                                          */
  /***************************************************************************/
  {NULL, "Screening list size", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F_803_CALL_COUNT_INFO_DELIV                                         */
  /***************************************************************************/
  {NULL, "Call count information delivered", 6, 1, {{1, 5}}},

  /***************************************************************************/
  /* BAF_F_803_CALL_COUNT_INFO_DELIV                                         */
  /***************************************************************************/
  {NULL, "Call count information anonymous / unavailable", 6, 1, {{1, 5}}},

  /***************************************************************************/
  /* BAF_F_803_CALL_COUNT_NAME_ONLY                                          */
  /***************************************************************************/
  {NULL, "Count of name only deliveries", 6, 1, {{1, 5}}},

  /***************************************************************************/
  /* BAF_F_803_CALL_COUNT_NUM_ONLY                                           */
  /***************************************************************************/
  {NULL, "Count of number only deliveries", 6, 1, {{1, 5}}},

  /***************************************************************************/
  /* BAF_F_804_CALLS_LOST_DATA                                               */
  /***************************************************************************/
  {NULL, "Number of calls with lost data", 8, 1, {{1, 7}}},

  /***************************************************************************/
  /* BAF_F_804_AMA_CALLS_LOST_DATA                                           */
  /***************************************************************************/
  {NULL, "Number of AMA calls with lost AMA call data", 8, 1, {{1, 7}}},

  /***************************************************************************/
  /* BAF_F_804_ABORTED_BAF_RECORDS                                           */
  /***************************************************************************/
  {NULL, "Number of aborted BAF records", 8, 1, {{1, 7}}},

  /***************************************************************************/
  /* BAF_F_804_FLAGGED_BAF_RECORDS                                           */
  /***************************************************************************/
  {NULL, "Number of flagged BAF records", 8, 1, {{1, 7}}},

  /***************************************************************************/
  /* BAF_F_804_BAF_RECORDS_TIME_ERR                                          */
  /***************************************************************************/
  {NULL, "Number of BAF records with timing errors", 8, 1, {{1, 7}}},

  /***************************************************************************/
  /* BAF_F_804_BAF_LOST_BLOCK_WRITE                                          */
  /***************************************************************************/
  {NULL, "Number of BAF records lost on block writes", 8, 1, {{1, 7}}},

  /***************************************************************************/
  /* BAF_F_805_NUMBER_OF_CALLS                                               */
  /***************************************************************************/
  {NULL, "Number of calls", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_805_NUMBER_OF_AMA_CALLS                                           */
  /***************************************************************************/
  {NULL, "Number of AMA calls", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_805_BAF_RECORDS                                                   */
  /***************************************************************************/
  {NULL, "Number of BAF records", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_805_NUM_ORIG_CALLS                                                */
  /***************************************************************************/
  {NULL, "Number of originating calls", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_805_NUM_TERM_CALLS                                                */
  /***************************************************************************/
  {NULL, "Number of terminating calls", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F_805_NUM_OUTGOING_CALLS                                            */
  /***************************************************************************/
  {NULL, "Number of outgoing calls", 10, 1, {{1, 9}}},

  /***************************************************************************/
  /* BAF_F__C1_FILE_SEQUENCE_NO                                              */
  /***************************************************************************/
  {NULL, "File Sequence number", 4, 1, {{1, 3}}},

  /***************************************************************************/
  /* BAF_F__C2_FILE_BLOCKS                                                   */
  /***************************************************************************/
  {NULL, "File blocks", 6, 1, {{1, 5}}},

  /***************************************************************************/
  /* BAF_F__C3_NUMBER_OF_RECORDS                                             */
  /***************************************************************************/
  {NULL, "Number of records", 8, 1, {{1, 7}}},

};

/*****************************************************************************/
/* Definition of which fields are in which structures.                       */
/*****************************************************************************/
NBB_CONST BAF_STRUCTURE baf_structure_descriptions[BAF_NUM_STRUCTURES] =
{
  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0001                                                  */
  /***************************************************************************/
  {1,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0020                                                  */
  /***************************************************************************/
  {20,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_028_WATS_INDICATOR,
    BAF_F_029_MSG_BILLING_INDEX,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0028                                                  */
  /***************************************************************************/
  {28,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_018_TIME,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0076                                                  */
  /***************************************************************************/
  {76,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_801_NUM_TRUNK_LEGS_USED,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0079                                                  */
  /***************************************************************************/
  {79,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0096                                                  */
  /***************************************************************************/
  {96,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_ACTIVATION_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_FWD_OVERSEAS_IND,
    BAF_F_016_017_FORWARD_TO_NUMBER,
    BAF_F_018_ACTIVATION_TIME,
    BAF_F_019_ELAPSED_TIME,
    BAF_F_006_PRESENT_DATE,
    BAF_F_018_PRESENT_TIME,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0110                                                  */
  /***************************************************************************/
  {110,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_415_CLASS_FEATURE_CODE,
    BAF_F_006_DATE,
    BAF_F_018_TIME,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_803_CALL_COUNT_INFO_DELIV,
    BAF_F_803_CALL_COUNT_INFO_ANON,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0220                                                  */
  /***************************************************************************/
  {220,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_280_COMPLETION_IND,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_077_SERV_LOGIC_ID,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0221                                                  */
  /***************************************************************************/
  {221,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_280_COMPLETION_IND,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_077_SERV_LOGIC_ID,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0360                                                  */
  /***************************************************************************/
  {360,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_013_014_DIALED_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_057_IC_INC_PREFIX,
    BAF_F_006_CARRIER_CONNECT_DATE,
    BAF_F_018_CARRIER_CONNECT_TIME,
    BAF_F_019_CARRIER_ELAPSED_TIME,
    BAF_F_058_IC_INC_EVENT_STATUS,
    BAF_F_083_TRUNK_GROUP_NUMBER,
    BAF_F_059_IC_INC_ROUTING_IND,
    BAF_F_085_DIALING_PRESUB_IND,
    BAF_F_060_ANI_CPN_INDICATOR,
    BAF_F_046_RAO,
    BAF_F_197_LATA,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0364                                                  */
  /***************************************************************************/
  {364,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_013_014_DIALED_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_046_RAO,
    BAF_F_197_LATA,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0500                                                  */
  /***************************************************************************/
  {500,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0614                                                  */
  /***************************************************************************/
  {614,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_FWD_OVERSEAS_IND,
    BAF_F_016_017_FORWARD_TO_NUMBER,
    BAF_F_018_ACTIVATION_TIME,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0625                                                  */
  /***************************************************************************/
  {625,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_057_IC_INC_PREFIX,
    BAF_F_006_CARRIER_CONNECT_DATE,
    BAF_F_018_CARRIER_CONNECT_TIME,
    BAF_F_019_CARRIER_ELAPSED_TIME,
    BAF_F_058_IC_INC_EVENT_STATUS,
    BAF_F_083_TRUNK_GROUP_NUMBER,
    BAF_F_059_IC_INC_ROUTING_IND,
    BAF_F_085_DIALING_PRESUB_IND,
    BAF_F_060_ANI_CPN_INDICATOR,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_0653                                                  */
  /***************************************************************************/
  {653,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_007_TIMING_INDICATOR,
    BAF_F_008_STUDY_INDICATOR,
    BAF_F_009_CALLED_PARTY_OFF_HOOK,
    BAF_F_010_SERV_OBS_TRAF_SAMPLED,
    BAF_F_011_OPERATOR_ACTION,
    BAF_F_012_SERVICE_FEATURE_CODE,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_057_IC_INC_PREFIX,
    BAF_F_006_CARRIER_CONNECT_DATE,
    BAF_F_018_CARRIER_CONNECT_TIME,
    BAF_F_019_CARRIER_ELAPSED_TIME,
    BAF_F_058_IC_INC_EVENT_STATUS,
    BAF_F_083_TRUNK_GROUP_NUMBER,
    BAF_F_059_IC_INC_ROUTING_IND,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_1030                                                  */
  /***************************************************************************/
  {1030,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_415_CLASS_FEATURE_CODE,
    BAF_F_013_014_CALLING_NUMBER,
    BAF_F_015_OVERSEAS_INDICATOR,
    BAF_F_016_017_CALLED_NUMBER,
    BAF_F_018_TIME,
    BAF_F_019_CALL_LENGTH,
    BAF_F_330_CLASS_FUNCTIONS,
    BAF_F_331_SCREEN_LIST_FEAT_STAT,
    BAF_F_802_SCREEN_LIST_SIZE_SCFA,
    BAF_F_802_SCREEN_LIST_SIZE_SCR,
    BAF_F_802_SCREEN_LIST_SIZE_DRCW,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_9000                                                  */
  /***************************************************************************/
  {9000,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_018_TIME_BEFORE,
    BAF_F_018_TIME_AFTER,
    BAF_F_006_DATE_BEFORE,
    BAF_F_006_DATE_AFTER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_9013                                                  */
  /***************************************************************************/
  {9013,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_018_TIME,
    BAF_F_120_GENERIC_ID,
    BAF_F_040_TRACER_AUDIT_TYPE,
    BAF_F__C1_FILE_SEQUENCE_NO,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_9014                                                  */
  /***************************************************************************/
  {9014,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_018_TIME,
    BAF_F_120_GENERIC_ID,
    BAF_F_040_TRACER_AUDIT_TYPE,
    BAF_F__C1_FILE_SEQUENCE_NO,
    BAF_F__C2_FILE_BLOCKS,
    BAF_F__C3_NUMBER_OF_RECORDS,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_STRUCT_9102                                                  */
  /***************************************************************************/
  {9102,
   {BAF_F_000_STRUCTURE_TYPE,
    BAF_F_001_CALL_TYPE,
    BAF_F_002_SENSOR_TYPE,
    BAF_F_003_SENSOR_ID,
    BAF_F_004_REC_OFF_TYPE,
    BAF_F_005_REC_OFF_ID,
    BAF_F_006_DATE,
    BAF_F_018_TIME,
    BAF_F_040_TRACER_AUDIT_TYPE,
    BAF_F_805_NUMBER_OF_CALLS,
    BAF_F_805_NUMBER_OF_AMA_CALLS,
    BAF_F_804_CALLS_LOST_DATA,
    BAF_F_804_AMA_CALLS_LOST_DATA,
    BAF_F_804_ABORTED_BAF_RECORDS,
    BAF_F_805_BAF_RECORDS,
    BAF_F_804_FLAGGED_BAF_RECORDS,
    BAF_F_804_BAF_RECORDS_TIME_ERR,
    BAF_F_804_BAF_LOST_BLOCK_WRITE,
    BAF_F_805_NUM_ORIG_CALLS,
    BAF_F_805_NUM_TERM_CALLS,
    BAF_F_805_NUM_OUTGOING_CALLS,
    BAF_FIELD_NO_FIELD}},

};

/*****************************************************************************/
/* Definition of which fields are in which modules.                          */
/*****************************************************************************/
NBB_CONST BAF_MODULE baf_module_descriptions[BAF_NUM_MODULES] =
{
  /***************************************************************************/
  /* BAF_DECODE_MODULE_0000                                                  */
  /***************************************************************************/
  {0,
   {BAF_F_088_MODULE_CODE,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0021                                                  */
  /***************************************************************************/
  {21,
   {BAF_F_088_MODULE_CODE,
    BAF_F_057_IC_INC_PREFIX,
    BAF_F_006_CARRIER_CONNECT_DATE,
    BAF_F_018_CARRIER_CONNECT_TIME,
    BAF_F_019_CARRIER_ELAPSED_TIME,
    BAF_F_058_IC_INC_EVENT_STATUS,
    BAF_F_083_TRUNK_GROUP_NUMBER,
    BAF_F_059_IC_INC_ROUTING_IND,
    BAF_F_085_DIALING_PRESUB_IND,
    BAF_F_060_ANI_CPN_INDICATOR,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0022                                                  */
  /***************************************************************************/
  {22,
   {BAF_F_088_MODULE_CODE,
    BAF_F_006_PRESENT_DATE,
    BAF_F_018_PRESENT_TIME,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0025                                                  */
  /***************************************************************************/
  {25,
   {BAF_F_088_MODULE_CODE,
    BAF_F_006_DATE,
    BAF_F_018_TIME,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0027                                                  */
  /***************************************************************************/
  {27,
   {BAF_F_088_MODULE_CODE,
    BAF_F_087_BUSINESS_ID,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0029                                                  */
  /***************************************************************************/
  {29,
   {BAF_F_088_MODULE_CODE,
    BAF_F_138_ALT_BILL_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0030                                                  */
  /***************************************************************************/
  {30,
   {BAF_F_088_MODULE_CODE,
    BAF_F_152_CONTEXT_ID,
    BAF_F_089_TRANS_SET_FIELD,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0040                                                  */
  /***************************************************************************/
  {40,
   {BAF_F_088_MODULE_CODE,
    BAF_F_078_DIGITS_ID,
    BAF_F_055_SIGNIFICANT_DIGITS,
    BAF_F_032_DIGITS,
    BAF_F_033_DIGITS,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0049                                                  */
  /***************************************************************************/
  {49,
   {BAF_F_088_MODULE_CODE,
    BAF_F_803_CALL_COUNT_NAME_ONLY,
    BAF_F_803_CALL_COUNT_NUM_ONLY,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0068                                                  */
  /***************************************************************************/
  {68,
   {BAF_F_088_MODULE_CODE,
    BAF_F_070_CALLED_DN_DESCRIPTION,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0070                                                  */
  /***************************************************************************/
  {70,
   {BAF_F_088_MODULE_CODE,
    BAF_F_412_BEARER_CAPS,
    BAF_F_410_NETWORK_INTERWORKING,
    BAF_F_413_SIG_SUPP_SERV_USAGE,
    BAF_F_411_RELEASE_CAUSE_IND,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0071                                                  */
  /***************************************************************************/
  {71,
   {BAF_F_088_MODULE_CODE,
    BAF_F_412_BEARER_CAPS,
    BAF_F_410_NETWORK_INTERWORKING,
    BAF_F_411_RELEASE_CAUSE_IND,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0074                                                  */
  /***************************************************************************/
  {74,
   {BAF_F_088_MODULE_CODE,
    BAF_F_407_BBG,
    BAF_F_188_CHARGEABLE_NPA,
    BAF_F_189_CHARGEABLE_EPN,
    BAF_F_083_TRUNK_GROUP_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0102                                                  */
  /***************************************************************************/
  {102,
   {BAF_F_088_MODULE_CODE,
    BAF_F_055_SIGNIFICANT_DIGITS,
    BAF_F_126_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0103                                                  */
  /***************************************************************************/
  {103,
   {BAF_F_088_MODULE_CODE,
    BAF_F_055_SIGNIFICANT_DIGITS,
    BAF_F_126_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0104                                                  */
  /***************************************************************************/
  {104,
   {BAF_F_088_MODULE_CODE,
    BAF_F_244_TRUNK_IDENTIFICATION,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0109                                                  */
  /***************************************************************************/
  {109,
   {BAF_F_088_MODULE_CODE,
    BAF_F_415_CLASS_FEATURE_CODE,
    BAF_F_330_CLASS_FUNCTIONS,
    BAF_F_802_SCREEN_LIST_SIZE_GEN,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0119                                                  */
  /***************************************************************************/
  {119,
   {BAF_F_088_MODULE_CODE,
    BAF_F_272_TRUNK_GROUP_INFO,
    BAF_F_273_CARRIER_INTERFACE,
    BAF_F_488_NETWORK_IDENTIFIER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0164                                                  */
  /***************************************************************************/
  {164,
   {BAF_F_088_MODULE_CODE,
    BAF_F_076_NUMBER_IDENTITY,
    BAF_F_165_COUNTRY_CODE,
    BAF_F_055_SIGNIFICANT_DIGITS,
    BAF_F_126_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0203                                                  */
  /***************************************************************************/
  {203,
   {BAF_F_088_MODULE_CODE,
    BAF_F_152_CONTEXT_ID,
    BAF_F_701_SERV_PROVIDER_ID,
    BAF_F_140_AMA_SEQUENCE_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0204                                                  */
  /***************************************************************************/
  {204,
   {BAF_F_088_MODULE_CODE,
    BAF_F_610_INDICATOR_ID,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0306                                                  */
  /***************************************************************************/
  {306,
   {BAF_F_088_MODULE_CODE,
    BAF_F_421_CALLING_LINE_INFO,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0307                                                  */
  /***************************************************************************/
  {307,
   {BAF_F_088_MODULE_CODE,
    BAF_F_423_LINE_NUMBER_TYPE,
    BAF_F_016_017_LINE_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0611                                                  */
  /***************************************************************************/
  {611,
   {BAF_F_088_MODULE_CODE,
    BAF_F_237_GENERIC_CONTEXT_ID,
    BAF_F_126_NUMBER,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0719                                                  */
  /***************************************************************************/
  {719,
   {BAF_F_088_MODULE_CODE,
    BAF_F_730_PARTY_ID,
    BAF_F_731_LRN,
    BAF_F_734_SUPPORTING_INFO,
    BAF_FIELD_NO_FIELD}},

  /***************************************************************************/
  /* BAF_DECODE_MODULE_0720                                                  */
  /***************************************************************************/
  {720,
   {BAF_F_088_MODULE_CODE,
    BAF_F_730_PARTY_ID,
    BAF_F_731_LRN,
    BAF_F_732_SERVICE_PROVIDER_ID,
    BAF_F_733_LOCATION,
    BAF_F_734_SUPPORTING_INFO,
    BAF_FIELD_NO_FIELD}},

};
#endif

#endif
