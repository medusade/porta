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
///   Date: 4/27/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_WRITER_HPP
#define _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_WRITER_HPP

#include "porta/protocol/http/cgi/environment/variables/Values.hpp"
#include "porta/protocol/http/cgi/environment/variable/Value.hpp"
#include "porta/io/Writer.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variables {

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
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WriterT(io::CharWriter& writer): m_writer(writer) {
    }
    virtual ~WriterT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(Values& values) {
        ssize_t count = 0, amount = 0;
        porta::protocol::http::cgi::environment::variable::Which e;
        for (e = porta::protocol::http::cgi::environment::variable::First;
             e <= porta::protocol::http::cgi::environment::variable::Last; ++e) {
            const char* name = porta::protocol::http::cgi::environment::variable::Name::OfWhich(e);
            if (name) {
                const char* value = values[e];
                if (0 < (amount = m_writer.Write(name))) {
                    count += amount;
                    if (0 < (amount = m_writer.Write(&eq_, 1))) {
                        count += amount;
                        if (value) {
                            if (0 <= (amount = m_writer.Write(value))) {
                                count += amount;
                            } else {
                                return amount;
                            }
                        }
                        if (0 < (amount = m_writer.Write(&cr_, 1))) {
                            count += amount;
                            if (0 < (amount = m_writer.Write(&lf_, 1))) {
                                count += amount;
                            } else {
                                return amount;
                            }
                        } else {
                            return amount;
                        }
                    } else {
                        return amount;
                    }
                } else {
                    return amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char eq_ = '=';
    const char cr_ = '\r';
    const char lf_ = '\n';
    io::CharWriter& m_writer;
};
typedef WriterT<> Writer;

} // namespace variables 
} // namespace environment 
} // namespace cgi 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLES_WRITER_HPP 
