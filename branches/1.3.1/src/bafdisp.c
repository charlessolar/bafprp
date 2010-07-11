/**MOD+***********************************************************************/
/* Module:    bafdisp.c                                                      */
/*                                                                           */
/* Purpose:   Functions to display fields - there is no decoding done in     */
/*            this module.                                                   */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2005                         */
/*                                                                           */
/* $Revision::   1.13               $ $Modtime::   Jul 19 2005 09:59:14   $  */
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
/* Name:      baf_display_class_feature_code                                 */
/*                                                                           */
/* Purpose:   Display a text string describing a BAF feature code (table     */
/*            415).                                                          */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_display_class_feature_code(NBB_UINT class_feature_code)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/

  switch (class_feature_code)
  {
    case 1:
      baf_verbose ? printf("Outgoing call barring daily contination\n") :
                    printf("OCB daily  : ");
      break;

    case 2:
      baf_verbose ? printf("Outgoing call barring activation\n") :
                    printf("OCB act    : ");
      break;

    case 3:
      baf_verbose ? printf("Outgoing call barring deactivation\n") :
                    printf("OCB deact  : ");
      break;

    case 32:
      baf_verbose ? printf("AR reactivation, delayed processing, setup\n") :
                    printf("AR react   : ");
      break;

    case 33:
      baf_verbose ? printf("AC reactivation, delayed processing, setup\n") :
                    printf("AC react   : ");
      break;

    case 34:
      baf_verbose ? printf("AR reactivation, busy ringback, no scanning\n") :
                    printf("AR react   : ");
      break;

    case 35:
      baf_verbose ? printf("AC reactivation, busy ringback, no scanning\n") :
                    printf("AC react   : ");
      break;

    case 36:
      baf_verbose ? printf("AR reactivation, delayed processing, timeout\n") :
                    printf("AR react   : ");
      break;

    case 37:
      baf_verbose ? printf("AC reactivation, delayed processing, timeout\n") :
                    printf("AC react   : ");
      break;

    case 38:
      baf_verbose ? printf("AR reactivation, delayed processing, de/react\n") :
                    printf("AR react   : ");
      break;

    case 39:
      baf_verbose ? printf("AC reactivation, delayed processing, de/react\n") :
                    printf("AC react   : ");
      break;

    case 52:
      baf_verbose ? printf("Selective call forwarding\n") :
                    printf("SCF        : ");
      break;

    case 57:
      baf_verbose ? printf("Anonymous call rejection activation\n") :
                    printf("ACR on     : ");
      break;

    case 58:
      baf_verbose ? printf("Anonymous call rejection deactivation\n") :
                    printf("ACR off    : ");
      break;

    case 59:
      baf_verbose ? printf("Anonymous call rejection continuation\n") :
                    printf("ACR cont   : ");
      break;

    case 60:
      baf_verbose ? printf("AR activation, immediate processing, setup\n") :
                    printf("AR act     : ");
      break;

    case 61:
      baf_verbose ? printf("AC activation, immediate processing, setup\n") :
                    printf("AC act     : ");
      break;

    case 62:
      baf_verbose ? printf("AR activation, delayed processing, setup\n") :
                    printf("AR act     : ");
      break;

    case 63:
      baf_verbose ? printf("AC activation, delayed processing, setup\n") :
                    printf("AC act     : ");
      break;

    case 64:
      baf_verbose ? printf("AR activation, busy ringback, no scanning\n") :
                    printf("AR act     : ");
      break;

    case 65:
      baf_verbose ? printf("AC activation, busy ringback, no scanning\n") :
                    printf("AC act     : ");
      break;

    case 66:
      baf_verbose ? printf("AR activation, delayed processing, timeout\n") :
                    printf("AR act     : ");
      break;

    case 67:
      baf_verbose ? printf("AC activation, delayed processing, timeout\n") :
                    printf("AC act     : ");
      break;

    case 68:
      baf_verbose ? printf("AR activation, delayed processing, de/react\n") :
                    printf("AR act     : ");
      break;

    case 69:
      baf_verbose ? printf("AC activation, delayed processing, de/react\n") :
                    printf("AC act     : ");
      break;

    case 70:
      baf_verbose ? printf("Customer originated trace activation\n") :
                    printf("COT act    : ");
      break;

    case 72:
      baf_verbose ? printf("Selective call rejection\n") :
                    printf("SCR        : ");
      break;

    case 73:
      baf_verbose ? printf("Distinctive Ringing / Call Waiting\n") :
                    printf("DRCW       : ");
      break;

    case 74:
      baf_verbose ? printf("Screen List editing daily contination\n") :
                    printf("SLE daily  : ");
      break;

    case 75:
      baf_verbose ? printf("Calling number delivery blocking activation\n") :
                    printf("CNDB act   : ");
      break;

    case 79:
      baf_verbose ? printf("Selective call acceptance\n") :
                    printf("SCA        : ");
      break;

    case 80:
      baf_verbose ? printf("Calling number delivery\n") :
                    printf("CND        : ");
      break;

    case 82:
      baf_verbose ? printf("Calling name delivery\n") :
                    printf("CNAM       : ");
      break;

    case 85:
      baf_verbose ? printf("Calling identity delivery and suppression\n") :
                    printf("CIDS       : ");
      break;

    case 95:
      baf_verbose ? printf("AR two-level activation\n") :
                    printf("AR act     : ");
      break;

    default:
      baf_verbose ? printf("Error - unknown CLASS feature code %d\n",
                           class_feature_code) :
                    printf("Unknown    : ");
      break;
  }

  return;

} /* baf_display_class_feature_code */

/**PROC+**********************************************************************/
/* Name:      baf_display_service_feature_code                               */
/*                                                                           */
/* Purpose:   Display a text string describing a service feature code (table */
/*            12).                                                           */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_display_service_feature_code(NBB_UINT service_feature_code)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/

  switch (service_feature_code)
  {
    case 0:
      baf_verbose ? printf("None\n") :
                    printf("normal     : ");
      break;

    case 10:
      baf_verbose ? printf("Three way calling\n") :
                    printf("three-way  : ");
      break;

    case 12:
      baf_verbose ? printf("Unconditional call forwarding\n") :
                    printf("uncon-fwd  : ");
      break;

    case 14:
      baf_verbose ? printf("Busy or delay call forwarding\n") :
                    printf("b/d-fwd    : ");
      break;

    case 18:
      baf_verbose ? printf("Three way calling usage\n") :
                    printf("three-way usage  : ");
      break;

    case 27:
      baf_verbose ? printf("Advanced Intelligent Network - Default\n") :
                    printf("AIN        : ");
      break;

    case 801:
      baf_verbose ? printf("Basic line hunting (MetaSwitch specific)\n") :
                    printf("Hunting    : ");
      break;

    case 802:
      baf_verbose ? printf("Find-me-follow-me (MetaSwitch specific)\n") :
                    printf("Find-me-follow-me : ");
      break;

    default:
      baf_verbose ? printf("Error - unknown service feature code %d\n",
                           service_feature_code) :
                    printf("unknown    : ");
      break;
  }

  return;

} /* baf_display_service_feature_code */
