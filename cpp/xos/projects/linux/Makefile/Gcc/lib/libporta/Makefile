########################################################################
# Copyright (c) 1988-2017 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: Makefile
#
# Author: $author$
#   Date: 10/13/2017
#
# Linux Gcc Makefile for porta Library libporta
########################################################################

OS = linux
PKG = ../../../../../..

BMK = build/Makefile/Gcc
MAK = projects/Makefile/Gcc
PRJ = projects/${OS}/Makefile/Gcc
SRC = src

include $(PKG)/$(BMK)/Makedefines
include $(PKG)/$(MAK)/Makedefines
include $(PKG)/$(MAK)/Makefile
include $(PKG)/$(BMK)/Makefile
include $(PKG)/$(MAK)/lib/libporta/Makefile

#
# target
#
LIBTARGET = ${libporta_LIBTARGET}

########################################################################

#
# user defines
#
USRDEFINES += \
${libporta_USRDEFINES}

#
# user includes
#
USRINCLUDES += \
${libporta_USRINCLUDES}

#
# user libdirs
#
USRLIBDIRS += \
${libporta_USRLIBDIRS}

#
# user c++ flags
#
USRCXXFLAGS += \
${libporta_USRCXXFLAGS}

#
# user c flags
#
USRCFLAGS += \
${libporta_USRCFLAGS}

#
# user ld flags
#
USRLDFLAGS += \
${libporta_USRLDFLAGS}

########################################################################

#
# Library C sources
#
LIB_C_SOURCES += \
${libporta_LIB_C_SOURCES}

#
# Library C++ .cc sources
#
LIB_CC_SOURCES += \
${libporta_LIB_CC_SOURCES}

#
# Library C++ .cxx sources
#
LIB_CXX_SOURCES += \
${libporta_LIB_CXX_SOURCES}

#
# Library C++ .cpp sources
#
LIB_CPP_SOURCES += \
${libporta_LIB_CPP_SOURCES}

#
# Library Objective C .m sources
#
LIB_M_SOURCES += \
${libporta_LIB_M_SOURCES}

#
# Library Objective C++ .mm sources
#
LIB_MM_SOURCES += \
${libporta_LIB_MM_SOURCES}

########################################################################

#
# Library depends
#
#LIBDEP += \
#$(PKG)/$(BLD)/libsomelib \
#
LIBDEP += \

#
# Library depend dirs
#
#LIBDEP_DIRS += \
#../libsomelib
#
LIBDEP_DIRS += \

include $(PKG)/$(MAK)/Makerules

#
# Library depend rules
#
#$(PKG)/$(BLD)/libsomelib.a:
#	@(echo Building libsomelib.a ...;\
#	  pushd ../libsomelib;\
#	  ((make) || (exit 1));\
#	  popd)
#


