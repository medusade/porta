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
$${texta_INCLUDEPATH} \
$${porta_INCLUDEPATH} \
$${crono_INCLUDEPATH} \
$${patrona_INCLUDEPATH} \
$${nadir_INCLUDEPATH} \

cgi_DEFINES += \
$${framework_DEFINES} \
$${porta_DEFINES} \
USE_TEXTA_NADIR_BASE \

########################################################################
# nadir
cgi_HEADERS += \
$${NADIR_SRC}/nadir/io/logger.hpp \
$${NADIR_SRC}/nadir/io/logger_stdio.hpp \
$${NADIR_SRC}/nadir/io/logger_message.hpp \
$${NADIR_SRC}/nadir/io/logger_location.hpp \
$${NADIR_SRC}/nadir/io/logger_level.hpp \
$${NADIR_SRC}/nadir/base/avl/tree.hpp \
$${NADIR_SRC}/nadir/base/binary/tree.hpp \
$${NADIR_SRC}/nadir/base/tree.hpp \
$${NADIR_SRC}/nadir/base/avl/branch.hpp \
$${NADIR_SRC}/nadir/base/binary/branch.hpp \
$${NADIR_SRC}/nadir/base/branch.hpp \
$${NADIR_SRC}/nadir/base/leaf.hpp \
$${NADIR_SRC}/nadir/console/main_main.hpp \

cgi_SOURCES += \
$${NADIR_SRC}/nadir/io/logger.cpp \
$${NADIR_SRC}/nadir/io/logger_stdio.cpp \
$${NADIR_SRC}/nadir/io/logger_message.cpp \
$${NADIR_SRC}/nadir/io/logger_location.cpp \
$${NADIR_SRC}/nadir/io/logger_level.cpp \
$${NADIR_SRC}/nadir/base/avl/tree.cpp \
$${NADIR_SRC}/nadir/base/avl/branch.cpp \
$${NADIR_SRC}/nadir/base/leaf.cpp \
$${NADIR_SRC}/nadir/console/main_main.cpp \

########################################################################
# texta
cgi_HEADERS += \
$${TEXTA_SRC}/texta/t/function.hpp \
$${TEXTA_SRC}/texta/t/t.hpp \
$${TEXTA_SRC}/texta/io/writer.hpp \
$${TEXTA_SRC}/texta/io/reader.hpp \
$${TEXTA_SRC}/texta/base/base.hpp \
$${TEXTA_SRC}/texta/nadir/base/base.hpp \
$${TEXTA_SRC}/texta/xos/base/base.hpp \

cgi_SOURCES += \
$${TEXTA_SRC}/texta/t/function.cpp \
$${TEXTA_SRC}/texta/t/t.cpp \
$${TEXTA_SRC}/texta/io/writer.hpp \
$${TEXTA_SRC}/texta/nadir/base/base.cpp \

########################################################################
cgi_LIBS += \
$${nadir_LIBS} \
