/*************************************************************************
 *
 * hlt.exe
 *
 * A simple program to communicate with the HLT driver.
 * This version uses a single thread to process all processors.
 * Andy Willis     10-22-2007    HLT version
 *
 */

#define INCL_DOS
#define INCL_32
#define INCL_NOPMAPI
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
    MPAFFINITY affinity;
    long i;
    long j;

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
          rc = DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
          j = 1;
          while (j < ( affinity.mask[0] ))
          {
          affinity.mask[0] = j;
          rc=DosSetThreadAffinity(&affinity);
//          printf("Set thread's affinity rc = %08.8xh\n", rc);
// printf("Set thread's affinity affinity[0] = %ld\n",
//        affinity.mask[0]);
          rc = DosDevIOCtl(hfFileHandle, 0x91, 0x01,NULL,0,NULL,0,0,0);
/*
          if (rc)
             printf ("DevIOCtl failed, error code = %ld\n", rc);
          else
             printf ("You should have heard a beep.\n");
 */
          DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
          j = j * 2;
          }
          DosSleep(0L);
                  }
     }
          rc = DosClose(hfFileHandle);
return rc;
}

