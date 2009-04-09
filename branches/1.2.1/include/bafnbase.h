
/**INC+***********************************************************************/
/* Header:    bafnbase.h                                                     */
/*                                                                           */
/* Purpose:   Minimal N-BASE header for compiling bafview.                   */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 2004, 2005                          */
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
/**INC-***********************************************************************/

typedef int NBB_BOOL;
typedef unsigned char NBB_BYTE;
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

#define TRUE 1
#define FALSE 0

