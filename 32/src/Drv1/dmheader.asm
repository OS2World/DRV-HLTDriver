;***************************************************************************
;*      Created 2005  eCo Software                                         *
;*                                                                         *
;*      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        *
;*      sample code created by eCo Software. This sample code is not part  *
;*      of any standard or eCo Software product and is provided to you     *
;*      solely for the purpose of assisting you in the development of your *
;*      applications.  The code is provided "AS IS", without               *
;*      warranty of any kind. eCo Software shall not be liable for any     *
;*      damages arising out of your use of the sample code, even if they   *
;*      have been advised of the possibility of such damages.              *
;*                                                                         *
;*       Author: Pavel Shtemenko <pasha@paco.odessa.ua>                    *
;*-------------------------------------------------------------------------*
                   include devhdr.inc
_TEXT              Segment word use16 public 'CODE'
                   extrn   Strat1:far 
                   extrn   IDCentry:far
_TEXT              EndS
;----------------------------------------------------------------------------
; Device Driver Header                                   
;                                                             
; This MUST be linked at the beginning of the data segment           
;----------------------------------------------------------------------------
                   Public  _DiskDDHeader
DDHeader           Segment word use16 public 'DATA'
;----------------------------------------------------------------------------
; Primary header for this driver. 
;----------------------------------------------------------------------------
_DiskDDHeader      dd      -1                           ; FAR ptr to next device header.
                   dw 1000100110000000b                 ; Device attributes
;                     ||||| +-+   ||||
;                     ||||| | |   |||+------------------ STDIN
;                     ||||| | |   ||+------------------- STDOUT
;                     ||||| | |   |+-------------------- NULL
;                     ||||| | |   +--------------------- CLOCK
;                     ||||| | |
;                     ||||| | +------------------------+ (001) OS/2
;                     ||||| |                          | (010) DosDevIOCtl2 + SHUTDOWN
;                     ||||| +--------------------------+ (011) Capability bit strip
;                     |||||
;                     ||||+----------------------------- OPEN/CLOSE (char) or Removable (blk)
;                     |||+------------------------------ Sharing support
;                     ||+------------------------------- IBM
;                     |+-------------------------------- IDC entry point
;                     +--------------------------------- char/block device driver
                   dw      OFFSET Strat1                ; Strategy 1 entry point.
                   dw      OFFSET IDCentry              ; IDC entry point. (пока нахрен не нужно)
                   db      "DRV001$ "                   ; Device name, must be 8 chars.
                   dw      0                            ; reserved
                   dw      0                            ; reserved
                   dw      0                            ; reserved
                   dw      0                            ; reserved
                   dd 0000000000110011b                 ; Level 3 device driver capabilities
;                               ||||||
;                               |||||+------------------ DosDevIOCtl2 + Shutdown
;                               ||||+------------------- More than 16 MB support
;                               |||+-------------------- Parallel port driver
;                               ||+--------------------- Adapter device driver
;                               |+---------------------- InitComplete
;                               +----------------------- SaveRestore
DDHeader           EndS
;----------------------------------------------------------------------------
                   End
