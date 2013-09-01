/************************************************************************\
**                                                                      **
**               OS/2(r) Physical Device Driver Libraries               **
**                         for Watcom C/C++ 10                          **
**                                                                      **
**  COPYRIGHT:                                                          **
**                                                                      **
**    (C) Copyright Advanced Gravis Computer Technology Ltd 1994.       **
**        All Rights Reserved.                                          **
**                                                                      **
**  DISCLAIMER OF WARRANTIES:                                           **
**                                                                      **
**    The following [enclosed] code is provided to you "AS IS",         **
**    without warranty of any kind.  You have a royalty-free right to   **
**    use, modify, reproduce and distribute the following code (and/or  **
**    any modified version) provided that you agree that Advanced       **
**    Gravis has no warranty obligations and shall not be liable for    **
**    any damages arising out of your use of this code, even if they    **
**    have been advised of the possibility of such damages.  This       **
**    Copyright statement and Disclaimer of Warranties may not be       **
**    removed.                                                          **
**                                                                      **
\************************************************************************/

/* IOCtl.c
 *
 * Process device specific I/O commands
 *
 * History:
 *
 * Sep 30, 94  David Bollo    Initial version
 * Jun 30, 07  M Greene <greenemk@cox.net>
 * Sep 12, 11  Andy Willis    HLT version
 */


#include <devhdr.h>
#include <devreqp.h>
#include <devtypes.h>

#define            IOCTLCAT               0x91

// Dispatch IOCtl requests received from the Strategy routine
uint16_t StratIOCtl(REQP_HEADER FAR* rp)
{
/*
    RPIOCtl FAR* _rp = (RPIOCtl FAR*)rp;

    if(_rp->Category != IOCTLCAT)
       return RPDONE;// | RPERR_COMMAND;

    switch (_rp->Function)
    {
    case 0x01:
*/
       __asm {
             hlt
             sti
             }
//       DosBeep(5440L, 3000L);
/*
       break;
    default:
       break;
    }
*/

    rp->status = RPDONE;
    return RPDONE;
}

