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
///   Date: 4/21/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_IO_READER_HPP
#define _PORTA_IO_READER_HPP

#include "porta/base/Base.hpp"
#include "patrona/cpp/xos/base/Attached.hpp"
#include "patrona/cpp/xos/io/Reader.hpp"

namespace porta {
namespace io {

typedef patrona::io::ReaderTImplements CharReaderImplements;
typedef patrona::io::CharReader CharReader;

typedef patrona::io::CharReader::sized_t CharsReaderTSized;
typedef const CharsReaderTSized* CharsReaderTAttachedTo;

typedef patrona::AttacherT
<CharsReaderTAttachedTo, CharsReaderTSized, 0,
 CharReaderImplements> CharsReaderTImplements;

typedef patrona::AttachedT
<CharsReaderTAttachedTo, CharsReaderTSized, 0,
 CharsReaderTImplements, CharReader> CharsReaderTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: CharsReaderT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = CharsReaderTImplements, class TExtends = CharsReaderTExtends>

class _EXPORT_CLASS CharsReaderT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::what_t what_t;
    typedef typename Extends::sized_t sized_t;
    typedef typename Extends::sized_t end_t;
    enum { end = 0 };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CharsReaderT(const sized_t* attached, size_t length)
    : Extends(attached), length_(length), tell_(0) {
    }
    virtual ~CharsReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(what_t* what, size_t size) {
        const sized_t* from = 0;

        if ((from = this->AttachedTo())) {
            sized_t* to = 0;

            if ((to = ((sized_t*)what)) && (size)) {
                if (length_ < (tell_ + size)) {
                    size = length_ - tell_;
                }
                if (size) {
                    chars_t::copy(to, from + tell_, size);
                    tell_ += size;
                    return size;
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t length_, tell_;
};
typedef CharsReaderT<> CharsReader;

} // namespace io
} // namespace porta 

#endif // _PORTA_IO_READER_HPP 
