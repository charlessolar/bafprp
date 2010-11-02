#ifndef BAFSTRC_INCLUDED
#define BAFSTRC_INCLUDED

/**INC+***********************************************************************/
/* Header:    bafstrc.h                                                      */
/*                                                                           */
/* Purpose:   Structure defintions for bafview.                              */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: bafstrc.h 1044 2008-09-20 03:52:52Z vpgbuild                     $  */
/* $URL:: http://enfieldsvn/repos/metaswitch/trunk/tools/code/tools/bafvi#$  */
/*                                                                           */
/* This program is provided by MetaSwitch at no charge on an "as is" basis   */
/* and is not part of Licensed Software as defined in our customer           */
/* agreements. It is provided without warranty of any kind and any use of    */
/* the software is at your own risk. MetaSwitch and its suppliers disclaim   */
/* all other warranties and conditions, either express or implied,           */
/* including, but not limited to, implied warranties and conditions of       */
/* merchantability, fitness for a particular purpose, title and              */
/* non-infringement. In no event shall MetaSwitch or its suppliers be liable */
/* for any special, incidental, indirect, or consequential damages arising   */
/* out of the use of or inability to use this program.                       */
/*                                                                           */
/* You may install and use this program for internal use only, but you may   */
/* not distribute it. If you do not agree with these terms and conditions    */
/* you should not use the program.                                           */
/*                                                                           */
/* The program is protected by copyright laws and international copyright    */
/* treaties, as well as other intellectual property laws and treaties. All   */
/* rights not expressly granted herein are reserved.                         */
/*                                                                           */
/**INC-***********************************************************************/

/*****************************************************************************/
/* Information about a value for a field.  An array of these defines how to  */
/* describe a field.                                                         */
/*****************************************************************************/
typedef struct baf_value
{
  /***************************************************************************/
  /* The minimum value.                                                      */
  /***************************************************************************/
  NBB_UINT min_value;

  /***************************************************************************/
  /* The maximum value.  This may be zero if only one value if valid for     */
  /* this descriptrion.  Otherwise it must be greater than the previous      */
  /* min_value.                                                              */
  /***************************************************************************/
  NBB_UINT max_value;

  /***************************************************************************/
  /* Name of the value for display purposes.                                 */
  /***************************************************************************/
  NBB_CHAR name[64];

} BAF_VALUE;

/*****************************************************************************/
/* Information about how to display an element in a field.                   */
/*****************************************************************************/
typedef struct baf_display
{
  /***************************************************************************/
  /* The first character of this element in the current field.               */
  /***************************************************************************/
  NBB_INT min_char;

  /***************************************************************************/
  /* The last character of this element in the current field.                */
  /***************************************************************************/
  NBB_INT max_char;

  /***************************************************************************/
  /* The number of valid elements in the below array.  If this is zero, the  */
  /* element is output as a number with the name above.                      */
  /***************************************************************************/
  NBB_INT num_values;

  /***************************************************************************/
  /* The possible values this element can take.                              */
  /***************************************************************************/
  BAF_VALUE values[BAF_MAX_VALUES_IN_ELEMENT];

  /***************************************************************************/
  /* Name of the value for display purposes.                                 */
  /***************************************************************************/
  NBB_CHAR name[64];

} BAF_DISPLAY;

/**STRUCT-********************************************************************/

/*****************************************************************************/
/* Information about an individual BAF field.                                */
/*****************************************************************************/
typedef struct baf_field
{
  /***************************************************************************/
  /* Function to be used to decode the field.                                */
  /***************************************************************************/
  BAF_FIELD_DECODER *decoder;

  /***************************************************************************/
  /* Name of the field for display purposes.                                 */
  /***************************************************************************/
  NBB_CHAR name[64];

  /***************************************************************************/
  /* Number of characters in the field.  If zero, no extra checking is done  */
  /* on the field, and the decoder is used directly to output the field.     */
  /***************************************************************************/
  NBB_INT num_chars;

  /***************************************************************************/
  /* Number of display elements for this field.                              */
  /***************************************************************************/
  NBB_INT num_displays;

  /***************************************************************************/
  /* Pointer to display array for the field.                                 */
  /***************************************************************************/
  BAF_DISPLAY displays[BAF_MAX_ELEMENTS_IN_FIELD];

} BAF_FIELD;

/*****************************************************************************/
/* Information about a BAF structure or module.                              */
/*****************************************************************************/
typedef struct baf_descriptor
{
  /***************************************************************************/
  /* Each is one of BAF_FIELDS; ending with BAF_FIELD_NO_FIELD.              */
  /***************************************************************************/
  NBB_LONG field[BAF_MAX_FIELDS_IN_DESCRIPTOR];

} BAF_DESCRIPTOR;

/*****************************************************************************/
/* Information about a BAF structure.                                        */
/*****************************************************************************/
typedef struct baf_structure
{
  /***************************************************************************/
  /* Structure code.                                                         */
  /***************************************************************************/
  NBB_UINT structure_code;

  /***************************************************************************/
  /* Descriptor                                                              */
  /***************************************************************************/
  BAF_DESCRIPTOR descriptor;

} BAF_STRUCTURE;

/*****************************************************************************/
/* Information about a BAF module.                                           */
/*****************************************************************************/
typedef struct baf_module
{
  /***************************************************************************/
  /* Module code.                                                            */
  /***************************************************************************/
  NBB_UINT module_code;

  /***************************************************************************/
  /* Descriptor.                                                             */
  /***************************************************************************/
  BAF_DESCRIPTOR descriptor;

} BAF_MODULE;

/*****************************************************************************/
/* This structure keeps decoded values of BAF fields that are useful for     */
/* traffic statistics when running in stats mode (baf_stats = TRUE).         */
/* When the field information is not present in the BAF record, a single     */
/* hyphen will be printed instead.                                           */
/*****************************************************************************/
typedef struct baf_stats_data
{
  /***************************************************************************/
  /* Structure type.                                                         */
  /***************************************************************************/
  NBB_LONG structure_type;

  /***************************************************************************/
  /* Module code.                                                            */
  /***************************************************************************/
  NBB_LONG module_code;

  /***************************************************************************/
  /* Carrier Connected Date (null terminated): yyyy/mm/dd                    */
  /***************************************************************************/
  NBB_CHAR call_date[11];

  /***************************************************************************/
  /* Carrier Connected time (null terminated): hh:mm:ss.d                    */
  /***************************************************************************/
  NBB_CHAR call_time[11];

  /***************************************************************************/
  /* Carrier Connected time (null terminated): mm:ss.d                       */
  /***************************************************************************/
  NBB_CHAR call_length[11];

  /***************************************************************************/
  /* Carrier elapsed time (null terminated): mm:ss.d                         */
  /***************************************************************************/
  NBB_CHAR call_elapsed_time[11];

  /***************************************************************************/
  /* Carrier ID (null terminated).                                           */
  /***************************************************************************/
  NBB_CHAR carrier_id[5];

  /***************************************************************************/
  /* Incoming trunk ID (null terminated).                                    */
  /***************************************************************************/
  NBB_CHAR incoming_trunk_id[5];

  /***************************************************************************/
  /* Outgoing trunk ID (null terminated).                                    */
  /***************************************************************************/
  NBB_CHAR outgoing_trunk_id[5];

} BAF_STATS_DATA;

#endif
