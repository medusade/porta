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
#   File: porta.pri
#
# Author: $author$
#   Date: 1/2/2019
#
# QtCreator .pri file for porta executable porta
########################################################################

########################################################################
# porta

# porta_exe TARGET
#
porta_exe_TARGET = porta

# porta_exe INCLUDEPATH
#
porta_exe_INCLUDEPATH += \
$${porta_INCLUDEPATH} \

# porta_exe DEFINES
#
porta_exe_DEFINES += \
$${porta_DEFINES} \

########################################################################
# porta_exe OBJECTIVE_HEADERS
#
#porta_exe_OBJECTIVE_HEADERS += \
#$${PORTA_SRC}/porta/base/Base.hh \

# porta_exe OBJECTIVE_SOURCES
#
#porta_exe_OBJECTIVE_SOURCES += \
#$${PORTA_SRC}/porta/base/Base.mm \

########################################################################
# porta_exe HEADERS
#
porta_exe_HEADERS += \
$${PORTA_SRC}/porta/console/lib/porta/version/Main.hpp \
$${PORTA_SRC}/porta/app/console/porta/Main.hpp \

# porta_exe SOURCES
#
porta_exe_SOURCES += \
$${PORTA_SRC}/porta/console/lib/porta/version/Main.hpp \
$${PORTA_SRC}/porta/app/console/porta/Main.cpp \

########################################################################
# porta_exe FRAMEWORKS
#
porta_exe_FRAMEWORKS += \
$${porta_FRAMEWORKS} \

# porta_exe LIBS
#
porta_exe_LIBS += \
$${porta_LIBS} \


