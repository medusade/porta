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
#   File: cgi.pri
#
# Author: $author$
#   Date: 5/20/2017
########################################################################

cgi_TARGET = porta-cgi

########################################################################
cgi_INCLUDEPATH += \
$${porta_INCLUDEPATH} \
$${crono_INCLUDEPATH} \
$${patrona_INCLUDEPATH} \
$${nadir_INCLUDEPATH} \

cgi_DEFINES += \
$${framework_DEFINES} \
$${porta_DEFINES} \

########################################################################
# nadir
cgi_HEADERS += \
$${NADIR_SRC}/nadir/io/logger.hpp \
$${NADIR_SRC}/nadir/io/logger_stdio.hpp \
$${NADIR_SRC}/nadir/io/logger_message.hpp \
$${NADIR_SRC}/nadir/io/logger_location.hpp \
$${NADIR_SRC}/nadir/io/logger_level.hpp \

cgi_SOURCES += \
$${NADIR_SRC}/nadir/io/logger.cpp \
$${NADIR_SRC}/nadir/io/logger_stdio.cpp \
$${NADIR_SRC}/nadir/io/logger_message.cpp \
$${NADIR_SRC}/nadir/io/logger_location.cpp \
$${NADIR_SRC}/nadir/io/logger_level.cpp \

########################################################################
# texta
cgi_HEADERS += \
$${PORTA_SRC}/porta/app/console/cgi/Main.hpp \
$${PORTA_SRC}/porta/console/Main_main.hpp \

cgi_SOURCES += \
$${PORTA_SRC}/porta/app/console/cgi/Main.cpp \
$${PORTA_SRC}/porta/console/Main_main.cpp \

########################################################################
cgi_LIBS += \
$${nadir_LIBS} \
