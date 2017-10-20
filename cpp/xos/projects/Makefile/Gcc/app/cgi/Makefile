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
# generic Gcc Makefile for porta Executable cgi
########################################################################


#
# target
#
cgi_EXETARGET = porta-cgi

########################################################################

#
# user c++ flags
#
cgi_USRCXXFLAGS += \
${porta_USRCXXFLAGS} \

#
# user defines
#
cgi_USRDEFINES += \
${porta_USRDEFINES} \
-DXOS_CONSOLE_CGI_THE_MAIN \

#
# user includes
#
cgi_USRINCLUDES += \
${porta_USRINCLUDES} \

#
# user libdirs
#
cgi_USRLIBDIRS += \
${porta_USRLIBDIRS} \

########################################################################

#
# Executable .c sources
#
#cgi_EXE_C_SOURCES += \
#${PORTA_SRC}/porta/base/Base.c \

#
# Executable .cc sources
#
#cgi_EXE_CC_SOURCES += \
#${PORTA_SRC}/porta/base/Base.cc \

#
# Executable .cxx sources
#
#cgi_EXE_CXX_SOURCES += \
#${PORTA_SRC}/porta/base/Base.cxx \

#
# Executable .cpp sources
#
cgi_EXE_CPP_SOURCES += \
${PORTA_SRC}/xos/console/cgi/Main.cpp \
${PORTA_SRC}/xos/console/cgi/MainOpt.cpp \
${FILA_SRC}/xos/console/mt/Main_main.cpp \

#
# Executable .m sources
#
#cgi_EXE_M_SOURCES += \
#${PORTA_SRC}/porta/base/Base.m \

#
# Executable .mm sources
#
#cgi_EXE_MM_SOURCES += \
#${PORTA_SRC}/porta/base/Base.mm \


########################################################################

#
# Executable libraries
#
cgi_LIBS += \
${porta_LIBS}



