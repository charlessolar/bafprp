#ifndef BAFSTRC_INCLUDED
#define BAFSTRC_INCLUDED

/**INC+***********************************************************************/
/* Header:    bafstrc.h                                                      */
/*                                                                           */
/* Purpose:   Structure defintions for bafview.                              */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001, 2002, 2005                    */
/*                                                                           */
/* $Revision::   1.3                $ $Modtime::   28 Jun 2005 12:30:26   $  */
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

#endif
