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
///   File: Value.hpp
///
/// Author: $author$
///   Date: 4/11/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_VALUE_HPP
#define _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_VALUE_HPP

#include "porta/protocol/http/cgi/environment/variable/Name.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variable {

typedef ImplementBase ValueTImplements;
typedef CharsWrapped ValueTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ValueT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ValueTImplements, class TExtends = ValueTExtends>

class _EXPORT_CLASS ValueT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::Char Char;
    typedef typename Extends::Chars Chars;
    typedef CharStringT<Char> CharString;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ValueT(variable::Which which): Extends(OfWhich(which)), m_which(which) {
        SetHasValue();
    }
    ValueT(const ValueT& copy): Extends(copy), m_which(copy.m_which) {
        SetHasValue();
    }
    ValueT(): m_which(variable::None) {
    }
    virtual ~ValueT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ValueT& Append(const char* chars, size_t length) {
        m_chars.Append(chars, length);
        return *this;
    }
    virtual ValueT& Set() {
        this->SetWrapped(m_chars.Chars());
        return *this;
    }
    virtual ValueT& Clear() {
        this->SetWrapped(0);
        m_chars.Clear();
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Char* Get(variable::Which which) {
        const Char* value = OfWhich(which);
        this->SetWrapped(value);
        value = SetHasValue();
        return value;
    }
    virtual ValueT& operator = (variable::Which which) {
        this->Get(which);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const Char* OfWhich(variable::Which which) {
        const Char* name = 0;
        if ((name = Name::OfWhich(which)) && (name[0])) {
            const Char* value = 0;
            CRONO_LOG_DEBUG("getenv(name = \"" << name << "\")...");
            if ((value = getenv(name))) {
                CRONO_LOG_DEBUG("...getenv(name = \"" << name << "\") = \"" << value << "\"");
                return value;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Char* SetHasValue() {
        const Char* value = this->Wrapped();
        m_chars.Assign(value);
        if (value) {
            value = m_chars.chars();
            this->SetWrapped(value);
        }
        return value;
    }
    virtual const Char* HasValue() const {
        const Char* value = this->Wrapped();
        return value;
    }
    virtual const Char* HasValue(size_t& length) const {
        const Char* value = this->Wrapped();
        length = (value)?(m_chars.length()):(0);
        return value;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual variable::Which SetWhich(variable::Which to) {
        m_which = to;
        return m_which;
    }
    virtual variable::Which Which() const {
        return m_which;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    variable::Which m_which;
    CharString m_chars;
};
typedef ValueT<> Value;

} // namespace variable
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_VALUE_HPP 
