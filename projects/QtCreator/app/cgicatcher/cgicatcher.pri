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
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Attached.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Mode.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/os/crt/file/Attached.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/os/Os.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/base/Chars.hpp \
$${PATRONA_SRC}/patrona/cpp/xos/base/Base.hpp \

cgicatcher_SOURCES += \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Stream.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Writer.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Reader.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Attached.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/crt/file/Mode.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/io/os/Os.cpp \
$${PATRONA_SRC}/patrona/cpp/xos/base/Chars.cpp \

########################################################################
cgicatcher_HEADERS += \
$${PORTA_SRC}/porta/io/os/crt/file/Attached.hpp \
$${PORTA_SRC}/porta/io/crt/file/Stream.hpp \
$${PORTA_SRC}/porta/io/crt/file/Writer.hpp \
$${PORTA_SRC}/porta/io/crt/file/Reader.hpp \
$${PORTA_SRC}/porta/io/crt/file/Mode.hpp \

########################################################################
cgicatcher_HEADERS += \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variables/Reader.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variables/Values.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variables/Exception.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Value.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Name.hpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variable/Which.hpp \
$${PORTA_SRC}/porta/protocol/http/message/header/field/Line.hpp \
$${PORTA_SRC}/porta/protocol/http/message/header/field/Name.hpp \
$${PORTA_SRC}/porta/protocol/http/message/header/field/Which.hpp \
$${PORTA_SRC}/porta/protocol/http/content/type/Name.hpp \
$${PORTA_SRC}/porta/protocol/http/content/type/Which.hpp \
$${PORTA_SRC}/porta/protocol/http/url/encoded/Reader.hpp \
$${PORTA_SRC}/porta/protocol/http/form/Reader.hpp \
$${PORTA_SRC}/porta/protocol/http/form/Fields.hpp \
$${PORTA_SRC}/porta/protocol/http/form/Field.hpp \

cgicatcher_SOURCES += \
$${PORTA_SRC}/porta/protocol/http/form/Reader.cpp \
$${PORTA_SRC}/porta/protocol/http/form/Fields.cpp \
$${PORTA_SRC}/porta/protocol/http/form/Field.cpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variables/Values.cpp \
$${PORTA_SRC}/porta/protocol/http/cgi/environment/variables/Exception.cpp \
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


