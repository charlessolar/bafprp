#ifndef BAFDEF_INCLUDED
#define BAFDEF_INCLUDED

/**INC+***********************************************************************/
/* Header:    bafdef.h                                                       */
/*                                                                           */
/* Purpose:   Header file for bafview definitions.                           */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2005                         */
/*                                                                           */
/* $Revision::   1.29               $ $Modtime::   03 Nov 2005 10:15:38   $  */
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
/* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.              */
/*                                                                           */
/**INC-***********************************************************************/

/*****************************************************************************/
/* Current version.                                                          */
/*****************************************************************************/
#define BAFVIEW_VERSION                 "4.0"

/*****************************************************************************/
/* Start of current decade.                                                  */
/*****************************************************************************/
#define BAF_START_OF_CURRENT_DECADE     2000

#define BAF_DECODE_UNKNOWN              (NBB_LONG)0xFFFFFFFF

/*****************************************************************************/
/* GROUP BAF_STRUCTURES                                                      */
/*                                                                           */
/* Note that these values are indexes into an array - so can't be            */
/* arbitrarily reordered!                                                    */
/*****************************************************************************/
#define BAF_DECODE_STRUCT_0001          (NBB_LONG)0
#define BAF_DECODE_STRUCT_0020          (NBB_LONG)1
#define BAF_DECODE_STRUCT_0028          (NBB_LONG)2
#define BAF_DECODE_STRUCT_0076          (NBB_LONG)3
#define BAF_DECODE_STRUCT_0079          (NBB_LONG)4
#define BAF_DECODE_STRUCT_0096          (NBB_LONG)5
#define BAF_DECODE_STRUCT_0110          (NBB_LONG)6
#define BAF_DECODE_STRUCT_0220          (NBB_LONG)7
#define BAF_DECODE_STRUCT_0221          (NBB_LONG)8
#define BAF_DECODE_STRUCT_0360          (NBB_LONG)9
#define BAF_DECODE_STRUCT_0364          (NBB_LONG)10
#define BAF_DECODE_STRUCT_0500          (NBB_LONG)11
#define BAF_DECODE_STRUCT_0614          (NBB_LONG)12
#define BAF_DECODE_STRUCT_0625          (NBB_LONG)13
#define BAF_DECODE_STRUCT_0653          (NBB_LONG)14
#define BAF_DECODE_STRUCT_1030          (NBB_LONG)15
#define BAF_DECODE_STRUCT_9000          (NBB_LONG)16
#define BAF_DECODE_STRUCT_9013          (NBB_LONG)17
#define BAF_DECODE_STRUCT_9014          (NBB_LONG)18
#define BAF_DECODE_STRUCT_9102          (NBB_LONG)19
/*****************************************************************************/
/* END GROUP                                                                 */
/*****************************************************************************/
#define BAF_NUM_STRUCTURES              (NBB_LONG)20

/*****************************************************************************/
/* GROUP BAF_MODULES                                                         */
/*                                                                           */
/* Note that these values are indexes into an array - so can't be            */
/* arbitrarily reordered!                                                    */
/*****************************************************************************/
#define BAF_DECODE_MODULE_0000          (NBB_LONG)0
#define BAF_DECODE_MODULE_0021          (NBB_LONG)1
#define BAF_DECODE_MODULE_0022          (NBB_LONG)2
#define BAF_DECODE_MODULE_0025          (NBB_LONG)3
#define BAF_DECODE_MODULE_0027          (NBB_LONG)4
#define BAF_DECODE_MODULE_0029          (NBB_LONG)5
#define BAF_DECODE_MODULE_0030          (NBB_LONG)6
#define BAF_DECODE_MODULE_0040          (NBB_LONG)7
#define BAF_DECODE_MODULE_0049          (NBB_LONG)8
#define BAF_DECODE_MODULE_0068          (NBB_LONG)9
#define BAF_DECODE_MODULE_0070          (NBB_LONG)10
#define BAF_DECODE_MODULE_0071          (NBB_LONG)11
#define BAF_DECODE_MODULE_0074          (NBB_LONG)12
#define BAF_DECODE_MODULE_0102          (NBB_LONG)13
#define BAF_DECODE_MODULE_0103          (NBB_LONG)14
#define BAF_DECODE_MODULE_0104          (NBB_LONG)15
#define BAF_DECODE_MODULE_0109          (NBB_LONG)16
#define BAF_DECODE_MODULE_0119          (NBB_LONG)17
#define BAF_DECODE_MODULE_0164          (NBB_LONG)18
#define BAF_DECODE_MODULE_0203          (NBB_LONG)19
#define BAF_DECODE_MODULE_0204          (NBB_LONG)20
#define BAF_DECODE_MODULE_0306          (NBB_LONG)21
#define BAF_DECODE_MODULE_0307          (NBB_LONG)22
#define BAF_DECODE_MODULE_0611          (NBB_LONG)23
#define BAF_DECODE_MODULE_0719          (NBB_LONG)24
#define BAF_DECODE_MODULE_0720          (NBB_LONG)25

/*****************************************************************************/
/* END GROUP                                                                 */
/*****************************************************************************/
#define BAF_NUM_MODULES                 (NBB_LONG)26

/*****************************************************************************/
/* GROUP BAF_FIELDS                                                          */
/*                                                                           */
/* Note that these values are indexes into an array - so can't be            */
/* arbitrarily reordered!                                                    */
/*****************************************************************************/
#define BAF_F_000_STRUCTURE_TYPE        (NBB_LONG)0
#define BAF_F_001_CALL_TYPE             (NBB_LONG)1
#define BAF_F_002_SENSOR_TYPE           (NBB_LONG)2
#define BAF_F_003_SENSOR_ID             (NBB_LONG)3
#define BAF_F_004_REC_OFF_TYPE          (NBB_LONG)4
#define BAF_F_005_REC_OFF_ID            (NBB_LONG)5
#define BAF_F_006_DATE                  (NBB_LONG)6
#define BAF_F_006_CARRIER_CONNECT_DATE  (NBB_LONG)7
#define BAF_F_006_PRESENT_DATE          (NBB_LONG)8
#define BAF_F_006_ACTIVATION_DATE       (NBB_LONG)9
#define BAF_F_006_DATE_BEFORE           (NBB_LONG)10
#define BAF_F_006_DATE_AFTER            (NBB_LONG)11
#define BAF_F_007_TIMING_INDICATOR      (NBB_LONG)12
#define BAF_F_008_STUDY_INDICATOR       (NBB_LONG)13
#define BAF_F_009_CALLED_PARTY_OFF_HOOK (NBB_LONG)14
#define BAF_F_010_SERV_OBS_TRAF_SAMPLED (NBB_LONG)15
#define BAF_F_011_OPERATOR_ACTION       (NBB_LONG)16
#define BAF_F_012_SERVICE_FEATURE_CODE  (NBB_LONG)17
#define BAF_F_013_014_CALLING_NUMBER    (NBB_LONG)18
#define BAF_F_013_014_DIALED_NUMBER     (NBB_LONG)19
#define BAF_F_015_OVERSEAS_INDICATOR    (NBB_LONG)20
#define BAF_F_015_FWD_OVERSEAS_IND      (NBB_LONG)21
#define BAF_F_016_017_CALLED_NUMBER     (NBB_LONG)22
#define BAF_F_016_017_LINE_NUMBER       (NBB_LONG)23
#define BAF_F_016_017_FORWARD_TO_NUMBER (NBB_LONG)24
#define BAF_F_018_TIME                  (NBB_LONG)25
#define BAF_F_018_CARRIER_CONNECT_TIME  (NBB_LONG)26
#define BAF_F_018_PRESENT_TIME          (NBB_LONG)27
#define BAF_F_018_ACTIVATION_TIME       (NBB_LONG)28
#define BAF_F_018_TIME_BEFORE           (NBB_LONG)29
#define BAF_F_018_TIME_AFTER            (NBB_LONG)30
#define BAF_F_019_CALL_LENGTH           (NBB_LONG)31
#define BAF_F_019_ELAPSED_TIME          (NBB_LONG)32
#define BAF_F_019_CARRIER_ELAPSED_TIME  (NBB_LONG)33
#define BAF_F_028_WATS_INDICATOR        (NBB_LONG)34
#define BAF_F_029_MSG_BILLING_INDEX     (NBB_LONG)35
#define BAF_F_032_DIGITS                (NBB_LONG)36
#define BAF_F_033_DIGITS                (NBB_LONG)37
#define BAF_F_040_TRACER_AUDIT_TYPE     (NBB_LONG)38
#define BAF_F_046_RAO                   (NBB_LONG)39
#define BAF_F_055_SIGNIFICANT_DIGITS    (NBB_LONG)40
#define BAF_F_057_IC_INC_PREFIX         (NBB_LONG)41
#define BAF_F_058_IC_INC_EVENT_STATUS   (NBB_LONG)42
#define BAF_F_059_IC_INC_ROUTING_IND    (NBB_LONG)43
#define BAF_F_060_ANI_CPN_INDICATOR     (NBB_LONG)44
#define BAF_F_070_CALLED_DN_DESCRIPTION (NBB_LONG)45
#define BAF_F_076_NUMBER_IDENTITY       (NBB_LONG)46
#define BAF_F_077_SERV_LOGIC_ID         (NBB_LONG)47
#define BAF_F_078_DIGITS_ID             (NBB_LONG)48
#define BAF_F_083_TRUNK_GROUP_NUMBER    (NBB_LONG)49
#define BAF_F_085_DIALING_PRESUB_IND    (NBB_LONG)50
#define BAF_F_087_BUSINESS_ID           (NBB_LONG)51
#define BAF_F_088_MODULE_CODE           (NBB_LONG)52
#define BAF_F_089_TRANS_SET_FIELD       (NBB_LONG)53
#define BAF_F_120_GENERIC_ID            (NBB_LONG)54
#define BAF_F_126_NUMBER                (NBB_LONG)55
#define BAF_F_138_ALT_BILL_NUMBER       (NBB_LONG)56
#define BAF_F_140_AMA_SEQUENCE_NUMBER   (NBB_LONG)57
#define BAF_F_152_CONTEXT_ID            (NBB_LONG)58
#define BAF_F_165_COUNTRY_CODE          (NBB_LONG)59
#define BAF_F_197_LATA                  (NBB_LONG)60
#define BAF_F_188_CHARGEABLE_NPA        (NBB_LONG)61
#define BAF_F_189_CHARGEABLE_EPN        (NBB_LONG)62
#define BAF_F_237_GENERIC_CONTEXT_ID    (NBB_LONG)63
#define BAF_F_244_TRUNK_IDENTIFICATION  (NBB_LONG)64
#define BAF_F_272_TRUNK_GROUP_INFO      (NBB_LONG)65
#define BAF_F_273_CARRIER_INTERFACE     (NBB_LONG)66
#define BAF_F_280_COMPLETION_IND        (NBB_LONG)67
#define BAF_F_330_CLASS_FUNCTIONS       (NBB_LONG)68
#define BAF_F_331_SCREEN_LIST_FEAT_STAT (NBB_LONG)69
#define BAF_F_407_BBG                   (NBB_LONG)70
#define BAF_F_410_NETWORK_INTERWORKING  (NBB_LONG)71
#define BAF_F_411_RELEASE_CAUSE_IND     (NBB_LONG)72
#define BAF_F_412_BEARER_CAPS           (NBB_LONG)73
#define BAF_F_413_SIG_SUPP_SERV_USAGE   (NBB_LONG)74
#define BAF_F_415_CLASS_FEATURE_CODE    (NBB_LONG)75
#define BAF_F_421_CALLING_LINE_INFO     (NBB_LONG)76
#define BAF_F_423_LINE_NUMBER_TYPE      (NBB_LONG)77
#define BAF_F_488_NETWORK_IDENTIFIER    (NBB_LONG)78
#define BAF_F_610_INDICATOR_ID          (NBB_LONG)79
#define BAF_F_701_SERV_PROVIDER_ID      (NBB_LONG)80
#define BAF_F_730_PARTY_ID              (NBB_LONG)81
#define BAF_F_731_LRN                   (NBB_LONG)82
#define BAF_F_732_SERVICE_PROVIDER_ID   (NBB_LONG)83
#define BAF_F_733_LOCATION              (NBB_LONG)84
#define BAF_F_734_SUPPORTING_INFO       (NBB_LONG)85
#define BAF_F_801_NUM_TRUNK_LEGS_USED   (NBB_LONG)86
#define BAF_F_802_SCREEN_LIST_SIZE_SCFA (NBB_LONG)87
#define BAF_F_802_SCREEN_LIST_SIZE_SCR  (NBB_LONG)88
#define BAF_F_802_SCREEN_LIST_SIZE_DRCW (NBB_LONG)89
#define BAF_F_802_SCREEN_LIST_SIZE_GEN  (NBB_LONG)90
#define BAF_F_803_CALL_COUNT_INFO_DELIV (NBB_LONG)91
#define BAF_F_803_CALL_COUNT_INFO_ANON  (NBB_LONG)92
#define BAF_F_803_CALL_COUNT_NAME_ONLY  (NBB_LONG)93
#define BAF_F_803_CALL_COUNT_NUM_ONLY   (NBB_LONG)94
#define BAF_F_804_CALLS_LOST_DATA       (NBB_LONG)95
#define BAF_F_804_AMA_CALLS_LOST_DATA   (NBB_LONG)96
#define BAF_F_804_ABORTED_BAF_RECORDS   (NBB_LONG)97
#define BAF_F_804_FLAGGED_BAF_RECORDS   (NBB_LONG)98
#define BAF_F_804_BAF_RECORDS_TIME_ERR  (NBB_LONG)99
#define BAF_F_804_BAF_LOST_BLOCK_WRITE  (NBB_LONG)100
#define BAF_F_805_NUMBER_OF_CALLS       (NBB_LONG)101
#define BAF_F_805_NUMBER_OF_AMA_CALLS   (NBB_LONG)102
#define BAF_F_805_BAF_RECORDS           (NBB_LONG)103
#define BAF_F_805_NUM_ORIG_CALLS        (NBB_LONG)104
#define BAF_F_805_NUM_TERM_CALLS        (NBB_LONG)105
#define BAF_F_805_NUM_OUTGOING_CALLS    (NBB_LONG)106
#define BAF_F__C1_FILE_SEQUENCE_NO      (NBB_LONG)107
#define BAF_F__C2_FILE_BLOCKS           (NBB_LONG)108
#define BAF_F__C3_NUMBER_OF_RECORDS     (NBB_LONG)109
/*****************************************************************************/
/* END GROUP                                                                 */
/*****************************************************************************/

#define BAF_NUM_FIELDS                  (NBB_LONG)110
#define BAF_FIELD_NO_FIELD              (NBB_LONG)0xFFFFFFFF
#define BAF_MAX_FIELDS_IN_DESCRIPTOR    (NBB_LONG)50
#define BAF_MAX_VALUES_IN_ELEMENT       (NBB_LONG)30
#define BAF_MAX_ELEMENTS_IN_FIELD       (NBB_LONG)9

/*****************************************************************************/
/* GROUP BAF_FIELD_OUTPUTS                                                   */
/*****************************************************************************/
#define BAF_FIELD_OK                    (NBB_BYTE)1
#define BAF_FIELD_NOT_USED              (NBB_BYTE)2
#define BAF_FIELD_ERROR                 (NBB_BYTE)3

/*****************************************************************************/
/* END GROUP                                                                 */
/*****************************************************************************/

/*****************************************************************************/
/* Macros.                                                                   */
/*****************************************************************************/
#define BAF_DECODE_FIELD(INPUT, LENGTH, FIELD)                               \
                    baf_field_list[(FIELD)].decoder((INPUT), (LENGTH), (FIELD))

#define BAF_FIELD_NAME(FIELD)                      baf_field_list[(FIELD)].name

#define BAF_STRUCTURE_DESCRIPTION(STRUCTURE)                                 \
                                        baf_structure_descriptions[(STRUCTURE)]

#define BAF_MODULE_DESCRIPTION(MODULE) baf_module_descriptions[(MODULE)]

#define BAF_ERROR_IN_RECORD(VERBOSE)                                          \
          if (baf_verbose)                                                    \
          {                                                                   \
            printf VERBOSE;                                                   \
          }                                                                   \
          else                                                                \
          {                                                                   \
            printf("*** encountered error in record ***");                    \
          }

/*****************************************************************************/
/* Typedef for functions which decode individual fields.                     */
/*                                                                           */
/* Purpose:   Decodes a fields in a BAF record.                              */
/*                                                                           */
/* Returns:   TRUE on success, else FALSE.                                   */
/*                                                                           */
/* Params:    IN/OUT input        - start of record to continue decoding     */
/*                                  from.                                    */
/*            IN/OUT length_of_record                                        */
/*                                - Length of record remaining.              */
/*                                                                           */
/*****************************************************************************/
typedef NBB_BOOL (BAF_FIELD_DECODER)(NBB_BYTE **, NBB_LONG *, NBB_LONG);

#endif
