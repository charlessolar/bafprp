
/**MOD+***********************************************************************/
/* Module:    bafmain.c                                                      */
/*                                                                           */
/* Purpose:   To decode and output formatted billing records.                */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: bafmain.c 12654 2009-09-17 10:16:54Z pf                          $  */
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

#define BAFVIEW_DEFINE_VARS
#include <bafincl.h>

/**PROC+**********************************************************************/
/* Name:      main                                                           */
/*                                                                           */
/* Purpose:   Main function for bafview program.                             */
/*                                                                           */
/* Returns:   0                                                              */
/*                                                                           */
/* Params:    IN     argc         - Number of arguments (including           */
/*                                  executable name)                         */
/*            IN     argv         - Pointer to array of arguments (including */
/*                                  executable name)                         */
/*                                                                           */
/* Operation: Check that bafview has been called with the correct command    */
/*            line paramteres.  If it hasn't output usage and exit.          */
/*                                                                           */
/*            Decode each file that we are passed.                           */
/*                                                                           */
/**PROC-**********************************************************************/

int main(int argc, char *argv[])
{
  /***************************************************************************/
  /* Local variables                                                         */
  /***************************************************************************/
  NBB_INT ii;
  NBB_BOOL usage_error = TRUE;
  NBB_BOOL merge_files = FALSE;
  NBB_BOOL first_file_merged = FALSE;
  NBB_CHAR filename_scratch[BAF_FILE_NAME_SCRATCH_SIZE];
  FILE *output_file = NULL;
  NBB_BYTE start_records;
  NBB_INT last_file = 0;
  NBB_BOOL output_start_records = FALSE;
  NBB_ULONG record_count = 0;
  NBB_ULONG file_sequence_number = 0;

  /***************************************************************************/
  /* Initialize structures used by bafview.                                  */
  /***************************************************************************/
  baf_initialize();

  /***************************************************************************/
  /* Check command line options.                                             */
  /***************************************************************************/
  if (argc > 1)
  {
    usage_error = FALSE;

    for (ii = 1; ii < argc; ii++)
    {
      if (argv[ii][0] == '-')
      {
        switch (argv[ii][1])
        {
          case 'v':
          case 'V':
            baf_verbose = TRUE;
            break;

          case 'd':
          case 'D':
            baf_dump = TRUE;
            break;

          case 'm':
          case 'M':
            merge_files = TRUE;
            break;

          case 's':
          case 'S':
            baf_stats = TRUE;
            break;

          default:
            baf_print("Invalid option selected: %s\n", argv[ii]);
            usage_error = TRUE;
            goto EXIT_LABEL;
            /* break; */
        }
      }
    }
  }

  if (((merge_files) && ((baf_verbose) || (baf_dump) || (baf_stats))) ||
      ((baf_stats) && ((baf_verbose) || (baf_dump) || (merge_files))))
  {
    /*************************************************************************/
    /* Merge files and statistics output are not compatible with any other   */
    /* option.                                                               */
    /*************************************************************************/
    usage_error = TRUE;
  }

  if (usage_error)
  {
    goto EXIT_LABEL;
  }

  if (!merge_files)
  {
    /*************************************************************************/
    /* Anything that isn't a command line option must be a filename.  Decode */
    /* each file.                                                            */
    /*************************************************************************/
    for (ii = 1; ii < argc; ii++)
    {
      if (argv[ii][0] != '-')
      {
        baf_decode_file(argv[ii]);
      }
    }
  }
  else
  {
    /*************************************************************************/
    /* Files are being merged.  Check that there are at least two filenames  */
    /* supplied (as well as the -m parameter).                               */
    /*************************************************************************/
    if (argc < 4)
    {
      baf_print("Files not merged as only one filename was supplied.\n");
      goto EXIT_LABEL;
    }

    /*************************************************************************/
    /* Determine whether start and end records should be included by         */
    /* checking the first and last files.                                    */
    /*************************************************************************/
    for (ii = 1; ii < argc; ii++)
    {
      /***********************************************************************/
      /* Find the first merged file.                                         */
      /***********************************************************************/
      if (argv[ii][0] != '-')
      {
        start_records = baf_check_start_records(argv[ii]);
        if (start_records == BAF_START_END_RC_YES)
        {
          output_start_records = TRUE;
        }

        break;
      }
    }

    if (output_start_records)
    {
      for (ii = 1; ii < (argc - 1); ii++)
      {
        /*********************************************************************/
        /* Find the last merged file.                                        */
        /*********************************************************************/
        if (argv[argc - ii][0] != '-')
        {
          start_records = baf_check_start_records(argv[argc - ii]);
          if (start_records == BAF_START_END_RC_YES)
          {
            last_file = argc - ii;
            break;
          }
          else if (start_records == BAF_START_END_RC_NO)
          {
            output_start_records = FALSE;
            break;
          }
        }
      }
    }

    for (ii = 1; ii < argc; ii++)
    {
      if (argv[ii][0] != '-')
      {
        if (!first_file_merged)
        {
          /*******************************************************************/
          /* Create a backup of the first file in case there is there is a   */
          /* problem.                                                        */
          /*******************************************************************/
          OS_MEMSET(filename_scratch, 0, BAF_FILE_NAME_SCRATCH_SIZE);
          if (OS_STRLEN(argv[ii]) > (BAF_FILE_NAME_SCRATCH_SIZE - 4))
          {
            baf_print("Filename %s is too long\n", argv[ii]);
            goto EXIT_LABEL;
          }

          OS_MEMCPY(filename_scratch, argv[ii], OS_STRLEN(argv[ii]));
          OS_STRCAT(filename_scratch, ".bak");

          if (OS_RENAME(argv[ii], filename_scratch) != 0)
          {
            baf_print("Failed to rename %s to %s.\n", argv[ii], filename_scratch);
            goto EXIT_LABEL;
          }

          /*******************************************************************/
          /* Open a new version of the first file and copy in the complete   */
          /* records from the backup file.                                   */
          /*******************************************************************/
          output_file = OS_FOPEN(argv[ii], "w");

          if (output_file == NULL)
          {
            baf_print("Failed to open output file %s.\n", argv[ii]);
            goto EXIT_LABEL;
          }

          /*******************************************************************/
          /* Copy the records across.                                        */
          /*******************************************************************/
          baf_merge_file(&output_file,
                         filename_scratch,
                         output_start_records,
                         &record_count,
                         &file_sequence_number,
                         TRUE,
                         (ii == last_file));

          first_file_merged = TRUE;
        }
        else
        {
          /*******************************************************************/
          /* Copy the records across.                                        */
          /*******************************************************************/
          baf_merge_file(&output_file,
                         argv[ii],
                         output_start_records,
                         &record_count,
                         &file_sequence_number,
                         FALSE,
                         (ii == last_file));
        }
      }
    }

    if (output_file != NULL)
    {
      OS_FCLOSE(output_file);
    }
  }

EXIT_LABEL:

  if (usage_error)
  {
    baf_print(BAF_DISCLAIMER);
    baf_print("Usage:   bafview <billing file> [[-v] [-d] | [-s] | "
           "[-m <intermediate files>]]\n");
    baf_print("         -v gives verbose output\n");
    baf_print("         -d to include byte dump\n");
    baf_print("         -m to merge billing records from intermediate files into "
           "billing file.\n");
    baf_print("         -s to decode and print only records used for traffic "
           "statistics\n            calculation.\n");
    baf_print("Build:   %s %s\n",__DATE__,__TIME__);
    baf_print("Purpose: Decodes AMA billing recordings produced by the "
           "MetaSwitch NE.\n");
    baf_print("         May also decode AMA billing recording produced by other "
           "Telcordia\n");
    baf_print("         GR-1100 compliant Class 5 switches.\n");
  }

  return(0);
} /* main */
