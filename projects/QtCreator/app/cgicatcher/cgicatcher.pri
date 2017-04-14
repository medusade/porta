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
#   Date: 4/4/2017
########################################################################

cgicatcher_TARGET = porta-cgicatcher

########################################################################
cgicatcher_INCLUDEPATH += \
$${porta_INCLUDEPATH} \
$${crono_INCLUDEPATH} \
$${patrona_INCLUDEPATH} \
$${nadir_INCLUDEPATH} \

cgicatcher_DEFINES += \
$${framework_DEFINES} \
$${porta_DEFINES} \

########################################################################
cgicatcher_HEADERS += \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Stream.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Writer.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Reader.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Mode.hpp \

cgicatcher_SOURCES += \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Stream.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Writer.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Reader.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Mode.cpp \

########################################################################
cgicatcher_HEADERS += \
$${PORTA_SRC}/porta/io/crt/file/Stream.hpp \
$${PORTA_SRC}/porta/io/crt/file/Writer.hpp \
$${PORTA_SRC}/porta/io/crt/file/Reader.hpp \
$${PORTA_SRC}/porta/io/crt/file/Mode.hpp \

########################################################################
cgicatcher_HEADERS += \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Value.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Name.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Which.hpp \

cgicatcher_SOURCES += \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Value.cpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Name.cpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Which.cpp \

########################################################################
cgicatcher_HEADERS += \
$${PORTA_SRC}/porta/app/console/cgi/catcher/Main.hpp \
$${PORTA_SRC}/porta/app/console/cgi/Main.hpp \
$${PORTA_SRC}/porta/app/console/cgi/MainOpt.hpp \
$${PORTA_SRC}/porta/console/getopt/Main.hpp \
$${PORTA_SRC}/porta/console/getopt/MainOpt.hpp \
$${PORTA_SRC}/porta/console/Main.hpp \
$${PORTA_SRC}/porta/console/Main_main.hpp \
$${PORTA_SRC}/porta/base/Base.hpp \

cgicatcher_SOURCES += \
$${PORTA_SRC}/porta/app/console/cgi/catcher/Main.cpp \
$${PORTA_SRC}/porta/app/console/cgi/MainOpt.cpp \
$${PORTA_SRC}/porta/console/Main_main.cpp \
$${PORTA_SRC}/porta/base/Base.cpp \

########################################################################
cgicatcher_LIBS += \
$${nadir_LIBS} \


