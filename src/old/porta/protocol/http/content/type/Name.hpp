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
///   Date: 4/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_CONTENT_TYPE_NAME_HPP
#define _PORTA_PROTOCOL_HTTP_CONTENT_TYPE_NAME_HPP

#include "porta/protocol/http/content/type/Which.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace content {
namespace type {

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
    typedef typename Extends::Chars Chars;
    typedef typename Extends::Char Char;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NameT(type::Which which): Extends(OfWhich(which)), m_which(which) {
    }
    NameT(const NameT& copy): Extends(copy), m_which(copy.m_wich) {
    }
    virtual ~NameT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual NameT& operator = (const Char* of) {
        m_which = WhichOf(this->SetWrapped(of));
        return *this;
    }
    virtual NameT& operator = (type::Which which) {
        this->SetWrapped(OfWhich(m_which = which));
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Char* Of(size_t& length) const {
        length = Length();
        return Of();
    }
    virtual const Char* Of() const {
        return this->Wrapped();
    }
    virtual type::Which Which() const {
        return m_which;
    }
    virtual size_t Length() const {
        size_t length = 0;
        const Char* chars = 0;
        if ((chars = this->wrapped())) {
            length = Chars::count(chars);
        }
        return length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const Char** OfWhich() {
        static const Char* name[Count + 1] = {
            PORTA_PROTOCOL_HTTP_CONTENT_TYPE_NAMES
            0
        };
        return name;
    }
    static const Char* OfWhich(type::Which which) {
        const Char** name = OfWhich();
        if ((name) && (which >= First) && (which <= Last)) {
            return name[which - First];
        }
        return 0;
    }
    static type::Which WhichOf(const Char* of) {
        if ((of)) {
            const Char* to = 0;
            for (type::Which which = First; which <= Last; ++which) {
                if ((to = OfWhich(which))) {
                    if (!(Chars::compare(of, to)))
                        return which;
                }
            }
        }
        return None;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    type::Which m_which;
};
typedef NameT<> Name;

} // namespace type 
} // namespace content 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_CONTENT_TYPE_NAME_HPP 
