/**MOD+***********************************************************************/
/* Module:    bafutil.c                                                      */
/*                                                                           */
/* Purpose:   General utility functions for bafview.                         */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2005                         */
/*                                                                           */
/* $Revision::   1.21               $ $Modtime::   09 Sep 2005 14:15:50   $  */
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
    printf("Couldn't get structure type %2.2x%2.2x%2.2x\n",
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
    printf("Couldn't get call type %2.2x%2.2x\n",
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
  /* Output some helpful descriptive text, baed on call type and structure   */
  /* type.                                                                   */
  /***************************************************************************/
  switch (call_type)
  {
    case 1:
      baf_verbose ? printf("Message rate call with MBI\n") :
                    printf("Msg rate MBI: ");
      break;

    case 5:
      /***********************************************************************/
      /* Call type 005.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Local message rate call\n") :
                    printf("Local call  : ");
      break;

    case 6:
      /***********************************************************************/
      /* Call type 006.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Toll call or non-US\n") :
                    printf("Toll call   : ");
      break;

    case 9:
      /***********************************************************************/
      /* Call type 009.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("411 Directory Assistance\n") :
                    printf("411 DA call : ");
      break;

    case 26:
      /***********************************************************************/
      /* Call type 026.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Conference Trunk Usage\n") :
                    printf("Conference  : ");
      break;

    case 31:
      /***********************************************************************/
      /* Call type 330 - need to check the structure.                        */
      /***********************************************************************/
      if (structure_type == 96)
      {
        baf_verbose ? printf("Call forwarding deactivation\n") :
                      printf("Forward off : ");
      }
      else if (structure_type == 614)
      {
        baf_verbose ? printf("Call forwarding activation\n") :
                      printf("Forward on  : ");
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
      baf_verbose ? printf("555 Directory Assistance\n") :
                    printf("555 DA call : ");
      break;

    case 42:
      /***********************************************************************/
      /* Call type 042.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Time change marker\n") :
                    printf("Time change : ");
      break;

    case 45:
      /***********************************************************************/
      /* Call type 045.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("ISDN call\n") :
                    printf("ISDN call   : ");
      break;

    case 47:
      /***********************************************************************/
      /* Call type 047.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Default AIN\n") :
                    printf("Default AIN : ");
      break;

    case 48:
      /***********************************************************************/
      /* Call type 048.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Conference resource usage\n") :
                    printf("Conference resource usage : ");
      break;

    case 49:
      /***********************************************************************/
      /* Call type 049.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Conference resource usage\n") :
                    printf("Conference resource usage : ");
      break;

    case 88:
      /***********************************************************************/
      /* Call type 088.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("555 Non-Directory Assistance\n") :
                    printf("555 Non-DA  : ");
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
        baf_verbose ? printf("Sensor Audit Record\n") :
                      printf("--- Audit   : ");
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
        baf_verbose ? printf("File start marker\n") :
                      printf("=== File start marker : ");
      }
      else if (structure_type == 9014)
      {
        /*********************************************************************/
        /* Structure 9014, call type 092.                                    */
        /*********************************************************************/
        baf_verbose ? printf("File end marker\n") :
                      printf("=== File end marker : ");
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
      baf_verbose ? printf("Interlata call\n") :
                    printf("Interlata   : ");
      break;

    case 119:
      /***********************************************************************/
      /* Call type 119.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Incoming CDR\n") :
                    printf("Incoming    : ");
      break;

    case 123:
      /***********************************************************************/
      /* Call type 123.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("CLASS feature activation\n") :
                    printf("CLASS act.  : ");
      break;

    case 131:
      /***********************************************************************/
      /* Call type 131.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Feature Group A - Originating\n") :
                    printf("Feat A Orig : ");
      break;

    case 132:
      /***********************************************************************/
      /* Call type 132.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Feature Group A - Terminating\n") :
                    printf("Feat A Term : ");
      break;

    case 134:
      /***********************************************************************/
      /* Call type 134.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("FGB call - Originating\n") :
                    printf("FGB Orig    : ");
      break;

    case 135:
      /***********************************************************************/
      /* Call type 135.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("FGB call - Terminating\n") :
                    printf("FGB Term    : ");
      break;

    case 141:
      /***********************************************************************/
      /* Call type 141.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Interexchange Carrier Number Services\n") :
                    printf("IC Num Servs: ");
      break;

    case 142:
      /***********************************************************************/
      /* Call type 142.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Local Exchange Carrier Number Services\n") :
                    printf("LEC Num Serv: ");
      break;

    case 264:
      baf_verbose ? printf("Calling Identity Delivery record\n") :
                    printf("CLASS (CLI) : ");
      break;

    case 330:
      /***********************************************************************/
      /* Call type 330 - need to check the structure.                        */
      /***********************************************************************/
      if (structure_type == 1030)
      {
        baf_verbose ? printf("CLASS functions call structure 1030\n") :
                      printf("CLASS usage : ");
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
          baf_verbose ? printf("CLASS feature: Outgoing Call Barring\n") :
                        printf("CLASS (OCB) : ");
        }
        else
        {
          baf_verbose ? printf("CLASS feature: Anonymous call rejection\n") :
                        printf("CLASS (ACR) : ");
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
      baf_verbose ? printf("Bulk Calling Identity statistics\n") :
                    printf("CLASS (BCLI): ");
      break;

    case 710:
      /***********************************************************************/
      /* Call type 710.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Originating Toll AMA Record\n") :
                    printf("Orig Toll   : ");
      break;

    case 711:
      /***********************************************************************/
      /* Call type 711.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Terminating Toll AMA Record\n") :
                    printf("Term Toll   : ");
      break;

    case 720:
      /***********************************************************************/
      /* Call type 720.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Connecting Network Access Incoming Record\n") :
                    printf("CNA         : ");
      break;

    case 721:
      /***********************************************************************/
      /* Call type 721.                                                      */
      /***********************************************************************/
      baf_verbose ? printf("Default Local Number Portability\n") :
                    printf("LNP         : ");
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
    baf_verbose ? printf("*** Unsupported call type %d / structure code %d\n",
                         call_type,
                         structure_type) :
                  printf("Unsupported : ");
  }

EXIT_LABEL:

  return(decode_type);

} /* baf_get_decode_type */
