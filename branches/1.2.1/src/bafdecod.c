/**MOD+***********************************************************************/
/* Module:    bafdecod.c                                                     */
/*                                                                           */
/* Purpose:   Functions to decode BAF structures.                            */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2003, 2005                   */
/*                                                                           */
/* $Revision::   1.27               $ $Modtime::   15 Jul 2005 14:32:50   $  */
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
/**MOD-***********************************************************************/

#include <bafincl.h>

/**PROC+**********************************************************************/
/* Name:      baf_decode_file                                                */
/*                                                                           */
/* Purpose:   Decode a single BAF file.                                      */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN file_name - Name of file to decode.                         */
/*                                                                           */
/* Operation: Check the file whose name we've been passed exists and open    */
/*            it.  If it doesn't exist output error message and exit.        */
/*            Loop getting records from the billing file.  This is done by   */
/*            getting 4 bytes (containing the length of the record) followed */
/*            by this length - 4 to get the rest of the record.  For each    */
/*            record call the decode function.                               */
/*            If there are any bytes left over (must be less than 4, output  */
/*            these.                                                         */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_file(NBB_CONST NBB_CHAR *file_name)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  FILE *billing_file;
  NBB_LONG length_of_record;
  NBB_BYTE scratch[1024];
  NBB_LONG bytes_read;
  NBB_INT ii;

  /***************************************************************************/
  /* Check to see if we can open the file.                                   */
  /***************************************************************************/
  billing_file = OS_FOPEN(file_name, "rb");
  if (billing_file == NULL)
  {
    printf("Can't open file %s\n\n", file_name);
    goto EXIT_LABEL;
  }
  else
  {
    printf("Performing ");
    baf_verbose ? printf("verbose ") : printf("concise ");
    printf("decoding of %s\n\n", file_name);
  }

  bytes_read = OS_FREAD((NBB_BYTE *)scratch,
                        1,
                        4,
                        billing_file);
  length_of_record = (256 * scratch[0]) + scratch[1];

  while ((bytes_read == 4) && (length_of_record >= 4))
  {
    /*************************************************************************/
    /* Read in the rest of the first record.                                 */
    /*************************************************************************/
    bytes_read += OS_FREAD((NBB_BYTE *)scratch + 4,
                           1,
                           length_of_record - 4,
                           billing_file);

    /*************************************************************************/
    /* Decode the record.                                                    */
    /*************************************************************************/
    baf_decode_record(scratch, length_of_record, bytes_read);

    /*************************************************************************/
    /* Get the beginning of the next record.                                 */
    /*************************************************************************/
    bytes_read = OS_FREAD((NBB_BYTE *)scratch,
                          1,
                          4,
                          billing_file);

    /*************************************************************************/
    /* Get the length of the record.                                         */
    /*************************************************************************/
    length_of_record = (256 * scratch[0]) + scratch[1];
  }

  if (bytes_read != 0)
  {
    printf("\n\n Warning: Had %d extra bytes left over.  These were\n",
           bytes_read);
    for (ii = 0;  ii < bytes_read; ii++)
    {
      printf("0x%2.2x ", scratch[ii]);
    }
    printf("\n");
  }

EXIT_LABEL:

  if (!baf_verbose)
  {
    printf("\n");
  }
  printf("Finished decoding of %s\n\n", file_name);

  /***************************************************************************/
  /* Close the file.                                                         */
  /***************************************************************************/
  if (billing_file != NULL)
  {
    OS_FCLOSE(billing_file);
  }

  return;

} /* baf_decode_file */

/**PROC+**********************************************************************/
/* Name:      baf_decode_record                                              */
/*                                                                           */
/* Purpose:   Decodes an entire call record.                                 */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing record       */
/*            IN     length_of_record                                        */
/*                                - Length of this record                    */
/*            IN     bytes_read   - Number of bytes already read             */
/*                                                                           */
/* Operation: XXX update                                                     */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_record(NBB_BYTE *input,
                           NBB_LONG length_of_record,
                           NBB_LONG bytes_read)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_LONG decode_type;
  NBB_INT ii;
  NBB_BOOL modules_appended;
  NBB_CONST BAF_DESCRIPTOR *descriptor;
  NBB_CHAR tempstr[16];
  NBB_CHAR outstr[64];

  /***************************************************************************/
  /* Get the decode type for this record.                                    */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("-------------------------------------------\n");
  }

  decode_type = baf_get_decode_type(input, length_of_record);

  if (baf_verbose)
  {
    printf("-------------------------------------------\n");
    printf("Length of record %d\n", length_of_record);
  }

  /***************************************************************************/
  /* Dump out the record if required.                                        */
  /***************************************************************************/
  if (baf_dump)
  {
    printf("-------------------------------------------\n");
    printf("Byte dump\n");

    outstr[0] = 0x00;
    for (ii = 0; ii < bytes_read; ii++)
    {
      sprintf(tempstr, "%2.2x ", input[ii]);
      strcat(outstr, tempstr);
      if (((ii % 8) == 7) || (ii == bytes_read - 1))
      {
        printf("%-4d: %s\n", ((ii / 8) * 8), outstr);
        outstr[0] = 0;
      }
    }
  }

  if (decode_type == BAF_DECODE_UNKNOWN)
  {
    BAF_ERROR_IN_RECORD(("Unknown decode type\n"));
    goto EXIT_LABEL;
  }

  if (baf_verbose)
  {
    printf("-------------------------------------------\n");
  }

  if (bytes_read != length_of_record)
  {
    /*************************************************************************/
    /* Incomplete record.  We may still be able to decode some of this       */
    /* record.                                                               */
    /*************************************************************************/
    if (baf_verbose)
    {
      printf("Incomplete record, only %d bytes, instead of %d\n",
             bytes_read,
             length_of_record);
    }

    if (bytes_read < 1)
    {
      /***********************************************************************/
      /* Don't have enough bytes to read Table 00, so must exit.             */
      /***********************************************************************/
      if (!baf_verbose)
      {
        printf("*** Bad Record ***\n");
      }
      goto EXIT_LABEL;
    }
  }

  input += 4;
  length_of_record -= 4;

  /***************************************************************************/
  /* We decode tables 00 and 0 by hand.                                      */
  /*                                                                         */
  /* Check Table 00.                                                         */
  /***************************************************************************/
  if (input[0] == 0xAB)
  {
    /*************************************************************************/
    /* Suspected or known errors in some field.  No need to give up though - */
    /* in verbose mode, we'll carry on and decode whatever we can.           */
    /*************************************************************************/
    BAF_ERROR_IN_RECORD(("Known or suspected errors somewhere in record\n"));
    if (!baf_verbose)
    {
      goto EXIT_LABEL;
    }
  }
  else if (input[0] != 0xAA)
  {
    /*************************************************************************/
    /* This is worse.  Don't know what to do with other values, so we will   */
    /* give up.                                                              */
    /*************************************************************************/
    BAF_ERROR_IN_RECORD(("Error in record - table 00 contains errors\n"));
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* See if modules are appended to this record.                             */
  /***************************************************************************/
  input++;
  length_of_record--;
  if ((input[0] >> 4) == 0x04)
  {
    if (baf_verbose)
    {
      printf("Modules appended to this record\n");
    }
    modules_appended = TRUE;
  }
  else if ((input[0] >> 4) == 0x00)
  {
    modules_appended = FALSE;
  }
  else
  {
    BAF_ERROR_IN_RECORD(("Error in record - unknown modules type\n"));

    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode the rest generically.                                            */
  /***************************************************************************/
  descriptor = &(baf_structure_descriptions[decode_type].descriptor);
  if (!baf_decode_all_fields(&input, &length_of_record, descriptor))
  {
    /*************************************************************************/
    /* Decode failed.  Error has been output in the above function so simply */
    /* goto the end.                                                         */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* If there are any modules appended, decode these.                        */
  /***************************************************************************/
  if (modules_appended)
  {
    /*************************************************************************/
    /* Note this function incremenets past the last field read, unlike the   */
    /* others.                                                               */
    /*************************************************************************/
    baf_decode_appended_modules(&input, &length_of_record);
  }

  /***************************************************************************/
  /* Check the record is now finished.                                       */
  /***************************************************************************/
  if (length_of_record != 0)
  {
    BAF_ERROR_IN_RECORD(("Error in record - %d bytes still remaining\n",
                         length_of_record));
    if (baf_verbose)
    {
      for (ii = 0; ii < length_of_record; ii++)
      {
        printf("0x%2.2x ", input[ii]);
      }
      printf("\n");
    }
    goto EXIT_LABEL;
  }

  if (baf_verbose)
  {
    printf("End of record\n");
  }

EXIT_LABEL:

  printf("\n");

  return;
}

/**PROC+**********************************************************************/
/* Name:      baf_decode_appended_modules                                    */
/*                                                                           */
/* Purpose:   Decode modules appended to a structure.                        */
/*                                                                           */
/* Returns:   TRUE on success, else FALSE.                                   */
/*                                                                           */
/* Params:    IN/OUT input        - start of record to continue decoding     */
/*                                  from.                                    */
/*            IN/OUT length_of_record                                        */
/*                                - Length of record remaining               */
/*                                                                           */
/* Operation: Step through the modules one by one decoding as we go.         */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_appended_modules(NBB_BYTE **input,
                                     NBB_LONG *length_of_record)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BOOL ret_code = FALSE;
  NBB_BYTE *new_input = (*input);
  NBB_LONG new_length_of_record = (*length_of_record);
  NBB_CONST BAF_DESCRIPTOR *descriptor;
  NBB_LONG decode_type = BAF_DECODE_UNKNOWN;
  NBB_ULONG module_type;
  NBB_INT ii;

  /***************************************************************************/
  /* Loop through the modules.                                               */
  /***************************************************************************/
  while (new_length_of_record > 1)
  {
    /*************************************************************************/
    /* Get the module type.                                                  */
    /*************************************************************************/
    if ((new_input[1] & 0x0F) != 0x0C)
    {
      BAF_ERROR_IN_RECORD(("Error in record - corrupt module record\n"));
      goto EXIT_LABEL;
    }
    baf_get_chars(new_input, 1, 3, &module_type);

    for (ii = 0; ii < BAF_NUM_MODULES; ii++)
    {
      if (module_type == baf_module_descriptions[ii].module_code)
      {
        decode_type = ii;
        break;
      }
    }

    if (decode_type == BAF_DECODE_UNKNOWN)
    {
      BAF_ERROR_IN_RECORD(("|| Module type %d currently unsupported\n",
                           module_type));
      goto EXIT_LABEL;
    }

    if (baf_verbose)
    {
      printf("|| Appended module %d\n", module_type);
    }

    /*************************************************************************/
    /* Find the descriptor and decode the module.                            */
    /*************************************************************************/
    descriptor = &(baf_module_descriptions[decode_type].descriptor);
    if (!baf_decode_all_fields(&new_input, &new_length_of_record, descriptor))
    {
      /***********************************************************************/
      /* Decode failed.  Error has been output in the above function so      */
      /* simply goto the end.                                                */
      /***********************************************************************/
      goto EXIT_LABEL;
    }
  }

  ret_code = TRUE;

EXIT_LABEL:

  if (!ret_code)
  {
    /*************************************************************************/
    /* Any failure means we must skip to the end of the record, as modules   */
    /* do not contain a length - it is implied from the module type.         */
    /*************************************************************************/
    new_input += new_length_of_record;
    (*input) = new_input;
    (*length_of_record) = 0;
  }
  else
  {
    (*input) = new_input;
    (*length_of_record) = new_length_of_record;
  }

  return(ret_code);

}

/**PROC+**********************************************************************/
/* Name:      baf_decode_all_fields                                          */
/*                                                                           */
/* Purpose:   Decodes all fields in a BAF record.                            */
/*                                                                           */
/* Returns:   TRUE on success, else FALSE.                                   */
/*                                                                           */
/* Params:    IN/OUT input        - start of record to continue decoding     */
/*                                  from.                                    */
/*            IN/OUT length_of_record                                        */
/*                                - Length of record remaining               */
/*            IN     descriptor   - Descriptor for decoding                  */
/*                                                                           */
/* Operation: Step through all fields in the record, decoding them.          */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_all_fields(NBB_BYTE **input,
                               NBB_LONG *length_of_record,
                               NBB_CONST BAF_DESCRIPTOR *descriptor)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BOOL ret_code = FALSE;
  NBB_LONG field;
  NBB_INT ii;
  NBB_BYTE *new_input = (*input);
  NBB_LONG new_length_of_record = (*length_of_record);

  /***************************************************************************/
  /* Get the first field in the descriptor.                                  */
  /***************************************************************************/
  field = descriptor->field[0];
  ii = 0;

  /***************************************************************************/
  /* Decode each field in turn.                                              */
  /***************************************************************************/
  while (field != BAF_FIELD_NO_FIELD)
  {
    if (!baf_decode_field(&new_input, &new_length_of_record, field))
    {
      goto EXIT_LABEL;
    }

    /*************************************************************************/
    /* Get next field.                                                       */
    /*************************************************************************/
    ii++;
    assert(ii < BAF_MAX_FIELDS_IN_DESCRIPTOR);
    field = descriptor->field[ii];
  }

  /***************************************************************************/
  /* Success to get here.                                                    */
  /***************************************************************************/
  ret_code = TRUE;

EXIT_LABEL:

  (*input) = new_input;
  (*length_of_record) = new_length_of_record;

  return(ret_code);

} /* baf_decode_all_fields */

/**PROC+**********************************************************************/
/* Name:      baf_decode_field                                               */
/*                                                                           */
/* Purpose:   Decode a field in a BAF record or module.                      */
/*                                                                           */
/* Returns:   TRUE on success, else FALSE.                                   */
/*                                                                           */
/* Params:    IN/OUT input        - start of record to continue decoding     */
/*                                  from.                                    */
/*            IN/OUT length_of_record                                        */
/*                                - Length of record remaining               */
/*            IN     field        - Field                                    */
/*                                                                           */
/* Operation: Step through the elements of the field and decode them.        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_field(NBB_BYTE **input,
                          NBB_LONG *length_of_record,
                          NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BOOL ret_code = FALSE;
  NBB_BOOL inc_length = FALSE;
  NBB_CONST BAF_FIELD *descriptor = &(baf_field_list[field]);
  NBB_CONST BAF_DISPLAY *display;
  NBB_CONST BAF_VALUE *value;
  NBB_INT ii;
  NBB_INT jj;
  NBB_ULONG chars;
  NBB_BOOL displayed;

  /***************************************************************************/
  /* Sanity.                                                                 */
  /***************************************************************************/
  assert(field <= BAF_NUM_FIELDS);

  /***************************************************************************/
  /* If there is a special decoder for the field then use that and that      */
  /* only.                                                                   */
  /***************************************************************************/
  if (descriptor->decoder != NULL)
  {
    ret_code = BAF_DECODE_FIELD(input, length_of_record, field);
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Print field name.                                                       */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s", descriptor->name);
  }

  /***************************************************************************/
  /* Check there is enough data left to decode this field.                   */
  /***************************************************************************/
  assert((descriptor->num_chars % 2) == 0);
  if (*length_of_record < (descriptor->num_chars / 2))
  {
    BAF_ERROR_IN_RECORD(("Error in field\n"));
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* After this point we need to increment the length, even if the decode    */
  /* goes to the EXIT label.                                                 */
  /***************************************************************************/
  inc_length = TRUE;

  /***************************************************************************/
  /* Check that the final character is a C (most common) or F (field not     */
  /* used) or D (error characters - continue).                               */
  /***************************************************************************/
  if (((*input)[(descriptor->num_chars / 2) - 1] & 0x0F) == 0x0F)
  {
    if (baf_verbose)
    {
      printf(" : Field not used\n");
    }
    ret_code = TRUE;
    goto EXIT_LABEL;
  }
  else if (((*input)[(descriptor->num_chars / 2) - 1] & 0x0F) == 0x0D)
  {
    if (baf_verbose)
    {
      printf(" : Field contains errors");
    }
  }
  else if (((*input)[(descriptor->num_chars / 2) - 1] & 0x0F) != 0x0C)
  {
    BAF_ERROR_IN_RECORD(("Error in field\n"));
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* In concise format, just move along.                                     */
  /***************************************************************************/
  if (!baf_verbose)
  {
    ret_code = TRUE;
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode the field by stepping through its elements.                      */
  /***************************************************************************/
  for (ii = 0; ii < descriptor->num_displays; ii++)
  {
    /*************************************************************************/
    /* Display the next element by getting the value for it.                 */
    /*************************************************************************/
    displayed = FALSE;
    display = &(descriptor->displays[ii]);

    /*************************************************************************/
    /* Output a separator and maybe a name.                                  */
    /*************************************************************************/
    printf(" : ");
    if (display->name[0] != 0)
    {
      printf("%s = ", display->name);
    }

    /*************************************************************************/
    /* Get the characters.  If there are no display elements, output the     */
    /* field as a value.                                                     */
    /*************************************************************************/
    assert(((display->min_char - display->max_char) < 9) ||
           (display->num_values == 0));

    /*************************************************************************/
    /* Check characters are used.                                            */
    /*************************************************************************/
    baf_get_chars(*input, display->min_char, display->min_char, &chars);
    if (chars == 0xF)
    {
      printf("Characters in error");
      displayed = TRUE;
    }

    if ((display->num_values > 0) &&
        (!displayed))
    {
      /***********************************************************************/
      /* May have value descriptors so run through them.                     */
      /***********************************************************************/
      baf_get_chars(*input, display->min_char, display->max_char, &chars);

      for (jj = 0; jj < display->num_values; jj++)
      {
        /*********************************************************************/
        /* Check if this value matches for this element and if some display. */
        /*********************************************************************/
        value = &(display->values[jj]);
        if ((chars >= value->min_value) &&
            (chars <= value->max_value))
        {
          printf("%s", value->name);
          if (value->min_value != value->max_value)
          {
            printf(" %d", chars);
          }
          displayed = TRUE;
        }
      }
    }

    /*************************************************************************/
    /* If we haven't already output something more useful, at least give the */
    /* value.                                                                */
    /*************************************************************************/
    if (!displayed)
    {
      baf_decode_number(*input, display->min_char, display->max_char);
    }
  }
  printf("\n");

  ret_code = TRUE;

EXIT_LABEL:

  /***************************************************************************/
  /* Move along.                                                             */
  /***************************************************************************/
  if (inc_length)
  {
    *input += descriptor->num_chars / 2;
    *length_of_record -= descriptor->num_chars / 2;
  }

  return(ret_code);

} /* baf_decode_field */

/**PROC+**********************************************************************/
/* Name:      baf_get_chars                                                  */
/*                                                                           */
/* Purpose:   Get characters for the field.                                  */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     input        - start of record to continue decoding     */
/*                                  from.                                    */
/*            IN     min_char     - Minimum character to get.                */
/*            IN     max_char     - Maximum character to get.                */
/*            OUT    chars        - Value of characters.                     */
/*                                                                           */
/* Operation: Get the characters.                                            */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_get_chars(NBB_BYTE *input,
                       NBB_INT min_char,
                       NBB_INT max_char,
                       NBB_ULONG *chars)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_INT ii;

  *chars = 0;

  /***************************************************************************/
  /* Not safe to use this function for more than 9 characters (because we're */
  /* decoding into a ULONG, and 0xFFFFFFFF is 4294967295, which is ten       */
  /* digits).                                                                */
  /*                                                                         */
  /* If you hit this assertion, you'll just have to write a specialist       */
  /* decoder for the field in question, and not rely on this function.       */
  /***************************************************************************/
  assert(max_char >= min_char);
  assert((max_char - min_char) < 9);
  for (ii = min_char; ii <= max_char; ii++)
  {
    *chars = *chars * 10;

    if ((ii % 2) == 1)
    {
      /***********************************************************************/
      /* First character of a two character byte.                            */
      /***********************************************************************/
      *chars = *chars + ((input[ii / 2] & 0xF0) >> 4);
    }
    else
    {
      /***********************************************************************/
      /* Second character of a two character byte.                           */
      /***********************************************************************/
      *chars = *chars + (input[(ii / 2) - 1] & 0x0F);
    }
  }

  return;

} /* baf_get_chars */

