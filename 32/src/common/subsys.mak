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
#==================================================================
# First figure out what our host processor
# and operating system is so that we use the
# right tools. Host_Proc and Host_Os will be set by build lab
#==================================================================

!if "$(HOST_PROC)" == "" || "$(HOST_OS)" == ""
!error Environment variables "HOST_PROC" and/or "HOST_OS not set!  Please set\
"HOST_PROC" to the type of processor on which $(MAKE) was invoked \
(one of 386, PPC, RISC) and "HOST_OS" to the operating system in which \
$(MAKE) was invoked (one of OS2, WPOS2, AIX, OSF)!
!endif

#==================================================================
# Specify subsystem specific options here.
#==================================================================

R_OS2_H16 = $(R_OS2_HDR)\16bit
R_OS2_INC = $(R_OS2_HDR)\inc

AINC = -I$(ROOT)\src\$(SUBSYS)\ifs -I$(R_OS2_INC)
