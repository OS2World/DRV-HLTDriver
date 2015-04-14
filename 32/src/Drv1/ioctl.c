/***************************************************************************
 *      Created 2005  eCo Software                                         *
 *                                                                         *
 *      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        *
 *      sample code created by eCo Software. This sample code is not part  *
 *      of any standard or eCo Software product and is provided to you     *
 *      solely for the purpose of assisting you in the development of your *
 *      applications.  The code is provided "AS IS", without               *
 *      warranty of any kind. eCo Software shall not be liable for any     *
 *      damages arising out of your use of the sample code, even if they   *
 *      have been advised of the possibility of such damages.              *
 *                                                                         *
 *       Author: Pavel Shtemenko <pasha@paco.odessa.ua>                    *
 *-------------------------------------------------------------------------*/
#define INCL_32
#define INCL_NOBASEAPI
#define INCL_NOPMAPI
#define INCL_ERROR_H

#include <os2.h>
#include "bseerr.h"
#include "miscx.h"
#include "reqpktx.h"
#include "bsekee.h"
#include "debug.h"
ULONG DoIoctl(ULONG fun,void *cur,ULONG SFN)
{
ULONG rc;

rc=0;
SayDebug(1,("Fun[%x] Exit IOctl rc=%d\n",fun,rc) );
#ifdef KERNEL_THREAD
      tid = 0;
      KernThunkStackTo16 ();
      VDHCreateThread(&tid, EventDoing);
      KernThunkStackTo32 ();
      rc = KernBlock(&GPE, 1000, 0, 0, 0);       // Waiting start thread
      if ( rc )
	  SayDebug(1,("Start thread is failed? rc=%d\n",rc));
#endif
return rc;
}

