/*************************************************************************
 *
 * test.exe
 *
 * A simple test program to communicate with the Hello World driver.
 * It opens and closes the driver which will beep in response.
 *
 */

#define INCL_DOSFILEMGR          /* File Manager values */
#define INCL_DOSPROCESS
#define INCL_DOSERRORS           /* DOS Error values    */
#include <os2.h>
#include <stdio.h>
#include <string.h>


void main( )
{
    ULONG rc;
    ULONG ulAction     = 0L;
    HFILE hfFileHandle = 0L;

    printf("About to beep....\n");
    rc = DosOpen( "Hello$",
              &hfFileHandle,
              &ulAction,
              0,
              FILE_NORMAL, FILE_OPEN, OPEN_SHARE_DENYNONE, NULL );
    printf("DosOpen return %d\n", rc);

    if( rc == 0 ) {
        printf("Sleep for 5 seconds....\n");
        DosSleep(5000L);
        printf("About to beep....\n");
        rc = DosClose(hfFileHandle);
        printf("DosClose return %d\n", rc);
    }
}

