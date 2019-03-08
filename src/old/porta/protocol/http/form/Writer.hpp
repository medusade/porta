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
///   File: Writer.hpp
///
/// Author: $author$
///   Date: 5/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_FORM_WRITER_HPP
#define _PORTA_PROTOCOL_HTTP_FORM_WRITER_HPP

#include "porta/protocol/http/form/Fields.hpp"
#include "porta/protocol/http/form/Field.hpp"
#include "porta/io/Writer.hpp"
#include "crono/io/Logger.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace form {

typedef ImplementBase WriterTImplements;
typedef Base WriterTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = WriterTImplements, class TExtends = WriterTExtends>

class _EXPORT_CLASS WriterT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef WriterT Derives;

    typedef Fields fields_t;
    typedef Field field_t;
    typedef Field::string_t string_t;
    typedef Field::char_t char_t;
    typedef io::CharWriter writer_t;
    typedef io::CharWriter::what_t what_t;
    typedef io::CharWriter::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WriterT(writer_t& writer)
    : m_writer(writer),
      m_separator("="), m_end("\r\n") {
    }
    virtual ~WriterT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const fields_t& fields) {
        ssize_t count = 0, amount = 0;
        fields_t::const_iterator e, i;

        for (e = fields.end(), i = fields.begin(); i != e; ++i) {
            const field_t& f = (*i);
            const char_t *name = 0, *value = 0;
            size_t name_length = 0, value_length = 0;

            if ((name = f.Name().HasChars(name_length))
                && (value = f.Value().Chars(value_length))) {

                if (0 < (amount = m_writer.Write(name, name_length))) {
                    count += amount;

                    if (0 < (amount = m_writer.Write
                        (m_separator.Chars(), m_separator.Length()))) {
                        count += amount;

                        if (0 <= (amount = m_writer.Write(value, value_length))) {
                            count += amount;

                            if (0 < (amount = m_writer.Write
                                (m_end.Chars(), m_end.Length()))) {
                                count += amount;
                            } else {
                                count = amount;
                            }
                        } else {
                            count = amount;
                        }
                    } else {
                        count = amount;
                    }
                } else {
                    count = amount;
                }
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    writer_t& m_writer;
    string_t m_separator, m_end;
};
typedef WriterT<> Writer;

} // namespace form 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_FORM_WRITER_HPP 
