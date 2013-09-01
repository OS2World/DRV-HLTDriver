#define INCL_DOS
#define INCL_32
#define INCL_DOSERRORS
#define INCL_NOPMAPI
#include <os2.h>
#include <stdio.h>

int main(void)
{
APIRET rc;
MPAFFINITY affinity;
    long i;
    long j;


rc = DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
printf("Query system's affinity rc = %b\n",rc);
printf("Query system's affinity affinity[0] = %b, affinity[1] = %b\n\n",
        affinity.mask[0], affinity.mask[1]);

          rc = DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
          j = 1;
          i = 1;
          while(i < (affinity.mask[0]))
          {
          affinity.mask[0] = j;
          rc=DosSetThreadAffinity(&affinity);

printf("Set thread's affinity rc = %b\n", rc);
printf("Set thread's affinity affinity[0] = %b, affinity[1] = %b\n\n",
        affinity.mask[0], affinity.mask[1]);

          DosQueryThreadAffinity(AFNTY_SYSTEM, &affinity);
          j = j * 2;
          i = i * 2;
          }

return rc;
}

