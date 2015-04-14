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
                   .386p
                   include devsym.inc
                   include devhlp.inc
;----------------------------------------------------------------------------
; external KEE for 16 bit only
;----------------------------------------------------------------------------
CODE32             Segment dword use32 public 'CODE'
                   extrn   KernThunkStackTo32:near
                   extrn   KernThunkStackTo16:near
                   extrn   Dev32Helper:near
                   extrn   FindAddress:near
CODE32             EndS
;----------------------------------------------------------------------------
; Data segment leave in resident memory
;----------------------------------------------------------------------------
_DATA              Segment dword use16 public 'DATA'
                   Public Gav                                        ;
                   Public GavCount                                   ;
                   Public DevHlp                                     ;
DevHlp             dd    ?                                           ; Address DevHelper
;----------------------------------------------------------------------------
GavBase            dw    1178                                        ; Struct for DevHlp_Save_Message
                   dw    1                                           ;
                   dw    offset Gav                                  ; offset
                   dw    _DATA                                       ; segment
;----------------------------------------------------------------------------
Gav                db 'ACPI compatible driver for eComStation v ', MJVER+'0','.',MNVER/10+'0',MNVER-(MNVER/10)*10+'0',0ah,0dh
                   db 'Copyright (C) eCo Software 2008',0ah,0dh
                   db 'This driver is licensed for use only in conjunction with eComStation',0
GavCount           dw $ - (offset Gav)
;----------------------------------------------------------------------------
DDHandle           dw    0                                           ; Handle for opened device drivers.
OpenAction         dw    0                                           ; Return Open Action.
;----------------------------------------------------------------------------
GavBaseErrInst     dw    1178                                        ; Struct for DevHlp_Save_Message
                   dw    1                                           ;
                   dw    offset GavAlready                           ; offset
                   dw    _DATA                                       ; segment
;----------------------------------------------------------------------------
GavAlready         db ' driver already loaded',0ah,0dh 
                   db ' Please check config.sys',0ah,0dh,0
DevName            db 'DRV001$',0
                   extrn  _edata:Near
_DATA              EndS
;----------------------------------------------------------------------------
; Segment of code, for easy link called as some in C compiler
;----------------------------------------------------------------------------
_TEXT              Segment word use16 public 'CODE'
                   assume  cs:_TEXT,ds:_DATA,es:Nothing
                   Public  Strat1
                   Public  IDCentry
                   Public  InitDriver
                   extrn   Strat32:Near
                   extrn   DOS16OPEN:Far 
                   extrn   DOS16CLOSE:Far
;----------------------------------------------------------------------------
; Strategy entry point
;----------------------------------------------------------------------------
                   assume    bx: Ptr Packet
Strat1             Proc Far
                   mov     al,byte ptr es:[bx].PktCmd                ; Command code in al
                   cmp     al,01bh                                   ; Init for basedev
                   jne     short @@Next1                             ;
                   push    ax                                        ; Save for call 32 bit init
                   call    InitDriver                                ; call my init (in R0)
                   pop     ax                                        ;
                   jmp     short  @@Supported                        ; goto 32 bit to find PSD
@@Next1:                                                             ;
                   or      al,al                                     ; test for init as device
                   jnz     short @@Funct                             ;
@@InitDrv:                                                           ;
                   call    InitDriver                                ; Init for device (in R3)
                   or      es:[bx].PktStatus,STDON                   ; Set DONE
                   ret                                               ;
@@Funct:                                                             ; called all function, exept init (R0)
                   cmp     al,020h                                   ; supported?
                   jl      short @@Supported                         ; supported, goto 32 bit
                   or      es:[bx].PktStatus,STERR                   ; not supported -> error
                   ret                                               ; 
@@Supported:                                                         ; supported function
                   push    edi                                       ; save regs
                   push    esi                                       ;
                   push    ebx                                       ;
                   cbw                                               ; traditions ;-)
                   xor     edi,edi                                   ; for use in 16 and 32 zero 32 bit
                   mov     di,ax                                     ; edi command code
                   shl     di,2                                      ; to tables index
;----------------------------------------------------------------------------
;  address input packet from 16:16 to linear
;----------------------------------------------------------------------------
                   mov     ax,es                                     ; selector input packet
                   xor     esi,esi                                   ; zero, paranoa
                   mov     si,bx                                     ; offset input packet
                   mov     dl,DevHlp_VirtToLin                       ; function
                   call    [DevHlp]                                  ; change to linear address
                   jnc     Short @@CallFun                           ; Problem?
                   int 3                                             ; Look in debug kernel pls
                   ret                                               ;
@@CallFun:                                                           ; No problem - working
                   mov    ebx,eax                                    ; save linear address of packet
                   call   Strat32                                    ; go to 32 bit
                   pop    ebx                                        ; restore regs
                   pop    esi                                        ;
                   pop    edi                                        ;
                   or     es:[bx].PktStatus,STDON                    ; set to DONE
                   ret                                               ;
Strat1             EndP                                              ;
;----------------------------------------------------------------------------
; Same as Strategy
;----------------------------------------------------------------------------
IDCentry           Proc  Far
                   mov     al,byte ptr es:[bx].PktCmd                ; Command code in al
                   cmp     al,01bh                                   ; Init for basedev ?
                   je      short @@IDCError                          ; Init is error
                   cmp     al,01fh                                   ; Second Init ?
                   je      short @@IDCError                          ; Init is error
                   or      al,al                                     ; test for init as device
                   jz      short @@IDCError                          ; Init is error
                   jmp     Strat1                                    ; Another to Strategy
@@IDCError:                                                          ;
                   or es:[bx].PktStatus,STERR                        ; not supported -> error
                   ret                                               ; 
IDCentry           EndP
;----------------------------------------------------------------------------
                   assume    bx: Ptr Packet
InitDriver         Proc Near
                   mov     ax,word ptr es:[bx].PktData+1             ; Save Devhelpers address
                   mov     word ptr DevHlp,ax                        ;
                   mov     ax,word ptr es:[bx].PktData+1+2           ;
                   mov     word ptr DevHlp+2,ax                      ;
ifdef DriverForDevice                                                ;
;----------------------------------------------------------------------------
; check already load first
; this can work only in device=
;----------------------------------------------------------------------------
                   push    si
                   mov     si,offset DevName                 ; offset to name
                   call    OpenDriver                        ; try open
                   pop     si                                ;
                   jnc     short @@DrvAbs                    ; driver don't load before
                   or      es:[bx].PktStatus,STERR           ; not supported -> error
                   mov     word ptr es:[bx].PktData+1,0      ;
                   mov     word ptr es:[bx].PktData+1+2,0    ;
                   pusha                                     ;
                   call    MessAlreadyInstaled               ; Say about error
                   popa                                      ;
                   ret                                       ;
@@DrvAbs:                                                    ;
endif
;----------------------------------------------------------------------------
; Here lock 32bit code segment, need for IRQ call
;----------------------------------------------------------------------------
                   push    bp                                        ;
                   mov     bp, sp                                    ;
                   sub     sp, 32                                    ;
                   mov     ax,offset InitDriver                      ; Code segment end
                   mov     word ptr es:[bx].PktData+1,ax             ;
                   mov     ax,offset _edata                          ; Data segment end
                   mov     word ptr es:[bx].PktData+1+2,ax           ;
;----------------------------------------------------------------------------
                   push  esi                                         ;
                   push  edi                                         ;
                   push  ebx                                         ;
;----------------------------------------------------------------------------
                   mov   ax, ss                                      ; stack segment
                   lea   esi, [bp-16]                                ; offset of local variable
                   mov   dl,DevHlp_VirtToLin                         ; function
                   call  [DevHlp]                                    ; change to linear address
                   jc    short @@1                                   ; Problem
;----------------------------------------------------------------------------
                   mov   esi, eax                                    ; linear address of lock handle
                   mov   edi, -1                                     ; no pagelist to return
                   mov   ebx, offset FLAT:Dev32Helper                ; start of 32bit code
                   and   ebx, not 4095                               ; round downwards
                   mov   ecx, offset FLAT:FindAddress + 4095         ; end of 32bit code
                   and   ecx, not 4095                               ; round up to next page
                   sub   ecx, ebx                                    ; lock length
                   mov   eax, 10h                                    ; VMDHL_LONG
                   mov   dl,DevHlp_VMLock                            ; function
                   call  [DevHlp]                                    ;
                   jnc   Short @@2	                                  ; O.K.
@@1:
;----------------------------------------------------------------------------
; do or say error or remove IRQ handler or don't install driver
;----------------------------------------------------------------------------
                   int   3                                           ;
@@2:                                                                 ;
                   pusha                                             ;
                   call    ShowMessage                               ; Moo to screen
                   popa                                              ;
                   pop   ebx                                         ;
                   pop   edi                                         ;
                   pop   esi                                         ;
                   leave                                             ;
                   ret                                               ;
InitDriver         EndP
;----------------------------------------------------------------------------
MessAlreadyInstaled Proc Near
                   push   ds                                         ;
                   mov    ax,_DATA                                   ;
                   mov    ds,ax                                      ;
                   mov    si, offset GavBaseErrInst                  ;
                   xor    bx,bx                                      ;
                   mov    dl,DevHlp_Save_Message                     ;
                   call   [DevHlp]                                   ;
                   pop    ds                                         ;
                   ret                                               ;
MessAlreadyInstaled EndP
;----------------------------------------------------------------------------
ShowMessage        Proc Near                                         ;
                   push   ds                                         ;
                   mov    ax,_DATA                                   ;
                   mov    ds,ax                                      ;
                   mov    si, offset GavBase                         ;
                   xor    bx,bx                                      ;
                   mov    dl,DevHlp_Save_Message                     ;
                   call   [DevHlp]                                   ;
                   pop    ds                                         ;
                   ret                                               ;
ShowMessage        EndP
;----------------------------------------------------------------------------
;       In:     ds:si = Pointer to device driver name.
;       Out:    Carry Set if driver found, Carry Clear if not.
;----------------------------------------------------------------------------
                   Public  OpenDriver
OpenDriver         Proc    Near                                      ;
                   Push    ds                                        ; Set pointer to Device driver name.
                   Push    si                                        ; 
                   Push    ds                                        ; Set pointer to DDHandle in our Data.
                   Push    Offset [DDHandle]                         ; 
                   Push    ds                                        ; Set pointer to action return.
                   Push    Offset [OpenAction]                       ; 
                   Push    0                                         ; Set file size of zero.
                   Push    0                                         ;
                   Push    0                                         ; Set file attribute to zero.
                   Push    1                                         ; Set open flag to Exist Only.
                   Push    0C2h                                      ; Set OpenMode to R/W Priv, Deny None.
                   Push    0                                         ; Set Reserved Dword.
                   Push    0                                         ;
                   Call    DOS16OPEN                                 ; Call the kernel.
                   Cmp     ax, 0                                     ; Were we successful?
                   Jne     short @@NotFound                          ; Brif not (we don't want to find the driver!).
                   Push    [DDHandle]                                ; Set the handle to close.
                   Call    DOS16CLOSE                                ; Close the driver.
                   clc                                               ; Indicate we found the driver.
                   Ret                                               ;
@@NotFound:                                                          ;
                   stc                                               ; Indicate we did not find the driver.
                   Ret                                               ;
OpenDriver         EndP                                              ;
;----------------------------------------------------------------------------
_TEXT              EndS
;----------------------------------------------------------------------------
                   End
