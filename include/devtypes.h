#ifndef _DEVTYPES_H_INCLUDED
#define _DEVTYPES_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ >= 1000
#pragma pack(push,1);
#else
#pragma pack(1);
#endif

//#include <os2def.h>
//#include <stdint.h>
#ifndef OS2_INCLUDED
#include <os2.h>
#endif

//#define NEAR __near
//#define FAR  __far
//typedef void __near *NPVOID;
typedef void *NPVOID;

typedef int     Status;
#define SUCCESS (Status)0
#define FAIL    (Status)-1

typedef int     Boolean;
#define False   (Boolean)0
#define True    (Boolean)1

#define PAGE_SIZE       4096

// Standard types
typedef unsigned long   DWORD;
typedef unsigned short  WORD16;
typedef unsigned long   WORD32;
//typedef       void            (*FUNCTION)();
typedef unsigned short  PORT;
typedef ULONG           FARPTR16;

// Pointer type for physical addresses
typedef       WORD32          PHYSICAL;

// Pointer type for linear addresses
typedef       BYTE NEAR *       LINEAR;

// Pointer types for virtual addresses
typedef       WORD16          SEGMENT;
typedef       WORD16          OFFSET;
typedef       WORD32          VIRTUAL;

// Selector type for local and global descriptor tables
//typedef       WORD16          SEL;

// Functions to convert between virtual address types
//inline SEL SELECTOROF(VIRTUAL addr)       {return (WORD16)((WORD32)addr>>16);}
//inline SEGMENT SEGMENTOF(VIRTUAL addr)    {return (WORD16)((WORD32)addr>>16);}
//inline OFFSET OFFSETOF(VIRTUAL addr)      {return (WORD16)addr;}

// Locked segment handle type
//typedef       WORD32          HLOCK;

// Context hook handle type
//typedef       WORD32          HCONTEXT;

// Semaphore handle type for system semaphores
//typedef       WORD32          HSEMAPHORE;

// Character queues
//struct QBASE
//  {
//  WORD16      Size;           // Size of queue (in bytes)
//  WORD16      Index;          // Index of next byte out
//  WORD16      Count;          // Count of bytes in queue
//  };
//template <int s> struct QUEUE : public QBASE
//  {
//  BYTE        Buffer[s];      // Queue buffer
//  };

// Inter device driver communication structure
struct IDCDATA {
    WORD16      Reserved1;      // Reserved (formerly real mode offset)
    WORD16      Reserved2;      // Reserved (formerly real mode code segment)
    WORD16      Reserved3;      // Reserved (formerly real mode data segment)
    OFFSET      Offset;         // Offset of IDC entry point
    SEGMENT     Segment;        // Segment of IDC entry point
    SEGMENT     Data;           // Data segment of IDC device driver
};

// Stack usage information
struct STACKUSAGE {
    WORD16 Size;           // Size of this structure = sizeof(STACKUSAGE)
    WORD16 Flags;          // Flags: bit 1 on = driver enables interrupts
    WORD16 IRQ;            // IRQ number for this stack information
    WORD16 CLIStack;       // Bytes of stack used while interrupts are clear
    WORD16 STIStack;       // Bytes of stack used while interrupts are set
    WORD16 EOIStack;       // Bytes of stack used after EOI is issued
    WORD16 NestingLevel;   // Maximum number of times to nest interrupt
};


//VMLock flags
#define VMDHL_WRITE             0x0008
#define VMDHL_LONG              0x0010
#define VMDHL_VERIFY            0x0020

// Offsets for the end of the resident code and data segments
#define OffsetFinalCS32        ((WORD32)&_OffFinalCS32)
#define OffsetFinalDS32        ((WORD32)&_OffFinalDS32)
#define OffsetBeginCS32        ((WORD32)&_OffBeginCS32)
#define OffsetBeginDS32        ((WORD32)&_OffBeginDS32)


#if __WATCOMC__ >= 1000
#pragma pack(pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
};
#endif

#endif // _DEVTYPES_H_INCLUDED

