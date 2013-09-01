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
# Dependency rule (dummy)
#
dep:
#    fastdep -o$$(O) -I$(ROOT)\src\$(SUBSYS)\common\include;f:\ddk\base\h;f:\tookit45\h;f:\ibmcxxo\include; *.c

#!include .depend

clean:

