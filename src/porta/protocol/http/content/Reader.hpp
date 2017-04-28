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
///   Date: 4/26/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_PROTOCOL_HTTP_CONTENT_READER_HPP
#define _PORTA_PROTOCOL_HTTP_CONTENT_READER_HPP

#include "porta/protocol/http/content/ReadObserver.hpp"
#include "porta/io/Reader.hpp"

namespace porta {
namespace protocol {
namespace http {
namespace content {

typedef ReadObserver ReaderTObserver;
typedef io::CharReaderImplements ReaderTImplements;
typedef io::CharReader ReaderTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<class TReadObserver = ReaderTObserver,
 class TImplements = ReaderTImplements, class TExtends = ReaderTExtends>

class _EXPORT_CLASS ReaderT:
virtual public TReadObserver, virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef Extends reader_t;
    typedef TReadObserver observer_t;
    typedef typename Extends::what_t what_t;
    typedef typename Extends::sized_t sized_t;
    typedef typename Extends::sized_t end_t;
    enum { end = 0 };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(observer_t& observer, reader_t& reader, size_t length)
    : observer_(observer), reader_(reader), length_(length), tell_(0) {
    }
    ReaderT(reader_t& reader, size_t length)
    : observer_(*this), reader_(reader), length_(length), tell_(0) {
    }
    virtual ~ReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(what_t* what, size_t size) {
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what)) && (size)) {
            if (length_ < (tell_ + size)) {
                size = tell_ - length_;
            }
            if ((size)) {
                ssize_t count = 0;
                if (0 < (count = reader_.Read(what, size))) {
                    observer_.OnReadContent(what, sized, size);
                    tell_ += count;
                } else {
                    CRONO_LOG_ERROR("...failed " << count << " on reader_.Read(what, size = " << size << ")");
                }
                return count;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    observer_t& observer_;
    reader_t& reader_;
    size_t length_, tell_;
};
typedef ReaderT<> Reader;

} // namespace content 
} // namespace http 
} // namespace protocol 
} // namespace porta 

#endif // _PORTA_PROTOCOL_HTTP_CONTENT_READER_HPP 
