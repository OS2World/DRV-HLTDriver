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
DATA32	            Segment para use32 public 'DATA'
                   Public   ComPort
                   ComPort  dd 0                                     ; if 0, output to int 10
DATA32             EndS
;---------------------------------------------------------------------------
CODE32             Segment dword use32 public 'CODE'
                   assume  CS:CODE32,DS:FLAT
                   Public PutCom
;---------------------------------------------------------------------------
; PutCom(ULONG)
; Send symbol to comport using HW flow control
;---------------------------------------------------------------------------
PutCom             Proc    Near                                      ;
                   xor     eax,eax                                   ;
                   mov     eax,ComPort                               ; Comport address
                   or      eax,eax                                   ; is it present?
                   jnz     short @@OutToCom                          ; if address is non zero 
                   ret                                               ; else return
;---------------------------------------------------------------------------
@@OutToCom:                                                          ;
                   mov     eax,Dword ptr [esp+4]                     ; parameter
                   push    edx                                       ; will use for comport address
                   push    ecx                                       ; will use for counter
;---------------------------------------------------------------------------
                   mov     ecx,10000h                                ; how many wait CTS
                   mov     edx,ComPort                               ; setting comport address
                   add     edx,6                                     ; MSR
                   xchg    ah,al                                     ; save symbol for save
@@WaitCTS:                                                           ; 
                   in      al,dx                                     ; Getting status
                   test    al,10h                                    ; CTS is on?
                   jnz     short @@SndB                              ; CTS is on, go to sending
                   loop    short @@WaitCTS                           ; CTS is off - wait
;---------------------------------------------------------------------------
@@SndB:                                                              ;
                   mov     edx,ComPort                               ; base address com port
                   add     edx,5                                     ; port of state
@@per:             in      al,dx                                     ; get status
                   test    al,01000000b                              ; is ready to send?
                   jz      short @@per                               ; No,waiting
                   test    al,00100000b                              ; is ready to send?
                   jz      short @@per                               ; No,waiting
                   xchg    ah,al                                     ; restore byte to send
                   mov     edx,ComPort                               ; address of port I/O
                   out     dx,al                                     ; send byte
;---------------------------------------------------------------------------
                   pop     ecx                                       ; restore using register
                   pop     edx                                       ;
                   ret                                               ;
PutCom             EndP                                              ;
;---------------------------------------------------------------------------
CODE32             EndS                                              ;
;---------------------------------------------------------------------------
                   End
