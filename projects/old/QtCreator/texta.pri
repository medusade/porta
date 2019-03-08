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
#   File: texta.pri
#
# Author: $author$
#   Date: 5/21/2017
########################################################################

########################################################################
# texta
TEXTA_PKG = $${FRAMEWORK_PKG}/../texta
TEXTA_PRJ = $${FRAMEWORK_PRO_DIR}$${TEXTA_PKG}
TEXTA_SRC = $${TEXTA_PRJ}/src
TEXTA_BLD = ../$${TEXTA_PKG}/build/$${FRAMEWORK_OS}/QtCreator/$${FRAMEWORK_CONFIG}
TEXTA_LIB = $${TEXTA_BLD}/lib

texta_INCLUDEPATH += \
$${TEXTA_SRC} \

texta_DEFINES += \

texta_LIBS += \
-L$${TEXTA_LIB}/libtexta \
-ltexta \

