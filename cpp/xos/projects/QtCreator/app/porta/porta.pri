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
#   File: porta.pri
#
# Author: $author$
#   Date: 9/19/2017
#
# QtCreator .pri file for porta executable porta
########################################################################

porta_exe_TARGET = porta

########################################################################
porta_exe_INCLUDEPATH += \
$${porta_INCLUDEPATH} \

porta_exe_DEFINES += \
$${porta_DEFINES} \
XOS_CONSOLE_CGI_THE_MAIN \

########################################################################
# rostra
porta_exe_HEADERS += \

porta_exe_SOURCES += \
$${ROSTRA_SRC}/xos/platform/platform.cpp \

########################################################################
# nadir
porta_exe_HEADERS += \
$${NADIR_SRC}/xos/io/microsoft/windows/crt/file/Attached.hpp \
$${NADIR_SRC}/xos/io/crt/file/Reader.hpp \
$${NADIR_SRC}/xos/io/crt/file/Attached.hpp \
$${NADIR_SRC}/xos/io/crt/file/Mode.hpp \
$${NADIR_SRC}/xos/io/Reader.hpp \
$${NADIR_SRC}/xos/base/CharsWrapped.hpp \
$${NADIR_SRC}/xos/base/Array.hpp \

porta_exe_SOURCES += \
$${NADIR_SRC}/xos/io/microsoft/windows/crt/file/Attached.cpp \
$${NADIR_SRC}/xos/io/crt/file/Mode.cpp \
$${NADIR_SRC}/xos/base/CharsWrapped.cpp \
$${NADIR_SRC}/xos/base/Array.cpp \

#$${NADIR_SRC}/xos/io/crt/file/Reader.cpp \

########################################################################
# patrona
porta_exe_HEADERS += \
$${PATRONA_SRC}/xos/base/Wrapped.hpp \

porta_exe_SOURCES += \
$${PATRONA_SRC}/xos/base/Wrapped.cpp \

########################################################################
# fila
porta_exe_HEADERS += \
$${FILA_SRC}/xos/console/mt/Main_main.hpp \

porta_exe_SOURCES += \
$${FILA_SRC}/xos/console/mt/Main_main.cpp \

########################################################################
# stara
porta_exe_HEADERS += \
$${STARA_SRC}/xos/protocol/http/url/encoded/form/Fields.hpp \
$${STARA_SRC}/xos/protocol/http/url/encoded/form/ContentType.hpp \
$${STARA_SRC}/xos/protocol/http/url/encoded/Reader.hpp \
$${STARA_SRC}/xos/protocol/http/form/Fields.hpp \
$${STARA_SRC}/xos/protocol/http/form/FieldsSignals.hpp \
$${STARA_SRC}/xos/protocol/http/form/Field.hpp \
$${STARA_SRC}/xos/protocol/http/content/type/header/Field.hpp \
$${STARA_SRC}/xos/protocol/http/header/Field.hpp \
$${STARA_SRC}/xos/protocol/http/message/header/field/Name.hpp \
$${STARA_SRC}/xos/protocol/http/message/header/field/Which.hpp \

porta_exe_SOURCES += \
$${STARA_SRC}/xos/protocol/http/url/encoded/form/Fields.cpp \
$${STARA_SRC}/xos/protocol/http/url/encoded/form/ContentType.cpp \
$${STARA_SRC}/xos/protocol/http/form/FieldsSignals.cpp \
$${STARA_SRC}/xos/protocol/http/content/type/header/Field.cpp \

#$${STARA_SRC}/xos/protocol/http/url/encoded/Reader.cpp \
#$${STARA_SRC}/xos/protocol/http/message/header/field/Name.cpp \
#$${STARA_SRC}/xos/protocol/http/message/header/field/Which.cpp \

########################################################################
# porta
porta_exe_HEADERS += \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variables/Reader.hpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variables/Values.hpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variable/Value.hpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variable/Name.hpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variable/Which.hpp \
$${PORTA_SRC}/xos/console/cgi/Main.hpp \
$${PORTA_SRC}/xos/console/cgi/MainOpt.hpp \

porta_exe_SOURCES += \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variables/Reader.cpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variables/Values.cpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variable/Value.cpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variable/Name.cpp \
$${PORTA_SRC}/xos/protocol/http/cgi/environment/variable/Which.cpp \
$${PORTA_SRC}/xos/console/cgi/Main.cpp \
$${PORTA_SRC}/xos/console/cgi/MainOpt.cpp \

########################################################################
porta_exe_LIBS += \
$${porta_LIBS} \



