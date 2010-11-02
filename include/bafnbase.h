
/**INC+***********************************************************************/
/* Header:    bafnbase.h                                                     */
/*                                                                           */
/* Purpose:   Minimal N-BASE header for compiling bafview.                   */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED                                     */
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
/**INC-***********************************************************************/

typedef int NBB_BOOL;
typedef unsigned char NBB_BYTE;
typedef short   NBB_SHORT;
typedef unsigned short   NBB_USHORT;
typedef int NBB_LONG;
typedef unsigned int NBB_UINT;
typedef char NBB_CHAR;
typedef int NBB_INT;
typedef void NBB_VOID;
typedef unsigned int NBB_ULONG;
#define NBB_CONST const

#define OS_FOPEN fopen
#define OS_FREAD fread
#define OS_FCLOSE fclose
#define OS_STRCPY strcpy
#define OS_STRLEN strlen
#define OS_MEMSET memset
#define OS_MEMCPY memcpy
#define OS_STRCAT strcat
#define OS_RENAME rename
#define OS_FWRITE fwrite
#define OS_FSEEK fseek

#define TRUE 1
#define FALSE 0

#define NBB_MIN(X, Y)   (((X)<(Y)) ? (X) : (Y))

