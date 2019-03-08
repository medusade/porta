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
#   File: cgi.pro
#
# Author: $author$
#   Date: 1/2/2019
#
# QtCreator .pro file for porta executable cgi
########################################################################
include(../../../../../build/QtCreator/porta.pri)
include(../../../../QtCreator/porta.pri)
include(../../porta.pri)
include(../../../../QtCreator/app/cgi/cgi.pri)

TARGET = $${cgi_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${cgi_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${cgi_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${cgi_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${cgi_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${cgi_HEADERS} \
$${OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${cgi_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${cgi_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${cgi_LIBS} \
$${FRAMEWORKS} \


