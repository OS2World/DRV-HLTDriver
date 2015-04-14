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

retos2c:
       $(MAKE) $(MAKE_OPTS) -f $(MAKEFILE_NAME) OPT=$@  all

dbgos2c:
       $(MAKE) $(MAKE_OPTS) -f $(MAKEFILE_NAME) OPT=$@  all

dekos2c:
       $(MAKE) $(MAKE_OPTS) -f $(MAKEFILE_NAME) OPT=$@  all

!if "$(OPT)" == "dbgos2c"
BLD_TYPE=debug
TARGET_PROC=386
TARGET_PROD=os2c
EXE_FMT=lx
SOM_VER=21
!endif

!if "$(OPT)" == "retos2c"
BLD_TYPE=retail
TARGET_PROC=386
TARGET_PROD=os2c
EXE_FMT=lx
SOM_VER=21
!endif

!if "$(OPT)" == "dekos2c"
BLD_TYPE=dekko
TARGET_PROC=386
TARGET_PROD=os2c
EXE_FMT=lx
SOM_VER=21
!endif
