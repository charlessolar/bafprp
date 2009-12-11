
/**MOD+***********************************************************************/
/* Module:    bafmain.c                                                      */
/*                                                                           */
/* Purpose:   To decode and output formatted billing records.                */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2003, 2005                   */
/*                                                                           */
/* $Revision::   1.10               $ $Modtime::   28 Jun 2005 12:30:34   $  */
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

  printf("\nbafview v%s Copyright (c) Data Connection Ltd 2002\n\n",
         BAFVIEW_VERSION);

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

          default:
            printf("Invalid option selected: %s\n", argv[ii]);
            usage_error = TRUE;
            goto EXIT_LABEL;
            /* break; */
        }
      }
    }
  }

  if (usage_error)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Anything that isn't a command line option must be a filename.  Decode   */
  /* each file.                                                              */
  /***************************************************************************/
  for (ii = 1; ii < argc; ii++)
  {
    if (argv[ii][0] != '-')
    {
      baf_decode_file(argv[ii]);
    }
  }

EXIT_LABEL:

  if (usage_error)
  {
    printf("Usage:   bafview <billing file> [-v] [-d]\n");
    printf("         -v gives verbose output\n");
    printf("         -d to include byte dump\n");
    printf("Version: %s\n", BAFVIEW_VERSION);
    printf("Purpose: Decodes AMA billing recordings produced by the "
           "MetaSwitch VP3000.\n");
    printf("         May also decode AMA billing recording produced by other "
           "Telcordia\n");
    printf("         GR-1100 compliant Class 5 switches.\n");
  }

  return(0);
}
