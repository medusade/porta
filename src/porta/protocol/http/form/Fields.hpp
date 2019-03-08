///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: Fields.hpp
///
/// Author: $author$
///   Date: 1/2/2019
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_FORM_FIELDS_HPP
#define _PORTA_PROTOCOL_HTTP_FORM_FIELDS_HPP

#include "porta/protocol/http/form/Field.hpp"
#include <list>

namespace porta {
namespace protocol {
namespace http {
namespace form {

typedef ImplementBase FieldsTImplements;
typedef ::std::list<Field> FieldsTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: FieldsT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = FieldsTImplements, class TExtends = FieldsTExtends>

class _EXPORT_CLASS FieldsT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::const_iterator const_iterator;
    typedef typename Extends::iterator iterator;
    typedef typename Field::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef Field field_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FieldsT(const FieldsT& copy): Extends(copy) {
    }
    FieldsT() {
    }
    virtual ~FieldsT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    const char_t* FindValue
    (const string_t& name, const field_t* from = 0) const {
        return FindValue(name.Chars(), from);
    }
    const char_t* FindValue
    (const char_t* name, const field_t* from = 0) const {
        field_t* f = 0;
        if ((f = Find(name, from))) {
            return f->Value().HasChars();
        }
        return 0;
    }
    const char_t* FindValue
    (const char_t** names, const field_t* from = 0) const {
        field_t* f = 0;
        if ((f = Find(names, from))) {
            return f->Value().HasChars();
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    field_t* Find(const string_t& name, const field_t* from = 0) const {
        return Find(name.Chars(), from);
    }
    field_t* Find(const char_t* name, const field_t* from = 0) const {
        const const_iterator begin = this->begin();
        const const_iterator end = this->end();
        for (const_iterator i = begin; i != end; ++i) {
            const field_t& found = (*i);
            if ((from)) {
                if (from == &found) {
                    from = 0;
                }
            } else {
                if (!(found.Name().compare(name))) {
                    return ((field_t*)&found);
                }
            }
        }
        return 0;
    }
    field_t* Find(const char_t** names, const field_t* from = 0) const {
        if ((names) && (names[0])) {
            const const_iterator begin = this->begin();
            const const_iterator end = this->end();
            for (const_iterator i = begin; i != end; ++i) {
                const field_t& found = (*i);
                if ((from)) {
                    if (from == &found) {
                        from = 0;
                    }
                } else {
                    size_t n = 0;
                    for (const char_t* name = names[n]; name; name = names[++n]) {
                        if (!(found.Name().compare(name))) {
                            return ((field_t*)&found);
                        }
                    }
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef FieldsT<> Fields;

} // namespace form 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_FORM_FIELDS_HPP 
