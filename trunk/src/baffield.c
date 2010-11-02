
/**MOD+***********************************************************************/
/* Module:    baffield.c                                                     */
/*                                                                           */
/* Purpose:   Functions to decode tables from BAF records.                   */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
/*                                                                           */
/* $Id:: baffield.c 12654 2009-09-17 10:16:54Z pf                         $  */
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
    baf_print("%s: %d\n", BAF_FIELD_NAME(field), structure_type);
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
    baf_print("%s: %d\n", BAF_FIELD_NAME(field), call_type);
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
    baf_print("%s: ", BAF_FIELD_NAME(field));
  }

  if (!baf_stats)
  {
    baf_display_class_feature_code(class_feature_code);
  }
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
    baf_print("%s: ", BAF_FIELD_NAME(field));
  }

  if (!baf_stats)
  {
    baf_display_service_feature_code(service_feature_code);
  }
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
    baf_print("%s: %s\n", BAF_FIELD_NAME(field), number);
  }
  else
  {
    if (!baf_stats)
    {
      baf_print("%s ", number);
    }
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
    baf_print("%s : %s\n", BAF_FIELD_NAME(field),
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
    baf_print("%s: %s\n", BAF_FIELD_NAME(field), number);
  }
  else
  {
    if (!baf_stats)
    {
      baf_print("-> %s : ", number);
    }
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
      baf_print("%s: Field not used\n", BAF_FIELD_NAME(field));
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
    baf_print("%s: %s\n", BAF_FIELD_NAME(field), decoded_length);
  }
  else if (field == BAF_F_019_CALL_LENGTH)
  {
    if (!baf_stats)
    {
      baf_print("%s : ", decoded_length);
    }
    else
    {
      /***********************************************************************/
      /* The field BAF_F_019_CALL_LENGTH may be used for traffic statistics  */
      /* if embedded in the appropriate BAF module and structure.            */
      /***********************************************************************/
      if (BAF_VALID_STATS(stats_data.module_code, stats_data.structure_type))
      {
        sprintf(stats_data.call_length, "%s", decoded_length);
      }
    }
  }
  else if (field == BAF_F_019_CARRIER_ELAPSED_TIME)
  {
    /*************************************************************************/
    /* The field BAF_F_019_ELAPSED_TIME may be used for traffic statistics   */
    /* if embedded in the appropriate BAF module and structure.              */
    /*************************************************************************/
    if ((baf_stats) &&
        (BAF_VALID_STATS(stats_data.module_code, stats_data.structure_type)))
    {
      sprintf(stats_data.call_elapsed_time, "%s", decoded_length);
    }
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
      baf_print("%s: Field not used\n", BAF_FIELD_NAME(field));
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
        (year == baf_year[0]) &&
        (month[0] == 0))
    {
      baf_print("%s: No date specified\n", BAF_FIELD_NAME(field));
    }
    else
    {
      baf_print("%s: %d %s %d\n", BAF_FIELD_NAME(field), day, month, year);
    }
  }
  else if (field == BAF_F_006_DATE)
  {
    /*************************************************************************/
    /* Note that the date is carefully formatted to look nice in this        */
    /* concise version.                                                      */
    /*************************************************************************/
    if ((day == 0) &&
        (year == baf_year[0]) &&
        (month[0] == 0))
    {
      if (baf_stats)
      {
        baf_print("No date specified\n");

        (*input) += 3;
        (*length) -= 3;
        ret_code = TRUE;
        goto EXIT_LABEL;
      }
      else
      {
        sprintf(concise_string, "No date specified", day, month, year);
      }
    }
    else
    {
      if (baf_stats)
      {
        sprintf(concise_string, "%.2d/%s/%d", day, month, year);
      }
      else
      {
        sprintf(concise_string, "%d %s %d", day, month, year);
      }
    }

    if (!baf_stats)
    {
      baf_print("%-17s : ", concise_string);
    }
    else
    {
      /***********************************************************************/
      /* The field BAF_F_006_DATE may be used for traffic statistics if      */
      /* embedded in the appropriate BAF module and structure.               */
      /***********************************************************************/
      if (BAF_VALID_STATS(stats_data.module_code, stats_data.structure_type))
      {
        sprintf(stats_data.call_date, "%s", concise_string);
      }
    }

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
      baf_print("%s: Field not used\n", BAF_FIELD_NAME(field));
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
    baf_print("%s: %s\n", BAF_FIELD_NAME(field), time);
  }
  else if (field == BAF_F_018_TIME)
  {
    if (!baf_stats)
    {
      baf_print("%s : ", time);
    }
    else
    {
      /***********************************************************************/
      /* The field BAF_F_018_TIME may be used for traffic statistics if      */
      /* embedded in the appropriate BAF module and structure.               */
      /***********************************************************************/
      if (BAF_VALID_STATS(stats_data.module_code, stats_data.structure_type))
      {
        sprintf(stats_data.call_time, "%s", time);
      }
    }
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

  if (temp[0] > 9)
  {
    /*************************************************************************/
    /* Badly formed year.                                                    */
    /*************************************************************************/
    goto EXIT_LABEL;
  }
  *year = baf_year[temp[0]];

  *day = temp[4] + (10 * temp[3]);
  if (*day > 31)
  {
    /*************************************************************************/
    /* Badly formed day.                                                     */
    /*************************************************************************/
    goto EXIT_LABEL;
  }

  temp_month = temp[2] + (10 * temp[1]);

  if (!baf_stats)
  {
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
        /* break;                                                            */
    }
  }
  else
  {
    sprintf(month, "%.2d", temp_month);
  }

  rc = BAF_FIELD_OK;

EXIT_LABEL:

  return(rc);
}

/**PROC+**********************************************************************/
/* Name:      baf_decode_byte                                                */
/*                                                                           */
/* Purpose:   Decodes a single byte from the input                           */
/*                                                                           */
/* Returns:   The byte decoded.                                              */
/*                                                                           */
/* Params:    IN     input        - Pointer to the input array               */
/*            IN     high         - Index of high bit to decode from         */
/*            IN     low          - Index of low bit to decode to            */
/*                                                                           */
/* Operation: We index the bits of the byte from 0 (most sig) to 7 (least    */
/*            sig).  Shift to the right to get the required bits to the      */
/*            least signifficant bits of the byte.  Then mask off the higher */
/*            bits.                                                          */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_BYTE baf_decode_byte(NBB_BYTE *input, NBB_BYTE high, NBB_BYTE low)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BYTE temp_byte = input[0];
  NBB_BYTE rshift = (NBB_BYTE)(7 - low);
  NBB_INT mask_num = (7 - (low - high));

  assert((high >= 0) && (high <= 7));
  assert((low >= 0) && (low <= 7));
  assert(low >= high);
  temp_byte = (NBB_BYTE)((temp_byte >> rshift) & baf_mask_byte[mask_num]);

  return(temp_byte);

} /* baf_decode_byte */

/**PROC+**********************************************************************/
/* Name:      baf_decode_2_bytes                                             */
/*                                                                           */
/* Purpose:   Decodes 2 bytes from the input                                 */
/*                                                                           */
/* Returns:   The ushort decoded.                                            */
/*                                                                           */
/* Params:    IN     input        - Pointer to the input array               */
/*            IN     high         - Index of high bit to decode from         */
/*            IN     low          - Index of low bit to decode to            */
/*                                                                           */
/* Operation: We index the bits of the byte from 0 (most sig) to 7 (least    */
/*            sig).  We decode each byte individually, left shift the higher */
/*            sig byte by 8, and add the low byte.                           */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_USHORT baf_decode_2_bytes(NBB_BYTE *input, NBB_BYTE high, NBB_BYTE low)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BYTE temp_byte;
  NBB_USHORT temp_short;

  assert((high >= 0) && (high <= 7));
  assert((low >= 0) && (low <= 7));

  /***************************************************************************/
  /* First put high byte into temp_short.                                    */
  /***************************************************************************/
  temp_short = (NBB_SHORT) baf_decode_byte(input + 1, high, 7);
  temp_short = (NBB_USHORT)(temp_short << (8 - (7 - low)));

  /***************************************************************************/
  /* Put the low byte into temp_byte.                                        */
  /***************************************************************************/
  temp_byte = baf_decode_byte(input, 0, low);

  /***************************************************************************/
  /* Combine the bytes into temp_short.                                      */
  /***************************************************************************/
  temp_short = (NBB_USHORT)(temp_short + temp_byte);

  return(temp_short);

} /* baf_decode_2_bytes */

/**PROC+**********************************************************************/
/* Name:      baf_decode_3_bytes                                             */
/*                                                                           */
/* Purpose:   Decodes 3 bytes from the input                                 */
/*                                                                           */
/* Returns:   The ulong decoded.                                             */
/*                                                                           */
/* Params:    IN     input        - Pointer to the input array               */
/*            IN     high         - Index of high bit to decode from         */
/*            IN     low          - Index of low bit to decode to            */
/*                                                                           */
/* Operation: We index the bits of the byte from 0 (most sig) to 7 (least    */
/*            sig).  We decode each byte individually, left shift the higher */
/*            sig byte by 16, middle byte by 8 and add the low byte.         */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_ULONG baf_decode_3_bytes(NBB_BYTE *input, NBB_BYTE high, NBB_BYTE low)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BYTE temp_byte;
  NBB_USHORT temp_short;
  NBB_ULONG temp_long;

  assert((high >= 0) && (high <= 7));
  assert((low >= 0) && (low <= 7));

  /***************************************************************************/
  /* First put high byte into temp_long.                                     */
  /***************************************************************************/
  temp_long = (NBB_ULONG)baf_decode_byte(input + 2, high, 7);
  temp_long = (NBB_ULONG)(temp_long << (16 - (7 - low)));

  /***************************************************************************/
  /* Put the middle byte in temp_short.                                      */
  /***************************************************************************/
  temp_short = (NBB_USHORT)baf_decode_byte(input + 1, 0, 7);
  temp_short = (NBB_USHORT)(temp_short << (8 - (7 - low)));

  /***************************************************************************/
  /* Put the low byte in temp_byte.                                          */
  /***************************************************************************/
  temp_byte = baf_decode_byte(input, 0, low);

  /***************************************************************************/
  /* Combine the bytes into temp_long                                        */
  /***************************************************************************/
  temp_long = temp_long + temp_short + temp_byte;

  return(temp_long);

} /* baf_decode_3_bytes */

/**PROC+**********************************************************************/
/* Name:      baf_decode_4_bytes                                             */
/*                                                                           */
/* Purpose:   Decodes 4 bytes from the input                                 */
/*                                                                           */
/* Returns:   The ulong decoded.                                             */
/*                                                                           */
/* Params:    IN     input        - Pointer to the input array               */
/*            IN     high         - Index of high bit to decode from         */
/*            IN     low          - Index of low bit to decode to            */
/*                                                                           */
/* Operation: We index the bits of the byte from 0 (most sig) to 7 (least    */
/*            sig).  We decode each byte individually, left shift the higher */
/*            sig byte by 24, second by 16, third by 8 and add the low byte. */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_ULONG baf_decode_4_bytes(NBB_BYTE *input, NBB_BYTE high, NBB_BYTE low)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_BYTE temp_byte;
  NBB_USHORT temp_short;
  NBB_ULONG temp_long;
  NBB_ULONG temp_long2;

  assert((high >= 0) && (high <= 7));
  assert((low >= 0) && (low <= 7));

  /***************************************************************************/
  /* Put first byte into temp_long.                                          */
  /***************************************************************************/
  temp_long = (NBB_ULONG) baf_decode_byte(input + 3, high, 7);
  temp_long = temp_long << (24 - (7 - low));

  /***************************************************************************/
  /* Put second byte into temp_long2.                                        */
  /***************************************************************************/
  temp_long2 = (NBB_ULONG) baf_decode_byte(input + 2, 0, 7);
  temp_long2 = temp_long2 << (16 - (7 - low));

  /***************************************************************************/
  /* Put the third byte in tmep_short.                                       */
  /***************************************************************************/
  temp_short = (NBB_USHORT) baf_decode_byte(input + 1, 0, 7);
  temp_short = (NBB_USHORT)(temp_short << (8 - (7 - low)));

  /***************************************************************************/
  /* Put the low byte in temp_byte.                                          */
  /***************************************************************************/
  temp_byte = baf_decode_byte(input, 0, low);

  /***************************************************************************/
  /* Combine the bytes into temp_long                                        */
  /***************************************************************************/
  temp_long = temp_long + temp_long2 + temp_short + temp_byte;

  return(temp_long);

} /* baf_decode_4_bytes */

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
    output[ii] = (NBB_BYTE)(temp[ii] + 0x30);
  }

  output[3] = (NBB_BYTE)('-');

  for (ii = 4; ii < 7; ii++)
  {
    output[ii] = (NBB_BYTE)(temp[ii] + 0x30);
  }

  output[7] = (NBB_BYTE)('-');

  for (ii = 8; ii < 12; ii++)
  {
    output[ii] = (NBB_BYTE)(temp[ii - 1] + 0x30);
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
  output[0] = (NBB_BYTE)((input[0] & 0xF0) >> 4);
  output[1] = (NBB_BYTE)((input[0] & 0x0F));

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
        output[out_pos++] = (NBB_BYTE)('-');
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
      output[out_pos++] = (NBB_BYTE)(temp[ii+skip] + 0x30);
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
      output[out_pos++] = (NBB_BYTE)(temp[ii+skip] + 0x30);
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

  output[0] = (NBB_BYTE)(temp[0] + 0x30);
  output[1] = (NBB_BYTE)(temp[1] + 0x30);
  output[2] = (NBB_BYTE)(':');
  output[3] = (NBB_BYTE)(temp[2] + 0x30);
  output[4] = (NBB_BYTE)(temp[3] + 0x30);
  output[5] = (NBB_BYTE)(':');
  output[6] = (NBB_BYTE)(temp[4] + 0x30);
  output[7] = (NBB_BYTE)(temp[5] + 0x30);
  output[8] = (NBB_BYTE)('.');
  output[9] = (NBB_BYTE)(temp[6] + 0x30);
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
    output[0] = (NBB_BYTE)(temp[1] + 0x30);
    output[1] = (NBB_BYTE)(temp[2] + 0x30);
    output[2] = (NBB_BYTE)(temp[3] + 0x30);
    output[3] = (NBB_BYTE)(temp[4] + 0x30);
    output[4] = (NBB_BYTE)(temp[5] + 0x30);
    ii = 5;
  }
  else if (temp[2] != 0)
  {
    output[0] = (NBB_BYTE)(temp[2] + 0x30);
    output[1] = (NBB_BYTE)(temp[3] + 0x30);
    output[2] = (NBB_BYTE)(temp[4] + 0x30);
    output[3] = (NBB_BYTE)(temp[5] + 0x30);
    ii = 4;
  }
  else if (temp[3] != 0)
  {
    output[0] = (NBB_BYTE)(temp[3] + 0x30);
    output[1] = (NBB_BYTE)(temp[4] + 0x30);
    output[2] = (NBB_BYTE)(temp[5] + 0x30);
    ii = 3;
  }
  else if (temp[4] != 0)
  {
    output[0] = (NBB_BYTE)(temp[4] + 0x30);
    output[1] = (NBB_BYTE)(temp[5] + 0x30);
    ii = 2;
  }
  else
  {
    output[0] = (NBB_BYTE)(temp[5] + 0x30);
    ii = 1;
  }

  output[ii] = (NBB_BYTE)(':');
  output[ii + 1] = (NBB_BYTE)(temp[6] + 0x30);
  output[ii + 2] = (NBB_BYTE)(temp[7] + 0x30);

  output[ii + 3] = (NBB_BYTE)('.');
  output[ii + 4] = (NBB_BYTE)(temp[8] + 0x30);

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
        baf_print("%1.1d", (input[(ii / 2) - 1] & 0x0F));
      }
      else
      {
        /*********************************************************************/
        /* Odd character.  Top 4 bits in byte.                               */
        /*********************************************************************/
        baf_print("%1.1d", (input[ii / 2] >> 4));
      }
    }
  }

  return;

} /* baf_decode_number */

/**PROC+**********************************************************************/
/* Name:      baf_decode_stat_number                                         */
/*                                                                           */
/* Purpose:   Decoder for the number field.                                  */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing number       */
/*            IN     min_char     - Minimum character to decode.             */
/*            IN     num_chars    - Maximum character to decode.             */
/*            OUT    value        - Decode field value.                      */
/*                                                                           */
/* Operation: Decode and update statistical information.                     */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_stat_number(NBB_BYTE *input,
                                NBB_INT min_char,
                                NBB_INT max_char,
                                NBB_CHAR *value)
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
  if ((baf_verbose) || (baf_stats))
  {
    for (ii = min_char; ii <= max_char; ii++)
    {
      if ((ii % 2) == 0)
      {
        /*********************************************************************/
        /* Even character.  Bottom four bits in bytes.                       */
        /*********************************************************************/
        value[ii - min_char] = (NBB_BYTE)('0' + (input[(ii / 2) - 1] & 0x0F));
      }
      else
      {
        /*********************************************************************/
        /* Odd character.  Top 4 bits in byte.                               */
        /*********************************************************************/
        value[ii - min_char] = (NBB_BYTE)('0' + (input[ii / 2] >> 4));
      }
    }
    value[ii - min_char] = '\0';
  }

  return;

} /* baf_decode_stat_number */

/**PROC+**********************************************************************/
/* Name:      baf_decode_stat_field                                          */
/*                                                                           */
/* Purpose:   Decode a field that contain information used for statistics    */
/*            calculation.                                                   */
/*                                                                           */
/* Returns:   Nothing.                                                       */
/*                                                                           */
/* Params:    IN     input        - Pointer to array containing number       */
/*            IN     descriptor   - Pointer to field structure.              */
/*            IN     field        - Field number.                            */
/*                                                                           */
/* Operation: Starts decoding if field is one of BAF_F_057_IC_INC_PREFIX,    */
/*            BAF_F_083_TRUNK_GROUP_NUMBER, BAF_F_244_TRUNK_IDENTIFICATION.  */
/*            If field is not one of them no action is taken.                */
/*                                                                           */
/**PROC-**********************************************************************/

NBB_VOID baf_decode_stat_field(NBB_BYTE **input,
                               NBB_CONST BAF_FIELD *descriptor,
                               NBB_LONG field)
{
  /***************************************************************************/
  /* Local Variables                                                         */
  /***************************************************************************/
  NBB_ULONG chars;
  NBB_ULONG buffer[BAF_MAX_ELEMENTS_IN_FIELD];
  NBB_CONST BAF_DISPLAY *display;

  switch (field)
  {
    case BAF_F_057_IC_INC_PREFIX:
      /***********************************************************************/
      /* The field BAF_F_057_IC_INC_PREFIX gives us the carrier ID, which    */
      /* may be used for traffic statistics if embedded in the appropriate   */
      /* BAF module and structure.  It is composed of three display          */
      /* elements.  We only care about the carrier identification code,      */
      /* which is the value in the first display element of this field.      */
      /***********************************************************************/
      display = &(descriptor->displays[0]);
      assert(display->num_values == 0);

      if (BAF_VALID_STATS(stats_data.module_code, stats_data.structure_type))
      {
        baf_decode_stat_number(*input,
                               display->min_char,
                               display->max_char,
                               stats_data.carrier_id);
      }

      break;

    case BAF_F_083_TRUNK_GROUP_NUMBER:
      /***********************************************************************/
      /* The field BAF_F_083_TRUNK_GROUP_NUMBER may be used for traffic      */
      /* statistics if embedded in the appropriate BAF module and structure. */
      /* It is composed of two display elements.  We only care about the     */
      /* trunk group ID, which is the value in the second display element.   */
      /***********************************************************************/
      display = &(descriptor->displays[1]);
      assert((display->max_char - display->min_char) < 9);

      if (BAF_VALID_TRUNK_GROUP_STATS(stats_data.module_code,
                                      stats_data.structure_type))
      {
        baf_decode_stat_number(*input,
                               display->min_char,
                               display->max_char,
                               stats_data.outgoing_trunk_id);
      }

      break;

    case BAF_F_244_TRUNK_IDENTIFICATION:
      /***********************************************************************/
      /* The field BAF_F_244_TRUNK_IDENTIFICATION may be used for traffic    */
      /* statistics if embedded in the appropriate BAF module and structure. */
      /* It is composed of three display elements.  The first display        */
      /* element contains the routing indicator, which we will use to        */
      /* determine whether the call is incoming or outgoing.  The second     */
      /* display element contains the trunk group ID.  We don't care about   */
      /* the third (trunk member).                                           */
      /***********************************************************************/
      display = &(descriptor->displays[0]);
      assert((display->max_char - display->min_char) < 9);

      /***********************************************************************/
      /* Get the first character of the current display element to check if  */
      /* it contains valid data (that is: chars != 0xF).                     */
      /***********************************************************************/
      baf_get_chars(*input, display->min_char, display->min_char, &chars);
      if (chars != 0xF)
      {
        if (display->num_values > 0)
        {
          /*******************************************************************/
          /* Save the value in the local buffer.                             */
          /*******************************************************************/
          baf_get_chars(*input,
                        display->min_char,
                        display->max_char,
                        buffer);
        }

        /*********************************************************************/
        /* Read the second display element to get trunk group number value.  */
        /*********************************************************************/
        display = &(descriptor->displays[1]);
        assert(display->num_values == 0);

        if (BAF_VALID_TRUNK_ID_STATS(stats_data.module_code,
                                      stats_data.structure_type))
        {
          /*******************************************************************/
          /* We will find out whether the trunk is incoming or outgoing      */
          /* based on the first 'character' from the buffer: odd values      */
          /* correspond to incoming trunks; even values correspond to        */
          /* outgoing trunks.                                                */
          /*******************************************************************/
          if ((buffer[0] % 2) == 0)
          {
            baf_decode_stat_number(*input,
                                   display->min_char,
                                   display->max_char,
                                   stats_data.outgoing_trunk_id);
          }
          else
          {
            baf_decode_stat_number(*input,
                                   display->min_char,
                                   display->max_char,
                                   stats_data.incoming_trunk_id);
          }
        }
      }
      break;

    default:
      /***********************************************************************/
      /* We don't care about other generic fields: do nothing.               */
      /***********************************************************************/
      break;
  }
} /* baf_decode_stat_field */
