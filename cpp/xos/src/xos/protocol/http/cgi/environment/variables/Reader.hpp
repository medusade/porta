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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 9/23/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_READER_HPP
#define _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_READER_HPP

#include "xos/protocol/http/cgi/environment/variables/Values.hpp"
#include "xos/protocol/http/cgi/environment/variable/Value.hpp"
#include "xos/io/Writer.hpp"
#include "xos/io/Reader.hpp"
#include "xos/logger/Interface.hpp"

namespace xos {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variables {

///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ImplementBase, class TExtends = Base>

class _EXPORT_CLASS WriterT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef Values values_t;
    typedef variable::Name name_t;
    typedef variable::Which which_t;
    static const which_t first = variable::First;
    static const which_t last = variable::Last;

    typedef io::CharWriter writer_t;
    typedef String string_t;
    typedef char char_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WriterT() {
    }
    virtual ~WriterT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Write(ssize_t& count, writer_t& writer, values_t& values) {
        static const char_t eq_ = '=';
        static const char_t cr_ = '\r';
        static const char_t lf_ = '\n';
        bool success = true;
        ssize_t amount = 0;
        const char_t *name = 0, *value = 0;

        for (which_t e = first; e <= last; ++e) {

            if ((name = name_t::OfWhich(e))) {

                if (!(value = values[e])) {
                    continue;
                } else {
                    XOS_LOG_DEBUG("writer.Write(name = \"" << name << "\")...");
                    if (0 < (amount = writer.Write(name))) {
                        count += amount;

                        XOS_LOG_DEBUG("writer.Write(\"" << string_t(&eq_, 1) << "\")...");
                        if (0 < (amount = writer.Write(&eq_, 1))) {
                            count += amount;

                            XOS_LOG_DEBUG("writer.Write(value = \"" << value << "\")...");
                            if (0 <= (amount = writer.Write(value))) {
                                count += amount;

                                XOS_LOG_DEBUG("writer.Write(\"" << string_t(&cr_, 1) << "\")...");
                                if (0 < (amount = writer.Write(&cr_, 1))) {
                                    count += amount;

                                    XOS_LOG_DEBUG("writer.Write(\"" << string_t(&lf_, 1) << "\")...");
                                    if (0 < (amount = writer.Write(&lf_, 1))) {
                                        count += amount;
                                        continue;
                                    } else {
                                        XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(\"" << string_t(&lf_, 1) << "\")");
                                    }
                                } else {
                                    XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(\"" << string_t(&cr_, 1) << "\")");
                                }
                            } else {
                                XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(value = \"" << value << "\")");
                            }
                        } else {
                            XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(\"" << string_t(&eq_, 1) << "\")");
                        }
                    } else {
                        XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(name = \"" << name << "\")");
                    }
                }
                count = amount;
                success = false;
                break;
            }
        }
        if ((success)) {
            XOS_LOG_DEBUG("writer.Write(\"" << string_t(&cr_, 1) << "\")...");
            if (0 < (amount = writer.Write(&cr_, 1))) {
                count += amount;

                XOS_LOG_DEBUG("writer.Write(\"" << string_t(&lf_, 1) << "\")...");
                if (0 < (amount = writer.Write(&lf_, 1))) {
                    count += amount;
                    return success;
                } else {
                    XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(\"" << string_t(&lf_, 1) << "\")");
                }
            } else {
                XOS_LOG_ERROR("...failed  " << amount << " = writer.Write(\"" << string_t(&cr_, 1) << "\")");
            }
            count = amount;
            success = false;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ImplementBase, class TExtends = Base>

class _EXPORT_CLASS ReaderT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef ReaderT Derives;

    typedef Values values_t;
    typedef io::CharReader reader_t;
    typedef String string_t;
    typedef char char_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(): m_onRead(0), m_value(0) {
    }
    virtual ~ReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Read(ssize_t& count, reader_t& reader, values_t& values) {
        bool success = true;
        ssize_t amount = 0;
        char_t c = 0;

        m_name.Clear();
        values.ClearAll();
        m_value = 0;
        m_onRead = &Derives::OnReadName;

        for (amount = 1; amount; count += amount) {
            if (0 > (amount = reader.Read(&c, 1))) {
                count = amount;
                success = false;
                break;
            } else {
                if (0 < (amount)) {
                    if (!(OnRead(values, c))) {
                        count = 0;
                        success = false;
                        break;
                    }
                }
            }
        }
        m_onRead = 0;
        m_value = 0;
        m_name.Clear();
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnRead(values_t& values, const char_t& c) {
        if ((m_onRead)) {
            return (this->*m_onRead)(values, c);
        }
        return false;
    }
    virtual bool OnReadName(values_t& values, const char_t& c) {
        if ((c != eq_)) {
            if ((c != cr_)) {
                if ((c != lf_)) {
                    m_name.Append(&c, 1);
                } else {
                    XOS_LOG_ERROR("...invalid char '" << string_t(&c,1) << "'");
                    return false;
                }
            } else {
                m_onRead = &Derives::OnReadNameCR;
            }
        } else {
            Value* value = 0;
            if ((value = ValueOf(values, m_name))) {
                m_name.Clear();
                value->Clear();
                m_value = value;
                m_onRead = &Derives::OnReadValue;
            } else {
                XOS_LOG_ERROR("...failed on ValueOf(..., \"" << m_name << "\")");
                m_name.Clear();
                return false;
            }
        }
        return true;
    }
    virtual bool OnReadNameCR(values_t& values, const char_t& c) {
        if ((c != eq_)) {
            if ((c != cr_)) {
                if ((c != lf_)) {
                    XOS_LOG_ERROR("...invalid char '" << string_t(&c,1) << "'");
                    return false;
                } else {
                    if (0 < (m_name.length())) {
                        Value* value = 0;
                        if ((value = ValueOf(values, m_name))) {
                            m_name.Clear();
                            value->Clear();
                            m_onRead = &Derives::OnReadName;
                        } else {
                            XOS_LOG_ERROR("...failed on ValueOf(..., \"" << m_name << "\")");
                            m_name.Clear();
                            return false;
                        }
                    }
                }
            } else {
                XOS_LOG_ERROR("...invalid char '" << string_t(&c,1) << "'");
                return false;
            }
        } else {
            XOS_LOG_ERROR("...invalid char '" << string_t(&c,1) << "'");
            return false;
        }
        return true;
    }
    virtual bool OnReadValue(values_t& values, const char_t& c) {
        if ((c != cr_)) {
            if ((m_value)) {
                m_value->Append(&c, 1);
            } else {
                return false;
            }
        } else {
            m_value->Set();
            XOS_LOG_DEBUG("...value = \"" << m_value->Wrapped() << "\"");
            m_onRead = &Derives::OnReadValueCR;
        }
        return true;
    }
    virtual bool OnReadValueCR(values_t& values, const char_t& c) {
        if ((c != cr_)) {
            if ((c != lf_)) {
                XOS_LOG_ERROR("...invalid char '" << string_t(&c,1) << "'");
                return false;
            } else {
                m_onRead = &Derives::OnReadName;
            }
        } else {
            XOS_LOG_ERROR("...invalid char '" << string_t(&c,1) << "'");
            return false;
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Value* ValueOf(values_t& values, const string_t& named) {
        const char_t* chars = 0;

        if ((chars = named.HasChars())) {
            Value& value = (values)[chars];

            if ((value.Which())) {
                return &value;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char_t eq_ = ((char_t)'=');
    const char_t cr_ = ((char_t)'\r');
    const char_t lf_ = ((char_t)'\n');
    bool (Derives::*m_onRead)(values_t& values, const char_t& c);
    Value* m_value;
    string_t m_name;
};
typedef ReaderT<> Reader;

} // namespace variables
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace xos 

#endif // _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_READER_HPP 
