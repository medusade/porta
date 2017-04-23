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
///   Date: 4/23/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_FORM_READER_HPP
#define _PORTA_PROTOCOL_HTTP_FORM_READER_HPP

#include "porta/protocol/http/form/Field.hpp"
#include "porta/io/Reader.hpp"

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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT() {
    }
    virtual ~ReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReaderT<> Reader;

} // namespace form 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_FORM_READER_HPP 
