









             OS/2(r) Physical Device Driver Libraries
                       for Watcom C/C++ 10

                           Version 0.1

                               by

                           David Bollo









i)    COPYRIGHT

  (C) Copyright Advanced Gravis Computer Technology Ltd 1994.
      All Rights Reserved.



ii)   DISCLAIMER OF WARRANTIES

  The following [enclosed] code is provided to you "AS IS",
  without warranty of any kind.  You have a royalty-free right to
  use, modify, reproduce and distribute the following code (and/or
  any modified version) provided that you agree that Advanced
  Gravis has no warranty obligations and shall not be liable for
  any damages arising out of your use of this code, even if they
  have been advised of the possibility of such damages.  This
  Copyright statement and Disclaimer of Warranties may not be
  removed.





iii)  WARNING

  This README file contains important information regarding the
  use of the Physical Device Driver Libraries for Watcom C++.
  Ignoring any or all of the information in this readme file would
  be BAD.

  "I'm fuzzy on the whole `good-bad' thing.  What do you mean `bad'?"
  "Try to imagine all life as you know it stopping instantaneously
   and every molecule in your body exploding at the speed of light."
  "Right.  That's `bad'.  Okay.  Important safety tip.  Thanks."

  -- Bill Murray and Harold Ramis discussing the meaning of "BAD"
     in the movie "Ghostbusters".



iv)   INTRODUCTION

  This package is a set of libraries for developing physical
  device drivers (PDDs) for OS/2 with revision 10 of the Watcom
  C++ compiler.

  When IBM developed their OS/2 device driver [development] kit
  (DDK), they only included supporting libraries for Microsoft C
  version 6.0 and MASM versions 5.1 and 6.0.  The libraries
  included in this package are designed to be used as replacements
  for the IBM DDK libraries, and in particular are designed to be
  used with Watcom C++ 10.

  This is the initial release of these libraries, and so, of
  course, the enclosed code is not as mature as the IBM equivalent.
  However, these libraries support Watcom 10, which (unlike
  Microsoft C 6.0) is a supported and shipping compiler.

  Note that these libraries _require_ Watcom C/C++ 10 (or greater)
  and they _require_ C++.  These requirements are reflected in the
  enclosed makefiles.

  This package contains two pieces of code:  a "device-support"
  library, and a sample physical device driver which uses the
  device-support library.  Currently, this file [readme.txt] is
  the only documentation that I provide with this package, however
  I have liberally commented the header files, and so those can be
  referred to in place of any manuals.  (Sadly, writing
  documentation just isn't as fun as writing code; so the docs
  tend to get left till last...)

  For reference material, I suggest the following sources (with
  whom I am unaffiliated in any way of course):

    - IBM Device Driver Source Kit for OS/2 CD

      I am currently using version 1.2, but I believe that IBM
      will be releasing an updated version in the near future.

    - Developer's Toolkit for OS/2 CD

      This CD provides some extra documentation on areas not
      covered by the DDK; in particular, it has information on
      the DOS* APIs which are available at Init time.

    - Writing OS/2 2.1 Device Driver in C
      Book by Steven J. Mastrianni

      From a text file on device drivers from IBM:

      "A book, 'Writing OS/2 2.1 Device Drivers in C', by Steve
      Mastrianni, is available on CompuServe from Compubooks (GO
      CBK), from Van Nostrand Reinhold (800-842-3636), or from IBM
      (800-879-2755, P/N SR28-4392).  It's the only tutorial on
      writing OS/2 2.x device drivers."

      "Another book, 'The Design of OS/2', by H.M.  Deitel and
      M.S. Kogan, provides an insight into the architecture of
      OS/2, multitasking implementation, memory management, and
      much more.  This book (P/N S325-4005) is also available from
      IBM, as well as the publisher, Addison-Wesley Publishing
      Company."

  This library is not officially supported by Advanced Gravis (or
  by anyone else, for that matter); however there are several
  sources for unofficial support.  For details, please refer to
  section 4 of this document.



1)    PACKAGE CONTENTS

  This package contains two pieces of code:  a "device-support"
  library which is located in the "DEV" subdirectory, and a sample
  physical device driver which is located in the root directory.

  The files for the sample physical device driver are as indicated
  in the table below.  They are all well commented (IMHO), and
  should serve as the building blocks for any new driver built
  with the libraries.  To build the sample driver, ensure that the
  "device-support" libraries are properly built, and that your
  environment is properly setup and then type "wmake" at the OS/2
  command prompt.

    FILENAME     SIZE   DATE      DESCRIPTION
    --------     ----   ----      -----------
    header.asm   3574   10-9-94   Device header structure
    init.c       4139   10-9-94   Initialization code
    ioctl.c      2973   10-9-94   Code to handle IOCtl
    makefile     3853   10-9-94   Makefile
    strategy.c   5820   10-9-94   Code to dispatch strategy calls

  The "device-support" libraries are located in the "DEV"
  subdirectory of this package.  (This assumes that you unpacked
  the .ZIP file with directory information; ie:  pkunzip -d.  If
  not, then you should do so.  The makefiles assume that the
  source files are in the correct subdirectory.)  The table below
  summarizes the contents of the files that make up the libraries.

    FILENAME     SIZE   DATE      DESCRIPTION
    --------     ----   ----      -----------
    comm.asm     8964   10-9-94   Debugging IO implementation
    debug.c      2882   10-9-94   Debugging IO data
    devdebug.h   9193   10-9-94   Debugging IO header
    devhelp.h   41152   10-9-94   DevHelp calls
    device.asm   3982   10-9-94   DevHelp data and segment declarations
    devinfo.h    5422   10-9-94   Types for OS/2 info segments
    devrp.h      8557   10-9-94   Types for request packets
    devtype.h    7090   10-9-94   Types for device help
    impdos.def   2664   10-9-94   Import information for DOS* functions
    impmsg.def   2025   10-9-94   Import information for DOS* functions
    impnls.def   1991   10-9-94   Import information for DOS* functions
    makefile     3717   10-9-94   Makefile
    math.asm     4862   10-9-94   Replacement for run-time "long" math



2)    COMPATIBILITY

  In order to prevent old code from using these libraries (see DevHelp.h
  for reasons why), I have adopted a different naming convention from
  either the libraries provided with the IBM DDK or with the Mastrianni
  "Writing OS/2 2.1 Device Drivers in C" book.  These naming differences
  are shown in the following table.

    +----------------------+----------------------+----------------------+
    |    WATCOM Library    |  Mastrianni Library  |     IBM Library      |
    +----------------------+----------------------+----------------------+
    | DevInit              | n/a                  | n/a                  |
    | DevDebug             | n/a                  | n/a                  |
    | DevInt3              | n/a                  | n/a                  |
    | DevDone              | DevDone              | DevHelp_DevDone      |
    | DevYield             | Yield                | DevHelp_Yield        |
    | DevTCYield           | TCYield              | DevHelp_TCYield      |
    | DevBlock             | Block                | DevHelp_ProcBlock    |
    | DevRun               | Run                  | DevHelp_ProcRun      |
    | DevSemRequest        | SemRequest           | DevHelp_SemRequest   |
    | DevSemClear          | SemClear             | DevHelp_SemClear     |
    | DevSemUseHandle      | SemHandle            | DevHelp_SemHandle    |
    | DevSemFreeHandle     | SemHandle            | DevHelp_SemHandle    |
    | DevReqPush           | PushReqPacket        | DevHelp_PushReqPa... |
    | DevReqPull           | PullReqPacket        | DevHelp_PullReqPa... |
    | DevReqPullParticular | PullParticular       | DevHelp_PullParti... |
    | DevReqPushSorted     | SortReqPacket        | DevHelp_SortReqPa... |
    | DevReqAlloc          | AllocReqPacket       | DevHelp_AllocReqP... |
    | DevReqFree           | FreeReqPacket        | DevHelp_FreeReqPa... |
    | DevQueueInit         | QueueInit            | DevHelp_QueueInit    |
    | DevQueueFlush        | QueueFlush           | DevHelp_QueueFlush   |
    | DevQueueWrite        | QueueWrite           | DevHelp_QueueWrite   |
    | DevQueueRead         | QueueRead            | DevHelp_QueueRead    |
    | DevSegLock           | LockSeg              | DevHelp_Lock         |
    | DevSegUnlock         | UnlockSeg            | DevHelp_Unlock       |
    | DevPhysToVirt        | PhysToVirt           | DevHelp_PhysToVirt   |
    | DevVirtToPhys        | VirtToPhys           | DevHelp_VirtToPhys   |
    | DevPhysToUVirt       | PhysToUVirt          | DevHelp_PhysToUVirt  |
    | DevPhysAlloc         | AllocPhys            | DevHelp_AllocPhys    |
    | DevPhysFree          | FreePhys             | DevHelp_FreePhys     |
    | DevIRQSet            | SetIRQ               | DevHelp_SetIRQ       |
    | DevIRQClear          | UnSetIRQ             | DevHelp_UnSetIRQ     |
    | DevTimerSet          | SetTimer             | DevHelp_SetTimer     |
    | DevTimerClear        | ResetTimer           | DevHelp_ResetTimer   |
    | DevGetDOSVar         | GetDOSVar            | DevHelp_GetDOSVar    |
    | DevSendEvent         | SendEvent            | DevHelp_SendEvent    |
    | DevVerifyAccess      | VerifyAccess         | DevHelp_VerifyAccess |
    | DevSysTrace          | n/a                  | DevHelp_RAS          |
    | DevAttachDD          | AttachDD             | DevHelp_AttachDD     |
    | DevInternalError     | InternalError        | DevHelp_InternalE... |
    | DevAllocGDTSel       | AllocGDTSelector     | DevHelp_AllocGDTS... |
    | DevPhysToGDTSel      | PhysToGDTSelector    | DevHelp_PhysToGDT... |
    | DevEOI               | EOI                  | DevHelp_EOI          |
    | DevTimerModify       | TickCount            | DevHelp_TickCount    |
    | DevIRQStackUsage     | RegisterStackUsage   | DevHelp_RegisterS... |
    | DevRegisterPDD       | RegisterPDD          | DevHelp_RegisterP... |
    | DevBeep              | Beep                 | DevHelp_Beep         |
    | DevFreeGDTSel        | FreeGDTSelector      | DevHelp_FreeGDTSe... |
    | DevVirtToLin         | VirtToLin            | DevHelp_VirtToLin    |
    | DevLinToGDTSel       | LinToGDTSelector     | DevHelp_LinToGDTS... |
    | DevCtxAllocate       | AllocateCtxHook      | DevHelp_AllocateC... |
    | DevCtxFree           | FreeCtxHook          | DevHelp_FreeCtxHook  |
    | DevCtxArm            | ArmCtxHook           | DevHelp_ArmCtxHook   |
    | DevEventOpen         | OpenEventSem         | DevHelp_OpenEventSem |
    | DevEventClose        | CloseEventSem        | DevHelp_CloseEven... |
    | DevEventPost         | PostEventSem         | DevHelp_PostEventSem |
    | DevEventReset        | ResetEventSem        | DevHelp_ResetEven... |
    | DevDynamicAPI16      | DynamicAPI           | DevHelp_DynamicAPI   |
    | DevDynamicAPI32      | DynamicAPI           | DevHelp_DynamicAPI   |
    +----------------------+----------------------+----------------------+

3)    FUTURE ENHANCEMENTS

  This is the first release of these libraries, and so there are
  bound to be several changes (as well as some bug fixes probably)
  between this and the next release.  In particular, there are a
  few areas that I am already working on (or at least contem-
  plating working on).  These areas are listed below.

    - DevHelps

      The DevHelp interfaces will be rewritten to minimize the
      amount of assembler code.  Each DevHelp will have two
      components:  an inline function which "massages" the
      parameters correctly, and an assembler thunk to the DevHelp
      entry point.  This change will let Watcom generate better
      code, and it will also separate the interface from the
      implementation, so that it's easier to use the header file
      as a reference (All of the "code" will be moved to a
      separate implementation file).

    - Device IO

      I am going to completely rewrite the IO interface to
      separate the formatting interface (streams) from the
      outputting interface (streambufs).  This will mean that I
      will also expand the streaming interface to support output
      devices other than the COM ports.  In particular I intend to
      add support for the DosWrite interface that is available at
      driver Init time.

      My goal with this rewrite is to keep the performance equal
      to or better than the current library.  I will pay special
      attention to continuing to ensure that if the stream is used
      as a "Nul stream" (as it is now when DEBUG is not defined),
      then _no_ code will be generated.

    - "Feature" Removal

      Of course, if any bugs ("features") are discovered before
      the next release, I will fix those too.

  I would of course love to hear from anyone who uses this
  library, and I hope to be able to collect suggestions for future
  improvements.  I am also eager to include more samples drivers
  with this package.  Details on contacting me are listed below in
  the section on support.



4)    SUPPORT

  Although this is an unsupported product, there are a few options
  for unofficial support.

  If you are experiencing problems with device driver writing in
  general, then you should contact the IBM Driver Development
  Support Center.  They provide excellent support, and can pass
  your questions on to the people who actually develop OS/2.  In
  their own words...

    "For device driver developers, free support is provided by
    the Driver Development Support Center (DDSC) team, via
    their DUDE (Dynamic Upload and Download Environment)
    system, by calling (407) 982-3217.  The communication
    parameters are N81, at 2400-14400 baud.  Registration is
    done on-line.  Questions are tracked by number, so you're
    assured that your question will get answered.

    "Periodically, the DDSC team archives the questions into a
    file after removing company and developer names, etc.  This
    file is available for download by registered DUDE users.

    "Device driver workshops are also available through the
    DDSC team.  For additional information and schedules, see
    the INFO file area on the DUDE."

  If you are having problems with the Watcom tools, then you
  can contact Watcom technical support.

  Finally, if you have any problems with this library, or if you
  discover any (gasp!) bugs, please feel free to contact me via
  my Internet e-mail address: dwbollo@unixg.ubc.ca.



5)    ACKNOWLEDGEMENTS

  As is usual, I could not have developed this without some
  support from others.  In particular, I would like to thank the
  following people and/or organizations for their assistance.

  - Advanced Gravis, for letting me distribute these libraries
    publicly;

  - Watcom, for providing me with technical support and
    development tool support;

  - IBM DDSC and the "Dude", for providing technical assistance,
    and for offering a helpful course, that was taught by...

  - Nick Mamich, for teaching an excellent device driver course at
    IBM.  Nick is a consultant who is listed in the "Sources and
    Solutions" publication by IBM.  I will reproduce his entry
    here (without permission) for those who are interested:

      "Mr. Nick Mamich
      Testek
      PO Box 429
      Oxford, ME 04270
      207-539-8825

      OS/2 device driver development and training; trained over
      340 programmers and engineers.  Developing OS/2 device
      drivers since version 1.0.  Extensive device driver
      library (PDD, VDD, PM, ADD) available to expedite
      development."

  - Adrienne, for keeping me sane; and

  - Anyone who uses this library and lets me know what they think,
    for letting me know that it wasn't all for nothing.  :)


  Thanks,

  David Bollo
  -----------
  dwbollo@unixg.ubc.ca
  david.bollo@gravis.com

