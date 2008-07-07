#ifndef BAFFUNC_INCLUDED
#define BAFFUNC_INCLUDED

/**INC+***********************************************************************/
/* Header:    baffunc.h                                                      */
/*                                                                           */
/* Purpose:   Header file containing function prototypes for bafview.        */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2005                         */
/*                                                                           */
/* $Revision::   1.14               $ $Modtime::   02 Jun 2005 16:21:50   $  */
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

/*****************************************************************************/
/* bafdecod.c                                                                */
/*****************************************************************************/
NBB_VOID baf_decode_file(NBB_CONST NBB_CHAR *);
NBB_VOID baf_decode_record(NBB_BYTE *,
                           NBB_LONG ,
                           NBB_LONG);
NBB_BOOL baf_decode_all_fields(NBB_BYTE **,
                               NBB_LONG *,
                               NBB_CONST BAF_DESCRIPTOR *);
NBB_BOOL baf_decode_field(NBB_BYTE **, NBB_LONG *, NBB_LONG);
NBB_VOID baf_get_chars(NBB_BYTE *, NBB_INT, NBB_INT, NBB_ULONG *);
NBB_BOOL baf_decode_appended_modules(NBB_BYTE **, NBB_LONG *);

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

#endif
