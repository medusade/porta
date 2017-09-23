///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: Which.hpp
///
/// Author: $author$
///   Date: 9/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_HPP
#define _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variable {

///////////////////////////////////////////////////////////////////////
///  Enum: Which
///////////////////////////////////////////////////////////////////////
typedef int Which;
enum {
    None = 0,

    GATEWAY_INTERFACE,
    SERVER_NAME,
    SERVER_PORT,
    SERVER_PROTOCOL,
    SERVER_SOFTWARE,
    AUTH_TYPE,
    CONTENT_FILE,
    CONTENT_LENGTH,
    CONTENT_TYPE,
    OUTPUT_FILE,
    PATH_INFO,
    PATH_TRANSLATED,
    QUERY_STRING,
    REMOTE_ADDR,
    REMOTE_USER,
    REQUEST_LINE,
    REQUEST_METHOD,
    REMOTE_HOST,
    REMOTE_IDENT,
    HTTP_ACCEPT,
    HTTP_USER_AGENT,
    SCRIPT_NAME,

    Next,
    First = (None + 1),
    Last = (Next - 1),
    Count = ((Last - First) + 1)
};

} // namespace variable
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace xos 

#endif // _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_HPP 
