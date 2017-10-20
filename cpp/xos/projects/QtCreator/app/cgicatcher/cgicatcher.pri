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
#   File: cgicatcher.pri
#
# Author: $author$
#   Date: 10/16/2017
#
# QtCreator .pri file for porta executable cgicatcher
########################################################################

cgicatcher_TARGET = porta-cgicatcher

########################################################################
cgicatcher_INCLUDEPATH += \
$${porta_INCLUDEPATH} \

cgicatcher_DEFINES += \
$${porta_DEFINES} \
XOS_CONSOLE_CGI_CATCHER_THE_MAIN \

########################################################################
# porta
cgicatcher_HEADERS += \
$${PORTA_SRC}/xos/console/cgi/catcher/Main.hpp \
$${PORTA_SRC}/xos/console/cgi/Main.hpp \
$${PORTA_SRC}/xos/console/cgi/MainOpt.hpp \

cgicatcher_SOURCES += \
$${PORTA_SRC}/xos/console/cgi/catcher/Main.cpp \
$${PORTA_SRC}/xos/console/cgi/MainOpt.cpp \
$${FILA_SRC}/xos/console/mt/Main_main.cpp \

########################################################################
cgicatcher_LIBS += \
$${porta_LIBS} \
