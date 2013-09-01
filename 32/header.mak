#----------------------------------------------------------------------------
#      Created 2005  eCo Software                                       
#                                                                       
#       DISCLAIMER OF WARRANTIES.  The following [enclosed] code is     
#       sample code created by eCo Software. This sample code is not part
#       of any standard or eCo Software product and is provided to you   
#       solely for the purpose of assisting you in the development of your
#       applications.  The code is provided "AS IS", without              
#       warranty of any kind. eCo Software shall not be liable for any    
#       damages arising out of your use of the sample code, even if they  
#       have been advised of the possibility of such damages.             
#                                                                         
#        Author: Pavel Shtemenko <pasha@paco.odessa.ua>                   
#----------------------------------------------------------------------------
#
# Global environment changes
#
!if [SET INCLUDE=.;$(ROOT)\src\common\include;$(INCLUDE);]
!endif

!ifdef BLD_TYPE
!   if "$(BLD_TYPE)"!="retail"
!      if "$(BLD_TYPE)"!="debug"
!         if "$(BLD_TYPE)"!="debugsrc"
!         error Unsupported build type!  We only differentiate between retail and debug
!         else
# DRV_DEBUG - Turn on output to comport
DBG_CFLAGS= /Ti+  /DRV_DEBUG
DBG_AFLAGS= +Od
LFLAGS = /map /nod /exepack /debug
DBG_C16FLAGS= /Zi
DBG_LFLAGS= /de
!         endif
!      else
DBG_CFLAGS=  /DDRV_DEBUG
DBG_AFLAGS= 
LFLAGS = /map /nod /exepack 
DBG_C16FLAGS= /Zi
DBG_LFLAGS= /de
!      endif
!   else
DBG_CFLAGS=
DBG_AFLAGS=
LFLAGS = /map /nod /exepack
!   endif
!endif

DBG_C16FLAGS=
!IFDEF IASL_MAKE
DEFINES = /DM_I386 /DINCL_NOPMAPI
!else
DEFINES = /DM_I386 /DINCL_NOPMAPI 
!endif

#
# VAC 3.6.5 for OS/2
#
CC                = icc
COMPILER_HDR1     = $(CXXMAIN)\include
COMPILER_LIB_PATH = $(CXXMAIN)\lib
CFLAGS =/Q+ /O3 /Os- /Op- /Ms /Rn /C /Ss /Sp8 /W3 /Gi+ /Gf+ /Gs+ /Fa+ /G5 /qtune=pentium /qarch=pentium $(DEFINES) $(DBG_DEFINES) $(DBG_CFLAGS)

#
#
YACC         =	bison
YFLAGS       = -v -d
#
#
LEX          =	flex
LEXFLAGS     = -i


#
# Assembler - ALP
#
AINC        = -I:. -I:$(ROOT)\src\$(SUBSYS)\common\include -I:$(DDKBASE)\inc
AS          = alp


#
# Linker - ilink from VAC 3.6.5
#
LINK        = ilink /nofree
#LINK        = link386 


#
# Librarian - ilib from VAC 3.6.5
#
LIBUTIL     = ilib


#
# Import Librarian - implib from VAC 3.6.5
#
IMPLIB      = implib


#
# Object directory
#
OBASE       = $(ROOT)\obj\$(SUBSYS)
O           = $(OBASE)\$(SUBSYS_RELATIVE)


#
# Div stubs
#
R_OS2_LIB   = $(ROOT)\lib


#
# Output paths. (OS2 system tree root dir is '$(ROOT)\bin')
#
OS2         = $(ROOT)\bin\os2
DLL         = $(OS2)\dll


#
# Create-path tool.
#
CREATE_PATH = $(ROOT)\createpath.cmd $(@D)


#
# Create object path.
#
!if [$(ROOT)\createpath.cmd $(O)]
!endif

