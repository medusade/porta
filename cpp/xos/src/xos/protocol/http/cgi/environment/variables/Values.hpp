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
///   File: Values.hpp
///
/// Author: $author$
///   Date: 9/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_VALUES_HPP
#define _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_VALUES_HPP

#include "xos/protocol/http/cgi/environment/variable/Value.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variables {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef variable::Value Value;
typedef variable::Name Name;
typedef variable::Which Which;
enum {
    First = variable::First,
    Last = variable::Last,
    Count = variable::Count
};

typedef ImplementBase ValuesTImplements;
typedef ArrayT<Value, ValuesTImplements, Base, Count> ValuesTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ValuesT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ValuesTImplements, class TExtends = ValuesTExtends>

class _EXPORT_CLASS ValuesT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ValuesT(const ValuesT& copy): Extends(copy) {
        Init();
    }
    ValuesT() {
        Init();
    }
    virtual ~ValuesT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ValuesT& GetAll() {
        for (Which which = First; which <= Last; ++which) {
            this->operator[](which).Get(which);
        }
        return *this;
    }
    virtual ValuesT& ClearAll() {
        for (Which which = First; which <= Last; ++which) {
            this->operator[](which).Clear();
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Value& operator[](const char* named) const {
        Which which = Name::WhichOf(named);
        if ((which >= First) && (which <= Last)) {
            return (Value&)(Extends::operator[](which-First));
        }
        return (Value&)m_none;
    }
    virtual Value& operator[](Which which) const {
        if ((which >= First) && (which <= Last)) {
            return (Value&)(Extends::operator[](which-First));
        }
        return (Value&)m_none;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ValuesT& Init() {
        for (Which which = First; which <= Last; ++which) {
            this->operator[](which).SetWhich(which);
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Value m_none;
};
typedef ValuesT<> Values;

} // namespace variables
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace xos 

#endif // _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_VALUES_HPP 
