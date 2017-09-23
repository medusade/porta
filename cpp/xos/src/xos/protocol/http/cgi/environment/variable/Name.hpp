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
///   File: Name.hpp
///
/// Author: $author$
///   Date: 9/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HPP
#define _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HPP

#include "xos/protocol/http/cgi/environment/variable/Which.hpp"
#include "xos/base/CharsWrapped.hpp"

#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_GATEWAY_INTERFACE "GATEWAY_INTERFACE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_NAME "SERVER_NAME"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PORT "SERVER_PORT"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PROTOCOL "SERVER_PROTOCOL"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_SOFTWARE "SERVER_SOFTWARE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_AUTH_TYPE "AUTH_TYPE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_FILE "CONTENT_FILE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_LENGTH "CONTENT_LENGTH"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_TYPE "CONTENT_TYPE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_OUTPUT_FILE "OUTPUT_FILE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_INFO "PATH_INFO"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_TRANSLATED "PATH_TRANSLATED"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_QUERY_STRING "QUERY_STRING"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_ADDR "REMOTE_ADDR"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_USER "REMOTE_USER"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_LINE "REQUEST_LINE"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_METHOD "REQUEST_METHOD"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_HOST "REMOTE_HOST"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_IDENT "REMOTE_IDENT"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_ACCEPT "HTTP_ACCEPT"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_USER_AGENT "HTTP_USER_AGENT"
#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SCRIPT_NAME "SCRIPT_NAME"

#define XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAMES \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_GATEWAY_INTERFACE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_NAME, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PORT, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PROTOCOL, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_SOFTWARE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_AUTH_TYPE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_FILE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_LENGTH, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_TYPE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_OUTPUT_FILE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_INFO, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_TRANSLATED, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_QUERY_STRING, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_ADDR, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_USER, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_LINE, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_METHOD, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_HOST, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_IDENT, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_ACCEPT, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_USER_AGENT, \
    XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SCRIPT_NAME,

namespace xos {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variable {

typedef ImplementBase NameTImplements;
typedef CharsWrapped NameTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: NameT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = NameTImplements, class TExtends = NameTExtends>
class _EXPORT_CLASS NameT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::chars_t chars_t;
    typedef typename Extends::char_t char_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NameT(variable::Which which): Extends(OfWhich(which)), m_which(which) {
    }
    NameT(const NameT& copy): Extends(copy), m_which(copy.m_wich) {
    }
    virtual ~NameT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual NameT& operator = (const char_t* of) {
        m_which = WhichOf(this->SetWrapped(of));
        return *this;
    }
    virtual NameT& operator = (variable::Which which) {
        this->SetWrapped(OfWhich(m_which = which));
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* Of(size_t& length) const {
        length = Length();
        return Of();
    }
    virtual const char_t* Of() const {
        return this->Wrapped();
    }
    virtual variable::Which Which() const {
        return m_which;
    }
    virtual size_t Length() const {
        size_t length = 0;
        const char_t* chars = 0;
        if ((chars = this->wrapped())) {
            length = chars_t::count(chars);
        }
        return length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const char_t** OfWhich() {
        static const char_t* name[Count + 1] = {
            XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAMES
            0
        };
        return name;
    }
    static const char_t* OfWhich(variable::Which which) {
        const char_t** name = OfWhich();
        if ((name) && (which >= First) && (which <= Last)) {
            return name[which - First];
        }
        return 0;
    }
    static variable::Which WhichOf(const char_t* of) {
        if ((of)) {
            const char_t* to = 0;
            for (variable::Which which = First; which <= Last; ++which) {
                if ((to = OfWhich(which))) {
                    if (!(chars_t::compare(of, to)))
                        return which;
                }
            }
        }
        return None;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    variable::Which m_which;
};
typedef NameT<> Name;

} // namespace variable
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace xos 

#endif // _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HPP 
