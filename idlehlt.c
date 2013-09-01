/*************************************************************************
 *
 * hlt.exe
 *
 * A simple test program to communicate with the Hello World driver.
 * It opens and closes the driver which will beep in response.
 *
 */

#define INCL_DOSFILEMGR          /* File Manager values */
#define INCL_DOSPROCESS
#define INCL_DOSERRORS           /* DOS Error values    */
#define      INCL_DOSDEVICES
#define      INCL_DOSDEVIOCTL
#include <os2.h>
#include <stdio.h>
#include <string.h>


int main( )
{
    ULONG rc;
    ULONG ulAction     = 0L;
    HFILE hfFileHandle = 0L;

DosSetPriority(PRTYS_PROCESS, PRTYC_IDLETIME, 0L, 0L);
    rc = DosOpen( "Idlehlt$",
              &hfFileHandle,
              &ulAction,
              0,
              FILE_NORMAL, FILE_OPEN, OPEN_SHARE_DENYNONE, NULL );
//    printf("DosOpen return %d\n", rc);

    if( rc == 0 )
    {
      while (1) {

          rc = DosDevIOCtl(hfFileHandle, 0x91, 0x01,NULL,0,NULL,0,0,0);
/*
          if (rc)
             printf ("DevIOCtl failed, error code = %ld\n", rc);
          else
             printf ("You should have heard a beep.\n");
*/
                 }
     }
          rc = DosClose(hfFileHandle);
//          DosSleep(0L); // Tried to comment this out thinking the DosSleep might be overriding the HLT
          // it ran the CPU heavy (which was expected) but still no temperature drop.  Tried various times
          // too, no benefit so far.  Either no DosSleep or DosSleep(0L) seems to be the best for cooling,
          // CPU usage now shows heavy as the idle process is not excluded because the idle process is
          // similar to Windows System Idle Process.  While loop has been moved so that this is no longer
          // within it, if desiring to add any DosSleep it needs to be moved into the While loop.
return rc;
}

