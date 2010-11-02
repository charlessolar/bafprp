/**MOD+***********************************************************************/
/* Module:    bafdecod.c                                                     */
/*                                                                           */
/* Purpose:   Functions to decode BAF structures.                            */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: bafdecod.c 12654 2009-09-17 10:16:54Z pf                         $  */
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
    baf_print("Can't open file %s\n\n", file_name);
    goto EXIT_LABEL;
  }
  else
  {
    if (!baf_stats)
    {
      baf_print("Performing ");
      baf_verbose ? baf_print("verbose ") : baf_print("concise ");
      baf_print("decoding of %s\n\n", file_name);
    }
  }

  /***************************************************************************/
  /* Read first byte of billing file, if it is a DNS billing file it will    */
  /* equal 0x1C.  If we are dealing with a DNS file decode the header,       */
  /* otherwise continue as normal.                                           */
  /***************************************************************************/
  bytes_read = OS_FREAD((NBB_BYTE *)scratch,
                        1,
                        1,
                        billing_file);
  if (scratch[0] == 0x1C)
  {

    /*************************************************************************/
    /* DNS header found, read rest of record and decode.                     */
    /*************************************************************************/
    length_of_record=scratch[0];
    bytes_read += OS_FREAD((NBB_BYTE *)scratch + 1,
                            1,
                            length_of_record -1,
                            billing_file);
    baf_decode_record(scratch, length_of_record, bytes_read, TRUE);
  }
  else
  {
    /*************************************************************************/
    /* DNS header not found, reset file pointer to beginning of file.        */
    /*************************************************************************/

    OS_FSEEK(billing_file, 0, SEEK_SET);

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
    baf_decode_record(scratch, length_of_record, bytes_read, FALSE);

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
    baf_print("\n\n Warning: Had %d extra bytes left over.  These were\n",
           bytes_read);
    for (ii = 0;  ii < bytes_read; ii++)
    {
      baf_print("0x%2.2x ", scratch[ii]);
    }
    baf_print("\n");
  }

EXIT_LABEL:

  if ((!baf_verbose) && (!baf_stats))
  {
    baf_print("\n");
  }

  if (!baf_stats)
  {
    baf_print("Finished decoding of %s\n\n", file_name);
  }

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
/*            IN     dns_header   - Is this record a DNS header?             */
/*                                                                           */
/* Operation: XXX update                                                     */
/*                                                                           */
/*            Note that as well as being called from within the main         */
/*            standalone bafview program, it is called directly from the     */
/*            code in bafruby.c (which interfaces between Ruby code and the  */
/*            main bafview C code).  Therefore if changing this behavior or  */
/*            interface to this function, the calling code in bafruby.c must */
/*            also be changed.                                               */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_record(NBB_BYTE *input,
                           NBB_LONG length_of_record,
                           NBB_LONG bytes_read,
                           NBB_BOOL dns_header)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_LONG decode_type = BAF_DECODE_UNKNOWN;
  NBB_INT ii;
  NBB_BOOL modules_appended;
  NBB_CONST BAF_DESCRIPTOR *descriptor;
  NBB_CHAR tempstr[16];
  NBB_CHAR outstr[64];
  NBB_BOOL decode_failed = FALSE;

  /***************************************************************************/
  /* Get the decode type for this record.                                    */
  /***************************************************************************/
  if (baf_verbose)
  {
    baf_print("-------------------------------------------\n");
  }

  if (dns_header)
  {
    baf_verbose ? baf_print("AMADNS Header\n") :
                  baf_print("=== AMADNS Header : ");
  }
  else
  {
    decode_type = baf_get_decode_type(input, length_of_record);
  }

  if (baf_verbose)
  {
    baf_print("-------------------------------------------\n");
    baf_print("Length of record %d\n", length_of_record);
  }

  /***************************************************************************/
  /* Running with statistical option, records without needed information     */
  /* will not be considered.                                                 */
  /***************************************************************************/
  if (baf_stats)
  {
    if (BAF_IS_STATS_STRUCT(decode_type))
    {
      /***********************************************************************/
      /* Set initial values for struct that will keep statistics.            */
      /***********************************************************************/
      stats_data.structure_type = decode_type;
      stats_data.module_code = -1;
      sprintf(stats_data.call_date, "-");
      sprintf(stats_data.call_time, "-");
      sprintf(stats_data.call_length, "-");
      sprintf(stats_data.call_elapsed_time, "-");
      sprintf(stats_data.carrier_id, "-");
      sprintf(stats_data.incoming_trunk_id, "-");
      sprintf(stats_data.outgoing_trunk_id, "-");
    }
    else
    {
      goto EXIT_LABEL;
    }
  }

  /***************************************************************************/
  /* Dump out the record if required.                                        */
  /***************************************************************************/
  if (baf_dump)
  {
    baf_print("-------------------------------------------\n");
    baf_print("Byte dump\n");

    outstr[0] = 0x00;
    for (ii = 0; ii < bytes_read; ii++)
    {
      sprintf(tempstr, "%2.2x ", input[ii]);
      strcat(outstr, tempstr);
      if (((ii % 8) == 7) || (ii == bytes_read - 1))
      {
        baf_print("%-4d: %s\n", ((ii / 8) * 8), outstr);
        outstr[0] = 0;
      }
    }
  }

  if ((decode_type == BAF_DECODE_UNKNOWN) && (!dns_header))
  {
    BAF_ERROR_IN_RECORD(("Unknown decode type\n"));
    decode_failed = TRUE;

    goto EXIT_LABEL;
  }

  if (baf_verbose)
  {
    baf_print("-------------------------------------------\n");
  }

  if (dns_header)
  {
   baf_decode_dns_header(input, &length_of_record, baf_verbose);
  }
  else
  {
    if (bytes_read != length_of_record)
    {
      /***********************************************************************/
      /* Incomplete record.  We may still be able to decode some of this     */
      /* record.                                                             */
      /***********************************************************************/
      if (baf_verbose)
      {
        baf_print("Incomplete record, only %d bytes, instead of %d\n",
               bytes_read,
               length_of_record);
      }

      if (bytes_read < 1)
      {
        /*********************************************************************/
        /* Don't have enough bytes to read Table 00, so must exit.           */
        /*********************************************************************/
        if (!baf_verbose)
        {
          baf_print("*** Bad Record ***\n");
        }
        goto EXIT_LABEL;
     }
    }

    input += 4;
    length_of_record -= 4;

    /*************************************************************************/
    /* We decode tables 00 and 0 by hand.                                    */
    /*                                                                       */
    /* Check Table 00.                                                       */
    /*************************************************************************/
    if (input[0] == 0xAB)
    {
      /***********************************************************************/
      /* Suspected or known errors in some field.  No need to give up though */
      /* - in verbose mode, we'll carry on and decode whatever we can.       */
      /***********************************************************************/
      BAF_ERROR_IN_RECORD(("Known or suspected errors somewhere in record\n"));
      if (!baf_verbose)
      {
        decode_failed = TRUE;
        goto EXIT_LABEL;
      }
    }
    else if (input[0] != 0xAA)
    {
      /***********************************************************************/
      /* This is worse.  Don't know what to do with other values, so we will */
      /* give up.                                                            */
      /***********************************************************************/
      BAF_ERROR_IN_RECORD(("Error in record - table 00 contains errors\n"));
      decode_failed = TRUE;

      goto EXIT_LABEL;
    }

    /*************************************************************************/
    /* See if modules are appended to this record.                           */
    /*************************************************************************/
    input++;
    length_of_record--;
    if ((input[0] >> 4) == 0x04)
    {
      if (baf_verbose)
      {
        baf_print("Modules appended to this record\n");
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
      decode_failed = TRUE;

      goto EXIT_LABEL;
    }

    /*************************************************************************/
    /* Decode the rest generically.                                          */
    /*************************************************************************/
    descriptor = &(baf_structure_descriptions[decode_type].descriptor);
    if (!baf_decode_all_fields(&input, &length_of_record, descriptor))
    {
      /***********************************************************************/
      /* Decode failed.  Error has been output in the above function so      */
      /* simply goto the end.                                                */
      /***********************************************************************/
      decode_failed = TRUE;
      goto EXIT_LABEL;
    }

    /*************************************************************************/
    /* If there are any modules appended, decode these.                      */
    /*************************************************************************/
    if (modules_appended)
    {
      /***********************************************************************/
      /* Note this function incremenets past the last field read, unlike the */
      /* others.                                                             */
      /***********************************************************************/
      decode_failed = (!(baf_decode_appended_modules(&input,
                                                     &length_of_record)));
    }
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
        baf_print("0x%2.2x ", input[ii]);
      }
      baf_print("\n");
    }
    decode_failed = TRUE;
    goto EXIT_LABEL;
  }

  if (baf_verbose)
  {
    baf_print("End of record\n");
  }

  /***************************************************************************/
  /* Dump out statistics.                                                    */
  /***************************************************************************/
  if (baf_stats)
  {
    baf_print_record(&stats_data);
  }

EXIT_LABEL:
  if (!baf_stats)
  {
    baf_print("\n");
  }

  /***************************************************************************/
  /* If failed to decode a record in statistics mode, it should dump bytes   */
  /* already read, helping to identify the record in the billing file if     */
  /* necessary.                                                              */
  /***************************************************************************/
  if ((baf_stats) && (decode_failed))
  {
    baf_print("\n");
    baf_print("Problem decoding the following record: ");

    outstr[0] = 0x00;
    for (ii = 0; ii < bytes_read; ii++)
    {
      sprintf(tempstr, "%2.2x ", input[ii]);
      strcat(outstr, tempstr);
      if (((ii % 8) == 7) || (ii == bytes_read - 1))
      {
        baf_print("%-4d: %s\n", ((ii / 8) * 8), outstr);
        outstr[0] = 0;
      }
    }
  }

  return;
}

/**PROC+**********************************************************************/
/* Name:      baf_decode_dns_header                                          */
/*                                                                           */
/* Purpose:   Decode and print a dns header.                                 */
/*                                                                           */
/* Returns:   Nothing                                                        */
/*                                                                           */
/* Params:    IN/OUT input        - start of record to continue decoding     */
/*                                  from.                                    */
/*            IN/OUT length       - Length of record remaining               */
/*            IN     verbose      - Whether or not in verbose mode.          */
/*                                                                           */
/* Operation: Step through the fields one by one decoding as we go.          */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_dns_header(NBB_BYTE *input,
                               NBB_LONG *length,
                               NBB_BOOL verbose)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BOOL failed = FALSE;
  NBB_BYTE temp_byte = 0;
  NBB_USHORT temp_ushort;
  NBB_ULONG temp_ulong;
  NBB_BYTE minute;
  NBB_BYTE hour;
  NBB_BYTE rec_src_info_type;

  /***************************************************************************/
  /* Decode 'File Header Length'.                                            */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 0, 7);
    baf_print("AMADNS Header Length: %d\n", temp_byte);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'Source Component Identification Number'.                        */
  /***************************************************************************/
  if ((*length) < 2)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ushort = baf_decode_2_bytes(input, 4, 7);
    baf_print("Source Component ID: %04hu\n", temp_ushort);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'Source Component Type'                                          */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 0, 3);
    baf_print("Source Component Type: %02d\n", temp_byte);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'Destination Component Identification Number'.                   */
  /***************************************************************************/
  if ((*length) < 2)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ushort = baf_decode_2_bytes(input, 4, 7);
    baf_print("Destination Component ID: %04hu\n", temp_ushort);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'Destination Component Type'.                                    */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 0, 3);
    baf_print("Destination Component Type: %02d\n", temp_byte);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'File Type'.                                                     */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 0, 4);
    baf_print("File Type: %02d\n", temp_byte);
  }
  /***************************************************************************/
  /* Decode 'Data Format Type'.                                              */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 5, 7);
    baf_print("Data Format Type: %d\n", temp_byte);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'Field Suppression Type'.                                        */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 0, 1);
    baf_print("Field Suppression Type: %d\n", temp_byte);
  }
  /***************************************************************************/
  /* Decode 'File Priority Level'.                                           */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 2, 4);
    baf_print("File Priority Level: %d\n", temp_byte);
  }
  /***************************************************************************/
  /* Decode 'Restart Status'.                                                */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 5, 5);
    baf_print("Restart Status: %d\n", temp_byte);
  }
  /***************************************************************************/
  /* Decode 'Primary/Secondary Status'.                                      */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 6, 6);
    baf_print("Primary/Secondary Status: %d\n", temp_byte);
  }
  /***************************************************************************/
  /* Decode 'Record Source Info Type'.                                       */
  /***************************************************************************/
  if ((*length) < 1)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_byte = baf_decode_byte(input, 7, 7);
    baf_print("Record Source Info Type: %d\n", temp_byte);
  }
  (*length) -= 1;
  input += 1;
  rec_src_info_type = temp_byte;

  /***************************************************************************/
  /* Decode 'File Sequence Number'.                                          */
  /***************************************************************************/
  if ((*length) < 2)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ushort = baf_decode_2_bytes(input, 0, 7);
    baf_print("File Sequence Number: %hu\n", temp_ushort);
  }
  (*length) -= 2;
  input += 2;

  /***************************************************************************/
  /* Decode 'File Creation Time'.                                            */
  /***************************************************************************/
  if ((*length) < 2)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  temp_ushort = baf_decode_2_bytes(input, 4, 7);
  hour = (NBB_BYTE)(temp_ushort / 100);
  minute = (NBB_BYTE)(temp_ushort % 100);
  if (verbose)
  {
    baf_print("File Creation Time: %02d:%02d\n", hour, minute);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'File Creation Date'.                                            */
  /***************************************************************************/
  if ((*length) < 3)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  temp_ulong = baf_decode_3_bytes(input, 0, 3);
  if (verbose)
  {
    baf_print("File Creation Date: ");
  }
  baf_print_dns_date(temp_ulong);
  if (verbose)
  {
    baf_print("\n");
  }
  else
  {
    baf_print(" : %02d:%02d :", hour, minute);
  }

  (*length) -= 3;
  input += 3;

  /***************************************************************************/
  /* Decode 'File Last Modification Time'.                                   */
  /***************************************************************************/
  if ((*length) < 2)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ushort = baf_decode_2_bytes(input, 4, 7);
    hour = (NBB_BYTE)(temp_ushort / 100);
    minute = (NBB_BYTE)(temp_ushort % 100);
    baf_print("File Last Modification Time: %02d:%02d\n", hour, minute);
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'File Last Modification Date'.                                   */
  /***************************************************************************/
  if ((*length) < 3)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ulong = baf_decode_3_bytes(input, 0, 3);
    baf_print("File Last Modification Date: ");
    baf_print_dns_date(temp_ulong);
    baf_print("\n");
  }
  (*length) -= 3;
  input += 3;

  /***************************************************************************/
  /* Decode 'File Length'.                                                   */
  /***************************************************************************/
  if ((*length) < 4)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ulong = baf_decode_4_bytes(input, 0, 7);
    baf_print("File Length: %lu\n", temp_ulong);
  }
  (*length) -= 4;
  input += 4;

  /***************************************************************************/
  /* Decode 'Number of Records in File'.                                     */
  /***************************************************************************/
  if ((*length) < 3)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ulong = baf_decode_3_bytes(input, 0, 7);
    baf_print("Number of Records in File: %lu\n", temp_ulong);
  }
  (*length) -= 3;
  input += 3;

  /***************************************************************************/
  /* Decode 'Record Source Type'.                                            */
  /***************************************************************************/
  if ((*length) < 2)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ushort = baf_decode_2_bytes(input, 4, 7);
    if (rec_src_info_type == 0)
    {
      baf_print("Record Source Type: %hu\n", temp_ushort);
    }
    else
    {
      baf_print("Record Source Type: %02hu\n", temp_ushort);
    }
  }
  (*length) -= 1;
  input += 1;

  /***************************************************************************/
  /* Decode 'Record Source Identification Number'.                           */
  /***************************************************************************/
  if ((*length) < 3)
  {
    failed = TRUE;
    goto EXIT_LABEL;
  }
  if (verbose)
  {
    temp_ulong = baf_decode_3_bytes(input, 0, 3);
    if (rec_src_info_type == 0)
    {
      baf_print("Record Source Identification Number: %lu\n", temp_ulong);
    }
    else
    {
      baf_print("Record Source Identification Number: %04lu\n", temp_ulong);
    }
  }
  (*length) -= 3;
  input += 3;

EXIT_LABEL:

  if (failed)
  {
    baf_print("ERROR: AMADNS Header Incomplete\n");
  }

  return;

} /* baf_decode_dns_header */

/**PROC+**********************************************************************/
/* Name:      baf_print_dns_date                                             */
/*                                                                           */
/* Purpose:   Decode and print a dns date.                                   */
/*                                                                           */
/* Returns:   Nothing                                                        */
/*                                                                           */
/* Params:    IN     date_long    - Date to be printed encoded as mmddyy     */
/*                                                                           */
/* Operation: Decode each part of the date in turn and print on the same     */
/*            line.                                                          */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_print_dns_date(NBB_ULONG date_long)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BYTE day;
  NBB_BYTE month;
  NBB_USHORT year;

  /***************************************************************************/
  /* Print day.                                                              */
  /***************************************************************************/
  day = (NBB_BYTE)((date_long / 100) % 100);
  baf_print("%d ", day);

  /***************************************************************************/
  /* Print month.                                                            */
  /***************************************************************************/
  month = (NBB_BYTE)(date_long / 10000);
  switch (month)
  {
    case 1:
      baf_print("January ");
      break;

    case 2:
      baf_print("February ");
      break;

    case 3:
      baf_print("March ");
      break;

    case 4:
      baf_print("April ");
      break;

    case 5:
      baf_print("May ");
      break;

    case 6:
      baf_print("June ");
      break;

    case 7:
      baf_print("July ");
      break;

    case 8:
      baf_print("August ");
      break;

    case 9:
      baf_print("September ");
      break;

    case 10:
      baf_print("October ");
      break;

    case 11:
      baf_print("November ");
      break;

    case 12:
      baf_print("December ");
      break;
  }

  /***************************************************************************/
  /* Print year.                                                             */
  /***************************************************************************/
  year = (NBB_USHORT)(((NBB_USHORT)(BAF_START_OF_CURRENT_CENTURY)) +
                      ((NBB_USHORT)(date_long % (NBB_ULONG)(100))));
  baf_print("%hu", year);

  return;

} /* baf_print_dns_date */

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

        if (baf_stats)
        {
          stats_data.module_code = decode_type;
        }
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
      baf_print("|| Appended module %d\n", module_type);
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
    baf_print("%s", descriptor->name);
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
      baf_print(" : Field not used\n");
    }
    ret_code = TRUE;
    goto EXIT_LABEL;
  }
  else if (((*input)[(descriptor->num_chars / 2) - 1] & 0x0F) == 0x0D)
  {
    if (baf_verbose)
    {
      baf_print(" : Field contains errors");
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
  if ((!baf_verbose) && (!baf_stats))
  {
    ret_code = TRUE;
    goto EXIT_LABEL;
  }

  if (baf_stats)
  {
    /*************************************************************************/
    /* Running in statistics mode, we are only interested in few fields that */
    /* contain data used for traffic statistics calculation.                 */
    /*************************************************************************/
    if (BAF_IS_STATS_FIELD(field))
    {
      baf_decode_stat_field(input, descriptor, field);
    }

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
    baf_print(" : ");
    if (display->name[0] != 0)
    {
      baf_print("%s = ", display->name);
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
      baf_print("Characters in error");
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
          baf_print("%s", value->name);
          if (value->min_value != value->max_value)
          {
            baf_print(" %d", chars);
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

  baf_print("\n");
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

/**PROC+**********************************************************************/
/* Name:      baf_write_num_records                                          */
/*                                                                           */
/* Purpose:   Write the number of records to the file.                       */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     output       - the record to write to.                  */
/*            IN     value        - the value to write to the field.         */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_write_num_records(NBB_BYTE *output, NBB_ULONG value)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/

  /***************************************************************************/
  /* Num records has range 0 to 9999999.  Write seven digits, two to a byte. */
  /* The field is terminated with an 0x0C.                                   */
  /***************************************************************************/
  assert(output != NULL);
  output[0] = (NBB_BYTE)((value / 1000000) << 4);
  output[0] |= (value / 100000) % 10;
  output[1] = (NBB_BYTE)(((value / 10000) % 10) << 4);
  output[1] |= (value / 1000) % 10;
  output[2] = (NBB_BYTE)(((value / 100) % 10) << 4);
  output[2] |= (value / 10) % 10;
  output[3] = (NBB_BYTE)((value % 10) << 4);
  output[3] |= 0x0C;

  return;

} /* baf_write_num_records */

/**PROC+**********************************************************************/
/* Name:      baf_write_file_sequence                                        */
/*                                                                           */
/* Purpose:   Write the file sequence number to the file.                    */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     output       - the record to write to.                  */
/*            IN     value        - the value to write to the field.         */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_write_file_sequence(NBB_BYTE *output, NBB_ULONG value)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/

  /***************************************************************************/
  /* File sequence number has range 0 to 999.  Write three digits, two to a  */
  /* byte.  The field is terminated with an 0x0C.                            */
  /***************************************************************************/
  assert(output != NULL);
  output[0] = (NBB_BYTE)(((value / 100) % 10) << 4);
  output[0] |= (value / 10) % 10;
  output[1] = (NBB_BYTE)((value % 10) << 4);
  output[1] |= 0x0C;

  return;

} /* baf_write_file_sequence */
