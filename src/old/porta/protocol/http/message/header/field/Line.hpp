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
///   File: Line.hpp
///
/// Author: $author$
///   Date: 4/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_MESSAGE_HEADER_FIELD_LINE_HPP
#define _PORTA_PROTOCOL_HTTP_MESSAGE_HEADER_FIELD_LINE_HPP

#include "porta/protocol/http/message/header/field/Name.hpp"
#include "porta/protocol/http/message/header/field/Which.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace message {
namespace header {
namespace field {

typedef CharString Part;
typedef ImplementBase LineTImplements;
typedef Part LineTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: LineT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = LineTImplements, class TExtends = LineTExtends>

class _EXPORT_CLASS LineT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef LineT Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LineT(const Which& which, const char* chars, size_t length)
    : m_name(Name::OfWhich(which)), m_value(chars, length) {
        Combine();
    }
    LineT(const Which& which, const char* chars)
    : m_name(Name::OfWhich(which)), m_value(chars) {
        Combine();
    }
    LineT(const Which& which)
    : m_name(Name::OfWhich(which)) {
        Combine();
    }
    ///////////////////////////////////////////////////////////////////////
    LineT(const char* chars, size_t length): Extends(chars, length) {
    }
    LineT(const char* chars): Extends(chars) {
    }
    LineT(const LineT& copy): Extends(copy) {
    }
    LineT() {
    }
    virtual ~LineT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Combine() {
        bool success = false;
        if (0 < (m_name.length())) {
            this->Assign(m_name);
            this->Append(": ");
            this->Append(m_value);
            this->Append("\r\n");
            return true;
        }
        return success;
    }
    virtual bool Separate() {
        bool success = false;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Part& SetName(const char* to) {
        m_name.Assign(to);
        Combine();
        return m_name;
    }
    virtual const Part& Name() const {
        return m_name;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Part& SetValue(const char* to) {
        m_value.Assign(to);
        Combine();
        return m_value;
    }
    virtual const Part& Value() const {
        return m_value;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Part m_name, m_value;
};
typedef LineT<> Line;

} // namespace field 
} // namespace header 
} // namespace message 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_MESSAGE_HEADER_FIELD_LINE_HPP 
