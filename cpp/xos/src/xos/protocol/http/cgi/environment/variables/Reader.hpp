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
#include "xos/io/Reader.hpp"
#include "xos/logger/Interface.hpp"

namespace xos {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variables {

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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(Values& values)
    : m_values(values), m_value(0), m_onRead(0) {
    }
    virtual ~ReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Read(ssize_t& count, io::CharReader& reader) {
        bool success = true;
        ssize_t amount = 0;
        char c = 0;

        m_name.Clear();
        m_values.ClearAll();
        m_value = 0;
        m_onRead = &Derives::OnReadName;

        for (amount = 1; amount; count += amount) {
            if (0 > (amount = reader.Read(&c, 1))) {
                count = amount;
                success = false;
                break;
            } else {
                if (0 < (amount)) {
                    if (!(OnRead(c))) {
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
    virtual bool OnRead(const char& c) {
        if ((m_onRead)) {
            return (this->*m_onRead)(c);
        }
        return false;
    }
    virtual bool OnReadName(const char& c) {
        if ((c != eq_)) {
            if ((c != cr_)) {
                if ((c != lf_)) {
                    m_name.Append(&c, 1);
                } else {
                    XOS_LOG_ERROR("...invalid char '" << String(&c,1) << "'");
                    return false;
                }
            } else {
                m_onRead = &Derives::OnReadNameCR;
            }
        } else {
            Value* value = 0;
            if ((value = ValueOf(m_name))) {
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
    virtual bool OnReadNameCR(const char& c) {
        if ((c != eq_)) {
            if ((c != cr_)) {
                if ((c != lf_)) {
                    XOS_LOG_ERROR("...invalid char '" << String(&c,1) << "'");
                    return false;
                } else {
                    if (0 < (m_name.length())) {
                        Value* value = 0;
                        if ((value = ValueOf(m_name))) {
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
                XOS_LOG_ERROR("...invalid char '" << String(&c,1) << "'");
                return false;
            }
        } else {
            XOS_LOG_ERROR("...invalid char '" << String(&c,1) << "'");
            return false;
        }
        return true;
    }
    virtual bool OnReadValue(const char& c) {
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
    virtual bool OnReadValueCR(const char& c) {
        if ((c != cr_)) {
            if ((c != lf_)) {
                XOS_LOG_ERROR("...invalid char '" << String(&c,1) << "'");
                return false;
            } else {
                m_onRead = &Derives::OnReadName;
            }
        } else {
            XOS_LOG_ERROR("...invalid char '" << String(&c,1) << "'");
            return false;
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Value* ValueOf(const String& named) {
        const char* chars = 0;

        if ((chars = named.HasChars())) {
            Value& value = (m_values)[chars];

            if ((value.Which())) {
                return &value;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef bool (Derives::*MOnRead)(const char& c);
    const char eq_ = '=';
    const char cr_ = '\r';
    const char lf_ = '\n';
    Values& m_values;
    Value* m_value;
    MOnRead m_onRead;
    String m_name;
};
typedef ReaderT<> Reader;

} // namespace variables
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace xos 

#endif // _XOS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_READER_HPP 
