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
///   File: ReadObserver.hpp
///
/// Author: $author$
///   Date: 1/2/2019
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_CONTENT_READOBSERVER_HPP
#define _PORTA_PROTOCOL_HTTP_CONTENT_READOBSERVER_HPP

#include "porta/base/Base.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace content {

typedef ImplementBase ReadObserverTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: ReadObserverT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 class TImplements = ReadObserverTImplements>

class _EXPORT_CLASS ReadObserverT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TWhat what_t;
    typedef TSized sized_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnReadContent
    (const what_t* what, const sized_t* sized, size_t size) {
    }
    virtual void OnBeginReadContent(size_t size) {
    }
    virtual void OnEndReadContent(size_t size) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReadObserverT<> ReadObserver;

} // namespace content 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_CONTENT_READOBSERVER_HPP 
