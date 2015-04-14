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
_DATA              Segment word use16 public 'DATA'
                   extrn   DevHlp:dword
FlatSegDs          dw 0
_DATA              EndS
;----------------------------------------------------------------------------
DATA32             Segment dword use32 public 'DATA'
CommandTable       dd    OFFSET FLAT:BAD                             ; Command code 0  Init, not called from here
                   dd    OFFSET FLAT:BAD                             ; Command code 1  Media check
                   dd    OFFSET FLAT:BAD                             ; Command code 2  Build Bios Parameter Block
                   dd    OFFSET FLAT:BAD                             ; Command code 3
                   dd    OFFSET FLAT:Read                            ; Command code 4  Read
                   dd    OFFSET FLAT:BAD                             ; Command code 5  Nondestructive Read no wait
                   dd    OFFSET FLAT:BAD                             ; Command code 6  Input Status
                   dd    OFFSET FLAT:BAD                             ; Command code 7  Flush input
                   dd    OFFSET FLAT:BAD                             ; Command code 8  Write
                   dd    OFFSET FLAT:BAD                             ; Command code 9  Write with Verify
                   dd    OFFSET FLAT:BAD                             ; Command code A  Output status
                   dd    OFFSET FLAT:BAD                             ; Command code B  Flush output
                   dd    OFFSET FLAT:BAD                             ; Command code C
                   dd    OFFSET FLAT:OpenDev                         ; Command code D  OPEN
                   dd    OFFSET FLAT:CloseDev                        ; Command code E  CLOSE
                   dd    OFFSET FLAT:BAD                             ; Command code F  Removable media
                   dd    OFFSET FLAT:IOCtl                           ; Command code 10 Generic IOCttl
                   dd    OFFSET FLAT:BAD                             ; Command code 11 Reset media
                   dd    OFFSET FLAT:BAD                             ; Command code 12 Get logical unit map
                   dd    OFFSET FLAT:BAD                             ; Command code 13 Set logical unit map
                   dd    OFFSET FLAT:BAD                             ; Command code 14 DEINSTALL Subroutine
                   dd    OFFSET FLAT:BAD                             ; Command code 15
                   dd    OFFSET FLAT:BAD                             ; Command code 16 Partionable hard disk
                   dd    OFFSET FLAT:BAD                             ; Command code 17 Get hard unit logical drive map
                   dd    OFFSET FLAT:BAD                             ; Command code 18
                   dd    OFFSET FLAT:BAD                             ; Command code 19
                   dd    OFFSET FLAT:BAD                             ; Command code 1A
                   dd    OFFSET FLAT:Init                            ; Command code 1B BasedevInit
                   dd    OFFSET FLAT:ShutDown                        ; Command code 1C Shutdown
                   dd    OFFSET FLAT:BAD                             ; Command code 1D Get driver capabilities
                   dd    OFFSET FLAT:BAD                             ; Command code 1E
                   dd    OFFSET FLAT:Init                            ; Command code 1F Initialization complete
                   dd    OFFSET FLAT:SaveRestore                     ; Command code 20 SaveRestore
;----------------------------------------------------------------------------
                   extrn  DOSFLATDS:word
eflags             dd ?
DATA32             EndS
;----------------------------------------------------------------------------
CODE32             Segment dword use32 public 'CODE'
                   extrn   KernThunkStackTo32:near                   ;
                   extrn   KernThunkStackTo16:near                   ;
                   extrn   KernSelToFlat:near                        ;
                   extrn   Init:near                                 ; Init for basedev=
                   extrn   BAD:near                                  ; For all don't support
                   extrn   OpenDev:near                              ; Open device call
                   extrn   CloseDev:near                             ; Close device call
                   extrn   IOCtl:near                                ; DevIOCtl call
                   extrn   Read:near                                 ; Read call, here using for log subsystem
                   extrn   ShutDown:near                             ; Shutdown call
                   extrn   SaveRestore:near                          ; Save/Restore state call
CODE32             EndS
;----------------------------------------------------------------------------
; Thunk routines
;----------------------------------------------------------------------------
_TEXT              Segment word use16 public 'CODE'
                   assume  CS:_TEXT, DS:_DATA
;----------------------------------------------------------------------------
; Call 32 bit Strat function
;----------------------------------------------------------------------------
                   Public  Strat32
Strat32            Proc Near
;----------------------------------------------------------------------------
; Set up stack frame. Make sure high order word of esp, ebp is 0 for 32 bit code.
; Save caller's registers for the environment from which we're called.
;----------------------------------------------------------------------------
                   pushfd                                            ;
                   pushad                                            ;
                   push    ds                                        ;
                   push    es                                        ; just to keep stack dword aligned
                   push    fs                                        ;
;----------------------------------------------------------------------------
                   push    ebp                                       ;
                   and     esp, 0ffffh                               ;
                   mov     ebp, esp                                  ;
;----------------------------------------------------------------------------
; Align stack on DWORD boundary
;----------------------------------------------------------------------------
                   and     sp, not 03h                               ;
;----------------------------------------------------------------------------
; Switch to 32 bit code segment
;----------------------------------------------------------------------------
                   jmp     far ptr FLAT:To32Fun                      ; Jmp to 32 code and call all need function
;----------------------------------------------------------------------------
To16Ret            Label   Far                                       ; Here back jmp from 32 code 
                   assume  CS:_TEXT , DS:_DATA                       ;
;----------------------------------------------------------------------------
; Restore caller's registers, restore stack, and return
;----------------------------------------------------------------------------
                   mov     esp,ebp                                   ;
                   pop     ebp                                       ;
                   pop     si                                        ; restore FS, if pop FS - can be trap
                   mov     fs,si                                     ;
                   pop     si                                        ; also ES
                   mov     es,si                                     ;
                   pop     ds                                        ;
                   popad                                             ;
                   popfd                                             ;
                   ret                                               ;
Strat32            EndP                                              ;
;----------------------------------------------------------------------------
_TEXT              EndS
;----------------------------------------------------------------------------
CODE32             Segment dword use32 public 'CODE'
                   assume  CS:CODE32 , DS:DATA32
;----------------------------------------------------------------------------
; Call 16 bit devhelper from 32 bit code
;----------------------------------------------------------------------------
Dev32Helper        Proc
                   assume  DS:_DATA
                   push    eax                                       ; save destroed
                   call    KernThunkStackTo16                        ; turn stack to 16
                   pop     eax                                       ; restore
                   push    ds                                        ; save FlatDS
                   push    es                                        ;
                   push    ax                                        ;
                   mov     ax, seg _DATA                             ;
                   mov     ds,ax                                     ; set 16 bit DS
                   pop     ax                                        ;
                   jmp     far ptr _TEXT:Dev32HelperTo16             ; goto 16 bit
;----------------------------------------------------------------------------
Dev32HelperTo32    Label Far                                         ; ret from 16
                   push   eax                                        ; save retcode
                   mov    ax,FlatSegDs                               ; restore 32 bit DS
                   mov    ds,ax                                      ;
                   call   KernThunkStackTo32                         ; turn stack to 32
                   pop    eax                                        ; restore retcode
                   pop    es                                         ;
                   pop    ds                                         ;
                   ret                                               ;
Dev32Helper        EndP
                   assume   DS:FLAT
;----------------------------------------------------------------------------
; Next some 32 Devhelpers, which absent in KEE
;----------------------------------------------------------------------------
; Beep 
; ULONG KernBeep(ULONG Freq,ULONG Duration);
;----------------------------------------------------------------------------
                   Public _KernBeep@8
_KernBeep@8        Proc
                   pushfd                                            ; save flag register
                   push   edx                                        ; using in 16 bit devhlp
                   push   ebx                                        ;
                   push   ecx                                        ;
;----------------------------------------------------------------------------
                   mov   ebx,[esp+4+4*3]                             ; Freq
                   mov   ecx,[esp+8+4*3]                             ; Duration
                   mov   dl,DevHlp_Beep                              ;
                   call  Dev32Helper                                 ;
;----------------------------------------------------------------------------
                   pop   ecx                                         ;
                   pop   ebx                                         ;
                   pop   edx                                         ;
                   popfd                                             ;
                   ret                                               ;
_KernBeep@8        EndP
;----------------------------------------------------------------------------
; Yield CPU
; ULONG KernYield(void);
;----------------------------------------------------------------------------
                   Public _KernYield@0                               ;
_KernYield@0       Proc                                              ;
                   push  edx                                         ; Using for 16 bit DevHlp
                   mov   dl,DevHlp_Yield                             ;
                   call  Dev32Helper                                 ;
                   pop   edx                                         ;
                   ret                                               ;
_KernYield@0       EndP
;----------------------------------------------------------------------------
; Thunk from StratCall to 32 bit
;----------------------------------------------------------------------------
To32Fun            Label  Far
                   mov     ax, _DATA                                 ; Sure ds is my
                   mov     ds,ax                                     ;
                   mov     eax, offset DOSFLATDS                     ; Get FLAT selector
                   ASSUME  DS: _DATA                                 ;
                   mov     FlatSegDs,ax                              ; Save it for any function
                   ASSUME  DS:FLAT                                   ;
                   mov     ds, ax                                    ; Change ds
                   mov     es, ax                                    ;        es
                   mov     fs, ax                                    ;        fs (for C++ modules)
                   call    KernThunkStackTo32                        ; turn stack to 32
                   push    ebx                                       ; push pointer to packet (parameter)
                   mov     eax,ebx                                   ;
                   call    CommandTable[edi]                         ; call function
                   pop     ebx                                       ; clear stack
                   call    KernThunkStackTo16                        ; turn stack to 16
                   jmp     far ptr _TEXT:To16Ret                     ; goto 16 bit code
;----------------------------------------------------------------------------
CODE32             EndS
;----------------------------------------------------------------------------
_TEXT              Segment word use16 public 'CODE'
                   assume cs:_TEXT,ds:_DATA,es:_DATA
;----------------------------------------------------------------------------
; Call 16 bit devhelper
;----------------------------------------------------------------------------
Dev32HelperTo16    Label  Far
                   push   _DATA                                      ; Set 16 bit DS
                   pop    ds                                         ;
                   call   [DevHlp]                                   ; call Devhelper
                   jc     short @@Retcaldev32                        ; return Error code
                   xor    eax,eax                                    ; Error code == Success
@@Retcaldev32:                                                       ;
                  jmp    far ptr FLAT:Dev32HelperTo32                ; goto 32
;----------------------------------------------------------------------------
_TEXT             EndS
;----------------------------------------------------------------------------
                  End
