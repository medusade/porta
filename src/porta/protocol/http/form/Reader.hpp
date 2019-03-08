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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 1/2/2019
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_FORM_READER_HPP
#define _PORTA_PROTOCOL_HTTP_FORM_READER_HPP

#include "porta/protocol/http/form/Fields.hpp"
#include "porta/protocol/http/form/Field.hpp"
#include "porta/io/Reader.hpp"
#include "crono/io/Logger.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace form {

typedef ImplementBase ReaderTImplements;
typedef Base ReaderTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ReaderTImplements, class TExtends = ReaderTExtends>

class _EXPORT_CLASS ReaderT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef ReaderT Derives;

    typedef Fields fields_t;
    typedef Field field_t;
    typedef io::CharReader reader_t;
    typedef io::CharReader::what_t what_t;
    typedef io::CharReader::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(fields_t& fields)
    : fields_(fields), end_(fields_.end()), field_(end_), on_(0) {
    }
    virtual ~ReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(reader_t& reader) {
        fields_.clear();
        return ReadMore(reader);
    }
    virtual ssize_t ReadMore(reader_t& reader) {
        ssize_t count = 0, amount = 0;
        sized_t sized;
        on_begin();
        while (0 < (amount = reader.Read(&sized, 1))) {
            on(sized);
        }
        on_end();
        return count;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_begin() {
        field_t field;
        fields_.push_back(field);
        --(field_ = (end_ = fields_.end()));
        on_ = &Derives::on_name;
    }
    virtual void on_end() {
        if ((field_ != end_)) {
            if (!((*field_).Name().length())) {
                fields_.pop_back();
            } else {
                CRONO_LOG_DEBUG("...value = \"" << (*field_).Value() << "\"");
            }
            field_ = (end_ = fields_.end());
        }
        on_ = 0;
    }
    virtual void on_next() {
        field_t field;
        fields_.push_back(field);
        --(field_ = fields_.end());
        on_ = &Derives::on_name;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on(const sized_t& sized) {
        if ((on_)) {
            (this->*on_)(sized);
        }
    }
    virtual void on_name(const sized_t& sized) {
        if ((field_ != end_)) {
            if ((sized != eq_)) {
                if ((sized != amp_)) {
                    (*field_).Name().append(&sized, 1);
                } else {
                    if (0 < ((*field_).Name().length())) {
                        on_next();
                    }
                }
            } else {
                if (0 < ((*field_).Name().length())) {
                    CRONO_LOG_DEBUG("...name = \"" << (*field_).Name() << "\"");
                    on_ = &Derives::on_value;
                } else {
                    on_ = &Derives::on_no_name;
                }
            }
        }
    }
    virtual void on_value(const sized_t& sized) {
        if ((field_ != end_)) {
            if ((sized != amp_)) {
                (*field_).Value().append(&sized, 1);
            } else {
                CRONO_LOG_DEBUG("...value = \"" << (*field_).Value() << "\"");
                on_next();
            }
        }
    }
    virtual void on_no_name(const sized_t& sized) {
        if ((sized == amp_)) {
            on_ = &Derives::on_name;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef void (Derives::*on_t)(const sized_t& sized);
    static const sized_t eq_ = '=';
    static const sized_t amp_ = '&';
    fields_t& fields_;
    typename fields_t::iterator end_;
    typename fields_t::iterator field_;
    on_t on_;
};
typedef ReaderT<> Reader;

} // namespace form 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_FORM_READER_HPP 
