/************************************************************************\
**                                                                      **
**               OS/2(r) Physical Device Driver Libraries               **
**                         for Watcom C/C++ 10                          **
**                                                                      **
**  COPYRIGHT:                                                          **
**                                                                      **
**    (C)ACPSoft 1996                                                   **
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


/* remove.c
 *
 * remove code
 * Support deinstallation of the drivers
 *
 * History:
 *
 * May 13, 96  Alger Pike    Initial version
 * Jun 30, 07  M Greene <greenemk@cox.net>
 */


#include <devhdr.h>
#include <devreqp.h>


void StratRemove(REQP_HEADER FAR* rp)
{
    DosBeep(3000L, 1000L);
    rp->status = RPDONE;
}

