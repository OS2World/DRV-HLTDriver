/*************************************************************************
 *
 * idlehlt-th.exe
 *
 * A simple program to communicate with the HLT driver.
 * This version uses a separate thread for each processor.
 * Andy Willis     10-22-2007    HLT version
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
#include <process.h>
#include <conio.h>
static   HFILE hfFileHandle = 0L;
int increment = 0;
long array[33];
int lock = 0;
int cont = 1;

void affinityt(void)
{
    int rc;
    MPAFFINITY affinity;
    long test = 0;
    while (lock) {
        DosDevIOCtl(hfFileHandle, 0x91, 0x01,NULL,0,NULL,0,0,0);
    }
    lock = 1;
    DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
    affinity.mask[0] = array[increment];
    increment++;
    rc =DosSetThreadAffinity(&affinity);
    DosSetThreadAffinity(&affinity);
    printf("Set thread's affinity rc = %ld\n", rc);
    printf("Set thread's affinity affinity[0] = %b\n", affinity.mask[0]);
    lock = 0;
    while (cont) {
       rc = DosDevIOCtl(hfFileHandle, 0x91, 0x01,NULL,0,NULL,0,0,0);
// The following was introduced to produce a timing variance to attempt to stop
// halts that occur on some systems.

       test++;
       if (test == 100000000)
       {
         DosSleep(1L);
         test = 0;
       } else {
       DosSleep(0L);
       }

/*
       if (rc)
             printf ("DevIOCtl failed, error code = %ld\n", rc);
       else
             printf ("You should have heard a beep.\n");
*/
    }
    printf("Ending thread\n");
    _endthread();
}

int main( )
{
    ULONG rc;
    ULONG ulAction     = 0L;
    MPAFFINITY affinity;
    long j = 1;
    int tid;
    int i = 0;
    char finish;

    rc = DosOpen( "Idlehlt$",
              &hfFileHandle,
              &ulAction,
              0,
              FILE_NORMAL, FILE_OPEN, OPEN_SHARE_DENYNONE, NULL );
//    printf("DosOpen return %d\n", rc);

    if( rc == 0 )
    {
          rc = DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
//              printf("Thread query return %d\n", rc);
          if (affinity.mask[0] >= 2) {
              affinity.mask[0] = ((affinity.mask[0] + 1) / 2);
          } else {
              affinity.mask[0] = 1;
          }

          rc = DosSetThreadAffinity(&affinity);
              printf("Thread set return %d\n", rc);
          rc = DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
          while (j < ( affinity.mask[0] ))
          {
          array[i] = j;
          tid = _beginthread(affinityt, NULL, 8192, NULL);
//              printf("Thread return %d\n", tid);
//          DosSleep(20L); // Needed to give time for the threads to start.
          j = j * 2;
          i++;
          }
          DosSetPriority(PRTYS_PROCESSTREE, PRTYC_IDLETIME, 0L, 0L);
          DosSleep(2000L);
          while (cont) {
              printf("\nPress Ctrl D to close.\n");
              finish = getch();
              if (finish == 4) {
                  cont = 0;
              } else {
                cont = 1;
              }
          }
          DosWaitThread((PTID)&tid, DCWW_WAIT);
     }
     printf("Closing handle");
     rc = DosClose(hfFileHandle);
return rc;
}

