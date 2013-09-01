


OS22_H   = $(%WATCOM)\h\os2
C32FLAGS = -i=$(OS22_H) -bt=OS2 -zq -wx
WC32     = wcc386 $(C32FLAGS)



# -ms     small memory model (small code/small data)
# -5      optimize for Pentium
# -omi
#     o   control optimization
#     m   generate inline code for math functions
#     i   expand intrinsic functions inline
# -s      remove stack overflow checks
# -zdp    DS is pegged to DGROUP
# -zff    FS floats i.e. not fixed to a segment
# -zgf    GS floats i.e. not fixed to a segment
# -zu     SS != DGROUP (i.e., don't assume stack is in your data segment)
# -zl     remove default library information
# -zq     operate quietly (equivalent to -q)
# -wx     set warning level to maximum setting

OS21_H   = $(%WATCOM)\h;$(%WATCOM)\h\os21x
INCLUDE16 = $(OS21_H);.\include
C16FLAGS = -i=$(INCLUDE16) -wcd=202 -bt=os2 -ms -5 -omi -s -zdp -zff -zgf -zu -zl -zq -wx
WC16     = wcc $(C16FLAGS)
LD16FLAG = op prot,map,st=0
TOOLKIT  = e:\os2tk45
LIBS     = $(TOOLKIT)\LIB

ASM      = wasm $(AFLAGS)
LD       = wlink


.SUFFIXES:
.SUFFIXES: .obj .c .asm
.c.obj: .AUTODEPEND
  $(WC16) $*.c

.asm.obj: .AUTODEPEND
  $(ASM) $*.asm

COREOBJ = devsegs.obj header.obj init.obj strategy.obj ioctl.obj
OPOBJS  = remove.obj shutdown.obj error.obj open.obj close.obj read.obj write.obj

OBJS = $(COREOBJ) $(OPOBJS)

SEGS = seg type DATA SHARED PRELOAD, '_TEXT' PRELOAD IOPL, '_INITCODE' PRELOAD IOPL

all: idlehlt.sys idlehlt.exe idlehlt-af.exe idlehlt-th.exe .SYMBOLIC

idlehlt.sys: $(OBJS)
  $(LD) name idlehlt.sys sys os2_dll initg $(LD16FLAG) lib os2 $(SEGS) FILE {$(OBJS)}

idlehlt.exe:
  wcl386 idlehlt.c

idlehlt-af.exe:
  wcl386 idlehlt-af.c -IMPORTS $(LIBS)\os2386.lib

idlehlt-th.exe:
  wcl386 idlehlt-th.c -IMPORTS $(LIBS)\os2386.lib

clean: .SYMBOLIC
CLEANEXT = sys exe obj err lnk sym lst map lib
  @for %a in ($(CLEANEXT)) do -@rm *.%a


