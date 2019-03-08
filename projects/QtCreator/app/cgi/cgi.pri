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
#   File: cgi.pri
#
# Author: $author$
#   Date: 1/2/2019
#
# QtCreator .pri file for porta executable cgi
########################################################################

########################################################################
# cgi

# cgi TARGET
#
cgi_TARGET = cgi

# cgi INCLUDEPATH
#
cgi_INCLUDEPATH += \
$${porta_INCLUDEPATH} \

# cgi DEFINES
#
cgi_DEFINES += \
$${porta_DEFINES} \

########################################################################
# cgi OBJECTIVE_HEADERS
#
#cgi_OBJECTIVE_HEADERS += \
#$${PORTA_SRC}/porta/base/Base.hh \

# cgi OBJECTIVE_SOURCES
#
#cgi_OBJECTIVE_SOURCES += \
#$${PORTA_SRC}/porta/base/Base.mm \

########################################################################
# cgi HEADERS
#
cgi_HEADERS += \
$${PATRONA_SRC}/patrona/console/Argv.hpp \
\
$${PORTA_SRC}/porta/app/console/cgi/Main.hpp \

# cgi SOURCES
#
cgi_SOURCES += \
$${PATRONA_SRC}/patrona/console/Argv.cpp \
\
$${PORTA_SRC}/porta/app/console/cgi/Main.cpp \

########################################################################
# cgi FRAMEWORKS
#
cgi_FRAMEWORKS += \
$${porta_FRAMEWORKS} \

# cgi LIBS
#
cgi_LIBS += \
$${porta_LIBS} \


