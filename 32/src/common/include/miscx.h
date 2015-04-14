/**************************************************************************
 *
 * SOURCE FILE NAME = MISC.H
 *
 * DESCRIPTIVE NAME = Miscellaneous defines
 *
 *
 * Copyright : COPYRIGHT IBM CORPORATION, 1991, 1992
 *             LICENSED MATERIAL - PROGRAM PROPERTY OF IBM
 *             REFER TO COPYRIGHT INSTRUCTION FORM#G120-2083
 *             RESTRICTED MATERIALS OF IBM
 *             IBM CONFIDENTIAL
 *
 * VERSION = V2.0
 *
 * DATE
 *
 * DESCRIPTION :
 *
 * Purpose:
 *
 *
 *
 *
 * FUNCTIONS  :
 *
 *
 *
 * NOTES
 *
 *
 * STRUCTURES
 *
 * EXTERNAL REFERENCES
 *
 *
 *
 * EXTERNAL FUNCTIONS
 *
 * CHANGE ACTIVITY =
 *   DATE      FLAG        APAR   CHANGE DESCRIPTION
 *   --------  ----------  -----  --------------------------------------
 *   mm/dd/yy  @VR.MPPPXX  XXXXX  XXXXXXX
 *
 ****************************************************************************/

#define ASECTORSIZE     512
#define BYTETOSECTORSHIFT 9
#define SECTORTOBYTESHIFT 9

#define ERROR                   1
#define NO_ERROR                0

#define YES                     1
#define NO                      0

#define MAX_DRIVERS             32

#define KB  1024
#define MB  KB*KB
#define GB  MB*KB

/* typedef_NearPointer(type, np_type)
 *
 * Define a near pointer typedef usable by both 16 bit Microsoft C
 * and 32 bit IBM C++ code. 
 *
 *    type     -  name of base type
 *    np_type  -  name of pointer to base type
 *
 * For 32 bit (INCL_32 defined) the type is set to USHORT.
 * For 16 bit, 'near *' is used.
 *
 */
#ifdef INCL_32
#define typedef_NearPointer(type, np_type)  typedef USHORT np_type
#else
#define typedef_NearPointer(type, np_type)  typedef type NEAR *np_type
#endif

