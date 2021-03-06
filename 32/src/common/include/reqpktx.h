/**************************************************************************
 *
 * IBM Confidential
 *
 * OCO Source Materials
 *
 * (c) Copyright IBM Corp. 1991, 1992, 1998
 *
 * The source code for this program is not published or otherwise divested of its
 * tradesecrets, irrespective of what has been deposited with the U.S. Copyright Office.
 *
 * SOURCE FILE NAME = REQPKTX.H
 *
 * DESCRIPTIVE NAME = ADD/DM - Include Files
 *                    OS/2 Request Packet structures
 *
 * VERSION = V2.0
 *
 * DATE
 *
 * DESCRIPTION :
 *
 * Purpose:  Defines OS/2 Request Packets for BLOCK type devices.
 *
 *
 *
 *
 * FUNCTIONS  :
 *
 *
 *
 * NOTES
 *
 *
 * STRUCTURES
 *
 * EXTERNAL REFERENCES
 *
 *
 *
 * EXTERNAL FUNCTIONS
 *
 * CHANGE ACTIVITY =
 *   DATE      FLAG        APAR   CHANGE DESCRIPTION
 *   --------  ----------  -----  --------------------------------------
 *   mm/dd/yy  @VR.MPPPXX  XXXXX  XXXXXXX
 *   08/02/98  @202143     XXXXX  John Stiles - add 32 bit RP define for OS2LVM
 *
 ****************************************************************************/
#ifndef REQPKTX_H
#define REQPKTX_H

/*
** Misc constants
*/

#define MAX_DISKDD_CMD          29

/*
** Device Driver Header
*/

typedef struct _DDHDR  {             /* DDH */

  PVOID  NextHeader;
  USHORT DevAttr;
  USHORT StrategyEP;
  USHORT InterruptEP;
  UCHAR  DevName[8];
  USHORT ProtModeCS;
  USHORT ProtModeDS;
  USHORT RealModeCS;
  USHORT RealModeDS;
  ULONG  SDevCaps;                   /* bit map of DD /MM restrictions */
} DDHDR;

/*
** BIOS Parameter Block
*/

typedef struct _BPB  {                  /* BPB */

  USHORT        BytesPerSector;
  UCHAR         SectorsPerCluster;
  USHORT        ReservedSectors;
  UCHAR         NumFATs;
  USHORT        MaxDirEntries;
  USHORT        TotalSectors;
  UCHAR         MediaType;
  USHORT        NumFATSectors;
  USHORT        SectorsPerTrack;
  USHORT        NumHeads;
  ULONG         HiddenSectors;
  ULONG         BigTotalSectors;
  UCHAR         Reserved_1[6];
} BPB, FAR *PBPB;

typedef_NearPointer(BPB, NPBPB);

#ifdef INCL_32
typedef USHORT       BPBS[];         /* An array of NEAR BPB Pointers */
#else
typedef BPB    NEAR *BPBS[];         /* An array of NEAR BPB Pointers */
#endif

typedef BPBS   FAR  *PBPBS;          /* A pointer to the above array  */

/*
**  Request Packet Header
*/

typedef struct _RPH  FAR *PRPH;
typedef_NearPointer(struct _RPH, NPRPH);

typedef struct _RPH  {                  /* RPH */

  UCHAR         Len;
  UCHAR         Unit;
  UCHAR         Cmd;
  USHORT        Status;
  UCHAR         Flags;
  UCHAR         Reserved_1[3];
  PRPH          Link;
} RPH;


/* Status word in RPH */

#define STERR        0x8000           /* Bit 15 - Error                */
#define STINTER      0x0400           /* Bit 10 - Interim character    */
#define STBUI        0x0200           /* Bit  9 - Busy                 */
#define STDON        0x0100           /* Bit  8 - Done                 */
#define STECODE      0x00FF           /* Error code                    */
#define WRECODE      0x0000

#define STATUS_DONE       0x0100
#define STATUS_ERR_UNKCMD 0x8003

/* Bit definitions for Flags field in RPH */

#define RPF_Int13RP         0x01        /* Int 13 Request Packet           */
#define RPF_CallOutDone     0x02        /* Int 13 Callout completed        */
#define RPF_PktDiskIOTchd   0x04        /* Disk_IO has touched this packet */
#define RPF_CHS_ADDRESSING  0x08        /* CHS Addressing used in RBA field*/
#define RPF_Internal        0x10        /* Internal request packet command */
#define RPF_TraceComplete   0x20        /* Trace completion flag           */

/*
**  Init Request Packet
*/

typedef struct _RPINIT  {               /* RPINI */

  RPH           rph;
  UCHAR         Unit;
  PFN           DevHlpEP;
  PSZ           InitArgs;
  UCHAR         DriveNum;
} RPINITIN, FAR *PRPINITIN;

typedef struct _RPINITOUT  {            /* RPINO */

  RPH           rph;
  UCHAR         Unit;
  USHORT        CodeEnd;
  USHORT        DataEnd;
  PBPBS         BPBArray;
  USHORT        Status;
} RPINITOUT, FAR *PRPINITOUT;

typedef struct _RP_DRIVELETTER          /* RPDL */
{
  RPH           rph;
  UCHAR         DriveLetter;
  ULONG         Spare;
} RP_DRIVELETTER, FAR *PRP_DRIVELETTER;

/*
** struct DDD_Parm_List moved to H\DSKINIT.H
*/


#ifndef INCL_INITRP_ONLY

/*
**  Media Check Request Packet
*/

typedef struct _RP_MEDIACHECK  {        /* RPMC */

  RPH           rph;
  UCHAR         MediaDescr;
  UCHAR         rc;
  PSZ           PrevVolID;
} RP_MEDIACHECK, FAR *PRP_MEDIACHECK;

/*
**  Build BPB
*/

typedef struct _RP_BUILDBPB  {          /* RPBPB */

  RPH           rph;
  UCHAR         MediaDescr;
  ULONG         XferAddr;
  PBPB          bpb;
  UCHAR         DriveNum;
} RP_BUILDBPB, FAR *PRP_BUILDBPB;


/*
**  Read, Write, Write Verify
*/

typedef struct _RP_RWV  {               /* RPRWV */

  RPH           rph;
  UCHAR         MediaDescr;
  ULONG         XferAddr;
  USHORT        NumSectors;
  ULONG         rba;
  USHORT        sfn;
} RP_RWV, FAR *PRP_RWV;


/*
**  Nondestructive Read
*/

typedef struct _RP_NONDESTRUCREAD  {    /* RPNDR */

  RPH           rph;
  UCHAR         character;
} RP_NONDESTRUCREAD;

typedef_NearPointer(struct _RP_NONDESTRUCREAD, RPR_NONDESTRUCREAD);


/*
**  Open/Close Device
*/

typedef struct _RP_OPENCLOSE  {         /* RPOC */

  RPH           rph;
  USHORT        sfn;
} RP_OPENCLOSE, FAR *PRP_OPENCLOSE;


/*
**  IOCTL Request Packet
*/

typedef struct _RP_GENIOCTL  {          /* RPGIO */

  RPH           rph;
  UCHAR         Category;
  UCHAR         Function;
  PUCHAR        ParmPacket;
  PUCHAR        DataPacket;
  USHORT        sfn;
  USHORT        ParmLen;                /* VPNP */
  USHORT        DataLen;                /* VPNP */
} RP_GENIOCTL, FAR *PRP_GENIOCTL;



/*
**  Save Restore Request Packet
*/

typedef struct _RPSaveRestore  {               /* RPSaveRestore */

  RPH           rph;
  UCHAR         FuncCode;
} RPSAVERESTORE, FAR *PRPSAVERESTORE;


/*
**  Partitionable Fixed Disks
*/

typedef struct _RP_PARTFIXEDDISKS  {    /* RPFD */

  RPH           rph;
  UCHAR         NumFixedDisks;
} RP_PARTFIXEDDISKS, FAR *PRP_PARTFIXEDDISKS;

/*
**  Get Unit Map
*/

typedef struct _RP_GETUNITMAP  {        /* RPUM */

  RPH           rph;
  ULONG         UnitMap;
} RP_GETUNITMAP, FAR *PRP_GETUNITMAP;


/*
**  Get Driver Capabilities  0x1D
*/

#ifdef Drova
typedef struct _RP_GETDRIVERCAPS  {     /* RPDC */

  RPH           rph;
  UCHAR         Reserved[3];
  P_DriverCaps  pDCS;
  P_VolChars    pVCS;

} RP_GETDRIVERCAPS, FAR *PRP_GETDRIVERCAPS;
#endif

/*
**  32 bit Request Packet  @202143
*/

#define DataPacketLocked   0x00000001  // Indicates the User's Data Packet is currently locked
#define ParmPacketLocked   0x00000002  // Indicates the User's Parm Packet is currently locked

typedef struct _RP32  {               /* RP32 */

  PRPH          pRPH;
  PUCHAR        pParmPacket;
  PUCHAR        pDataPacket;
  PUCHAR        pUserBuffer;
  PVOID         pRP16;
  ULONG         LockFlags;
  UCHAR         DataPacketLockHandle[12];
  UCHAR         ParmPacketLockHandle[12];
} RP32, FAR *PRP32;

#endif
#endif
