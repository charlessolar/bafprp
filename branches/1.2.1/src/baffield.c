
/**MOD+***********************************************************************/
/* Module:    baffield.c                                                     */
/*                                                                           */
/* Purpose:   Functions to decode tables from BAF records.                   */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2001 - 2005                         */
/*                                                                           */
/* $Revision::   1.23               $ $Modtime::   08 Jul 2005 14:54:14   $  */
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

/*****************************************************************************/
/* Global variable used to remember the last overseas indicator decoded.     */
/*****************************************************************************/
NBB_UINT global_overseas_ind = 0;

/**PROC+**********************************************************************/
/* Name:      baf_decode_structure_type                                      */
/*                                                                           */
/* Purpose:   Decoder for the structure type field.                          */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_structure_type(NBB_BYTE **input,
                                   NBB_LONG *length,
                                   NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_LONG structure_type;
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get structure type.                                                     */
  /***************************************************************************/
  if (!baf_get_structure_type(*input, &structure_type, *length))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: %d\n", BAF_FIELD_NAME(field), structure_type);
  }
  (*input) += 3;
  (*length) -= 3;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_structure_type */

/**PROC+**********************************************************************/
/* Name:      baf_decode_call_type                                           */
/*                                                                           */
/* Purpose:   Decoder for the call type field.                               */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_call_type(NBB_BYTE **input,
                              NBB_LONG *length,
                              NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_ULONG call_type;
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get call type.                                                          */
  /***************************************************************************/
  if ((*length < 2) ||
      (((*input)[1] & 0x0F) != 0x0C))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }
  baf_get_chars(*input, 1, 3, &call_type);

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: %d\n", BAF_FIELD_NAME(field), call_type);
  }
  (*input) += 2;
  (*length) -= 2;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_call_type */

/**PROC+**********************************************************************/
/* Name:      baf_decode_class_feature_code                                  */
/*                                                                           */
/* Purpose:   Decoder for the CLASS feature code field.                      */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_class_feature_code(NBB_BYTE **input,
                                       NBB_LONG *length,
                                       NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_ULONG class_feature_code;
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get call type.                                                          */
  /***************************************************************************/
  if ((*length < 2) ||
      (((*input)[1] & 0x0F) != 0x0C))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }
  baf_get_chars(*input, 1, 3, &class_feature_code);

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: ", BAF_FIELD_NAME(field));
  }
  baf_display_class_feature_code(class_feature_code);
  (*input) += 2;
  (*length) -= 2;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_class_feature_code */

/**PROC+**********************************************************************/
/* Name:      baf_decode_service_feature_code                                */
/*                                                                           */
/* Purpose:   Decoder for the Service feature code field (table 12).         */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_service_feature_code(NBB_BYTE **input,
                                         NBB_LONG *length,
                                         NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_ULONG service_feature_code;
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get call type.                                                          */
  /***************************************************************************/
  if ((*length < 2) ||
      (((*input)[1] & 0x0F) != 0x0C))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }
  baf_get_chars(*input, 1, 3, &service_feature_code);

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: ", BAF_FIELD_NAME(field));
  }
  baf_display_service_feature_code(service_feature_code);
  (*input) += 2;
  (*length) -= 2;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_service_feature_code */

/**PROC+**********************************************************************/
/* Name:      baf_decode_calling_number                                      */
/*                                                                           */
/* Purpose:   Decoder for the calling number.                                */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_calling_number(NBB_BYTE **input,
                                   NBB_LONG *length,
                                   NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_CHAR number[16];
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get call type.                                                          */
  /***************************************************************************/
  if (!baf_get_calling_number(*input, number, *length))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: %s\n", BAF_FIELD_NAME(field), number);
  }
  else
  {
    printf("%s ", number);
  }

  (*input) += 6;
  (*length) -= 6;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_calling_number */

/**PROC+**********************************************************************/
/* Name:      baf_decode_overseas_ind                                        */
/*                                                                           */
/* Purpose:   Decoder for the overseas indicator.                            */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_overseas_ind(NBB_BYTE **input,
                                 NBB_LONG *length,
                                 NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_CHAR number[2];
  NBB_UINT overseas_ind;
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get overseas indicator.                                                 */
  /***************************************************************************/
  if (!baf_get_overseas_ind(*input, number, *length))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  overseas_ind = number[0];
  global_overseas_ind = overseas_ind;

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s : %s\n", BAF_FIELD_NAME(field),
                  baf_field_list[field].displays[0].values[overseas_ind].name);
  }

  (*input) += 1;
  (*length) -= 1;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_overseas_ind */

/**PROC+**********************************************************************/
/* Name:      baf_decode_called_number                                       */
/*                                                                           */
/* Purpose:   Decoder for the called number.                                 */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_called_number(NBB_BYTE **input,
                                  NBB_LONG *length,
                                  NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_CHAR number[16];
  NBB_BOOL ret_code = FALSE;

  /***************************************************************************/
  /* Get call type.                                                          */
  /***************************************************************************/
  if (!baf_get_called_number(*input, number, *length))
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not read %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: %s\n", BAF_FIELD_NAME(field), number);
  }
  else
  {
    printf("-> %s : ", number);
  }
  (*input) += 7;
  (*length) -= 7;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_called_number */

/**PROC+**********************************************************************/
/* Name:      baf_decode_length                                              */
/*                                                                           */
/* Purpose:   Decoder for the length fields                                  */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_length(NBB_BYTE **input,
                           NBB_LONG *length,
                           NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BOOL ret_code = FALSE;
  NBB_CHAR decoded_length[16];
  NBB_BYTE get_length_rc;

  get_length_rc = baf_get_length(*input, decoded_length, *length);

  if (get_length_rc == BAF_FIELD_ERROR)
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not decode %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  if (get_length_rc == BAF_FIELD_NOT_USED)
  {
    if (baf_verbose)
    {
      printf("%s: Field not used\n", BAF_FIELD_NAME(field));
    }
    *input += 5;
    *length -= 5;
    ret_code = TRUE;
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: %s\n", BAF_FIELD_NAME(field), decoded_length);
  }
  else if (field == BAF_F_019_CALL_LENGTH)
  {
    printf("%s : ", decoded_length);
  }

  *input += 5;
  *length -= 5;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_length */

/**PROC+**********************************************************************/
/* Name:      baf_get_structure_type                                         */
/*                                                                           */
/* Purpose:   Gets the structure type of a call record.                      */
/*                                                                           */
/* Returns:   TRUE if successful, FALSE if the record is too short, or       */
/*            doesn't contain a valid value.                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing structure    */
/*                                  type                                     */
/*            OUT    output       - Pointer to the structure type            */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the structure type.     */
/*            Put each digit of the structure type in a separate byte in a   */
/*            temporary array.                                               */
/*            Combine the new array of digits into a long and return.        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_get_structure_type(NBB_BYTE *input,
                                NBB_LONG *output,
                                NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BOOL rc = FALSE;
  NBB_INT temp[5];

  if (length < 3)
  {
    goto EXIT_LABEL;
  }

  temp[0] = (input[0] & 0x0F);
  temp[1] = (input[1] & 0xF0) >> 4;
  temp[2] = (input[1] & 0x0F);
  temp[3] = (input[2] & 0xF0) >> 4;
  temp[4] = (input[2] & 0x0F);

  if (temp[4] != 0x0C)
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  *output = temp[3] + (10 * temp[2]) + (100 * temp[1]) + (1000 * temp[0]);
  rc = TRUE;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_decode_date                                                */
/*                                                                           */
/* Purpose:   Decoder for the date field.                                    */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_date(NBB_BYTE **input, NBB_LONG *length, NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BOOL ret_code = FALSE;
  NBB_LONG year;
  NBB_LONG day;
  NBB_CHAR month[32] = {0};
  NBB_CHAR concise_string[64];
  NBB_BYTE get_date_rc;

  get_date_rc = baf_get_date(*input, &year, month, &day, *length);

  if (get_date_rc == BAF_FIELD_ERROR)
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not get %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  if (get_date_rc == BAF_FIELD_NOT_USED)
  {
    if (baf_verbose)
    {
      printf("%s: Field not used\n", BAF_FIELD_NAME(field));
    }
    (*input) += 3;
    (*length) -= 3;
    ret_code = TRUE;
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    if ((day == 0) &&
        (year == BAF_START_OF_CURRENT_DECADE) &&
        (month[0] == 0))
    {
      printf("%s: No date specified\n", BAF_FIELD_NAME(field));
    }
    else
    {
      printf("%s: %d %s %d\n", BAF_FIELD_NAME(field), day, month, year);
    }
  }
  else if (field == BAF_F_006_DATE)
  {
    /*************************************************************************/
    /* Note that the date is carefully formatted to look nice in this        */
    /* concise version.                                                      */
    /*************************************************************************/
    if ((day == 0) &&
        (year == BAF_START_OF_CURRENT_DECADE) &&
        (month[0] == 0))
    {
      sprintf(concise_string, "No date specified", day, month, year);
    }
    else
    {
      sprintf(concise_string, "%d %s %d", day, month, year);
    }
    printf("%-17s : ", concise_string);
  }

  (*input) += 3;
  (*length) -= 3;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_date */

/**PROC+**********************************************************************/
/* Name:      baf_decode_time                                                */
/*                                                                           */
/* Purpose:   Decoder for the time field.                                    */
/*                                                                           */
/* Returns:                                                                  */
/*                                                                           */
/* Params:                                                                   */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_decode_time(NBB_BYTE **input, NBB_LONG *length, NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BOOL ret_code = FALSE;
  NBB_CHAR time[16];
  NBB_BYTE get_time_rc;

  get_time_rc = baf_get_time(*input, time, *length);

  if (get_time_rc == BAF_FIELD_ERROR)
  {
    BAF_ERROR_IN_RECORD(("Error in record - could not get %s\n",
                         BAF_FIELD_NAME(field)));
    goto EXIT_LABEL;
  }

  if (get_time_rc == BAF_FIELD_NOT_USED)
  {
    if (baf_verbose)
    {
      printf("%s: Field not used\n", BAF_FIELD_NAME(field));
    }
    (*input) += 4;
    (*length) -= 4;
    ret_code = TRUE;
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Success.                                                                */
  /***************************************************************************/
  if (baf_verbose)
  {
    printf("%s: %s\n", BAF_FIELD_NAME(field), time);
  }
  else if (field == BAF_F_018_TIME)
  {
    printf("%s : ", time);
  }

  (*input) += 4;
  (*length) -= 4;
  ret_code = TRUE;

EXIT_LABEL:

  return(ret_code);

} /* baf_decode_time */

/**PROC+**********************************************************************/
/* Name:      baf_get_date                                                   */
/*                                                                           */
/* Purpose:   Gets the date of a call record.                                */
/*                                                                           */
/* Returns:   One of                                                         */
/*                                                                           */
/*            BAF_FIELD_OK if successful                                     */
/*                                                                           */
/*            BAF_FIELD_NOT_USED if the field is not used                    */
/*                                                                           */
/*            BAF_FIELD_ERROR if the record is too short, or doesn't contain */
/*            a valid value.                                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing date         */
/*            OUT    year         - Pointer to the year                      */
/*            OUT    month        - Pointer to the month                     */
/*            OUT    day          - Pointer to the day                       */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the date.  Put each     */
/*            digit of the date in a separate byte in a temporary array.     */
/*            Extract the year, month and day and return.                    */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BYTE baf_get_date(NBB_BYTE *input,
                      NBB_LONG *year,
                      NBB_CHAR *month,
                      NBB_LONG *day,
                      NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BYTE rc = BAF_FIELD_ERROR;
  NBB_INT temp[6];
  NBB_LONG temp_month;

  if (length < 3)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Split out the encoding.                                                 */
  /***************************************************************************/
  temp[0] = (input[0] & 0xF0) >> 4;
  temp[1] = (input[0] & 0x0F);
  temp[2] = (input[1] & 0xF0) >> 4;
  temp[3] = (input[1] & 0x0F);
  temp[4] = (input[2] & 0xF0) >> 4;
  temp[5] = (input[2] & 0x0F);

  if (temp[5] == 0x0F)
  {
    rc = BAF_FIELD_NOT_USED;
    goto EXIT_LABEL;
  }
  else if (temp[5] != 0x0C)
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  *year = BAF_START_OF_CURRENT_DECADE + temp[0];

  *day = temp[4] + (10 * temp[3]);
  if (*day > 31)
  {
    /*************************************************************************/
    /* Badly formed day.                                                     */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  temp_month = temp[2] + (10 * temp[1]);

  switch (temp_month)
  {
    case 0:
      break;

    case 1:
      OS_STRCPY(month, "January");
      break;

    case 2:
      OS_STRCPY(month, "February");
      break;

    case 3:
      OS_STRCPY(month, "March");
      break;

    case 4:
      OS_STRCPY(month, "April");
      break;

    case 5:
      OS_STRCPY(month, "May");
      break;

    case 6:
      OS_STRCPY(month, "June");
      break;

    case 7:
      OS_STRCPY(month, "July");
      break;

    case 8:
      OS_STRCPY(month, "August");
      break;

    case 9:
      OS_STRCPY(month, "September");
      break;

    case 10:
      OS_STRCPY(month, "October");
      break;

    case 11:
      OS_STRCPY(month, "November");
      break;

    case 12:
      OS_STRCPY(month, "December");
      break;

    default:
      goto EXIT_LABEL;
      /* break;                                                              */
  }

  rc = BAF_FIELD_OK;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_get_calling_number                                         */
/*                                                                           */
/* Purpose:   Gets the calling number of a call record.                      */
/*                                                                           */
/* Returns:   TRUE if successful, FALSE if the record is too short, or       */
/*            doesn't contain a valid value.                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing calling      */
/*                                  number                                   */
/*            OUT    output       - Pointer to the calling number            */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the calling number.     */
/*            Put each digit of the calling number in a separate byte in a   */
/*            temporary array.                                               */
/*            Combine the new array of digits into a long and return.        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_get_calling_number(NBB_BYTE *input,
                                NBB_CHAR *output,
                                NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BOOL rc = FALSE;
  NBB_INT temp[12];
  NBB_INT ii;

  if (length < 6)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode.                                                                 */
  /***************************************************************************/
  temp[0] = (input[0] & 0xF0) >> 4;
  temp[1] = (input[0] & 0x0F);
  temp[2] = (input[1] & 0xF0) >> 4;
  temp[3] = (input[1] & 0x0F);
  temp[4] = (input[2] & 0xF0) >> 4;
  temp[5] = (input[2] & 0x0F);
  temp[6] = (input[3] & 0xF0) >> 4;
  temp[7] = (input[3] & 0x0F);
  temp[8] = (input[4] & 0xF0) >> 4;
  temp[9] = (input[4] & 0x0F);
  temp[10] = (input[5] & 0xF0) >> 4;
  temp[11] = (input[5] & 0x0F);

  if ((temp[11] != 0x0C) || (temp[3] != 0x0C))
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  for (ii = 0; ii < 3; ii++)
  {
    output[ii] = temp[ii] + 0x30;
  }

  output[3] = '-';

  for (ii = 4; ii < 7; ii++)
  {
    output[ii] = temp[ii] + 0x30;
  }

  output[7] = '-';

  for (ii = 8; ii < 12; ii++)
  {
    output[ii] = temp[ii - 1] + 0x30;
  }

  output[12] = 0;

  rc = TRUE;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_get_overseas_ind                                           */
/*                                                                           */
/* Purpose:   Gets the overseas indicator of a call record.                  */
/*                                                                           */
/* Returns:   TRUE if successful, FALSE if the record is too short, or       */
/*            doesn't contain a valid value.                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing overseas     */
/*                                  indicator.                               */
/*            OUT    output       - Pointer to the overseas indicator.       */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the overseas indicator. */
/*            Put each digit of the called number in a separate byte in a    */
/*            temporary array.                                               */
/*            Combine the new array of digits into a long and return.        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_get_overseas_ind(NBB_BYTE *input,
                              NBB_CHAR *output,
                              NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BOOL rc = FALSE;

  if (length < 2)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode.                                                                 */
  /***************************************************************************/
  output[0] = (input[0] & 0xF0) >> 4;
  output[1] = (input[0] & 0x0F);

  if (output[0] > 9)
  {
    /*************************************************************************/
    /* Invalid value.                                                        */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  if (output[1] != 0x0C)
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  rc = TRUE;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_get_called_number                                          */
/*                                                                           */
/* Purpose:   Gets the called number of a call record.                       */
/*                                                                           */
/* Returns:   TRUE if successful, FALSE if the record is too short, or       */
/*            doesn't contain a valid value.                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing called       */
/*                                  number                                   */
/*            OUT    output       - Pointer to the called number             */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the called number.      */
/*            Put each digit of the called number in a separate byte in a    */
/*            temporary array.                                               */
/*            Combine the new array of digits into a long and return.        */
/*                                                                           */
/*            Take account of the overseas indicator.                        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BOOL baf_get_called_number(NBB_BYTE *input,
                               NBB_CHAR *output,
                               NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BOOL rc = FALSE;
  NBB_INT temp[14];
  NBB_INT ii;
  NBB_INT sig_len;
  NBB_INT out_pos;
  NBB_INT skip;
  NBB_BOOL international = FALSE;
  NBB_INT first_byte = 0;

  if (length < 7)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode.                                                                 */
  /***************************************************************************/
  temp[0] = (input[0] & 0xF0) >> 4;
  temp[1] = (input[0] & 0x0F);
  temp[2] = (input[1] & 0xF0) >> 4;
  temp[3] = (input[1] & 0x0F);
  temp[4] = (input[2] & 0xF0) >> 4;
  temp[5] = (input[2] & 0x0F);
  temp[6] = (input[3] & 0xF0) >> 4;
  temp[7] = (input[3] & 0x0F);
  temp[8] = (input[4] & 0xF0) >> 4;
  temp[9] = (input[4] & 0x0F);
  temp[10] = (input[5] & 0xF0) >> 4;
  temp[11] = (input[5] & 0x0F);
  temp[12] = (input[6] & 0xF0) >> 4;
  temp[13] = (input[6] & 0x0F);

  /***************************************************************************/
  /* Is this an international number?  The previously stored overseas        */
  /* indicator tells us.                                                     */
  /*                                                                         */
  /* Overseas indicator...   ...indicates an international number of length  */
  /*           3                       7                                     */
  /*           4                       8                                     */
  /*           5                       9                                     */
  /*           6                      10                                     */
  /*           7                      11                                     */
  /*           8                      12                                     */
  /***************************************************************************/
  if ((global_overseas_ind >= 3) && (global_overseas_ind <= 8))
  {
    sig_len = global_overseas_ind + 4;
    first_byte = 12 - sig_len;
    international = TRUE;
  }
  else
  {
    /*************************************************************************/
    /* Check significant length field.  If it's zero then this is a NANPA    */
    /* number and has length 10.                                             */
    /*************************************************************************/
    if (input[0] != 0)
    {
      sig_len = temp[0]*10 + temp[1];

      if (sig_len > 10)
      {
        /*********************************************************************/
        /* Badly formatted record.                                           */
        /*********************************************************************/
        goto EXIT_LABEL;
      }
    }
    else
    {
      sig_len = 10;
    }
  }

  if ((temp[13] != 0x0C) || (temp[5] != 0x0C))
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  out_pos = 0;

  if (!international)
  {
    /*************************************************************************/
    /* Decode an NPA number.                                                 */
    /*                                                                       */
    /* We are dealing with a 14 digit array with the following contents      */
    /*                                                                       */
    /* The digits at offset 0 and 1 contain the significant length of the    */
    /* address (L)                                                           */
    /*                                                                       */
    /* The digits at offset 5 and 13 are padding nibbles (P)                 */
    /*                                                                       */
    /* |L|L| | | |P| | | | | | | | |P|                                       */
    /*                                                                       */
    /* The remaining 10 digits contain the address.                          */
    /*                                                                       */
    /* Within these 10 digits, the significant digits are right justified    */
    /* and padded with zeroes on the left.                                   */
    /*************************************************************************/

    /*************************************************************************/
    /* Start by skipping over the length digits (L).                         */
    /*************************************************************************/
    skip = 2;

    /*************************************************************************/
    /* Continue by skipping over the zero pad digits until the first         */
    /* significant digit is reached.  This is later adjusted to cope with    */
    /* the padding nibble at offset 5.                                       */
    /*                                                                       */
    /* Continue to the end.                                                  */
    /*************************************************************************/
    for (ii = (10 - sig_len); ii < 10; ii++)
    {
      /***********************************************************************/
      /* If this is a 10 digit number then add a - character after the first */
      /* and second group of 3 digits.                                       */
      /***********************************************************************/
      if ((sig_len == 10) && ((ii == 3) || (ii == 6)))
      {
        output[out_pos++] = '-';
      }

      /***********************************************************************/
      /* Skip the padding nibble at offset 5.                                */
      /*                                                                     */
      /* If the significant length is less than or equal to 7 then we are    */
      /* starting from at or beyond the padding nibble so skip one digit     */
      /* immediately.                                                        */
      /*                                                                     */
      /* If the signficant length is greater then 7 then we are starting     */
      /* from before the padding nibble wait until we reach it before        */
      /* skipping one digit.                                                 */
      /***********************************************************************/
      if ((sig_len <= 7) &&
          (ii == (10 - sig_len)))
      {
        skip++;
      }
      else if ((sig_len > 7) &&
               (ii == (sig_len - 7)))
      {
        skip++;
      }
      output[out_pos++] = temp[ii+skip] + 0x30;
    }
  }
  else
  {
    /*************************************************************************/
    /* Decode an international number.                                       */
    /*************************************************************************/
    skip = 0;

    for (ii = first_byte; ii < 12; ii++)
    {
      /***********************************************************************/
      /* Skip padding 0xC nibble after first 5 digits.                       */
      /***********************************************************************/
      if (ii == 5)
      {
        skip++;
      }
      output[out_pos++] = temp[ii+skip] + 0x30;
    }
  }

  output[out_pos] = 0;

  rc = TRUE;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_get_time                                                   */
/*                                                                           */
/* Purpose:   Gets the time of a call record.                                */
/*                                                                           */
/* Returns:   One of                                                         */
/*                                                                           */
/*            BAF_FIELD_OK if successful                                     */
/*                                                                           */
/*            BAF_FIELD_NOT_USED if the field is not used                    */
/*                                                                           */
/*            BAF_FIELD_ERROR if the record is too short, or doesn't contain */
/*            a valid value.                                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing time         */
/*            OUT    output       - Pointer to the time                      */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the time.               */
/*            Put each digit of the time in a separate byte in a temporary   */
/*            array.                                                         */
/*            Combine the new array of digits into a long and return.        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BYTE baf_get_time(NBB_BYTE *input, NBB_CHAR *output, NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BYTE rc = BAF_FIELD_ERROR;
  NBB_INT temp[8];

  if (length < 4)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode.                                                                 */
  /***************************************************************************/
  temp[0] = (input[0] & 0xF0) >> 4;
  temp[1] = (input[0] & 0x0F);
  temp[2] = (input[1] & 0xF0) >> 4;
  temp[3] = (input[1] & 0x0F);
  temp[4] = (input[2] & 0xF0) >> 4;
  temp[5] = (input[2] & 0x0F);
  temp[6] = (input[3] & 0xF0) >> 4;
  temp[7] = (input[3] & 0x0F);

  if (temp[7] == 0x0F)
  {
    rc = BAF_FIELD_NOT_USED;
    goto EXIT_LABEL;
  }
  else if (temp[7] != 0x0C)
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  output[0] = temp[0] + 0x30;
  output[1] = temp[1] + 0x30;
  output[2] = ':';
  output[3] = temp[2] + 0x30;
  output[4] = temp[3] + 0x30;
  output[5] = ':';
  output[6] = temp[4] + 0x30;
  output[7] = temp[5] + 0x30;
  output[8] = '.';
  output[9] = temp[6] + 0x30;
  output[10] = 0;

  rc = BAF_FIELD_OK;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_get_length                                                 */
/*                                                                           */
/* Purpose:   Gets the overall length of a call.                             */
/*                                                                           */
/* Returns:   One of                                                         */
/*                                                                           */
/*            BAF_FIELD_OK if successful                                     */
/*                                                                           */
/*            BAF_FIELD_NOT_USED if the field is not used                    */
/*                                                                           */
/*            BAF_FIELD_ERROR if the record is too short, or doesn't contain */
/*            a valid value.                                                 */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing length       */
/*            OUT    output       - Pointer to the length                    */
/*            IN     length       - Valid length of input                    */
/*                                                                           */
/* Operation: Check the length is long enough to get the length.             */
/*            Put each digit of the length in a separate byte in a temporary */
/*            array.                                                         */
/*            Combine the new array of digits into a long and return.        */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BYTE baf_get_length(NBB_BYTE *input, NBB_CHAR *output, NBB_LONG length)
{
  /***************************************************************************/
  /* Local variables.                                                        */
  /***************************************************************************/
  NBB_BYTE rc = BAF_FIELD_ERROR;
  NBB_INT temp[10];
  NBB_INT ii;

  if (length < 5)
  {
    goto EXIT_LABEL;
  }

  /***************************************************************************/
  /* Decode.                                                                 */
  /***************************************************************************/
  temp[0] = (input[0] & 0xF0) >> 4;
  temp[1] = (input[0] & 0x0F);
  temp[2] = (input[1] & 0xF0) >> 4;
  temp[3] = (input[1] & 0x0F);
  temp[4] = (input[2] & 0xF0) >> 4;
  temp[5] = (input[2] & 0x0F);
  temp[6] = (input[3] & 0xF0) >> 4;
  temp[7] = (input[3] & 0x0F);
  temp[8] = (input[4] & 0xF0) >> 4;
  temp[9] = (input[4] & 0x0F);

  if (temp[9] == 0x0F)
  {
    rc = BAF_FIELD_NOT_USED;
    goto EXIT_LABEL;
  }
  else if ((temp[9] != 0x0C) || (temp[0] != 0))
  {
    /*************************************************************************/
    /* Badly formatted record.                                               */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  if (temp[1] != 0)
  {
    output[0] = temp[1] + 0x30;
    output[1] = temp[2] + 0x30;
    output[2] = temp[3] + 0x30;
    output[3] = temp[4] + 0x30;
    output[4] = temp[5] + 0x30;
    ii = 5;
  }
  else if (temp[2] != 0)
  {
    output[0] = temp[2] + 0x30;
    output[1] = temp[3] + 0x30;
    output[2] = temp[4] + 0x30;
    output[3] = temp[5] + 0x30;
    ii = 4;
  }
  else if (temp[3] != 0)
  {
    output[0] = temp[3] + 0x30;
    output[1] = temp[4] + 0x30;
    output[2] = temp[5] + 0x30;
    ii = 3;
  }
  else if (temp[4] != 0)
  {
    output[0] = temp[4] + 0x30;
    output[1] = temp[5] + 0x30;
    ii = 2;
  }
  else
  {
    output[0] = temp[5] + 0x30;
    ii = 1;
  }

  output[ii] = ':';
  output[ii + 1] = temp[6] + 0x30;
  output[ii + 2] = temp[7] + 0x30;

  output[ii + 3] = '.';
  output[ii + 4] = temp[8] + 0x30;

  output[ii + 5] = 0;

  rc = BAF_FIELD_OK;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_decode_number                                              */
/*                                                                           */
/* Purpose:   Decoder for the number field.                                  */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing number       */
/*            IN     min_char     - Minimum character to decode.             */
/*            IN     num_chars    - Maximum character to decode.             */
/*                                                                           */
/* Operation: Print out each character in turn.                              */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_number(NBB_BYTE *input,
                           NBB_INT min_char,
                           NBB_INT max_char)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_INT ii;

  /***************************************************************************/
  /* And, finally, get the number.  Must be an odd number of characters.     */
  /***************************************************************************/
  assert(min_char <= max_char);
  assert(min_char > 0);
  if (baf_verbose)
  {
    for (ii = min_char; ii <= max_char; ii++)
    {
      if ((ii % 2) == 0)
      {
        /*********************************************************************/
        /* Even character.  Bottom four bits in bytes.                       */
        /*********************************************************************/
        printf("%1.1d", (input[(ii / 2) - 1] & 0x0F));
      }
      else
      {
        /*********************************************************************/
        /* Odd character.  Top 4 bits in byte.                               */
        /*********************************************************************/
        printf("%1.1d", (input[ii / 2] >> 4));
      }
    }
  }

  return;

} /* baf_decode_number */

