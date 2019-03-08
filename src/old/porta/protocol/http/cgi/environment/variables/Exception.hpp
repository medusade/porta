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
///   File: Exception.hpp
///
/// Author: $author$
///   Date: 4/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_EXCEPTION_HPP
#define _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_EXCEPTION_HPP

#include "porta/protocol/http/cgi/environment/variable/Which.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variables {

typedef int ExceptionTStatus;
typedef ImplementBase ExceptionTImplements;
typedef Base ExceptionTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ExceptionT
///////////////////////////////////////////////////////////////////////
template
<typename TStatus = ExceptionTStatus,
 class TImplements = ExceptionTImplements, class TExtends = ExceptionTExtends>

class _EXPORT_CLASS ExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TStatus status_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    enum {
        Success = 0,
        Failed = 1,
        InvalidWhich = 2
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ExceptionT(status_t status): m_status(status) {
    }
    ExceptionT(const ExceptionT& copy): m_status(copy.m_status) {
    }
    virtual ~ExceptionT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual status_t SetStatus(status_t to) {
        m_status = to;
        return m_status;
    }
    virtual status_t Status() const {
        return m_status;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    status_t m_status;
};
typedef ExceptionT<> Exception;

} // namespace variables 
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_EXCEPTION_HPP 
