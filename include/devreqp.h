/*
 * Some type definitions for OS/2 2.x/3.x  driver request packets.
 */
#ifndef _DEVREQP_H_INCLUDED
#define _DEVREQP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ >= 1000
#pragma pack(push,1);
#else
#pragma pack(1);
#endif

/*
 * Look at \WATCOM\H\OS2\DEVSYM.INC for a description
 * of the Device Driver Request Packet Definitions
 */

//typedef struct REQP_HEADER REQP_HEADER;
typedef struct _REQP_HEADER {
    uint8_t            length;        // Length of request packet
    uint8_t            unit;          // Unit code (B)
    uint8_t            command;       // Command code
    uint16_t           status;        // Status code
    uint32_t           res1;          // Flags
    struct REQP_HEADER FAR *next;     // Link to next request packet in queue
} REQP_HEADER;


typedef struct {
    REQP_HEADER header;
    union{
        struct{
            uint8_t   res;            // Unused
            uint32_t  devhlp;         // Address of Dev Help entry point
            int8_t    *parms;         // Command-line arguments   PCHAR
            uint8_t   drive;          // Drive number of first unit
        } in;
        struct  {
            uint8_t   units;          // Number of supported units
            uint16_t  finalcs;        // Offset to end of code
            uint16_t  finalds;        // Offset of end of data
            void      *bpb;           // BIOS parameter block   PVOID
        } out;
    };
} REQP_INIT;


typedef struct {
    REQP_HEADER header;
    uint8_t     media;          // Media descriptor
    uint32_t    transaddr;      // Transfer physical address
    uint16_t    count;          // bytes/sectors count
    uint32_t    start;          // Starting sector for block device
    HFILE       fileid;         // System file number
} REQP_RWV;


typedef struct{
    REQP_HEADER header;
    HFILE       fileid;         // System file number
} REQP_OPENCLOSE;


// Request packet 10 (BC): IO Control
typedef struct {
    uint8_t       Category;     // Category code
    uint8_t       Function;     // Function code
    uint32_t      ParmPacket;   // Parameter packet
    uint32_t      DataPacket;   // Data packet
    uint16_t      FileID;       // System file number
    uint16_t      ParmLength;   // Parameter packet length
    uint16_t      DataLength;   // Data packet length
} RPIOCtl;


typedef enum {
    RPERR               =   0x8000,     // Error
    RPDEV               =   0x4000,     // Device-specific error code
    RPBUSY              =   0x0200,     // Device is busy
    RPDONE              =   0x0100,     // Command complete
    RPERR_PROTECT       =   0x8000,     // Write-protect error
    RPERR_UNIT          =   0x8001,     // Unknown unit
    RPERR_READY         =   0x8002,     // Not ready
    RPERR_COMMAND       =   0x8003,     // Unknown command
    RPERR_CRC           =   0x8004,     // CRC error
    RPERR_LENGTH        =   0x8005,     // Bad request length
    RPERR_SEEK          =   0x8006,     // Seek error
    RPERR_FORMAT        =   0x8007,     // Unknown media
    RPERR_SECTOR        =   0x8008,     // Sector not found
    RPERR_PAPER         =   0x8009,     // Out of paper
    RPERR_WRITE         =   0x800A,     // Write fault
    RPERR_READ          =   0x800B,     // Read fault
    RPERR_GENERAL       =   0x800C,     // General failure
    RPERR_DISK          =   0x800D,     // Disk change
    RPERR_MEDIA         =   0x8010,     // Uncertain media
    RPERR_INTERRUPTED   =   0x8011,     // Call interrupted (character)
    RPERR_MONITOR       =   0x8012,     // Monitors unsupported
    RPERR_PARAMETER     =   0x8013,     // Invalid parameter
    RPERR_USE           =   0x8014,     // Device in use
    RPERR_INIT          =   0x8015,     // Non-critical init failure
} REQP_status;


typedef union {
    REQP_HEADER         header;
    REQP_INIT           init;
    REQP_RWV            rwv;
    REQP_OPENCLOSE      openclose;
} REQP_ANY;

/*
 * Look at \WATCOM\H\OS2\DEVCMD.INC for a list
 * of the Device Driver Request Packet Commands
 */

typedef enum {
     RP_INIT            =   0x00, // CMDMedChk          Media Check
     RP_MEDIA_CHECK     =   0x01, // CMDBldBPB          build BPB
     RP_BUILD_BPB       =   0x02, // CMDBldBPB          build BPB
     // 0x03 Reserved                CMDIOCTLR          reserved for 3.x compatability
     RP_READ            =   0x04, // CMDINPUT           read data from device                   ³
     RP_READ_NO_WAIT    =   0x05, // CMDNDR             non-destructive read                    ³
     RP_INPUT_STATUS    =   0x06, // CMDInputS          input status                            ³
     RP_INPUT_FLUSH     =   0x07, // CMDInputF          input flush                             ³
     RP_WRITE           =   0x08, // CMDOUTPUT          write data to device                    ³
     RP_WRITE_VERIFY    =   0x09, // CMDOUTPUTV         write data and verify                   ³
     RP_OUTPUT_STATUS   =   0x0a, // CMDOutputS         output status                           ³
     RP_OUTPUT_FLUSH    =   0x0b, // CMDOutputF         output flush                            ³
     // 0x0C Reserved                CMDIOCTLW          reserved for 3.x compatability
     RP_OPEN            =   0x0d, // CMDOpen            device open
     RP_CLOSE           =   0x0e, // CMDClose           device close
     RP_REMOVABLE       =   0x0f, // CMDRemMed          is media removable
     RP_IOCTL           =   0x10, // CMDGenIOCTL        Generic IOCTL
     RP_RESET           =   0x11, // CMDResMed          reset media uncertain
     RP_GET_DRIVE_MAP   =   0x12, // CMDGetLogMap
     RP_SET_DRIVE_MAP   =   0x13, // CMDSetLogMap
     RP_DEINSTALL       =   0x14, // CMDDeInstall       De-Install driver
     // 0x15 Reserved                reserved
     RP_PARTITIONABLE   =   0x16, // CMDPartfixeddisks  Partitionable Fixed Disks
     RP_GET_FIXED_MAP   =   0x17, // CMDGetfd_log       Get Fixed Disk/Logical Unit Map
     RP_INPUT_BYPASS    =   0x18, // CMDInputBypass     cache bypass read data
     RP_OUTPUT_BYPASS   =   0x19, // CMDOutputBypass    cache bypass write data
     RP_OUTPUT_BYPASSV  =   0x1a, // CMDOutputBypassV   cache bypass write data and verify
     RP_BASEDEVINIT     =   0x1b, // CMDInitBase        INIT command for base DDs
     RP_SHUTDOWN        =   0x1c, // CMDShutdown
     RP_GET_DRIVER_CAPS =   0x1d, // CMDGetDevSupport   query for extended capability
     // 0x1e Reserved                reserved
     RP_INIT_DONE       =   0x1f, // CMDInitComplete    Init complete for all DD's
     RP_SAVE_RESTORE    =   0x20, // CMDSaveRestore
     // 0x21 through 0x60 Reserved   reserved
     RP_ADD_ON_PREP     =   0x61, // CMDAddOnPrep       Prepare for add on
     RP_START_START     =   0x62, // CMDStarstart       console output
     RP_STOP            =   0x63, // CMDStop            stop console output
     RP_END                       // nothing - was in OW header
} REQP_command;


#if __WATCOMC__ >= 1000
#pragma pack(pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
};
#endif

#endif // _DEVREQP_H_INCLUDED

