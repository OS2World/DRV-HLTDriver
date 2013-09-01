/************************************************************************\
**                                                                      **
**               OS/2 Physical Device Driver Example Code               **
**                       for Open Watcom C/C++                          **
**                                                                      **
**  COPYRIGHT:                                                          **
**                                                                      **
**    (C) Copyright Advanced Gravis Computer Technology Ltd 1994.       **
**        All Rights Reserved.                                          **
**                                                                      **
**    Also includes code from Open Watcom perforce tree which was       **
**    originally adapted from the Fall 1991 issue of                    **
**    IBM Personal Systems Developer magazine.                          **
**                                                                      **
**    Adapted for Open Watcom C/C++                                     **
**    Original Author: Rick Fishman                                     **
**                     Code Blazers, Inc.                               **
**                     4113 Apricot                                     **
**                     Irvine, CA 92720                                 **
**                                                                      **
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

/* Strategy.c
 *
 * Device driver strategy entry point and dispatch table
 *
 * History:
 *
 * Sep 30, 94  David Bollo    Initial version
 *
 * Jul 02, 2007 M Greene       Modified for Open Watcom use as hello world
 *                             device driver example
 *
 * Sep 13, 2011 Andy Willis    HLT version
 */

#include <devhdr.h>
#include <devreqp.h>

// Declare strategy entry points that are located in other source files
//
// StratInit  - Initialization entry point [Init.c]
// StratIOCtl - Audio IOCtl interface [IOCtl.c]

extern uint16_t StratInit(REQP_INIT FAR *rp);
extern void StratOpen(REQP_HEADER FAR* rp);
extern void StratClose(REQP_HEADER FAR* rp);
extern void StratWrite(REQP_HEADER FAR* rp);
extern void StratRead(REQP_HEADER FAR* rp);
extern void StratError(REQP_HEADER FAR* rp);
extern void StratRemove(REQP_HEADER FAR* rp);
extern void StratShutdown(REQP_HEADER FAR* rp);
extern uint16_t StratIOCtl(REQP_HEADER FAR* rp);


// Strategy entry point
//
// The strategy entry point must be declared according to the STRATEGY
// calling convention, which fetches arguments from the correct registers.


ULONG  DevHlp;  // DevHelp Interface Address

#pragma aux STRATEGY far parm [es bx];
#pragma aux (STRATEGY) Strategy;

static void StratNoOp( REQP_HEADER FAR *rp )
{
    rp->status = RPDONE;
}

void Strategy( REQP_ANY FAR *rp )
{
    // Strategy routine for device set in header.c
    if( rp->header.command < RP_END ) {

        switch( rp->header.command ) {

        case RP_INIT:
            StratInit( (REQP_INIT FAR *)rp );
            break;

        case RP_OPEN:
            StratOpen( (REQP_HEADER FAR *)rp );
            break;

        case RP_CLOSE:
            StratClose( (REQP_HEADER FAR *)rp );
            break;

        case RP_READ:
            StratRead( (REQP_HEADER FAR *)rp );
            break;

        case RP_WRITE:
            StratWrite( (REQP_HEADER FAR *)rp );
            break;

        case RP_IOCTL:
            StratIOCtl( (REQP_HEADER FAR *)rp );
            break;

        case RP_READ_NO_WAIT:
        case RP_INPUT_STATUS:
        case RP_INPUT_FLUSH:
        case RP_WRITE_VERIFY:
        case RP_OUTPUT_STATUS:
        case RP_OUTPUT_FLUSH:
            StratNoOp( (REQP_HEADER FAR *)rp );
            break;
        default:
            rp->header.status = RPERR_COMMAND | RPDONE;
        }
    } else {
        rp->header.status = RPERR_COMMAND | RPDONE;
    }
}

