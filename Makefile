#
# Tremulous Makefile
#
# GNU Make required
#

COMPILE_PLATFORM=$(shell uname|sed -e s/_.*//|tr '[:upper:]' '[:lower:]'|sed -e 's/\//_/g')

COMPILE_ARCH=$(shell uname -m | sed -e s/i.86/x86/)

ifeq ($(COMPILE_PLATFORM),sunos)
  # Solaris uname and GNU uname differ
  COMPILE_ARCH=$(shell uname -p | sed -e s/i.86/x86/)
endif
ifeq ($(COMPILE_PLATFORM),darwin)
  # Apple does some things a little differently...
  COMPILE_ARCH=$(shell uname -p | sed -e s/i.86/x86/)
endif

ifndef BUILD_STANDALONE
  BUILD_STANDALONE =0
endif
ifndef BUILD_CLIENT
  BUILD_CLIENT     =0
endif
ifndef BUILD_CLIENT_SMP
  BUILD_CLIENT_SMP =0
endif
#Turn this to empty the first time and everytime /src/server/* is modified
ifndef BUILD_SERVER
  BUILD_SERVER     =0
endif
ifndef BUILD_GAME_SO
  BUILD_GAME_SO    =0
endif
ifndef BUILD_GAME_QVM
  BUILD_GAME_QVM   =1
endif
ifndef BUILD_MISSIONPACK
  BUILD_MISSIONPACK=0
endif

ifneq ($(PLATFORM),darwin)
  BUILD_CLIENT_SMP = 0
endif

#############################################################################
#
# If you require a different configuration from the defaults below, create a
# new file named "Makefile.local" in the same directory as this file and define
# your parameters there. This allows you to change configuration without
# causing problems with keeping up to date with the repository.
#
#############################################################################
-include Makefile.local

ifndef PLATFORM
PLATFORM=$(COMPILE_PLATFORM)
endif
export PLATFORM

ifeq ($(COMPILE_ARCH),powerpc)
  COMPILE_ARCH=ppc
endif
ifeq ($(COMPILE_ARCH),powerpc64)
  COMPILE_ARCH=ppc64
endif

ifndef ARCH
ARCH=$(COMPILE_ARCH)
endif
export ARCH

ifneq ($(PLATFORM),$(COMPILE_PLATFORM))
  CROSS_COMPILING=1
else
  CROSS_COMPILING=0

  ifneq ($(ARCH),$(COMPILE_ARCH))
    CROSS_COMPILING=1
  endif
endif
export CROSS_COMPILING

ifndef COPYDIR
COPYDIR="/usr/local/games/tremulous"
endif

ifndef COPYBINDIR
COPYBINDIR=$(COPYDIR)
endif

ifndef MOUNT_DIR
MOUNT_DIR=src
endif

ifndef BUILD_DIR
BUILD_DIR=build
endif

ifndef TEMPDIR
TEMPDIR=/tmp
endif

ifndef GENERATE_DEPENDENCIES
GENERATE_DEPENDENCIES=1
endif

ifndef USE_OPENAL
USE_OPENAL=1
endif

ifndef USE_OPENAL_DLOPEN
USE_OPENAL_DLOPEN=1
endif

ifndef USE_CURL
USE_CURL=1
endif

ifndef USE_CURL_DLOPEN
  ifeq ($(PLATFORM),mingw32)
    USE_CURL_DLOPEN=0
  else
    USE_CURL_DLOPEN=1
  endif
endif

ifndef USE_CODEC_VORBIS
USE_CODEC_VORBIS=0
endif

ifndef USE_MUMBLE
USE_MUMBLE=1
endif

ifndef USE_VOIP
USE_VOIP=1
endif

ifndef USE_INTERNAL_SPEEX
USE_INTERNAL_SPEEX=1
endif

ifndef USE_INTERNAL_ZLIB
USE_INTERNAL_ZLIB=1
endif

ifndef USE_INTERNAL_JPEG
USE_INTERNAL_JPEG=1
endif

ifndef USE_LOCAL_HEADERS
USE_LOCAL_HEADERS=1
endif

ifndef BUILD_MASTER_SERVER
BUILD_MASTER_SERVER=0
endif

ifndef DEBUG_CFLAGS
DEBUG_CFLAGS=-g -O0
endif

#############################################################################

BD=$(BUILD_DIR)/debug-$(PLATFORM)-$(ARCH)
BR=$(BUILD_DIR)/release-$(PLATFORM)-$(ARCH)
CDIR=$(MOUNT_DIR)/client
SDIR=$(MOUNT_DIR)/server
RDIR=$(MOUNT_DIR)/renderer
CMDIR=$(MOUNT_DIR)/qcommon
SDLDIR=$(MOUNT_DIR)/sdl
ASMDIR=$(MOUNT_DIR)/asm
SYSDIR=$(MOUNT_DIR)/sys
GDIR=$(MOUNT_DIR)/game
CGDIR=$(MOUNT_DIR)/cgame
NDIR=$(MOUNT_DIR)/null
UIDIR=$(MOUNT_DIR)/ui
JPDIR=$(MOUNT_DIR)/jpeg-8c
SPEEXDIR=$(MOUNT_DIR)/libspeex
ZDIR=$(MOUNT_DIR)/zlib
Q3ASMDIR=$(MOUNT_DIR)/tools/asm
LBURGDIR=$(MOUNT_DIR)/tools/lcc/lburg
Q3CPPDIR=$(MOUNT_DIR)/tools/lcc/cpp
Q3LCCETCDIR=$(MOUNT_DIR)/tools/lcc/etc
Q3LCCSRCDIR=$(MOUNT_DIR)/tools/lcc/src
SDLHDIR=$(MOUNT_DIR)/SDL12
LIBSDIR=$(MOUNT_DIR)/libs
MASTERDIR=$(MOUNT_DIR)/master
TEMPDIR=/tmp

bin_path=$(shell which $(1) 2> /dev/null)

# We won't need this if we only build the server
ifneq ($(BUILD_CLIENT),0)
  # set PKG_CONFIG_PATH to influence this, e.g.
  # PKG_CONFIG_PATH=/opt/cross/i386-mingw32msvc/lib/pkgconfig
  ifneq ($(call bin_path, pkg-config),)
    CURL_CFLAGS=$(shell pkg-config --silence-errors --cflags libcurl)
    CURL_LIBS=$(shell pkg-config --silence-errors --libs libcurl)
    OPENAL_CFLAGS=$(shell pkg-config --silence-errors --cflags openal)
    OPENAL_LIBS=$(shell pkg-config --silence-errors --libs openal)
    SDL_CFLAGS=$(shell pkg-config --silence-errors --cflags sdl|sed 's/-Dmain=SDL_main//')
    SDL_LIBS=$(shell pkg-config --silence-errors --libs sdl)
  endif
  # Use sdl-config if all else fails
  ifeq ($(SDL_CFLAGS),)
    ifneq ($(call bin_path, sdl-config),)
      SDL_CFLAGS=$(shell sdl-config --cflags)
      SDL_LIBS=$(shell sdl-config --libs)
    endif
  endif
endif

# version info
VERSION=gpp1

USE_SVN=
SVN_VERSION=
ifeq ($(wildcard .svn),.svn)
  SVN_REV=$(shell LANG=C svnversion .)
  ifneq ($(SVN_REV),)
    VERSION:=$(VERSION)_SVN$(SVN_REV)
    SVN_VERSION=svn$(SVN_REV)
    USE_SVN=1
  endif
endif


#############################################################################
# SETUP AND BUILD -- LINUX
#############################################################################

## Defaults
LIB=lib

INSTALL=install
MKDIR=mkdir

ifneq (,$(findstring "$(PLATFORM)", "linux" "gnu_kfreebsd" "kfreebsd-gnu"))

  ifeq ($(ARCH),axp)
    ARCH=alpha
  else
  ifeq ($(ARCH),x86_64)
    LIB=lib64
  else
  ifeq ($(ARCH),ppc64)
    LIB=lib64
  else
  ifeq ($(ARCH),s390x)
    LIB=lib64
  endif
  endif
  endif
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -pipe -DUSE_ICON
  CLIENT_CFLAGS = $(SDL_CFLAGS)
  SERVER_CFLAGS =

  ifeq ($(USE_OPENAL),1)
    CLIENT_CFLAGS += -DUSE_OPENAL
    ifeq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_CFLAGS += -DUSE_OPENAL_DLOPEN
    endif
  endif

  ifeq ($(USE_CURL),1)
    CLIENT_CFLAGS += -DUSE_CURL
    ifeq ($(USE_CURL_DLOPEN),1)
      CLIENT_CFLAGS += -DUSE_CURL_DLOPEN
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_CFLAGS += -DUSE_CODEC_VORBIS
  endif

  OPTIMIZEVM = -O3 -funroll-loops -fomit-frame-pointer
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  ifeq ($(ARCH),x86_64)
    OPTIMIZEVM = -O3 -fomit-frame-pointer -funroll-loops \
      -falign-loops=2 -falign-jumps=2 -falign-functions=2 \
      -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED = true
  else
  ifeq ($(ARCH),x86)
    OPTIMIZEVM = -O3 -march=i586 -fomit-frame-pointer \
      -funroll-loops -falign-loops=2 -falign-jumps=2 \
      -falign-functions=2 -fstrength-reduce
    OPTIMIZE = $(OPTIMIZEVM) -ffast-math
    HAVE_VM_COMPILED=true
  else
  ifeq ($(ARCH),ppc)
    BASE_CFLAGS += -maltivec
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -maltivec
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),sparc)
    OPTIMIZE += -mtune=ultrasparc3 -mv8plus
    OPTIMIZEVM += -mtune=ultrasparc3 -mv8plus
    HAVE_VM_COMPILED=true
  endif
  ifeq ($(ARCH),alpha)
    # According to http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=410555
    # -ffast-math will cause the client to die with SIGFPE on Alpha
    OPTIMIZE = $(OPTIMIZEVM)
  endif
  endif
  endif

  ifneq ($(HAVE_VM_COMPILED),true)
    BASE_CFLAGS += -DNO_VM_COMPILED
  endif

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC -fvisibility=hidden
  SHLIBLDFLAGS= -shared $(LDFLAGS)

  THREAD_LIBS=-lpthread
  LIBS=-ldl -lm

  CLIENT_LIBS=$(SDL_LIBS) -lGL

  ifeq ($(USE_OPENAL),1)
    ifneq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_LIBS += -lopenal
    endif
  endif

  ifeq ($(USE_CURL),1)
    ifneq ($(USE_CURL_DLOPEN),1)
      CLIENT_LIBS += -lcurl
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_LIBS += -lvorbisfile -lvorbis -logg
  endif

  ifeq ($(USE_MUMBLE),1)
    CLIENT_LIBS += -lrt
  endif

  ifeq ($(USE_LOCAL_HEADERS),1)
    CLIENT_CFLAGS += -I$(SDLHDIR)/include
  endif

  ifeq ($(ARCH),x86)
    # linux32 make ...
    BASE_CFLAGS += -m32
  else
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -m64
  endif
  endif
else # ifeq Linux

#############################################################################
# SETUP AND BUILD -- MAC OS X
#############################################################################

ifeq ($(PLATFORM),darwin)
  HAVE_VM_COMPILED=true
  CLIENT_LIBS=
  OPTIMIZEVM=

  BASE_CFLAGS = -Wall -Wimplicit -Wstrict-prototypes
  CLIENT_CFLAGS = 
  SERVER_CFLAGS =

  ifeq ($(ARCH),ppc)
    BASE_CFLAGS += -faltivec
    OPTIMIZEVM += -O3
  endif
  ifeq ($(ARCH),ppc64)
    BASE_CFLAGS += -faltivec
  endif
  ifeq ($(ARCH),x86)
    OPTIMIZEVM += -march=prescott -mfpmath=sse
    # x86 vm will crash without -mstackrealign since MMX instructions will be
    # used no matter what and they corrupt the frame pointer in VM calls
    BASE_CFLAGS += -mstackrealign
  endif

  BASE_CFLAGS += -fno-strict-aliasing -DMACOS_X -fno-common -pipe

  ifeq ($(USE_OPENAL),1)
    BASE_CFLAGS += -DUSE_OPENAL
    ifneq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_LIBS += -framework OpenAL
    else
      CLIENT_CFLAGS += -DUSE_OPENAL_DLOPEN
    endif
  endif

  ifeq ($(USE_CURL),1)
    CLIENT_CFLAGS += -DUSE_CURL
    ifneq ($(USE_CURL_DLOPEN),1)
      CLIENT_LIBS += -lcurl
    else
      CLIENT_CFLAGS += -DUSE_CURL_DLOPEN
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_CFLAGS += -DUSE_CODEC_VORBIS
    CLIENT_LIBS += -lvorbisfile -lvorbis -logg
  endif

  BASE_CFLAGS += -D_THREAD_SAFE=1

  ifeq ($(USE_LOCAL_HEADERS),1)
    BASE_CFLAGS += -I$(SDLHDIR)/include
  endif

  # We copy sdlmain before ranlib'ing it so that subversion doesn't think
  #  the file has been modified by each build.
  LIBSDLMAIN=$(B)/libSDLmain.a
  LIBSDLMAINSRC=$(LIBSDIR)/macosx/libSDLmain.a
  CLIENT_LIBS += -framework Cocoa -framework IOKit -framework OpenGL \
    $(LIBSDIR)/macosx/libSDL-1.2.0.dylib

  OPTIMIZEVM += -falign-loops=16
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  ifneq ($(HAVE_VM_COMPILED),true)
    BASE_CFLAGS += -DNO_VM_COMPILED
  endif

  SHLIBEXT=dylib
  SHLIBCFLAGS=-fPIC -fno-common
  SHLIBLDFLAGS=-dynamiclib $(LDFLAGS)

  NOTSHLIBCFLAGS=-mdynamic-no-pic

  TOOLS_CFLAGS += -DMACOS_X

else # ifeq darwin


#############################################################################
# SETUP AND BUILD -- MINGW32
#############################################################################

ifeq ($(PLATFORM),mingw32)

  # Some MinGW installations define CC to cc, but don't actually provide cc,
  # so explicitly use gcc instead (which is the only option anyway)
  ifeq ($(call bin_path, $(CC)),)
    CC=gcc
  endif

  ifndef WINDRES
    WINDRES=windres
  endif

  ARCH=x86

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -DUSE_ICON
  CLIENT_CFLAGS =
  SERVER_CFLAGS =

  # In the absence of wspiapi.h, require Windows XP or later
  ifeq ($(shell test -e $(CMDIR)/wspiapi.h; echo $$?),1)
    BASE_CFLAGS += -DWINVER=0x501
  endif

  ifeq ($(USE_OPENAL),1)
    CLIENT_CFLAGS += -DUSE_OPENAL
    CLIENT_CFLAGS += $(OPENAL_CFLAGS)
    ifeq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_CFLAGS += -DUSE_OPENAL_DLOPEN
    else
      CLIENT_LDFLAGS += $(OPENAL_LDFLAGS)
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_CFLAGS += -DUSE_CODEC_VORBIS
  endif

  OPTIMIZEVM = -O3 -march=i586 -fno-omit-frame-pointer \
    -falign-loops=2 -funroll-loops -falign-jumps=2 -falign-functions=2 \
    -fstrength-reduce
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  HAVE_VM_COMPILED = true

  SHLIBEXT=dll
  SHLIBCFLAGS=
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  BINEXT=.exe

  LIBS= -lws2_32 -lwinmm
  CLIENT_LDFLAGS = -mwindows
  CLIENT_LIBS = -lgdi32 -lole32 -lopengl32

  ifeq ($(USE_CURL),1)
    CLIENT_CFLAGS += -DUSE_CURL
    CLIENT_CFLAGS += $(CURL_CFLAGS)
    ifneq ($(USE_CURL_DLOPEN),1)
      ifeq ($(USE_LOCAL_HEADERS),1)
        CLIENT_CFLAGS += -DCURL_STATICLIB
        CLIENT_LIBS += $(LIBSDIR)/win32/libcurl.a
      else
        CLIENT_LIBS += $(CURL_LIBS)
      endif
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_LIBS += -lvorbisfile -lvorbis -logg
  endif

  ifeq ($(ARCH),x86)
    # build 32bit
    BASE_CFLAGS += -m32
  endif

  # libmingw32 must be linked before libSDLmain
  CLIENT_LIBS += -lmingw32
  ifeq ($(USE_LOCAL_HEADERS),1)
    CLIENT_CFLAGS += -I$(SDLHDIR)/include
    CLIENT_LIBS += $(LIBSDIR)/win32/libSDLmain.a \
                      $(LIBSDIR)/win32/libSDL.dll.a
  else
    CLIENT_CFLAGS += $(SDL_CFLAGS)
    CLIENT_LIBS += $(SDL_LIBS)
  endif

  BUILD_CLIENT_SMP = 0

else # ifeq mingw32

#############################################################################
# SETUP AND BUILD -- FREEBSD
#############################################################################

ifeq ($(PLATFORM),freebsd)

  # flags
  ifneq (,$(findstring alpha,$(shell uname -m)))
    ARCH=axp
  else #default to x86
    ARCH=x86
  endif #alpha test

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -DUSE_ICON
  CLIENT_CFLAGS = $(SDL_CFLAGS)
  SERVER_CFLAGS = 

  ifeq ($(USE_OPENAL),1)
    CLIENT_CFLAGS += -DUSE_OPENAL
    ifeq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_CFLAGS += -DUSE_OPENAL_DLOPEN
    endif
  endif
 
  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_CFLAGS += -DUSE_CODEC_VORBIS
  endif

  OPTIMIZEVM = -O3 -funroll-loops -fomit-frame-pointer

  ifeq ($(ARCH),axp)
    BASE_CFLAGS += -DNO_VM_COMPILED
    OPTIMIZEVM += -fexpensive-optimizations
  else
  ifeq ($(ARCH),x86)
    OPTIMIZEVM += -mtune=pentiumpro \
      -march=pentium -pipe -falign-loops=2 -falign-jumps=2 \
      -falign-functions=2 -funroll-loops -fstrength-reduce
    HAVE_VM_COMPILED=true
  else
    BASE_CFLAGS += -DNO_VM_COMPILED
  endif
  endif

  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LIBS=-lpthread
  # don't need -ldl (FreeBSD)
  LIBS=-lm

  CLIENT_LIBS =

  CLIENT_LIBS += $(SDL_LIBS) -lGL

  ifeq ($(USE_OPENAL),1)
    ifneq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_LIBS += $(THREAD_LIBS) -lopenal
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_LIBS += -lvorbisfile -lvorbis -logg
  endif

else # ifeq freebsd

#############################################################################
# SETUP AND BUILD -- OPENBSD
#############################################################################

ifeq ($(PLATFORM),openbsd)

  #default to i386, no tests done on anything else
  ARCH=i386

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -DUSE_ICON
  CLIENT_CFLAGS = $(SDL_CFLAGS)
  SERVER_CFLAGS = 

  ifeq ($(USE_OPENAL),1)
    CLIENT_CFLAGS += -DUSE_OPENAL
    ifeq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_CFLAGS += -DUSE_OPENAL_DLOPEN
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_CFLAGS += -DUSE_CODEC_VORBIS
  endif

  ifeq ($(USE_CURL),1)
    CLIENT_CFLAGS += -DUSE_CURL $(CURL_CFLAGS)
    USE_CURL_DLOPEN=0
  endif

  BASE_CFLAGS += -DNO_VM_COMPILED
  HAVE_VM_COMPILED=false

  SHLIBEXT=so
  SHLIBNAME=.$(SHLIBEXT)
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LIBS=-pthread
  LIBS=-lm

  CLIENT_LIBS =

  CLIENT_LIBS += $(SDL_LIBS) -lGL

  ifeq ($(USE_OPENAL),1)
    ifneq ($(USE_OPENAL_DLOPEN),1)
      CLIENT_LIBS += $(THREAD_LIBS) -lossaudio -lopenal
    endif
  endif

  ifeq ($(USE_CODEC_VORBIS),1)
    CLIENT_LIBS += -lvorbisfile -lvorbis -logg
  endif

  ifeq ($(USE_CURL),1) 
    ifneq ($(USE_CURL_DLOPEN),1)
      CLIENT_LIBS += -lcurl
    endif
  endif

else # ifeq openbsd

#############################################################################
# SETUP AND BUILD -- NETBSD
#############################################################################

ifeq ($(PLATFORM),netbsd)

  ifeq ($(shell uname -m),i386)
    ARCH=x86
  endif

  LIBS=-lm
  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)
  THREAD_LIBS=-lpthread

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes
  CLIENT_CFLAGS =
  SERVER_CFLAGS =

  ifneq ($(ARCH),x86)
    BASE_CFLAGS += -DNO_VM_COMPILED
  endif

  BUILD_CLIENT = 0
  BUILD_GAME_QVM = 0

else # ifeq netbsd

#############################################################################
# SETUP AND BUILD -- IRIX
#############################################################################

ifeq ($(PLATFORM),irix64)

  ARCH=mips  #default to MIPS

  CC = c99
  MKDIR = mkdir -p

  BASE_CFLAGS=-Dstricmp=strcasecmp -Xcpluscomm -woff 1185 \
    -I. -I$(ROOT)/usr/include -DNO_VM_COMPILED
  CLIENT_CFLAGS = $(SDL_CFLAGS)
  OPTIMIZE = -O3
  
  SHLIBEXT=so
  SHLIBCFLAGS=
  SHLIBLDFLAGS=-shared

  LIBS=-ldl -lm -lgen
  # FIXME: The X libraries probably aren't necessary?
  CLIENT_LIBS=-L/usr/X11/$(LIB) $(SDL_LIBS) -lGL \
    -lX11 -lXext -lm

else # ifeq IRIX

#############################################################################
# SETUP AND BUILD -- SunOS
#############################################################################

ifeq ($(PLATFORM),sunos)

  CC=gcc
  INSTALL=ginstall
  MKDIR=gmkdir
  COPYDIR="/usr/local/share/games/tremulous"

  ifneq (,$(findstring i86pc,$(shell uname -m)))
    ARCH=x86
  else #default to sparc
    ARCH=sparc
  endif

  ifneq ($(ARCH),x86)
    ifneq ($(ARCH),sparc)
      $(error arch $(ARCH) is currently not supported)
    endif
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes \
    -pipe -DUSE_ICON
  CLIENT_CFLAGS = $(SDL_CFLAGS)
  SERVER_CFLAGS =

  OPTIMIZEVM = -O3 -funroll-loops

  ifeq ($(ARCH),sparc)
    OPTIMIZEVM += -O3 \
      -fstrength-reduce -falign-functions=2 \
      -mtune=ultrasparc3 -mv8plus -mno-faster-structs
    HAVE_VM_COMPILED=true
  else
  ifeq ($(ARCH),x86)
    OPTIMIZEVM += -march=i586 -fomit-frame-pointer \
      -falign-loops=2 -falign-jumps=2 \
      -falign-functions=2 -fstrength-reduce
    HAVE_VM_COMPILED=true
    BASE_CFLAGS += -m32
    CLIENT_CFLAGS += -I/usr/X11/include/NVIDIA
    CLIENT_LDFLAGS += -L/usr/X11/lib/NVIDIA -R/usr/X11/lib/NVIDIA
  endif
  endif
  
  OPTIMIZE = $(OPTIMIZEVM) -ffast-math

  ifneq ($(HAVE_VM_COMPILED),true)
    BASE_CFLAGS += -DNO_VM_COMPILED
  endif

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LIBS=-lpthread
  LIBS=-lsocket -lnsl -ldl -lm

  BOTCFLAGS=-O0

  CLIENT_LIBS +=$(SDL_LIBS) -lGL -lX11 -lXext -liconv -lm

else # ifeq sunos

#############################################################################
# SETUP AND BUILD -- GENERIC
#############################################################################
  BASE_CFLAGS=-DNO_VM_COMPILED
  OPTIMIZE = -O3

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared

endif #Linux
endif #darwin
endif #mingw32
endif #FreeBSD
endif #OpenBSD
endif #NetBSD
endif #IRIX
endif #SunOS

TARGETS =

ifndef FULLBINEXT
  FULLBINEXT=.$(ARCH)$(BINEXT)
endif

ifndef SHLIBNAME
  SHLIBNAME=$(ARCH).$(SHLIBEXT)
endif

ifneq ($(BUILD_SERVER),0)
  TARGETS += $(B)/tremded$(FULLBINEXT)
endif

ifneq ($(BUILD_CLIENT),0)
  TARGETS += $(B)/tremulous$(FULLBINEXT)
  ifneq ($(BUILD_CLIENT_SMP),0)
    TARGETS += $(B)/tremulous-smp$(FULLBINEXT)
  endif
endif

ifneq ($(BUILD_GAME_SO),0)
  TARGETS += \
    $(B)/base/cgame$(SHLIBNAME) \
    $(B)/base/game$(SHLIBNAME) \
    $(B)/base/ui$(SHLIBNAME)
endif

ifneq ($(BUILD_GAME_QVM),0)
  ifneq ($(CROSS_COMPILING),1)
    TARGETS += \
      $(B)/base/vm/cgame.qvm \
      $(B)/base/vm/game.qvm \
      $(B)/base/vm/ui.qvm
  endif
endif

ifeq ($(USE_MUMBLE),1)
  CLIENT_CFLAGS += -DUSE_MUMBLE
endif

ifeq ($(USE_VOIP),1)
  CLIENT_CFLAGS += -DUSE_VOIP
  SERVER_CFLAGS += -DUSE_VOIP
  ifeq ($(USE_INTERNAL_SPEEX),1)
    CLIENT_CFLAGS += -DFLOATING_POINT -DUSE_ALLOCA -I$(SPEEXDIR)/include
  else
    CLIENT_LIBS += -lspeex -lspeexdsp
  endif
endif

ifeq ($(USE_INTERNAL_ZLIB),1)
  BASE_CFLAGS += -DNO_GZIP
  ifneq ($(USE_LOCAL_HEADERS),1)
    BASE_CFLAGS += -I$(ZDIR)
  endif
else
  LIBS += -lz
endif

ifeq ($(USE_INTERNAL_JPEG),1)
  BASE_CFLAGS += -DUSE_INTERNAL_JPEG
  BASE_CFLAGS += -I$(JPDIR)
else
  CLIENT_LIBS += -ljpeg
endif

ifdef DEFAULT_BASEDIR
  BASE_CFLAGS += -DDEFAULT_BASEDIR=\\\"$(DEFAULT_BASEDIR)\\\"
endif

ifeq ($(USE_LOCAL_HEADERS),1)
  BASE_CFLAGS += -DUSE_LOCAL_HEADERS
endif

ifeq ($(BUILD_STANDALONE),1)
  BASE_CFLAGS += -DSTANDALONE
endif

ifeq ($(GENERATE_DEPENDENCIES),1)
  DEPEND_CFLAGS = -MMD
else
  DEPEND_CFLAGS =
endif

ifeq ($(NO_STRIP),1)
  STRIP_FLAG =
else
  STRIP_FLAG = -s
endif

BASE_CFLAGS += -DPRODUCT_VERSION=\\\"$(VERSION)\\\"
BASE_CFLAGS += -DSVN_VERSION=\\\"$(SVN_VERSION)\\\"

ifeq ($(V),1)
echo_cmd=@:
Q=
else
echo_cmd=@echo
Q=@
endif

define DO_CC
$(echo_cmd) "CC $<"
$(Q)$(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) $(CLIENT_CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_SMP_CC
$(echo_cmd) "SMP_CC $<"
$(Q)$(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) $(CLIENT_CFLAGS) $(OPTIMIZE) -DSMP -o $@ -c $<
endef

ifeq ($(GENERATE_DEPENDENCIES),1)
  DO_QVM_DEP=cat $(@:%.o=%.d) | sed -e 's/\.o/\.asm/g' >> $(@:%.o=%.d)
endif

define DO_SHLIB_CC
$(echo_cmd) "SHLIB_CC $<"
$(Q)$(CC) $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_GAME_CC
$(echo_cmd) "GAME_CC $<"
$(Q)$(CC) -DGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_CGAME_CC
$(echo_cmd) "CGAME_CC $<"
$(Q)$(CC) -DCGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_UI_CC
$(echo_cmd) "UI_CC $<"
$(Q)$(CC) -DUI $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZEVM) -o $@ -c $<
$(Q)$(DO_QVM_DEP)
endef

define DO_AS
$(echo_cmd) "AS $<"
$(Q)$(CC) $(CFLAGS) $(OPTIMIZE) -x assembler-with-cpp -o $@ -c $<
endef

define DO_DED_CC
$(echo_cmd) "DED_CC $<"
$(Q)$(CC) $(NOTSHLIBCFLAGS) -DDEDICATED $(CFLAGS) $(SERVER_CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_WINDRES
$(echo_cmd) "WINDRES $<"
$(Q)$(WINDRES) -i $< -o $@
endef


#############################################################################
# MAIN TARGETS
#############################################################################

default: release
all: debug release

debug:
	@$(MAKE) targets B=$(BD) CFLAGS="$(CFLAGS) $(BASE_CFLAGS) $(DEPEND_CFLAGS)" \
	  OPTIMIZE="$(DEBUG_CFLAGS)" OPTIMIZEVM="$(DEBUG_CFLAGS)" \
	  CLIENT_CFLAGS="$(CLIENT_CFLAGS)" SERVER_CFLAGS="$(SERVER_CFLAGS)" V=$(V)
ifeq ($(BUILD_MASTER_SERVER),1)
	$(MAKE) -C $(MASTERDIR) debug
endif

release:
	@$(MAKE) targets B=$(BR) CFLAGS="$(CFLAGS) $(BASE_CFLAGS) $(DEPEND_CFLAGS)" \
	  OPTIMIZE="-DNDEBUG $(OPTIMIZE)" OPTIMIZEVM="-DNDEBUG $(OPTIMIZEVM)" \
	  CLIENT_CFLAGS="$(CLIENT_CFLAGS)" SERVER_CFLAGS="$(SERVER_CFLAGS)" V=$(V)
ifeq ($(BUILD_MASTER_SERVER),1)
	$(MAKE) -C $(MASTERDIR) release
endif

# Create the build directories, check libraries and print out
# an informational message, then start building
targets: makedirs
	@echo ""
	@echo "Building Tremulous in $(B):"
	@echo "  PLATFORM: $(PLATFORM)"
	@echo "  ARCH: $(ARCH)"
	@echo "  VERSION: $(VERSION)"
	@echo "  COMPILE_PLATFORM: $(COMPILE_PLATFORM)"
	@echo "  COMPILE_ARCH: $(COMPILE_ARCH)"
	@echo "  CC: $(CC)"
	@echo ""
	@echo "  CFLAGS:"
	-@for i in $(CFLAGS); \
	do \
		echo "    $$i"; \
	done
	-@for i in $(OPTIMIZE); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  CLIENT_CFLAGS:"
	-@for i in $(CLIENT_CFLAGS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  SERVER_CFLAGS:"
	-@for i in $(SERVER_CFLAGS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  LDFLAGS:"
	-@for i in $(LDFLAGS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  LIBS:"
	-@for i in $(LIBS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  CLIENT_LIBS:"
	-@for i in $(CLIENT_LIBS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  Output:"
	-@for i in $(TARGETS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
ifneq ($(TARGETS),)
	@$(MAKE) $(TARGETS) V=$(V)
endif

makedirs:
	@if [ ! -d $(BUILD_DIR) ];then $(MKDIR) $(BUILD_DIR);fi
	@if [ ! -d $(B) ];then $(MKDIR) $(B);fi
	@if [ ! -d $(B)/client ];then $(MKDIR) $(B)/client;fi
	@if [ ! -d $(B)/clientsmp ];then $(MKDIR) $(B)/clientsmp;fi
	@if [ ! -d $(B)/ded ];then $(MKDIR) $(B)/ded;fi
	@if [ ! -d $(B)/base ];then $(MKDIR) $(B)/base;fi
	@if [ ! -d $(B)/base/cgame ];then $(MKDIR) $(B)/base/cgame;fi
	@if [ ! -d $(B)/base/game ];then $(MKDIR) $(B)/base/game;fi
	@if [ ! -d $(B)/base/ui ];then $(MKDIR) $(B)/base/ui;fi
	@if [ ! -d $(B)/base/qcommon ];then $(MKDIR) $(B)/base/qcommon;fi
	@if [ ! -d $(B)/base/vm ];then $(MKDIR) $(B)/base/vm;fi
	@if [ ! -d $(B)/tools ];then $(MKDIR) $(B)/tools;fi
	@if [ ! -d $(B)/tools/asm ];then $(MKDIR) $(B)/tools/asm;fi
	@if [ ! -d $(B)/tools/etc ];then $(MKDIR) $(B)/tools/etc;fi
	@if [ ! -d $(B)/tools/rcc ];then $(MKDIR) $(B)/tools/rcc;fi
	@if [ ! -d $(B)/tools/cpp ];then $(MKDIR) $(B)/tools/cpp;fi
	@if [ ! -d $(B)/tools/lburg ];then $(MKDIR) $(B)/tools/lburg;fi

#############################################################################
# QVM BUILD TOOLS
#############################################################################

TOOLS_OPTIMIZE = -g -O2 -Wall -fno-strict-aliasing
TOOLS_CFLAGS += $(TOOLS_OPTIMIZE) \
                -DTEMPDIR=\"$(TEMPDIR)\" -DSYSTEM=\"\" \
                -I$(Q3LCCSRCDIR) \
                -I$(LBURGDIR)
TOOLS_LIBS =
TOOLS_LDFLAGS =

ifeq ($(GENERATE_DEPENDENCIES),1)
	TOOLS_CFLAGS += -MMD
endif

define DO_TOOLS_CC
$(echo_cmd) "TOOLS_CC $<"
$(Q)$(CC) $(TOOLS_CFLAGS) -o $@ -c $<
endef

define DO_TOOLS_CC_DAGCHECK
$(echo_cmd) "TOOLS_CC_DAGCHECK $<"
$(Q)$(CC) $(TOOLS_CFLAGS) -Wno-unused -o $@ -c $<
endef

LBURG       = $(B)/tools/lburg/lburg$(BINEXT)
DAGCHECK_C  = $(B)/tools/rcc/dagcheck.c
Q3RCC       = $(B)/tools/q3rcc$(BINEXT)
Q3CPP       = $(B)/tools/q3cpp$(BINEXT)
Q3LCC       = $(B)/tools/q3lcc$(BINEXT)
Q3ASM       = $(B)/tools/q3asm$(BINEXT)

LBURGOBJ= \
	$(B)/tools/lburg/lburg.o \
	$(B)/tools/lburg/gram.o

$(B)/tools/lburg/%.o: $(LBURGDIR)/%.c
	$(DO_TOOLS_CC)

$(LBURG): $(LBURGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3RCCOBJ = \
  $(B)/tools/rcc/alloc.o \
  $(B)/tools/rcc/bind.o \
  $(B)/tools/rcc/bytecode.o \
  $(B)/tools/rcc/dag.o \
  $(B)/tools/rcc/dagcheck.o \
  $(B)/tools/rcc/decl.o \
  $(B)/tools/rcc/enode.o \
  $(B)/tools/rcc/error.o \
  $(B)/tools/rcc/event.o \
  $(B)/tools/rcc/expr.o \
  $(B)/tools/rcc/gen.o \
  $(B)/tools/rcc/init.o \
  $(B)/tools/rcc/inits.o \
  $(B)/tools/rcc/input.o \
  $(B)/tools/rcc/lex.o \
  $(B)/tools/rcc/list.o \
  $(B)/tools/rcc/main.o \
  $(B)/tools/rcc/null.o \
  $(B)/tools/rcc/output.o \
  $(B)/tools/rcc/prof.o \
  $(B)/tools/rcc/profio.o \
  $(B)/tools/rcc/simp.o \
  $(B)/tools/rcc/stmt.o \
  $(B)/tools/rcc/string.o \
  $(B)/tools/rcc/sym.o \
  $(B)/tools/rcc/symbolic.o \
  $(B)/tools/rcc/trace.o \
  $(B)/tools/rcc/tree.o \
  $(B)/tools/rcc/types.o

$(DAGCHECK_C): $(LBURG) $(Q3LCCSRCDIR)/dagcheck.md
	$(echo_cmd) "LBURG $(Q3LCCSRCDIR)/dagcheck.md"
	$(Q)$(LBURG) $(Q3LCCSRCDIR)/dagcheck.md $@

$(B)/tools/rcc/dagcheck.o: $(DAGCHECK_C)
	$(DO_TOOLS_CC_DAGCHECK)

$(B)/tools/rcc/%.o: $(Q3LCCSRCDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3RCC): $(Q3RCCOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3CPPOBJ = \
	$(B)/tools/cpp/cpp.o \
	$(B)/tools/cpp/lex.o \
	$(B)/tools/cpp/nlist.o \
	$(B)/tools/cpp/tokens.o \
	$(B)/tools/cpp/macro.o \
	$(B)/tools/cpp/eval.o \
	$(B)/tools/cpp/include.o \
	$(B)/tools/cpp/hideset.o \
	$(B)/tools/cpp/getopt.o \
	$(B)/tools/cpp/unix.o

$(B)/tools/cpp/%.o: $(Q3CPPDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3CPP): $(Q3CPPOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3LCCOBJ = \
	$(B)/tools/etc/lcc.o \
	$(B)/tools/etc/bytecode.o

$(B)/tools/etc/%.o: $(Q3LCCETCDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3LCC): $(Q3LCCOBJ) $(Q3RCC) $(Q3CPP)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $(Q3LCCOBJ) $(TOOLS_LIBS)

define DO_Q3LCC
$(echo_cmd) "Q3LCC $<"
$(Q)$(Q3LCC) -o $@ $<
endef

define DO_CGAME_Q3LCC
$(echo_cmd) "CGAME_Q3LCC $<"
$(Q)$(Q3LCC) -DPRODUCT_VERSION=\"$(VERSION)\" -DCGAME -DSVN_VERSION=\"$(SVN_VERSION)\" -o $@ $<
endef

define DO_GAME_Q3LCC
$(echo_cmd) "GAME_Q3LCC $<"
$(Q)$(Q3LCC) -DPRODUCT_VERSION=\"$(VERSION)\" -DGAME -DSVN_VERSION=\"$(SVN_VERSION)\" -o $@ $<
endef

define DO_UI_Q3LCC
$(echo_cmd) "UI_Q3LCC $<"
$(Q)$(Q3LCC) -DPRODUCT_VERSION=\"$(VERSION)\" -DUI -DSVN_VERSION=\"$(SVN_VERSION)\" -o $@ $<
endef


Q3ASMOBJ = \
  $(B)/tools/asm/q3asm.o \
  $(B)/tools/asm/cmdlib.o

$(B)/tools/asm/%.o: $(Q3ASMDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3ASM): $(Q3ASMOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)


#############################################################################
# CLIENT/SERVER
#############################################################################

Q3OBJ = \
  $(B)/client/cl_cgame.o \
  $(B)/client/cl_cin.o \
  $(B)/client/cl_console.o \
  $(B)/client/cl_input.o \
  $(B)/client/cl_keys.o \
  $(B)/client/cl_main.o \
  $(B)/client/cl_net_chan.o \
  $(B)/client/cl_parse.o \
  $(B)/client/cl_scrn.o \
  $(B)/client/cl_ui.o \
  $(B)/client/cl_avi.o \
  \
  $(B)/client/cm_load.o \
  $(B)/client/cm_patch.o \
  $(B)/client/cm_polylib.o \
  $(B)/client/cm_test.o \
  $(B)/client/cm_trace.o \
  \
  $(B)/client/cmd.o \
  $(B)/client/common.o \
  $(B)/client/cvar.o \
  $(B)/client/files.o \
  $(B)/client/md4.o \
  $(B)/client/md5.o \
  $(B)/client/msg.o \
  $(B)/client/net_chan.o \
  $(B)/client/net_ip.o \
  $(B)/client/huffman.o \
  $(B)/client/parse.o \
  \
  $(B)/client/snd_adpcm.o \
  $(B)/client/snd_dma.o \
  $(B)/client/snd_mem.o \
  $(B)/client/snd_mix.o \
  $(B)/client/snd_wavelet.o \
  \
  $(B)/client/snd_main.o \
  $(B)/client/snd_codec.o \
  $(B)/client/snd_codec_wav.o \
  $(B)/client/snd_codec_ogg.o \
  \
  $(B)/client/qal.o \
  $(B)/client/snd_openal.o \
  \
  $(B)/client/cl_curl.o \
  \
  $(B)/client/sv_ccmds.o \
  $(B)/client/sv_client.o \
  $(B)/client/sv_game.o \
  $(B)/client/sv_init.o \
  $(B)/client/sv_main.o \
  $(B)/client/sv_net_chan.o \
  $(B)/client/sv_snapshot.o \
  $(B)/client/sv_world.o \
  \
  $(B)/client/q_math.o \
  $(B)/client/q_shared.o \
  \
  $(B)/client/unzip.o \
  $(B)/client/ioapi.o \
  $(B)/client/puff.o \
  $(B)/client/vm.o \
  $(B)/client/vm_interpreted.o \
  \
  $(B)/client/tr_animation.o \
  $(B)/client/tr_backend.o \
  $(B)/client/tr_bsp.o \
  $(B)/client/tr_cmds.o \
  $(B)/client/tr_curve.o \
  $(B)/client/tr_flares.o \
  $(B)/client/tr_font.o \
  $(B)/client/tr_image.o \
  $(B)/client/tr_image_png.o \
  $(B)/client/tr_image_jpg.o \
  $(B)/client/tr_image_bmp.o \
  $(B)/client/tr_image_tga.o \
  $(B)/client/tr_image_pcx.o \
  $(B)/client/tr_init.o \
  $(B)/client/tr_light.o \
  $(B)/client/tr_main.o \
  $(B)/client/tr_marks.o \
  $(B)/client/tr_mesh.o \
  $(B)/client/tr_model.o \
  $(B)/client/tr_noise.o \
  $(B)/client/tr_scene.o \
  $(B)/client/tr_shade.o \
  $(B)/client/tr_shade_calc.o \
  $(B)/client/tr_shader.o \
  $(B)/client/tr_shadows.o \
  $(B)/client/tr_sky.o \
  $(B)/client/tr_surface.o \
  $(B)/client/tr_world.o \
  \
  $(B)/client/sdl_gamma.o \
  $(B)/client/sdl_input.o \
  $(B)/client/sdl_snd.o \
  \
  $(B)/client/con_passive.o \
  $(B)/client/con_log.o \
  $(B)/client/sys_main.o

ifneq ($(USE_INTERNAL_JPEG),0)
  Q3OBJ += \
    $(B)/client/jaricom.o \
    $(B)/client/jcapimin.o \
    $(B)/client/jcapistd.o \
    $(B)/client/jcarith.o \
    $(B)/client/jccoefct.o  \
    $(B)/client/jccolor.o \
    $(B)/client/jcdctmgr.o \
    $(B)/client/jchuff.o   \
    $(B)/client/jcinit.o \
    $(B)/client/jcmainct.o \
    $(B)/client/jcmarker.o \
    $(B)/client/jcmaster.o \
    $(B)/client/jcomapi.o \
    $(B)/client/jcparam.o \
    $(B)/client/jcprepct.o \
    $(B)/client/jcsample.o \
    $(B)/client/jctrans.o \
    $(B)/client/jdapimin.o \
    $(B)/client/jdapistd.o \
    $(B)/client/jdarith.o \
    $(B)/client/jdatadst.o \
    $(B)/client/jdatasrc.o \
    $(B)/client/jdcoefct.o \
    $(B)/client/jdcolor.o \
    $(B)/client/jddctmgr.o \
    $(B)/client/jdhuff.o \
    $(B)/client/jdinput.o \
    $(B)/client/jdmainct.o \
    $(B)/client/jdmarker.o \
    $(B)/client/jdmaster.o \
    $(B)/client/jdmerge.o \
    $(B)/client/jdpostct.o \
    $(B)/client/jdsample.o \
    $(B)/client/jdtrans.o \
    $(B)/client/jerror.o \
    $(B)/client/jfdctflt.o \
    $(B)/client/jfdctfst.o \
    $(B)/client/jfdctint.o \
    $(B)/client/jidctflt.o \
    $(B)/client/jidctfst.o \
    $(B)/client/jidctint.o \
    $(B)/client/jmemmgr.o \
    $(B)/client/jmemnobs.o \
    $(B)/client/jquant1.o \
    $(B)/client/jquant2.o \
    $(B)/client/jutils.o
endif

ifeq ($(ARCH),x86)
  Q3OBJ += \
    $(B)/client/snd_mixa.o \
    $(B)/client/matha.o \
    $(B)/client/ftola.o \
    $(B)/client/snapvectora.o
endif

ifeq ($(USE_VOIP),1)
ifeq ($(USE_INTERNAL_SPEEX),1)
Q3OBJ += \
  $(B)/client/bits.o \
  $(B)/client/buffer.o \
  $(B)/client/cb_search.o \
  $(B)/client/exc_10_16_table.o \
  $(B)/client/exc_10_32_table.o \
  $(B)/client/exc_20_32_table.o \
  $(B)/client/exc_5_256_table.o \
  $(B)/client/exc_5_64_table.o \
  $(B)/client/exc_8_128_table.o \
  $(B)/client/fftwrap.o \
  $(B)/client/filterbank.o \
  $(B)/client/filters.o \
  $(B)/client/gain_table.o \
  $(B)/client/gain_table_lbr.o \
  $(B)/client/hexc_10_32_table.o \
  $(B)/client/hexc_table.o \
  $(B)/client/high_lsp_tables.o \
  $(B)/client/jitter.o \
  $(B)/client/kiss_fft.o \
  $(B)/client/kiss_fftr.o \
  $(B)/client/lpc.o \
  $(B)/client/lsp.o \
  $(B)/client/lsp_tables_nb.o \
  $(B)/client/ltp.o \
  $(B)/client/mdf.o \
  $(B)/client/modes.o \
  $(B)/client/modes_wb.o \
  $(B)/client/nb_celp.o \
  $(B)/client/preprocess.o \
  $(B)/client/quant_lsp.o \
  $(B)/client/resample.o \
  $(B)/client/sb_celp.o \
  $(B)/client/smallft.o \
  $(B)/client/speex.o \
  $(B)/client/speex_callbacks.o \
  $(B)/client/speex_header.o \
  $(B)/client/stereo.o \
  $(B)/client/vbr.o \
  $(B)/client/vq.o \
  $(B)/client/window.o
endif
endif

ifeq ($(USE_INTERNAL_ZLIB),1)
Q3OBJ += \
  $(B)/client/adler32.o \
  $(B)/client/crc32.o \
  $(B)/client/inffast.o \
  $(B)/client/inflate.o \
  $(B)/client/inftrees.o \
  $(B)/client/zutil.o
endif

ifeq ($(HAVE_VM_COMPILED),true)
  ifeq ($(ARCH),x86)
    Q3OBJ += $(B)/client/vm_x86.o
  endif
  ifeq ($(ARCH),x86_64)
    Q3OBJ += $(B)/client/vm_x86_64.o $(B)/client/vm_x86_64_assembler.o
  endif
  ifeq ($(ARCH),ppc)
    Q3OBJ += $(B)/client/vm_powerpc.o $(B)/client/vm_powerpc_asm.o
  endif
  ifeq ($(ARCH),ppc64)
    Q3OBJ += $(B)/client/vm_powerpc.o $(B)/client/vm_powerpc_asm.o
  endif
  ifeq ($(ARCH),sparc)
    Q3OBJ += $(B)/client/vm_sparc.o
  endif
endif

ifeq ($(PLATFORM),mingw32)
  Q3OBJ += \
    $(B)/client/win_resource.o \
    $(B)/client/sys_win32.o
else
  Q3OBJ += \
    $(B)/client/sys_unix.o
endif

ifeq ($(PLATFORM),darwin)
  Q3OBJ += \
    $(B)/client/sys_cocoa.o
endif

ifeq ($(USE_MUMBLE),1)
  Q3OBJ += \
    $(B)/client/libmumblelink.o
endif

Q3POBJ += \
  $(B)/client/sdl_glimp.o

Q3POBJ_SMP += \
  $(B)/clientsmp/sdl_glimp.o

$(B)/tremulous$(FULLBINEXT): $(Q3OBJ) $(Q3POBJ) $(LIBSDLMAIN)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CLIENT_CFLAGS) $(CFLAGS) $(CLIENT_LDFLAGS) $(LDFLAGS) \
		-o $@ $(Q3OBJ) $(Q3POBJ) \
		$(LIBSDLMAIN) $(CLIENT_LIBS) $(LIBS)

$(B)/tremulous-smp$(FULLBINEXT): $(Q3OBJ) $(Q3POBJ_SMP) $(LIBSDLMAIN)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CLIENT_CFLAGS) $(CFLAGS) $(CLIENT_LDFLAGS) $(LDFLAGS) $(THREAD_LDFLAGS) \
		-o $@ $(Q3OBJ) $(Q3POBJ_SMP) \
		$(THREAD_LIBS) $(LIBSDLMAIN) $(CLIENT_LIBS) $(LIBS)

ifneq ($(strip $(LIBSDLMAIN)),)
ifneq ($(strip $(LIBSDLMAINSRC)),)
$(LIBSDLMAIN) : $(LIBSDLMAINSRC)
	cp $< $@
	ranlib $@
endif
endif



#############################################################################
# DEDICATED SERVER
#############################################################################

Q3DOBJ = \
  $(B)/ded/sv_client.o \
  $(B)/ded/sv_ccmds.o \
  $(B)/ded/sv_game.o \
  $(B)/ded/sv_init.o \
  $(B)/ded/sv_main.o \
  $(B)/ded/sv_net_chan.o \
  $(B)/ded/sv_snapshot.o \
  $(B)/ded/sv_world.o \
  \
  $(B)/ded/cm_load.o \
  $(B)/ded/cm_patch.o \
  $(B)/ded/cm_polylib.o \
  $(B)/ded/cm_test.o \
  $(B)/ded/cm_trace.o \
  $(B)/ded/cmd.o \
  $(B)/ded/common.o \
  $(B)/ded/cvar.o \
  $(B)/ded/files.o \
  $(B)/ded/md4.o \
  $(B)/ded/msg.o \
  $(B)/ded/net_chan.o \
  $(B)/ded/net_ip.o \
  $(B)/ded/huffman.o \
  $(B)/ded/parse.o \
  \
  $(B)/ded/q_math.o \
  $(B)/ded/q_shared.o \
  \
  $(B)/ded/unzip.o \
  $(B)/ded/ioapi.o \
  $(B)/ded/vm.o \
  $(B)/ded/vm_interpreted.o \
  \
  $(B)/ded/null_client.o \
  $(B)/ded/null_input.o \
  $(B)/ded/null_snddma.o \
  \
  $(B)/ded/con_log.o \
  $(B)/ded/sys_main.o

ifeq ($(ARCH),x86)
  Q3DOBJ += \
      $(B)/ded/ftola.o \
      $(B)/ded/snapvectora.o \
      $(B)/ded/matha.o
endif

ifeq ($(USE_INTERNAL_ZLIB),1)
Q3DOBJ += \
  $(B)/ded/adler32.o \
  $(B)/ded/crc32.o \
  $(B)/ded/inffast.o \
  $(B)/ded/inflate.o \
  $(B)/ded/inftrees.o \
  $(B)/ded/zutil.o
endif

ifeq ($(HAVE_VM_COMPILED),true)
  ifeq ($(ARCH),x86)
    Q3DOBJ += $(B)/ded/vm_x86.o
  endif
  ifeq ($(ARCH),x86_64)
    Q3DOBJ += $(B)/ded/vm_x86_64.o $(B)/ded/vm_x86_64_assembler.o
  endif
  ifeq ($(ARCH),ppc)
    Q3DOBJ += $(B)/ded/vm_powerpc.o $(B)/ded/vm_powerpc_asm.o
  endif
  ifeq ($(ARCH),ppc64)
    Q3DOBJ += $(B)/ded/vm_powerpc.o $(B)/ded/vm_powerpc_asm.o
  endif
  ifeq ($(ARCH),sparc)
    Q3DOBJ += $(B)/ded/vm_sparc.o
  endif
endif

ifeq ($(PLATFORM),mingw32)
  Q3DOBJ += \
    $(B)/ded/win_resource.o \
    $(B)/ded/sys_win32.o \
    $(B)/ded/con_win32.o
else
  Q3DOBJ += \
    $(B)/ded/sys_unix.o \
    $(B)/ded/con_tty.o
endif

$(B)/tremded$(FULLBINEXT): $(Q3DOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(Q3DOBJ) $(LIBS)



#############################################################################
## TREMULOUS CGAME
#############################################################################

CGOBJ_ = \
  $(B)/base/cgame/cg_main.o \
  $(B)/base/cgame/bg_misc.o \
  $(B)/base/cgame/bg_pmove.o \
  $(B)/base/cgame/bg_slidemove.o \
  $(B)/base/cgame/bg_lib.o \
  $(B)/base/cgame/bg_alloc.o \
  $(B)/base/cgame/bg_voice.o \
  $(B)/base/cgame/cg_consolecmds.o \
  $(B)/base/cgame/cg_buildable.o \
  $(B)/base/cgame/cg_animation.o \
  $(B)/base/cgame/cg_animmapobj.o \
  $(B)/base/cgame/cg_draw.o \
  $(B)/base/cgame/cg_drawtools.o \
  $(B)/base/cgame/cg_ents.o \
  $(B)/base/cgame/cg_event.o \
  $(B)/base/cgame/cg_marks.o \
  $(B)/base/cgame/cg_players.o \
  $(B)/base/cgame/cg_playerstate.o \
  $(B)/base/cgame/cg_predict.o \
  $(B)/base/cgame/cg_servercmds.o \
  $(B)/base/cgame/cg_snapshot.o \
  $(B)/base/cgame/cg_view.o \
  $(B)/base/cgame/cg_weapons.o \
  $(B)/base/cgame/cg_scanner.o \
  $(B)/base/cgame/cg_attachment.o \
  $(B)/base/cgame/cg_trails.o \
  $(B)/base/cgame/cg_particles.o \
  $(B)/base/cgame/cg_tutorial.o \
  $(B)/base/ui/ui_shared.o \
  \
  $(B)/base/qcommon/q_math.o \
  $(B)/base/qcommon/q_shared.o

CGOBJ = $(CGOBJ_) $(B)/base/cgame/cg_syscalls.o
CGVMOBJ = $(CGOBJ_:%.o=%.asm)

$(B)/base/cgame$(SHLIBNAME): $(CGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(CGOBJ)

$(B)/base/vm/cgame.qvm: $(CGVMOBJ) $(CGDIR)/cg_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(CGVMOBJ) $(CGDIR)/cg_syscalls.asm



#############################################################################
## TREMULOUS GAME
#############################################################################

GOBJ_ = \
  $(B)/base/game/g_main.o \
  $(B)/base/game/bg_misc.o \
  $(B)/base/game/bg_pmove.o \
  $(B)/base/game/bg_slidemove.o \
  $(B)/base/game/bg_lib.o \
  $(B)/base/game/bg_alloc.o \
  $(B)/base/game/bg_voice.o \
  $(B)/base/game/g_active.o \
  $(B)/base/game/g_client.o \
  $(B)/base/game/g_cmds.o \
  $(B)/base/game/g_combat.o \
  $(B)/base/game/g_physics.o \
  $(B)/base/game/g_buildable.o \
  $(B)/base/game/g_misc.o \
  $(B)/base/game/g_missile.o \
  $(B)/base/game/g_mover.o \
  $(B)/base/game/g_session.o \
  $(B)/base/game/g_spawn.o \
  $(B)/base/game/g_svcmds.o \
  $(B)/base/game/g_target.o \
  $(B)/base/game/g_team.o \
  $(B)/base/game/g_trigger.o \
  $(B)/base/game/g_utils.o \
  $(B)/base/game/g_maprotation.o \
  $(B)/base/game/g_weapon.o \
  $(B)/base/game/g_admin.o \
  $(B)/base/game/g_bot.o \
  $(B)/base/game/g_namelog.o \
  \
  $(B)/base/qcommon/q_math.o \
  $(B)/base/qcommon/q_shared.o

GOBJ = $(GOBJ_) $(B)/base/game/g_syscalls.o
GVMOBJ = $(GOBJ_:%.o=%.asm)

$(B)/base/game$(SHLIBNAME): $(GOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(GOBJ)

$(B)/base/vm/game.qvm: $(GVMOBJ) $(GDIR)/g_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(GVMOBJ) $(GDIR)/g_syscalls.asm



#############################################################################
## TREMULOUS UI
#############################################################################

UIOBJ_ = \
  $(B)/base/ui/ui_main.o \
  $(B)/base/ui/ui_atoms.o \
  $(B)/base/ui/ui_shared.o \
  $(B)/base/ui/ui_gameinfo.o \
  \
  $(B)/base/ui/bg_misc.o \
  $(B)/base/ui/bg_lib.o \
  $(B)/base/qcommon/q_math.o \
  $(B)/base/qcommon/q_shared.o

UIOBJ = $(UIOBJ_) $(B)/base/ui/ui_syscalls.o
UIVMOBJ = $(UIOBJ_:%.o=%.asm)

$(B)/base/ui$(SHLIBNAME): $(UIOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(UIOBJ)

$(B)/base/vm/ui.qvm: $(UIVMOBJ) $(UIDIR)/ui_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(UIVMOBJ) $(UIDIR)/ui_syscalls.asm



#############################################################################
## CLIENT/SERVER RULES
#############################################################################

$(B)/client/%.o: $(ASMDIR)/%.s
	$(DO_AS)

$(B)/client/%.o: $(CDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(SDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(CMDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(JPDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(SPEEXDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(ZDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(RDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(SDLDIR)/%.c
	$(DO_CC)

$(B)/clientsmp/%.o: $(SDLDIR)/%.c
	$(DO_SMP_CC)

$(B)/client/%.o: $(SYSDIR)/%.c
	$(DO_CC)

$(B)/client/%.o: $(SYSDIR)/%.m
	$(DO_CC)

$(B)/client/%.o: $(SYSDIR)/%.rc
	$(DO_WINDRES)


$(B)/ded/%.o: $(ASMDIR)/%.s
	$(DO_AS)

$(B)/ded/%.o: $(SDIR)/%.c
	$(DO_DED_CC)

$(B)/ded/%.o: $(CMDIR)/%.c
	$(DO_DED_CC)

$(B)/ded/%.o: $(ZDIR)/%.c
	$(DO_DED_CC)

$(B)/ded/%.o: $(SYSDIR)/%.c
	$(DO_DED_CC)

$(B)/ded/%.o: $(SYSDIR)/%.m
	$(DO_DED_CC)

$(B)/ded/%.o: $(SYSDIR)/%.rc
	$(DO_WINDRES)

$(B)/ded/%.o: $(NDIR)/%.c
	$(DO_DED_CC)

# Extra dependencies to ensure the SVN version is incorporated
ifeq ($(USE_SVN),1)
  $(B)/client/cl_console.o : .svn/entries
  $(B)/client/common.o : .svn/entries
  $(B)/ded/common.o : .svn/entries
endif


#############################################################################
## GAME MODULE RULES
#############################################################################

$(B)/base/cgame/bg_%.o: $(GDIR)/bg_%.c
	$(DO_CGAME_CC)

$(B)/base/cgame/%.o: $(CGDIR)/%.c
	$(DO_CGAME_CC)

$(B)/base/cgame/bg_%.asm: $(GDIR)/bg_%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)

$(B)/base/cgame/%.asm: $(CGDIR)/%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)


$(B)/base/game/%.o: $(GDIR)/%.c
	$(DO_GAME_CC)

$(B)/base/game/%.asm: $(GDIR)/%.c $(Q3LCC)
	$(DO_GAME_Q3LCC)


$(B)/base/ui/bg_%.o: $(GDIR)/bg_%.c
	$(DO_UI_CC)

$(B)/base/ui/%.o: $(UIDIR)/%.c
	$(DO_UI_CC)

$(B)/base/ui/bg_%.asm: $(GDIR)/bg_%.c $(Q3LCC)
	$(DO_UI_Q3LCC)

$(B)/base/ui/%.asm: $(UIDIR)/%.c $(Q3LCC)
	$(DO_UI_Q3LCC)


$(B)/base/qcommon/%.o: $(CMDIR)/%.c
	$(DO_SHLIB_CC)

$(B)/base/qcommon/%.asm: $(CMDIR)/%.c $(Q3LCC)
	$(DO_Q3LCC)

#############################################################################
# MISC
#############################################################################

OBJ = $(Q3OBJ) $(Q3POBJ) $(Q3POBJ_SMP) $(Q3DOBJ) \
  $(GOBJ) $(CGOBJ) $(UIOBJ) \
  $(GVMOBJ) $(CGVMOBJ) $(UIVMOBJ)
TOOLSOBJ = $(LBURGOBJ) $(Q3CPPOBJ) $(Q3RCCOBJ) $(Q3LCCOBJ) $(Q3ASMOBJ)


clean: clean-debug clean-release
	@$(MAKE) -C $(MASTERDIR) clean

clean-debug:
	@$(MAKE) clean2 B=$(BD)

clean-release:
	@$(MAKE) clean2 B=$(BR)

clean2:
	@echo "CLEAN $(B)"
	@rm -f $(OBJ)
	@rm -f $(OBJ_D_FILES)
	@rm -f $(TARGETS)

toolsclean: toolsclean-debug toolsclean-release

toolsclean-debug:
	@$(MAKE) toolsclean2 B=$(BD)

toolsclean-release:
	@$(MAKE) toolsclean2 B=$(BR)

toolsclean2:
	@echo "TOOLS_CLEAN $(B)"
	@rm -f $(TOOLSOBJ)
	@rm -f $(TOOLSOBJ_D_FILES)
	@rm -f $(LBURG) $(DAGCHECK_C) $(Q3RCC) $(Q3CPP) $(Q3LCC) $(Q3ASM)

distclean: clean toolsclean
	@rm -rf $(BUILD_DIR)

dist:
	rm -rf tremulous-$(SVN_VERSION)
	svn export . tremulous-$(SVN_VERSION)
	tar --owner=root --group=root --force-local -cjf tremulous-$(SVN_VERSION).tar.bz2 tremulous-$(SVN_VERSION)
	rm -rf tremulous-$(SVN_VERSION)

#############################################################################
# DEPENDENCIES
#############################################################################

ifneq ($(B),)
  OBJ_D_FILES=$(filter %.d,$(OBJ:%.o=%.d))
  TOOLSOBJ_D_FILES=$(filter %.d,$(TOOLSOBJ:%.o=%.d))
  -include $(OBJ_D_FILES) $(TOOLSOBJ_D_FILES)
endif

.PHONY: all clean clean2 clean-debug clean-release copyfiles \
	debug default dist distclean makedirs \
	release targets \
	toolsclean toolsclean2 toolsclean-debug toolsclean-release \
	$(OBJ_D_FILES) $(TOOLSOBJ_D_FILES)
