#ifndef BAFFUNC_INCLUDED
#define BAFFUNC_INCLUDED

/**INC+***********************************************************************/
/* Header:    baffunc.h                                                      */
/*                                                                           */
/* Purpose:   Header file containing function prototypes for bafview.        */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: baffunc.h 12654 2009-09-17 10:16:54Z pf                          $  */
/* $URL:: http://enfieldsvn/repos/metaswitch/trunk/tools/code/tools/bafvi#$  */
/*                                                                           */
/* This program is provided by MetaSwitch at no charge on an "as is" basis   */
/* and is not part of Licensed Software as defined in our customer           */
/* agreements.  It is provided without warranty of any kind and any use of   */
/* the software is at your own risk.  MetaSwitch and its suppliers disclaim  */
/* all other warranties and conditions, either express or implied,           */
/* including, but not limited to, implied warranties and conditions of       */
/* merchantability, fitness for a particular purpose, title and              */
/* non-infringement.  In no event shall MetaSwitch or its suppliers be       */
/* liable for any special, incidental, indirect, or consequential damages    */
/* arising out of the use of or inability to use this program.               */
/*                                                                           */
/* You may install and use this program for internal use only, but you may   */
/* not distribute it.  If you do not agree with these terms and conditions   */
/* you should not use the program.                                           */
/*                                                                           */
/* The program is protected by copyright laws and international copyright    */
/* treaties, as well as other intellectual property laws and treaties.  All  */
/* rights not expressly granted herein are reserved.                         */
/*                                                                           */
/**INC-***********************************************************************/

/*****************************************************************************/
/* bafdecod.c                                                                */
/*****************************************************************************/
NBB_VOID baf_decode_file(NBB_CONST NBB_CHAR *);
NBB_VOID baf_decode_record(NBB_BYTE *,
                           NBB_LONG,
                           NBB_LONG,
                           NBB_BOOL);
NBB_VOID baf_decode_dns_header(NBB_BYTE *, NBB_LONG *, NBB_BOOL);
NBB_VOID baf_print_dns_date(NBB_ULONG);
NBB_BOOL baf_decode_all_fields(NBB_BYTE **,
                               NBB_LONG *,
                               NBB_CONST BAF_DESCRIPTOR *);
NBB_BOOL baf_decode_field(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_VOID baf_get_chars(NBB_BYTE *, NBB_INT, NBB_INT, NBB_ULONG *);
NBB_BOOL baf_decode_appended_modules(NBB_BYTE **, NBB_LONG *);
NBB_VOID baf_write_num_records(NBB_BYTE *, NBB_ULONG);
NBB_VOID baf_write_file_sequence(NBB_BYTE *, NBB_ULONG);

/*****************************************************************************/
/* bafdisp.c                                                                 */
/*****************************************************************************/
NBB_VOID baf_display_service_feature_code(NBB_UINT);
NBB_VOID baf_display_class_feature_code(NBB_UINT);

/*****************************************************************************/
/* baffield.c                                                                */
/*****************************************************************************/
NBB_BOOL baf_decode_structure_type(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_call_type(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_class_feature_code(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_date(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_time(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_generic_id(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_baf_lost_block_write(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_calling_number(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_overseas_ind(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_called_number(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_length(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_class_functions(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_scr_list_feat_stat(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_scr_list_size(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_digits_id(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_business_id(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_service_feature_code(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_ic_inc_prefix(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_trunk_group_number(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_dial_presub_ind(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_module_code(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_country_code(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_BOOL baf_decode_significant_digits(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_VOID baf_decode_number(NBB_BYTE *, NBB_INT, NBB_INT);
NBB_VOID baf_decode_stat_number(NBB_BYTE *, NBB_INT, NBB_INT, NBB_CHAR *);
NBB_VOID baf_decode_stat_field(NBB_BYTE **, NBB_CONST BAF_FIELD *, NBB_LONG);
NBB_BYTE baf_decode_byte(NBB_BYTE *, NBB_BYTE, NBB_BYTE);
NBB_USHORT baf_decode_2_bytes(NBB_BYTE *, NBB_BYTE, NBB_BYTE);
NBB_ULONG baf_decode_3_bytes(NBB_BYTE *, NBB_BYTE, NBB_BYTE);
NBB_ULONG baf_decode_4_bytes(NBB_BYTE *, NBB_BYTE, NBB_BYTE);
NBB_BOOL baf_get_structure_type(NBB_BYTE *,
                                NBB_LONG *,
                                NBB_LONG);
NBB_BYTE baf_get_date(NBB_BYTE *,
                      NBB_LONG *,
                      NBB_CHAR *,
                      NBB_LONG *,
                      NBB_LONG);
NBB_BOOL baf_get_calling_number(NBB_BYTE *,
                                NBB_CHAR *,
                                NBB_LONG);
NBB_BOOL baf_get_overseas_ind(NBB_BYTE *, NBB_CHAR *, NBB_LONG);
NBB_BOOL baf_get_called_number(NBB_BYTE *,
                               NBB_CHAR *,
                               NBB_LONG);
NBB_BYTE baf_get_time(NBB_BYTE *, NBB_CHAR *, NBB_LONG);
NBB_BYTE baf_get_length(NBB_BYTE *, NBB_CHAR *, NBB_LONG);

/*****************************************************************************/
/* bafutil.c                                                                 */
/*****************************************************************************/
NBB_LONG baf_get_decode_type(NBB_BYTE *, NBB_LONG);
NBB_VOID baf_merge_file(FILE **,
                        NBB_CHAR *,
                        NBB_BOOL,
                        NBB_ULONG *,
                        NBB_ULONG *,
                        NBB_BOOL,
                        NBB_BOOL);
NBB_BYTE baf_check_start_records(NBB_CHAR *);
NBB_VOID baf_print_record(BAF_STATS_DATA *);
NBB_VOID baf_print(NBB_CONST NBB_CHAR *, ...);
NBB_VOID baf_initialize();


#endif
