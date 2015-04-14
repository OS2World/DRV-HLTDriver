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
#pragma pack(1)
#include "bseerr.h"
#include "miscx.h"
#include "reqpktx.h"
#include "bsekee.h"
#include "debug.h"
#pragma pack()

#include <psd.h>
#include <acpi.h>
#include <acpiapi.h>
#include <ipdc.h>
#include <acpifun.h>

void _cdecl printk (char * , ...);
void PutCom(unsigned short );
ULONG GetESP (void);
ULONG DoIoctl (ULONG,void *,ULONG);
void PutToRead(ULONG ch);
ULONG CopyToUser(UCHAR *Buffer, ULONG count);
void  PrintDevCall(PRPH pkt, char *who);


/*
 *  Function OPEN
 *  in:  standard drivers packet
 *  out: nothing
 */
void OpenDev(
    PRPH pkt)
{
    PRP_OPENCLOSE opn; 
    ULONG         rc = 0;

    opn=(PRP_OPENCLOSE)pkt;
    PrintDevCall(pkt, "Open");
    SayDebug(1,("SFN   0x%x\n",(ULONG)opn->sfn));

    pkt->Status |= STDON;

    if (rc)
    {
        pkt->Status |= (STERR | 87);
    }
}
/*
 *  Function CLOSE
 *  in:  standard drivers packet
 *  out: nothing
 */
void CloseDev(
    PRPH pkt)
{
    PRP_OPENCLOSE opn;

    opn = (PRP_OPENCLOSE)pkt;

    PrintDevCall(pkt, "Close");
    SayDebug(1,("SFN   0x%x\n",(ULONG)opn->sfn));

    pkt->Status |= STDON;

}
/*
 *  Function Read
 *  in:  standard drivers packet
 *  out: debug log from acpi.psd
 */
void Read(
    PRPH pkt)
{
    PRP_RWV  opn;
    UCHAR  *ppLinAddr;
    USHORT Sel;
    ULONG rc,Size;

    opn = (PRP_RWV)pkt;

#ifdef NEED_DEBUG_READ
    PrintDevCall(pkt, "Read");
    SayDebug(1,("Media  0x%x\n",(unsigned long)opn->MediaDescr));
    SayDebug(1,("XferAd 0x%x\n",opn->XferAddr));
    SayDebug(1,("NumSec 0x%x\n",(unsigned long)opn->NumSectors));
    SayDebug(1,("RBA    0x%x\n",(unsigned long)opn->rba));
    SayDebug(1,("SFN    0x%x\n",(unsigned long)opn->sfn));
#endif

    pkt->Status |= STDON;

    Size = (ULONG)opn->NumSectors & (~0xfff);
    if (Size != (ULONG)opn->NumSectors)
    {
        Size +=0x1000;
    }
    rc = KernVMAlloc (Size, VMDHA_PHYS , (void **)&ppLinAddr,(void **)&opn->XferAddr,(void **)&Sel);
    if (rc == 0)
    {
        opn->NumSectors=(USHORT)CopyToUser(ppLinAddr,(ULONG)opn->NumSectors);
        rc = KernVMFree(ppLinAddr);
    }

}

/*
 *  Function IOCTL
 *  in:  standard drivers packet
 *  out: nothing
 */
void IOCtl(
    PRPH pkt)
{
    PRP_GENIOCTL ioc;
    ULONG  SizeP,SizeD, rc;

    ioc=(PRP_GENIOCTL)pkt;

#ifdef NEED_FULL_IOCTL_DEBUG_CALL
    PrintDevCall(pkt, "IOCtl");
    SayDebug(1,("Category   0x%x\n",(unsigned long)ioc->Category));
    SayDebug(1,("ParmPacket 0x%x\n",ioc->ParmPacket));
    SayDebug(1,("DataPacket 0x%x\n",ioc->DataPacket));
#endif
    SayDebug(1,("Function   0x%x\n",(unsigned long)ioc->Function));
    SayDebug(1,("SFN        0x%x\n",(unsigned long)ioc->sfn));

    if (pkt->Len == sizeof(RP_GENIOCTL))               // work with IOCTL2
    {
#ifdef NEED_FULL_IOCTL_DEBUG_CALL
        SayDebug(1,("ParmLen    0x%x\n",(unsigned long)ioc->ParmLen));
        SayDebug(1,("DataLen    0x%x\n",(unsigned long)ioc->DataLen));
#endif
        SizeP = (ULONG)ioc->ParmLen;
        SizeD = (ULONG)ioc->DataLen;
    }

}
void SaveRestore(PRPSAVERESTORE pkt)
{
    PrintDevCall((PRPH)pkt, "SaveRestore");
    SayDebug(1,("SaveRestore - %x\n",(ULONG)pkt->FuncCode));
}
ULONG NoIrq=0;
extern ULONG ComPort;
void ParseCmd(
    char *s)
{
    ULONG i;
    char *p;

    p=s;
       if (p)
          while(*p)
               {
               if( (*p) == '/')
                 {
                 p++;
                 switch(*p)
                       {
                       // Com port number for debug output
                       case 'O':
                       case 'o':
                          i=0;
                          p++;
                          if( ((*p) >= '0') && ((*p) <= '9') )
                            i = (*p) - '0';
                          if(i == 1)
                            ComPort=0x3F8;
                          else
                          if(i == 2)
                            ComPort=0x2F8;
                          break;
                       case 'N':
                       case 'n':
                          NoIrq=1;
                          break;
                       default:
                          break;
                       }
                 }
               p++;
               }
}
extern unsigned long _edata;
void Zend(void);
extern ULONG *IRQFlag;
ULONG KernBeep(ULONG Freq,ULONG Duration);

ULONG InitDrv=0;
PACPIFUNCTION PSD = NULL;                   // Pointer to ACPI function
unsigned char *DebugAddr=0;

/*
 *  Function Init
 *  in:  standard drivers packet
 *  out: nothing
 */
void 
Init(
    PRPH pkt)
{
    ULONG size,rc,StartAdr,EndAdr,i;
    KernVMLock_t    lock;
    unsigned char *s;
    PRPINITIN rp;

    rp = (PRPINITIN)pkt;

    if ((ULONG)pkt->Cmd == 0x1b)
    {
        s = (PUCHAR)KernSelToFlat((ULONG)rp->InitArgs);
        SayDebug(1,("Argv: %s\n",s));
        ParseCmd(s);
        SayDebug(1,("ComPort: %x Ni:%d\n",ComPort,NoIrq));
    }

    // After parse com port number we can do debug output
    PrintDevCall(pkt, "Init");
// KernBeep(5000,1000);

    if (InitDrv)
    {
        SayDebug(1,("Already init\n"));
        pkt->Status |= STDON;
        return;
    }
    // Debug memory
    rc = KernVMAlloc( 0xFFFF , VMDHA_FIXED | VMDHA_USEHIGHMEM , (void **)&DebugAddr, (void **)&StartAdr, (void **)&EndAdr );
    SayDebug(1,("AllocD rc=%d\n",rc));
    if (rc == 87)    //EarlyMemoryInit
    {
        rc = KernVMAlloc( 0xFFFF ,VMDHA_FIXED , (void **)&DebugAddr, (void **)&StartAdr, (void **)&EndAdr);
        SayDebug(1,("Alloc2 rc=%d\n",rc));
        if (rc)
        {
            DebugAddr = 0;
        }
    }
    PSD = (PACPIFUNCTION)InitACPICall("DRV1");
    InitDrv++;

    pkt->Status |= STDON;
    SayDebug(1,("ESP %x\n",GetESP()));
}
/*
 *  Function Shutdown
 *  in:  standard drivers packet
 *  out: nothing
 */
void 
ShutDown(
    PRPH pkt)
{
    ULONG rc;
    PrintDevCall(pkt, "Shutdown");

}
/*
 *  Function BAD
 *  in:  no
 *  out: error
 */
void 
BAD(
    PRPH pkt)
{
    PrintDevCall(pkt, "Unsupported");
    pkt->Status |= (STERR + STATUS_ERR_UNKCMD + STDON);
}

void PUTC(ULONG c)
{
 if(ComPort)
    PutCom(c);
PutToRead(c);
}
/*
 * Debug output ComPort, Screen, Buffer for Read operation in acpica$
 */
ULONG CurPoint=0;
ULONG ReadPoint=0;
/**
* Copy debug to user buffer
* @Buffer   pointer to user buffer
* @count    size of user buffer
* @return   really coping
*/
ULONG
CopyToUser(
    UCHAR *Buffer,
    ULONG count)
{
    ULONG i;

    if (ReadPoint > CurPoint) 
    {
        ReadPoint=0;                            // Large 4Gb pointer
    }
    if (ReadPoint == CurPoint)
    {
        return 0;   
    }

    if ((CurPoint - ReadPoint) > 0xffff) 
    {
        ReadPoint=CurPoint-0xffff;  // Large 64kb record
    }

    for (i=0; i < count; i ++)
    {
        if (ReadPoint >= CurPoint)                                      // Nothing to out
        {
           ReadPoint = 0;                                                // Zero pointers
           CurPoint  = 0;
           break;
        }
        Buffer[i]=DebugAddr[ReadPoint & 0xffff];                        // copy to user buffer
        ReadPoint++;
    }

    return i;

}
/**
* Insert symbol to user buffer
* @ch     symbol to insert
* @return None
*/
void 
PutToRead(
    ULONG ch)
{
    UCHAR c;

    c = (unsigned char)ch;
    if (DebugAddr)
    {
        DebugAddr[CurPoint & 0xffff]=c;
        CurPoint++;
    }

}

/*
 * Debug output
 */
void putl (ULONG ul, ULONG base)
{
    if (ul / base != 0)
	putl (ul / base, base);
    PUTC ("0123456789ABCDEF"[ul % base]);
}

void putll (unsigned long ul, ULONG base)
{
    if (ul / base != 0)
	putll (ul / base, base);
    PUTC ("0123456789ABCDEF"[ul % base]);
}

/*  format - replace the C runtime formatting routines.
 *
 *  format is a near-replacement for the *printf routines in the C runtime.
 *
 *  fmt 	formatting string.  Formats currently understood are:
 *		    %c single character
 *		    %[l[l]]d %[l[l]]x
 *		    %[F]s
 *		    %p
 *		      * may be used to copy in values for m and n from arg
 *			list.
 *		    %%
 *  arg 	is a list of arguments
 */
void format (char *fmt, PVOID pv)
{
   char c;
    PSZ psz;
    ULONG base;
    ULONG MaxS,MinS,Point;

    while (c = *fmt++)
    {
           if (c == '\n') 
           {
	        PUTC ('\r');
	        PUTC ('\n');
	    }
	    else
	      if (c != '%')
             {
	          PUTC (c);
             }
	      else 
             {
	          BOOL fLongLong = FALSE;
	          BOOL fFar = FALSE;

                 MaxS  = 0;
                 MinS  = 0;
                 Point = 0;
                 base  = 10;
	          while ((*fmt >= '+') && (*fmt <= '9')) /* Ignore length for now */
                 {
		          if (*fmt == '.') 
                        {
                            Point++;
                        }
		          if ((*fmt >= '0') && (*fmt <= '9'))
		          {
		              if (Point)
                            {
                                if (MinS)
                                {
                                    MinS *= 10;
                                }
		                  MinS = (MinS +(*fmt-'0'));
                            }
		              else
                            {
                                if (MaxS)
                                {
                                    MaxS *= 10;
                                }
		                  MaxS = ( MaxS + (*fmt-'0'));
                            }
                        }      
		          fmt++;
                 }
	    if (*fmt == 'h')                       /* Ignore for now */
		fmt++;
	    if (*fmt == 'l')
	      {
		fmt++;
		if ( (*fmt == 'l') ||(*fmt == 'L'))  {
		    fLongLong = TRUE;
		    fmt++;
		}
	    }
	    if (*fmt == 'F') {
		fFar = TRUE;
		fmt++;
	    }

	    switch (*fmt++) {
	    case 'c':
		PUTC ((char) * MAKETYPE (pv, PULONG));
		++ MAKETYPE (pv, PULONG);
		break;
	    case 'x':
	    case 'X':
	    case 'p':          //PS
		base = 16;
	    case 'd':
	    case 'u':
		if (fLongLong) {
		    putll (* MAKETYPE (pv, UINT64 *), base);
		    ++ MAKETYPE (pv, UINT64 *);
		} else {
		    putl (* MAKETYPE (pv, PULONG), base);
		    ++ MAKETYPE (pv, PULONG);
		}
		break;
	    case 's':
		if (fFar) {
		    psz = * MAKETYPE (pv, PSZ *);
		    ++ MAKETYPE (pv, PSZ *);
		} else {
		    psz = * MAKETYPE (pv, NPSZ *);
		    ++ MAKETYPE (pv, NPSZ *);
		}
	      if(MaxS ==  0 ) MaxS=512;
	      if(MaxS > 512 ) MaxS=512;
	      if (psz)
		   while ( (*psz >= ' ') && (MaxS != 0))
		       {
			PUTC (*psz);
		       psz++;
		       MaxS--;
		       if(MinS)MinS--;
		       }
	      MaxS=0;
	      MinS=0;
	      Point=0;
		break;
	    case '%':
		PUTC ('%');
		break;
	    default:
		PUTC ('?');
		PUTC ('\'');
		PUTC (fmt[-1]);
		PUTC ('\'');
	    }
	}
    }
}
void _cdecl PrintfDev (char * fmt, ...)
{
    format (fmt, (PVOID) (&fmt+1));
}
void _cdecl printk (char * fmt, ...)
{
 PrintfDev("MON: ");
 format (fmt, (PVOID) (&fmt+1));
}
void 
PrintDevCall(
    PRPH pkt, 
    char *who)
{

    SayDebug(1,("%s %x\n",who,pkt));
    SayDebug(1,("Len    %d\n",(unsigned long)pkt->Len));
    SayDebug(1,("Unit   %d\n",(unsigned long)pkt->Unit));
    SayDebug(1,("Cmd    0x%x\n",(unsigned long)pkt->Cmd)); 
    SayDebug(1,("Status 0x%x\n",(unsigned long)pkt->Status));
    SayDebug(1,("Flags  0x%x\n",(unsigned long)pkt->Flags));
    SayDebug(1,("Link   0x%x\n",pkt->Link));

}