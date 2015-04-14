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
;----------------------------------------------------------------------------
; ORDER NOT TRY !!!!! And unuse segment not remove!!!!
; if remove -  think. think and one more think
;----------------------------------------------------------------------------
; Assembler Helper to order segments  
;----------------------------------------------------------------------------
; Fisrt (and must be first)
DDHeader           Segment word use16 public 'DATA'
DDHeader           EndS
;----------------------------------------------------------------------------
; For ICC second, for another, can be another
;----------------------------------------------------------------------------
_DATA              Segment word use16 public 'DATA'
_DATA              EndS
;----------------------------------------------------------------------------
; Next see your compiler
;----------------------------------------------------------------------------
_BSS               Segment dword public 'BSS'
_BSS               EndS
;----------------------------------------------------------------------------
_TEXT              Segment word use16 public 'CODE'
_TEXT              EndS
;----------------------------------------------------------------------------
DGROUP             group   DDHeader,  _DATA 
;----------------------------------------------------------------------------
                   End
