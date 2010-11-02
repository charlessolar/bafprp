/**MOD+***********************************************************************/
/* Module:    bafdisp.c                                                      */
/*                                                                           */
/* Purpose:   Functions to display fields - there is no decoding done in     */
/*            this module.                                                   */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: bafdisp.c 1044 2008-09-20 03:52:52Z vpgbuild                     $  */
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
      baf_verbose ? baf_print("Outgoing call barring daily contination\n") :
                    baf_print("OCB daily  : ");
      break;

    case 2:
      baf_verbose ? baf_print("Outgoing call barring activation\n") :
                    baf_print("OCB act    : ");
      break;

    case 3:
      baf_verbose ? baf_print("Outgoing call barring deactivation\n") :
                    baf_print("OCB deact  : ");
      break;

    case 32:
      baf_verbose ? baf_print("AR reactivation, delayed processing, setup\n") :
                    baf_print("AR react   : ");
      break;

    case 33:
      baf_verbose ? baf_print("AC reactivation, delayed processing, setup\n") :
                    baf_print("AC react   : ");
      break;

    case 34:
      baf_verbose ? baf_print("AR reactivation, busy ringback, no scanning\n") :
                    baf_print("AR react   : ");
      break;

    case 35:
      baf_verbose ? baf_print("AC reactivation, busy ringback, no scanning\n") :
                    baf_print("AC react   : ");
      break;

    case 36:
      baf_verbose ? baf_print("AR reactivation, delayed processing, timeout\n") :
                    baf_print("AR react   : ");
      break;

    case 37:
      baf_verbose ? baf_print("AC reactivation, delayed processing, timeout\n") :
                    baf_print("AC react   : ");
      break;

    case 38:
      baf_verbose ? baf_print("AR reactivation, delayed processing, de/react\n") :
                    baf_print("AR react   : ");
      break;

    case 39:
      baf_verbose ? baf_print("AC reactivation, delayed processing, de/react\n") :
                    baf_print("AC react   : ");
      break;

    case 52:
      baf_verbose ? baf_print("Selective call forwarding\n") :
                    baf_print("SCF        : ");
      break;

    case 57:
      baf_verbose ? baf_print("Anonymous call rejection activation\n") :
                    baf_print("ACR on     : ");
      break;

    case 58:
      baf_verbose ? baf_print("Anonymous call rejection deactivation\n") :
                    baf_print("ACR off    : ");
      break;

    case 59:
      baf_verbose ? baf_print("Anonymous call rejection continuation\n") :
                    baf_print("ACR cont   : ");
      break;

    case 60:
      baf_verbose ? baf_print("AR activation, immediate processing, setup\n") :
                    baf_print("AR act     : ");
      break;

    case 61:
      baf_verbose ? baf_print("AC activation, immediate processing, setup\n") :
                    baf_print("AC act     : ");
      break;

    case 62:
      baf_verbose ? baf_print("AR activation, delayed processing, setup\n") :
                    baf_print("AR act     : ");
      break;

    case 63:
      baf_verbose ? baf_print("AC activation, delayed processing, setup\n") :
                    baf_print("AC act     : ");
      break;

    case 64:
      baf_verbose ? baf_print("AR activation, busy ringback, no scanning\n") :
                    baf_print("AR act     : ");
      break;

    case 65:
      baf_verbose ? baf_print("AC activation, busy ringback, no scanning\n") :
                    baf_print("AC act     : ");
      break;

    case 66:
      baf_verbose ? baf_print("AR activation, delayed processing, timeout\n") :
                    baf_print("AR act     : ");
      break;

    case 67:
      baf_verbose ? baf_print("AC activation, delayed processing, timeout\n") :
                    baf_print("AC act     : ");
      break;

    case 68:
      baf_verbose ? baf_print("AR activation, delayed processing, de/react\n") :
                    baf_print("AR act     : ");
      break;

    case 69:
      baf_verbose ? baf_print("AC activation, delayed processing, de/react\n") :
                    baf_print("AC act     : ");
      break;

    case 70:
      baf_verbose ? baf_print("Customer originated trace activation\n") :
                    baf_print("COT act    : ");
      break;

    case 72:
      baf_verbose ? baf_print("Selective call rejection\n") :
                    baf_print("SCR        : ");
      break;

    case 73:
      baf_verbose ? baf_print("Distinctive Ringing / Call Waiting\n") :
                    baf_print("DRCW       : ");
      break;

    case 74:
      baf_verbose ? baf_print("Screen List editing daily contination\n") :
                    baf_print("SLE daily  : ");
      break;

    case 75:
      baf_verbose ? baf_print("Calling number delivery blocking activation\n") :
                    baf_print("CNDB act   : ");
      break;

    case 79:
      baf_verbose ? baf_print("Selective call acceptance\n") :
                    baf_print("SCA        : ");
      break;

    case 80:
      baf_verbose ? baf_print("Calling number delivery\n") :
                    baf_print("CND        : ");
      break;

    case 82:
      baf_verbose ? baf_print("Calling name delivery\n") :
                    baf_print("CNAM       : ");
      break;

    case 85:
      baf_verbose ? baf_print("Calling identity delivery and suppression\n") :
                    baf_print("CIDS       : ");
      break;

    case 95:
      baf_verbose ? baf_print("AR two-level activation\n") :
                    baf_print("AR act     : ");
      break;

    default:
      baf_verbose ? baf_print("Error - unknown CLASS feature code %d\n",
                           class_feature_code) :
                    baf_print("Unknown    : ");
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
      baf_verbose ? baf_print("None\n") :
                    baf_print("normal     : ");
      break;

    case 10:
      baf_verbose ? baf_print("Three way calling\n") :
                    baf_print("three-way  : ");
      break;

    case 12:
      baf_verbose ? baf_print("Unconditional call forwarding\n") :
                    baf_print("uncon-fwd  : ");
      break;

    case 14:
      baf_verbose ? baf_print("Busy or delay call forwarding\n") :
                    baf_print("b/d-fwd    : ");
      break;

    case 18:
      baf_verbose ? baf_print("Three way calling usage\n") :
                    baf_print("three-way usage  : ");
      break;

    case 27:
      baf_verbose ? baf_print("Advanced Intelligent Network - Default\n") :
                    baf_print("AIN        : ");
      break;

    case 801:
      baf_verbose ? baf_print("Basic line hunting (MetaSwitch specific)\n") :
                    baf_print("Hunting    : ");
      break;

    case 802:
      baf_verbose ? baf_print("Find-me-follow-me (MetaSwitch specific)\n") :
                    baf_print("Find-me-follow-me : ");
      break;

    default:
      baf_verbose ? baf_print("Error - unknown service feature code %d\n",
                           service_feature_code) :
                    baf_print("unknown    : ");
      break;
  }

  return;

} /* baf_display_service_feature_code */
