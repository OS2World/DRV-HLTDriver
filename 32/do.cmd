@ECHO OFF
@rem  ***************************************************************************
@rem  *      Created 2005  eCo Software                                         *
@rem  *                                                                         *
@rem  *      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        *
@rem  *      sample code created by eCo Software. This sample code is not part  *
@rem  *      of any standard or eCo Software product and is provided to you     *
@rem  *      solely for the purpose of assisting you in the development of your *
@rem  *      applications.  The code is provided "AS IS", without               *
@rem  *      warranty of any kind. eCo Software shall not be liable for any     *
@rem  *      damages arising out of your use of the sample code, even if they   *
@rem  *      have been advised of the possibility of such damages.              *
@rem  *                                                                         *
@rem  *       Author: Pavel Shtemenko <pasha@paco.odessa.ua>                    *
@rem  *-------------------------------------------------------------------------*
SET CXXMAIN=e:\compilers\ibmcxxo
SET FILEVER="@#HLT 32 bit driver"
SET DRV1_MAJOR_VERSION=1
SET DRV1_MINOR_VERSION=0
rem ***********************************************************
REM Set retail with minumum output
rem ***********************************************************
rem SET BLD_TYPE=retail
rem ***********************************************************
REM Set debug with output and debug source info
rem ***********************************************************
rem SET BLD_TYPE=debugsrc
rem ***********************************************************
REM Set debug with output
rem ***********************************************************
SET BLD_TYPE=debug
 
rem ***********************************************************
rem IBM C and C++ Compilers for OS/2 environment variable settings
rem ***********************************************************
call setenv

@SET ACPITLK=D:\work\ddk\base32\src\acpi\src\acpi\common\include;D:\work\ddk\base32\src\acpi\src\acpi\common\include\platform;

@SET BEGINLIBPATH=%CXXMAIN%\DLL;%BEGINLIBPATH%
@SET DPATH=%CXXMAIN%\HELP;%CXXMAIN%\LOCALE;%DPATH%
@SET HELP=%CXXMAIN%\HELP;%HELP%
@SET INCLUDE=%CXXMAIN%\INCLUDE;%ACPITLK%;%INCLUDE%
@SET IPFC=%CXXMAIN%\BIN;%IPFC%
@SET LIB=%CXXMAIN%\LIB;%LIB%
@SET CPP_DBG_LANG=CPP
@SET LANG=en_us
@SET NLSPATHTEMP=%CXXMAIN%\MSG\%%N
@SET NLSPATH=%NLSPATHTEMP%;%NLSPATH%
@SET NLSPATHTEMP=
@SET PATH=%CXXMAIN%\BIN;%PATH%;d:\Work\ddk\ddktools\toolkits\msc60\binp;

call setenv
@nmake
exit