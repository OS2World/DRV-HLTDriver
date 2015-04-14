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
#----------------------------------------------------------------------------
# SUBSYS is a macro to define the name of the subsystem that this makefile is a
# part of.   It is the name of the subdirectory that is above all of the
# individual components.
#
# SUBSYS_RELATIVE is a macro to define the name of this component.
# SRC_RELATIVE is the full path for the current directory from the
# ROOT.
#
# This uses the substitution feature which takes the current directory of
# this makefile (MAKEDIR) and removes the relative part of the directory to
# get the TOP level directory.
#
# The other macros are used to build directories in other levels of the tree.
#------------------------------------------------------------------------------

SUBSYS          = mydrv
SUBSYS_RELATIVE = Drv1
SRC_RELATIVE    = src\$(SUBSYS)\$(SUBSYS_RELATIVE)
SRC_NL_RELATIVE = mri\$(NLV)\$(SUBSYS)\$(SUBSYS_RELATIVE)


#------------------------------------------------------------------------------
#  Use built in macro "MAKEDIR" to establish "ROOT".  Due to case sensitivity
#
#  of nmake macro substitution, try all lowercase then all uppercase.  Fail if
#  current working directory path is mixed case.  This is a current nmake
#  limitation on macro substitutions but should not be a problem for most
#  people.  We are searching for a fix to this problem.
#------------------------------------------------------------------------------
# \src\mm\misc\mmpmcrt is an example of the path for a specific component
# in the tree structure. Please change the path as applied to your component.
# Refer to Nmake documentation, if you have any questions about MAKEDIR
#------------------------------------------------------------------------------

ROOT            = $(MAKEDIR:\src\drv1=)
!if "$(ROOT)" == "$(MAKEDIR)"
ROOT            = $(MAKEDIR:\SRC\DRV1=)
!endif
!if "$(ROOT)" == "$(MAKEDIR)"
!error Problem setting "ROOT"! Make sure current working directory is either all\
uppercase or all lowercase!
!endif

#-----------------------------------------------------------------
# Set up component/subsystem specific macros for use in header.mak
# This allows you establish a search order for header and lib paths.  A
# prefix would be a path that you would like to add to the beginning of
# the standard path which is set in header.mak.  A suffix tags onto the
# end of the standard path.
#-----------------------------------------------------------------
# If using Visual Age C++ you need to specify the version required
#
# Currently using v3 due to v36 ILINK bug preventing ICAT source level
# debugging in mixed MSC / VAC++ module environment.
#   NOT! Using v36 to allow proper build with JFS.
VACPP_VER =v36

# Directory for include files shared by dasd components os2dasd and os2lvm
#
DASD_INCLUDE = $(SBASE)\$(SUBSYS_RELATIVE)\..\include

# LVM engine include directory.  Definitions of LVM disk structures.
#
LVM_INCLUDE = $(ROOT)\src\lvm\common\include

#CMP_HDR_PREFIX = <specify non-default path(s) for front of INCLUDE path>
CMP_HDR_PREFIX = $(DASD_INCLUDE)

#CMP_HDR_SUFFIX = <specify non-default path(s) for back INCLUDE path>
CMP_HDR_SUFFIX= $(LVM_INCLUDE)

#CMP_LIB_PREFIX = <specify non-default path(s) for front of LIB path>
#CMP_LIB_PREFIX= $(SUBSYS_LIB)
#CMP_LIB_SUFFIX = <specify non-default path(s) for back LIB path>
#CMP_LIB_SUFFIX= $(SUBSYS_LIB)

#-----------------------------------------------------------------------
#INSTPATH = <specify the path for the files to be put in release tree>
#Instpath should be defined to get to the root of the install tree.
#For Example, suppose you want to place binaries in
#   \wpos\rel\386\retail\os2\toolkt\version1
# \wpos\rel\386\retail would be represented by $(R)
# Instpath = \os2\toolkt\version1
# Since REL=$(R)+$(INSTPATH), REL will become
# \wpos\rel\386\retail\os2\toolkt\version1
#-----------------------------------------------------------------------


# Uncomment to use ibmc libs.  With this out, it uses the
# default metaware libs location.
USE_IBMC_LIB = 1

#-----------------------------------------------------------------------------
# PUBLIC can be one of "ibmmk", "cps","os2".  Please define the below macros
# if you want to include the public files in a different order.  These macros
# would be used if you have a preference as to which directory gets searched
# first.  For example, you would like to search the OS2 header or include
# files before you search the ibmmk header or include files.  In this case,
# you would specify PUBLIC1 = OS2 and PUBLIC2= IBMMK and PUBLIC3 = CPS.
# These macros are then used in header.mak to set the path order.
#------------------------------------------------------------------------------

PUBLIC1 = os2
PUBLIC2 = os2\16bit
PUBLIC3 = os2\inc

#------------------------------------------------------------------------------
# HOST_PROC and HOST_OS will be set in the environment by the build lab.
# Set them in your private builds.
# Please don't set these variables in the public build.
#-----------------------------------------------------------------------------

HOST_PROC=386
HOST_OS=OS2

#------------------------------------------------------------------------------
# header.mak is the public makefile that sets up all paths and options.  It
# should not be altered.  Additions or changes to header.mak for a component
# can be overwritten in this makefile.  Additions or changes to header.mak
# for an entire subsystem can be overwritten in subsys.mak
#-----------------------------------------------------------------------------

!include $(ROOT)\header.mak

#-------------------------------------------------------------------------
# subsys.mak is used as a way for each subsystem to override any settings
# that were set in header.mak.  It is owned by development.
#-------------------------------------------------------------------------

!include $(ROOT)\src\common\subsys.mak

#----------------------------------------------------------------
# Set up the list of suffixes, if the suffixes in header.mak are not
# sufficient.  Be sure to include the entire list.
#-----------------------------------------------------------------

#.suffixes:

DEFINES = /DMJVER=$(DRV1_MAJOR_VERSION) /DMNVER=$(DRV1_MINOR_VERSION)
AFLAGS= -D:MJVER=$(DRV1_MAJOR_VERSION) -D:MNVER=$(DRV1_MINOR_VERSION) $(DBG_AFLAGS)
AINC = -I:$(SBASE)\$(SUBSYS_RELATIVE)\..\include -I:$(R_OS2_HDR)\inc -I:$(SBASE)\common\include
CPPFLAGS= /O+ /Os- /Op- /Mt /Gs- /Gi+ /Gx+ /Gr+ /Rn /C /G5 /qtune=pentium /Ss /W3 /Sp1 /Tdp /Fa+ /Q $(DEFINES) $(DBG_DEFINES) $(DBG_CFLAGS)
LFLAGS = /ig /pdd /map /nod /nofix /exepack:2 /packd /a:2 $(DBG_LFLAGS)

#--------------------------------------------------------------------------
# If the Inference rules defined in header.mak are not sufficient, then
# define the inference rules necessary at this point.
# The following inference rules are just an example.
# You can delete this section if you don't need to add more inference rules.
#-------------------------------------------------------------------------

.asm{$(O)}.obj:
        $(AS) $(AFLAGS) $(AINC)  $< -Fl:$(O)\$(@B).lst -Fo:$@

.asm.lst:
        $(AS) $(AFLAGS) $(AINC) $< -Fl:$@

.cpp{$(O)}.obj:
        $(CC) $(CPPFLAGS) /Fo$@  $<

.c{$(O)}.obj:
        $(CC) $(CFLAGS) /Fo$@ /Fa$(O)\$(@B).lst $<

.c.lst:
        $(CC) $(CFLAGS) /Fa$@ $<

#------------------------------------------------------------------------
#Component defines start here.
#------------------------------------------------------------------------

BASEDD_LIB = $(REL)\lib\basedd

LIB386  = os2386.lib os2286.lib
LIBP    = os2386p.lib os2286.lib
LIBDDE  = cpprns36.lib
KEELIB  = $(R_OS2_LIB)\kee.lib
FSHELP  = $(R_OS2_LIB)\fshelper.lib
ACPIDEV = $(R_OS2_LIB)\AcpiDrv.lib
ACPILIB = $(R_OS2_LIB)\Acpi.lib
LIBS    = dhcalls.lib rmcalls.lib $(KEELIB) $(LIBP) $(ACPIDEV) $(ACPILIB)
# $(LIBDDE)

##  !!! order is important !!!!!
OBJASM = $(O)\dmsegs.obj $(O)\dmheader.obj $(O)\thunk.obj $(O)\strat1.obj  \
         $(O)\debug.obj


OBJC32 = $(O)\command.obj $(O)\ioctl.obj

OBJS = $(OBJASM) $(OBJC32)

#--------------------------------------------------------------------------
# The all target is used to specify a list of targets that need to be built
# Please don't delete "dep" from the target list.  It is used to generate the
# depend.mak file.
# Please look at the example for more details.
#-------------------------------------------------------------------------

all: dep $(OS2)\drv1.sys
# $(OS2)\system\trace\trc0007.tff

# 16 bit C code  (Microsoft C 6)
#
#$(OBJC16): $$(@B).c
#        $(CC16) $(C16FLAGS) /Fo$@ $(@B).c

# 32 bit C code  (IBM VAC++)
#
$(OBJC32): $$(@B).c
        $(CC) $(CFLAGS) /Fo$@ /Fa$(O)\$(@B).lst $(@B).c

# 32 bit C++ code  (IBM VAC++)
#
##$(OBJCPP): $$(@B).cpp
##           $(CPP) $(CPPFLAGS) /Fo$@ $(@B).cpp

# Objects extracted from MSC libh.lib
#
# Note: These objects are extracted and linked directly rather than
# by linking to the library.  This allows the objects to be linked before
# dminit.obj.  Linking to the library would place the objects after
# dminit.obj, causing the code to be discarded when the initialization
# code is discarded (bad).
#
#$(OBJOBJ): $(R_OS2_LIB)\libh.lib
#        cd $(O)
#        lib $(R_OS2_LIB)\libh.lib *$@;
#        cd $(MAKEDIR)

# Link
#
$(OS2)\drv1.sys: $(OBJS) $(O)\$(@B).def makefile
        $(CREATE_PATH)
        -4$(LINK) $(LFLAGS) @<<$(O)\$(@B).lnk
$(OBJS: =+^
)
$@
$(O)\$(@B).map
$(LIBS)
$(O)\$(@B).def
; $@ end of generated file (see makefile)
<<keep
        cd $(@D)
        mapsym $(O)\$(@B).map
        cd $(MAKEDIR)

# Linker directives .def file
#
# Important BUG: When using ILINK (VAC++ v3 or v36), do NOT use the IOPL
# directive for code segments.  This causes linker fixup errors.
# (no linker error given, just load module which traps to due bad fixup).
# IOPL does not seem to be needed to keep the segments around after
# initialization (even SwapCode, which is the third segment is OK).
#
$(O)\drv1.def: makefile
         rem creating def file<<$@
PHYSICAL DEVICE CRCDRV

DESCRIPTION $(FILEVER)

PROTMODE

SEGMENTS
 DDHeader       CLASS 'DATA'         MIXED1632
 DATA32         CLASS 'DATA'         MIXED1632
 _DATA          CLASS 'DATA'         MIXED1632
 _BSS           CLASS 'BSS'          MIXED1632
 'CODE'         CLASS 'CODE'   ALIAS
 _TEXT          CLASS 'CODE'   ALIAS
 CODE32         CLASS 'CODE'   ALIAS IOPL


<<keep

#***************************************************************************
# Include Footer.mak at this point.
#***************************************************************************

#****************************************************************************
#  Dependency generation and Checking
#****************************************************************************

$(O)\depend.mak:  $(O)\dephold
        -$(CREATE_PATH)
        -$(TOUCH) $(O)\depchk
        -echo generate depend.mak
        includes -e -i -l -S$$(O) -P$$(ROOT)=$(ROOT) -C=hh -C=xh -C=api *.c *.asm >$@ 2>$(O)\depend.err
       -del $(O)\depchk

$(O)\dephold:
        -$(TOUCH) $@


!include $(ROOT)\footer.mak
