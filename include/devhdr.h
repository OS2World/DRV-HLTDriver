/*
 * Device driver header
 */
#ifndef _DEVHDR_H_INCLUDED
#define _DEVHDR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ >= 1000
#pragma pack(push,1);
#else
#pragma pack(1);
#endif

#include <stdint.h>
#include <devtypes.h>

/*
 * Device Table Record
 *
 * Devices are described by a chain of these records
 *
 * Look at DEVHDR.INC for a description
 * of the Device Driver Header
 */

typedef struct DEVHEADER DEVHEADER;
struct DEVHEADER {
  struct DEVHEADER FAR *next;      // next driver in chain
  uint16_t         DAWFlags;       // device attribute word
  NPVOID           StrategyEntry;  // offset to strategy routine
  NPVOID           IDCEntry;       // offset to IDC routine
  uint8_t          Name[8];        // driver name
  uint16_t         DAWProtCS;      // * Protect-mode CS of strategy entry pt
  uint16_t         DAWProtDS;      // * Protect-mode DS
  uint16_t         DAWRealCS;      // * Real-mode CS of strategy entry pt
  uint16_t         DAWRealDS;      // * Real-mode DS
  uint32_t         Capabilities;   // Capabilities bit strip
};
/*
   * listed as reserved in docs (8 bytes but def'd as USHORT - WTF?

   uint8_t   (unsigned char)   BYTE
   uint16_t  (unsigned short)  WORD
   uint32_t  (unsigned long)   DWORD
*/

/*
 * Marks end of DEVHEADER chain
 */
#define       FENCE       ((DEVHEADER FAR*)0xFFFFFFFFul)

/*
 * Constants for device attribute word

F E D C B A 9 8 7 6 5 4 3 2 1 0
| | | | | | | | | | | | | | | |
| | | | | | | | | | | | | | |  - DAW_STDIN
| | | | | | | | | | | | | |  --- DAW_STDOUT
| | | | | | | | | | | | |  ----- DAW_NUL
| | | | | | | | | | | |  ------- DAW_CLOCK
| | | | | | | | | | |  --------- DAW_SPEC
| | | | | | | | | |  ----------- DAW_ADD_ON
| | | | | | | | |  ------------- DAW_GIOCTL
| | | | | |  ------------------- DAW_FCNLEV (DAW_LEVEL1,DAW_LEVEL2,DAW_LEVEL3)
| | | | |  --------------------- ???? (Reserved set to 0)
| | | |  ----------------------- DAW_OPENCLOSE
| | |  ------------------------- DAW_SHARE
| |  --------------------------- DAW_NONIBM
|  ----------------------------- DAW_IDC
 ------------------------------- DAW_CHARACTER

DAW_FCNLEV
   DAW_LEVEL0  DOS 3.0 and before
   DAW_LEVEL1  DOS 5.0
   DAW_LEVEL2  OS/2 v1.2
   DAW_LEVEL3  OS/2 v2.0 (support of memory above 16MB)

*/
typedef enum{
    DAW_STDIN     = 0x0001,     // Standard input device
    DAW_STDOUT    = 0x0002,     // Standard output device
    DAW_NUL       = 0x0004,     // Nul device
    DAW_CLOCK     = 0x0008,     // Clock device
    DAW_SPEC      = 0x0010,     // Supports INT 29H
    DAW_ADD_ON    = 0x0020,     // Device is add-on driver (BWS)
    DAW_GIOCTL    = 0x0040,     // Device supports generic ioctl

    DAW_LEVEL0    = 0x0000,     // Level 0 device
    DAW_LEVEL1    = 0x0080,     // Level 1 device
    DAW_LEVEL2    = 0x0100,     // Level 2 device
    DAW_LEVEL3    = 0x0180,     // Level 3 device
    DAW_FCNLEV    = 0x0380,     // Device function level

/*                  0x0400      ??? */
    DAW_OPENCLOSE = 0x0800,     // Requires open, close, remove media requests
    DAW_SHARE     = 0x1000,     // Sharable device
    DAW_NONIBM    = 0x2000,     // Non-IBM Block device
    DAW_IDC       = 0x4000,     // IDC aware device
    DAW_CHARACTER = 0x8000,     // Character device
} DAW_flags;


/*
 * Constants for capabilities bit strip (used by level 3 devices)

6 5 4 3 2 1 0
| | | | | | |
| | | | | |  - CAP_SHUTDOWN
| | | | |  --- CAP_32BIT
| | | |  ----- CAP_PARALLEL
| | |  ------- CAP_ADD
| |  --------- CAP_COMPLETE
|  ----------- CAP_SAVERESTORE
 ------------- CAP_LVM
*/

typedef enum {
    CAP_NULL        = 0x00000000,
    CAP_SHUTDOWN    = 0x00000001, // Supports IOCtl2 and shutdown
    CAP_32BIT       = 0x00000002, // Supports addressing above 16MB
    CAP_PARALLEL    = 0x00000004, // Supports parallel ports
    CAP_ADD         = 0x00000008, // Participates in ADD strategy
    CAP_COMPLETE    = 0x00000010, // Supports Init Complete request
    CAP_SAVERESTORE = 0x00000020,
    CAP_LVM         = 0x00000040  // Can handle LVM DMD interfaces
} CAP_flags;

#if __WATCOMC__ >= 1000
#pragma pack(pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
};
#endif

#endif // _DEVHDR_H_INCLUDED

