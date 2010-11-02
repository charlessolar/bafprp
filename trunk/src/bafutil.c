/**MOD+***********************************************************************/
/* Module:    bafutil.c                                                      */
/*                                                                           */
/* Purpose:   General utility functions for bafview.                         */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: bafutil.c 12654 2009-09-17 10:16:54Z pf                          $  */
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
/**MOD-***********************************************************************/

#include <bafincl.h>

/**PROC+**********************************************************************/
/* Name:      baf_get_decode_type                                            */
/*                                                                           */
/* Purpose:   Gets the type of record for bafview to decode.                 */
/*                                                                           */
/* Returns:   One of BAF_DECODE_TYPES.                                       */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing record       */
/*            IN     length       - Valid length of record                   */
/*                                                                           */
/* Operation: Look at structure code and call type to decide on the type of  */
/*            decode.                                                        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_LONG baf_get_decode_type(NBB_BYTE *input, NBB_LONG length)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_LONG decode_type = BAF_DECODE_UNKNOWN;
  NBB_ULONG structure_type;
  NBB_ULONG call_type;
  NBB_ULONG class_feature_code = 0;
  NBB_BOOL unsupported = FALSE;
  NBB_INT ii;

  /***************************************************************************/
  /* Get structure type.                                                     */
  /***************************************************************************/
  input += 5;
  length -= 5;
  if ((length < 3) ||
      ((input[2] & 0x0F) != 0x0C))
  {
    baf_print("Couldn't get structure type %2.2x%2.2x%2.2x\n",
           input[0],
           input[1],
           input[2]);
    goto EXIT_LABEL;
  }
  baf_get_chars(input, 2, 5, &structure_type);

  /***************************************************************************/
  /* Get call type.                                                          */
  /***************************************************************************/
  input += 3;
  length -= 3;
  if ((length < 2) ||
      ((input[1] & 0x0F) != 0x0C))
  {
    baf_print("Couldn't get call type %2.2x%2.2x\n",
           input[0],
           input[1]);
    goto EXIT_LABEL;
  }
  baf_get_chars(input, 1, 3, &call_type);

  /***************************************************************************/
  /* Convert the structure type into an internal value (providing an index   */
  /* to baf_structure_descriptions).                                         */
  /***************************************************************************/
  for (ii = 0; ii < BAF_NUM_STRUCTURES; ii++)
  {
    if (structure_type == baf_structure_descriptions[ii].structure_code)
    {
      decode_type = ii;
      break;
    }
  }

  /***************************************************************************/
  /* If running in statistics mode, we only need to decode type information. */
  /***************************************************************************/
  if (baf_stats)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Output some helpful descriptive text, baed on call type and structure   */
  /* type.                                                                   */
  /***************************************************************************/
  switch (call_type)
  {
    case 1:
      baf_verbose ? baf_print("Message rate call with MBI\n") :
                    baf_print("Msg rate MBI: ");
      break;

    case 5:
      /***********************************************************************/
      /* Call type 005.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Local message rate call\n") :
                    baf_print("Local call  : ");
      break;

    case 6:
      /***********************************************************************/
      /* Call type 006.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Toll call or non-US\n") :
                    baf_print("Toll call   : ");
      break;

    case 9:
      /***********************************************************************/
      /* Call type 009.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("411 Directory Assistance\n") :
                    baf_print("411 DA call : ");
      break;

    case 26:
      /***********************************************************************/
      /* Call type 026.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Conference Trunk Usage\n") :
                    baf_print("Conference  : ");
      break;

    case 31:
      /***********************************************************************/
      /* Call type 330 - need to check the structure.                        */
      /***********************************************************************/
      if (structure_type == 96)
      {
        baf_verbose ? baf_print("Call forwarding deactivation\n") :
                      baf_print("Forward off : ");
      }
      else if (structure_type == 614)
      {
        baf_verbose ? baf_print("Call forwarding activation\n") :
                      baf_print("Forward on  : ");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 33:
      /***********************************************************************/
      /* Call type 033.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("555 Directory Assistance\n") :
                    baf_print("555 DA call : ");
      break;

    case 42:
      /***********************************************************************/
      /* Call type 042.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Time change marker\n") :
                    baf_print("Time change : ");
      break;

    case 45:
      /***********************************************************************/
      /* Call type 045.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("ISDN call\n") :
                    baf_print("ISDN call   : ");
      break;

    case 47:
      /***********************************************************************/
      /* Call type 047.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Default AIN\n") :
                    baf_print("Default AIN : ");
      break;

    case 48:
      /***********************************************************************/
      /* Call type 048.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Conference resource usage\n") :
                    baf_print("Conference resource usage : ");
      break;

    case 49:
      /***********************************************************************/
      /* Call type 049.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Conference resource usage\n") :
                    baf_print("Conference resource usage : ");
      break;

    case 63:
      /***********************************************************************/
      /* Call type 063                                                       */
      /***********************************************************************/
      if (structure_type == 220 ||
          structure_type == 221 ||
          structure_type == 614 ||
          structure_type == 625 ||
          structure_type == 653)
      {
        baf_verbose ? baf_print("Cellular Mobile Carrier - Type 1 or 2B "
                                                           "(Originating)\n") :
                      baf_print("Wireless - Type 1/2B (Orig) : ");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 64:
      /***********************************************************************/
      /* Call type 064                                                       */
      /***********************************************************************/
      if (structure_type == 220 ||
          structure_type == 221 ||
          structure_type == 614 ||
          structure_type == 625 ||
          structure_type == 653)
      {
        baf_verbose ? baf_print("Cellular Mobile Carrier - Type 2A "
                                                           "(Originating)\n") :
                      baf_print("Wireless - Type 2A (Orig.):");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 65:
      /***********************************************************************/
      /* Call type 065                                                       */
      /***********************************************************************/
      if (structure_type == 220 ||
          structure_type == 221 ||
          structure_type == 614 ||
          structure_type == 625 ||
          structure_type == 653)
      {
        baf_verbose ? baf_print("Cellular Mobile Carrier - Type 1 or 2B "
                                                           "(Terminating)\n") :
                      baf_print("Wireless - Type 1/2B (Term.):");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 66:
      /***********************************************************************/
      /* Call type 066                                                       */
      /***********************************************************************/
      if (structure_type == 614 ||
          structure_type == 625 ||
          structure_type == 653)
      {
        baf_verbose ? baf_print("Cellular Mobile Carrier - Type 2A "
                                                           "(Terminating)\n") :
                      baf_print("Wireless - Type 2A (Term.):");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 88:
      /***********************************************************************/
      /* Call type 088.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("555 Non-Directory Assistance\n") :
                    baf_print("555 Non-DA  : ");
      break;

    case 90:
      /***********************************************************************/
      /* Call type 90.                                                       */
      /***********************************************************************/
      if (structure_type == 9102)
      {
        /*********************************************************************/
        /* Structure 9102, call type 090.                                    */
        /*********************************************************************/
        baf_verbose ? baf_print("Sensor Audit Record\n") :
                      baf_print("--- Audit   : ");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 92:
      /***********************************************************************/
      /* Call type 92 - need to check the structure type.                    */
      /***********************************************************************/
      if (structure_type == 9013)
      {
        /*********************************************************************/
        /* Structure 9013, call type 092.                                    */
        /*********************************************************************/
        baf_verbose ? baf_print("File start marker\n") :
                      baf_print("=== File start marker : ");
      }
      else if (structure_type == 9014)
      {
        /*********************************************************************/
        /* Structure 9014, call type 092.                                    */
        /*********************************************************************/
        baf_verbose ? baf_print("File end marker\n") :
                      baf_print("=== File end marker : ");
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 110:
      /***********************************************************************/
      /* Call type 110.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Interlata call\n") :
                    baf_print("Interlata   : ");
      break;

    case 119:
      /***********************************************************************/
      /* Call type 119.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Incoming CDR\n") :
                    baf_print("Incoming    : ");
      break;

    case 123:
      /***********************************************************************/
      /* Call type 123.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("CLASS feature activation\n") :
                    baf_print("CLASS act.  : ");
      break;

    case 131:
      /***********************************************************************/
      /* Call type 131.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Feature Group A - Originating\n") :
                    baf_print("Feat A Orig : ");
      break;

    case 132:
      /***********************************************************************/
      /* Call type 132.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Feature Group A - Terminating\n") :
                    baf_print("Feat A Term : ");
      break;

    case 134:
      /***********************************************************************/
      /* Call type 134.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("FGB call - Originating\n") :
                    baf_print("FGB Orig    : ");
      break;

    case 135:
      /***********************************************************************/
      /* Call type 135.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("FGB call - Terminating\n") :
                    baf_print("FGB Term    : ");
      break;

    case 141:
      /***********************************************************************/
      /* Call type 141.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Interexchange Carrier Number Services\n") :
                    baf_print("IC Num Servs: ");
      break;

    case 142:
      /***********************************************************************/
      /* Call type 142.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Local Exchange Carrier Number Services\n") :
                    baf_print("LEC Num Serv: ");
      break;

    case 264:
      baf_verbose ? baf_print("Calling Identity Delivery record\n") :
                    baf_print("CLASS (CLI) : ");
      break;

    case 330:
      /***********************************************************************/
      /* Call type 330 - need to check the structure.                        */
      /***********************************************************************/
      if (structure_type == 1030)
      {
        baf_verbose ? baf_print("CLASS functions call structure 1030\n") :
                      baf_print("CLASS usage : ");
      }
      else if (structure_type == 110)
      {
        /*********************************************************************/
        /* CAll type 330, structure code 110.  Still don't know what is      */
        /* going on here.  Need to get the CLASS feature code if possible.   */
        /*********************************************************************/
        if (length >= 16)
        {
          baf_get_chars(input, 29, 31, &class_feature_code);
        }

        if ((class_feature_code == 1) ||
            (class_feature_code == 2) ||
            (class_feature_code == 3))
        {
          baf_verbose ? baf_print("CLASS feature: Outgoing Call Barring\n") :
                        baf_print("CLASS (OCB) : ");
        }
        else
        {
          baf_verbose ? baf_print("CLASS feature: Anonymous call "
                                                               "rejection\n") :
                        baf_print("CLASS (ACR) : ");
        }
      }
      else
      {
        unsupported = TRUE;
      }
      break;

    case 331:
      /***********************************************************************/
      /* Call type 331.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Bulk Calling Identity statistics\n") :
                    baf_print("CLASS (BCLI): ");
      break;

    case 710:
      /***********************************************************************/
      /* Call type 710.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Originating Toll AMA Record\n") :
                    baf_print("Orig Toll   : ");
      break;

    case 711:
      /***********************************************************************/
      /* Call type 711.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Terminating Toll AMA Record\n") :
                    baf_print("Term Toll   : ");
      break;

    case 720:
      /***********************************************************************/
      /* Call type 720.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Connecting Network Access Incoming Record\n") :
                    baf_print("CNA         : ");
      break;

    case 721:
      /***********************************************************************/
      /* Call type 721.                                                      */
      /***********************************************************************/
      baf_verbose ? baf_print("Default Local Number Portability\n") :
                    baf_print("LNP         : ");
      break;

    default:
      /***********************************************************************/
      /* Unsupported call type.                                              */
      /***********************************************************************/
      unsupported = TRUE;
      break;
  }

  /***************************************************************************/
  /* Check if call type / structure code was unsupported.                    */
  /***************************************************************************/
  if (unsupported)
  {
    baf_verbose ? baf_print("*** Unsupported call type %d / structure code "
                                                                        "%d\n",
                         call_type,
                         structure_type) :
                  baf_print("Unsupported : ");
  }

EXIT_LABEL:

  return(decode_type);

} /* baf_get_decode_type */

/**PROC+**********************************************************************/
/* Name:      baf_merge_file                                                 */
/*                                                                           */
/* Purpose:   Copy the complete record from a billing file into a merged     */
/*            file.                                                          */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN/OUT output_file  - file handle for the output file.         */
/*            IN     filename     - name of the file to copy records from.   */
/*            IN     output_start_records                                    */
/*                                - whether start and end records should be  */
/*                                  included.                                */
/*            IN/OUT record_count - a count of the number of records in the  */
/*                                  output file.  This does not include      */
/*                                  start and end records.                   */
/*            IN/OUT file_sequence_number                                    */
/*                                - the file sequence number.                */
/*            IN     first_file   - whether this is the first file to be     */
/*                                  merged into the output file.             */
/*            IN     last_file    - whether this is the last file to be      */
/*                                  merged into the output file.             */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_merge_file(FILE **output_file,
                        NBB_CHAR *filename,
                        NBB_BOOL output_start_records,
                        NBB_ULONG *record_count,
                        NBB_ULONG *file_sequence_number,
                        NBB_BOOL first_file,
                        NBB_BOOL last_file)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  FILE *input_file;
  NBB_LONG length_of_record;
  NBB_BYTE scratch[1024];
  NBB_LONG bytes_read;
  NBB_ULONG structure_type;
  NBB_CONST BAF_DESCRIPTOR *descriptor;
  NBB_CONST BAF_FIELD *field;
  NBB_INT offset = 0;
  NBB_INT ii;

  assert(record_count != NULL);
  assert(file_sequence_number != NULL);

  /***************************************************************************/
  /* Open the input file.                                                    */
  /***************************************************************************/
  input_file = OS_FOPEN(filename, "r");

  if (input_file == NULL)
  {
    baf_print("Failed to open file %s.\n", filename);
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Read in the length of the record.                                       */
  /***************************************************************************/
  bytes_read = OS_FREAD((NBB_BYTE *)scratch,
                        1,
                        4,
                        input_file);
  length_of_record = (256 * scratch[0]) + scratch[1];

  while ((bytes_read == 4) && (length_of_record >= 8))
  {
    /*************************************************************************/
    /* Read in the rest of the record.                                       */
    /*************************************************************************/
    bytes_read += OS_FREAD((NBB_BYTE *)scratch + 4,
                           1,
                           length_of_record - 4,
                           input_file);

    if (bytes_read != length_of_record)
    {
      break;
    }

    /*************************************************************************/
    /* Determine whether this is a start record (type 9013) or an end record */
    /* (type 9014).                                                          */
    /*************************************************************************/
    baf_get_chars(&scratch[5], 2, 5, &structure_type);

    if (structure_type == 9013)
    {
      /***********************************************************************/
      /* Start records should only be written if                             */
      /* - this is the first file.                                           */
      /* - start and end records should be included in the merged file.      */
      /*                                                                     */
      /* If this start record is being included record the file sequence     */
      /* number so that it can be used in the end record.                    */
      /***********************************************************************/
      if ((first_file) && (output_start_records))
      {
        /*********************************************************************/
        /* Locate the structure descriptor.  Step through the fields to      */
        /* determine the offset to the file sequence number.  The first 5    */
        /* bytes are a header.  The first two fields are the structure type  */
        /* (3 bytes) and call type (2 bytes).  Records also contain a date   */
        /* (3 bytes) and time field (4 bytes) that are decoded using special */
        /* functions.                                                        */
        /*********************************************************************/
        descriptor =
              &(baf_structure_descriptions[BAF_DECODE_STRUCT_9013].descriptor);
        offset = 17;

        for (ii = 2;
             ((ii < BAF_MAX_FIELDS_IN_DESCRIPTOR) &&
              (descriptor->field[ii] != BAF_FIELD_NO_FIELD));
             ii++)
        {
          /*******************************************************************/
          /* Two characters are stored in each byte, so increment the offset */
          /* by half of the number of characters in the field.               */
          /*******************************************************************/
          if (descriptor->field[ii] == BAF_F__C1_FILE_SEQUENCE_NO)
          {
            baf_get_chars(&scratch[offset], 1, 3, file_sequence_number);
            break;
          }

          field = &(baf_field_list[descriptor->field[ii]]);
          offset += (field->num_chars / 2);
        }

        OS_FWRITE(scratch, bytes_read, 1, *output_file);
      }
    }
    else if (structure_type == 9014)
    {
      /***********************************************************************/
      /* End records should only be written if                               */
      /* - this is the last file.                                            */
      /* - start and end records should be included in the merged file.      */
      /*                                                                     */
      /* Before the record is written to the merged file update the file     */
      /* sequence number and record count.                                   */
      /***********************************************************************/
      if ((last_file) && (output_start_records))
      {
        /*********************************************************************/
        /* Locate the structure descriptor.  Step through the fields to      */
        /* determine the offset to the file sequence number and number of    */
        /* records fields.  The first two fields are the structure type (3   */
        /* bytes) and call type (2 bytes).  Records also contain a date (3   */
        /* bytes) and time field (4 bytes) that are decoded using special    */
        /* functions.                                                        */
        /*********************************************************************/
        descriptor =
              &(baf_structure_descriptions[BAF_DECODE_STRUCT_9014].descriptor);
        offset = 17;

        for (ii = 2;
             ((ii < BAF_MAX_FIELDS_IN_DESCRIPTOR) &&
              (descriptor->field[ii] != BAF_FIELD_NO_FIELD));
             ii++)
        {
          field = &(baf_field_list[descriptor->field[ii]]);

          if (descriptor->field[ii] == BAF_F__C1_FILE_SEQUENCE_NO)
          {
            baf_write_file_sequence(&scratch[offset], *file_sequence_number);
          }
          else if (descriptor->field[ii] == BAF_F__C2_NUMBER_OF_RECORDS)
          {
            baf_write_num_records(&scratch[offset], *record_count);
          }

          /*******************************************************************/
          /* Two characters are stored in each byte, so increment the offset */
          /* by half of the number of characters in the field.               */
          /*******************************************************************/
          offset += (field->num_chars / 2);
        }

        OS_FWRITE(scratch, bytes_read, 1, *output_file);
      }
    }
    else
    {
      /***********************************************************************/
      /* Write the record to the output file.                                */
      /***********************************************************************/
      OS_FWRITE(scratch, bytes_read, 1, *output_file);
      (*record_count)++;
    }

    /*************************************************************************/
    /* Get the beginning of the next record.                                 */
    /*************************************************************************/
    bytes_read = OS_FREAD((NBB_BYTE *)scratch,
                          1,
                          4,
                          input_file);

    /*************************************************************************/
    /* Get the length of the record.                                         */
    /*************************************************************************/
    length_of_record = (256 * scratch[0]) + scratch[1];
  }

  if (bytes_read != 0)
  {
    baf_print("Failed to merge somes records from %s.\n", filename);
  }

  OS_FCLOSE(input_file);

EXIT_LABEL:

  return;

} /* baf_merge_file */

/**PROC+**********************************************************************/
/* Name:      baf_check_start_records                                        */
/*                                                                           */
/* Purpose:   Check whether a file has start and end records.                */
/*                                                                           */
/* Returns:   One of BAF_START_END_RCs.                                      */
/*                                                                           */
/* Params:    IN     file_name    - the name of the file to check.           */
/*                                                                           */
/* Operation: Open the file and read the first record.  If it is a start     */
/*            record the file contains start and end records.                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BYTE baf_check_start_records(NBB_CHAR *filename)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BYTE rc = BAF_START_END_RC_FAIL;
  FILE *input_file;
  NBB_BYTE scratch[1024];
  NBB_LONG bytes_read;
  NBB_LONG length_of_record;
  NBB_ULONG structure_type;

  /***************************************************************************/
  /* Open the input file.                                                    */
  /***************************************************************************/
  input_file = OS_FOPEN(filename, "r");

  if (input_file == NULL)
  {
    baf_print("Failed to open file %s.\n", filename);
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Read in the length of the first record.                                 */
  /***************************************************************************/
  bytes_read = OS_FREAD((NBB_BYTE *)scratch,
                        1,
                        4,
                        input_file);
  length_of_record = (256 * scratch[0]) + scratch[1];

  if ((bytes_read == 4) && (length_of_record >= 8))
  {
    bytes_read += OS_FREAD((NBB_BYTE *)scratch + 4,
                           1,
                           length_of_record - 4,
                           input_file);

    if (bytes_read != length_of_record)
    {
      goto EXIT_LABEL;
    }

    /*************************************************************************/
    /* Check whether this is a start record which has structure type 9013.   */
    /*************************************************************************/
    baf_get_chars(&scratch[5], 2, 5, &structure_type);

    if (structure_type == 9013)
    {
      rc = BAF_START_END_RC_YES;
    }
    else
    {
      rc = BAF_START_END_RC_NO;
    }
  }

EXIT_LABEL:

  if (input_file != NULL)
  {
    OS_FCLOSE(input_file);
  }

  return(rc);

} /* baf_check_start_records */

/**PROC+**********************************************************************/
/* Name:      baf_print_record                                               */
/*                                                                           */
/* Purpose:   Print in stdout the information collected in BAF_STATS_DATA    */
/*                                                                           */
/* Params:    IN     stats_data    - pointer to structure to be printed.     */
/*                                                                           */
/* Operation: Print out fields kept in BAF_STATS_DATA separating each value  */
/*            with a blank space.                                            */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_print_record(BAF_STATS_DATA *stats_data)
{
  if (stats_data->call_date[0] != '-')
  {
    /*************************************************************************/
    /* A '#' character is used to differentiate records decoded correctly    */
    /* from error and warning messages printed by bafview.                   */
    /*************************************************************************/
    baf_print("# %s %s %s %s %s %s\n", stats_data->call_date,
                                    stats_data->call_time,
                                    stats_data->call_length,
                                    stats_data->carrier_id,
                                    stats_data->incoming_trunk_id,
                                    stats_data->outgoing_trunk_id);
  }
} /* baf_print_record */

/**PROC+**********************************************************************/
/* Name:      baf_print                                                      */
/*                                                                           */
/* Purpose:   Replacement for standard printf.                               */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN    fmt_string - The baf_print format specifier.             */
/*                                                                           */
/* Operation: If BAF_PRINT_TO_BUFFER is defined, this outputs the data to a  */
/*            buffer (increasing the buffer size if needed).                 */
/*                                                                           */
/*            Otherwise this behaves like standard printf.                   */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_print(NBB_CONST NBB_CHAR *format_string, ...)
{
  /***************************************************************************/
  /* Local variables                                                         */
  /***************************************************************************/
  va_list arglist;
#ifdef BAF_PRINT_TO_BUFFER
  int remaining_buf_size = print_buf_end - print_buf_ptr;
  int nchars;
  int buf_ptr_offset;
  int new_print_buf_size;
  int print_buf_offset;
#endif

  /***************************************************************************/
  /* Convert the variable length args into an arglist.                       */
  /***************************************************************************/
  va_start(arglist, format_string);

#ifndef BAF_PRINT_TO_BUFFER
  /***************************************************************************/
  /* We're simply printing to stdout - just use vprintf.                     */
  /***************************************************************************/
  vprintf(format_string, arglist);
#else
  /***************************************************************************/
  /* Print to the buffer set up in the global variable.                      */
  /***************************************************************************/
  nchars = vsnprintf(print_buf_ptr,
                     remaining_buf_size,
                     format_string,
                     arglist);

  if (nchars >= remaining_buf_size)
  {
    /*************************************************************************/
    /* We've run out of space in our buffer.  Realloc the buffer to a larger */
    /* size sufficient to print this string (in multiples of                 */
    /* BAF_OUTPUT_STRING_SIZE so as not to realloc too often).               */
    /*************************************************************************/
    print_buf_offset = print_buf_ptr - print_buf_start;
    new_print_buf_size = (print_buf_size +
                          (BAF_PRINT_BUFFER_SIZE_UNIT *
          (((nchars - remaining_buf_size) / BAF_PRINT_BUFFER_SIZE_UNIT) + 1)));
    buf_ptr_offset = (print_buf_ptr - print_buf_start);
    print_buf_start = realloc(print_buf_start, new_print_buf_size);
    print_buf_ptr = print_buf_start + print_buf_offset;
    print_buf_size = new_print_buf_size;
    print_buf_end = print_buf_start + print_buf_size;
    nchars = vsnprintf(print_buf_ptr,
                       remaining_buf_size,
                       format_string,
                       arglist);
  }

  /***************************************************************************/
  /* Move along by the amount of data we've written.                         */
  /***************************************************************************/
  print_buf_ptr += nchars;
#endif

  va_end(arglist);

  return;

} /* baf_print */

/**PROC+**********************************************************************/
/* Name:      baf_initialize                                                 */
/*                                                                           */
/* Purpose:   Initializes structures used by bafview.                        */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    None.                                                          */
/*                                                                           */
/* Operation: Work out what the current year is and then setup the baf_year  */
/*            structure.                                                     */
/*                                                                           */
/*            Sadly there is no generic way of working out what the current  */
/*            year is, so the code below may need modification on some       */
/*            platforms.                                                     */
/*                                                                           */
/**PROC-**********************************************************************/
NBB_VOID baf_initialize()
{
  /***************************************************************************/
  /* Local variables                                                         */
  /***************************************************************************/
  int ii;
  int year;
  int year_digit;
  int year_decade;
  time_t time_in_seconds;
  struct tm* date_time;

  /***************************************************************************/
  /* Work out what the current year is. A straightforward way is via time    */
  /* and gmtime which returns a year delta from 1900. On Unix this is valid  */
  /* until 2038.                                                             */
  /***************************************************************************/
  time(&time_in_seconds);
  date_time = gmtime(&time_in_seconds);
  year = date_time->tm_year + 1900;

  /***************************************************************************/
  /* We have the year so can now set up the baf_year structure. Note that    */
  /* its plausible the date of this system is slightly earlier than it       */
  /* should be, so allow for that below by adding 2 to it.                   */
  /***************************************************************************/
  year += 2;
  year_digit = year % 10;
  year_decade = year - year_digit;
  for (ii = 0; ii <= year_digit ; ii++)
  {
    baf_year[ii] = year_decade + ii;
  }
  for (ii = year_digit + 1; ii < 10 ; ii++)
  {
    baf_year[ii] = year_decade + ii - 10;
  }

  return;

} /* baf_initialize */
