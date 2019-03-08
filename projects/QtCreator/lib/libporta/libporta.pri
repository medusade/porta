########################################################################
# Copyright (c) 1988-2019 $organization$
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
#   File: libporta.pri
#
# Author: $author$
#   Date: 1/2/2019
#
# QtCreator .pri file for porta library libporta
########################################################################

########################################################################
# libporta

# libporta TARGET
#
libporta_TARGET = porta
libporta_TEMPLATE = lib
libporta_CONFIG += staticlib

# libporta INCLUDEPATH
#
libporta_INCLUDEPATH += \
$${porta_INCLUDEPATH} \

# libporta DEFINES
#
libporta_DEFINES += \
$${porta_DEFINES} \

########################################################################
# libporta OBJECTIVE_HEADERS
#
#libporta_OBJECTIVE_HEADERS += \
#$${PORTA_SRC}/porta/base/Base.hh \

# libporta OBJECTIVE_SOURCES
#
#libporta_OBJECTIVE_SOURCES += \
#$${PORTA_SRC}/porta/base/Base.mm \

########################################################################
# libporta HEADERS
#
libporta_HEADERS += \
$${PORTA_SRC}/porta/base/Base.hpp \
$${PORTA_SRC}/porta/lib/Version.hpp \
$${PORTA_SRC}/porta/lib/porta/Version.hpp \

# libporta SOURCES
#
libporta_SOURCES += \
$${PORTA_SRC}/porta/base/Base.cpp \
$${PORTA_SRC}/porta/lib/porta/Version.cpp \

########################################################################



