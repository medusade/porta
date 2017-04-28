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
///   File: Base.hpp
///
/// Author: $author$
///   Date: 4/4/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_BASE_BASE_HPP
#define _PORTA_BASE_BASE_HPP

#include "nadir/base/chars.hpp"
#include "nadir/base/array.hpp"
#include "nadir/base/string.hpp"
#include "nadir/base/to_string.hpp"
#include "nadir/base/wrapped.hpp"
#include "patrona/cpp/xos/base/Chars.hpp"
#include "crono/io/Logger.hpp"

namespace porta {

typedef nadir::implement_base ImplementBase;
typedef nadir::base Base;

typedef nadir::chars_t chars_t;
typedef nadir::tchars_t tchars_t;
typedef nadir::wchars_t wchars_t;

typedef nadir::char_string string_t;
typedef nadir::tchar_string tstring_t;
typedef nadir::wchar_string wstring_t;

typedef nadir::char_array char_array;
typedef nadir::tchar_array tchar_array;
typedef nadir::wchar_array wchar_array;

typedef nadir::int_to_string int_to_string;

typedef patrona::Chars Chars;
typedef patrona::TChars TChars;
typedef patrona::WChars WChars;

///////////////////////////////////////////////////////////////////////
/// Class CharArrayT
///////////////////////////////////////////////////////////////////////
template <typename TChar, class TExtends = nadir::arrayt<TChar> >
class _EXPORT_CLASS CharArrayT: public TExtends {
public:
    typedef TExtends Extends;
    typedef TChar Char;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CharArrayT(const wchar_t* chars) {
        this->Append(chars);
    }
    CharArrayT(const wchar_t* chars, size_t length) {
        this->Append(chars, length);
    }
    CharArrayT(const char* chars) {
        this->Append(chars);
    }
    CharArrayT(const char* chars, size_t length) {
        this->Append(chars, length);
    }
    CharArrayT(const CharArrayT& copy): Extends(copy) {
    }
    CharArrayT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharArrayT& Assign(const wchar_t* chars) {
        this->clear();
        this->Append(chars);
        return *this;
    }
    virtual CharArrayT& Assign(const wchar_t* chars, size_t length) {
        this->clear();
        this->Append(chars, length);
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual CharArrayT& Assign(const char* chars) {
        this->clear();
        this->Append(chars);
        return *this;
    }
    virtual CharArrayT& Assign(const char* chars, size_t length) {
        this->clear();
        this->Append(chars, length);
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharArrayT& Append(const wchar_t* chars) {
        this->Append(chars, wchars_t::count(chars));
        return *this;
    }
    virtual CharArrayT& Append(const wchar_t* chars, size_t length) {
        if ((chars) && (length)) {
            for (Char c = 0; length; --length, ++chars) {
                c = ((Char)(*chars));
                this->append(&c, 1);
            }
        }
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual CharArrayT& Append(const char* chars) {
        this->Append(chars, chars_t::count(chars));
        return *this;
    }
    virtual CharArrayT& Append(const char* chars, size_t length) {
        if ((chars) && (length)) {
            for (Char c = 0; length; --length, ++chars) {
                c = ((Char)(*chars));
                this->append(&c, 1);
            }
        }
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CharArrayT<char> CharArray;
typedef CharArrayT<tchar_t> TCharArray;
typedef CharArrayT<wchar_t> WCharArray;

///////////////////////////////////////////////////////////////////////
/// Class CharStringT
///////////////////////////////////////////////////////////////////////
template <typename TChar, class TExtends = nadir::char_stringt<TChar> >
class _EXPORT_CLASS CharStringT: public TExtends {
public:
    typedef TExtends Extends;
    typedef TChar Char;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CharStringT(const wchar_t* chars) {
        this->Append(chars);
    }
    CharStringT(const wchar_t* chars, size_t length) {
        this->Append(chars, length);
    }
    CharStringT(const char* chars) {
        this->Append(chars);
    }
    CharStringT(const char* chars, size_t length) {
        this->Append(chars, length);
    }
    CharStringT(const CharStringT& copy): Extends(copy) {
    }
    CharStringT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharStringT& Clear() {
        this->clear();
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharStringT& Assign(const CharStringT& s) {
        return this->Assign(s.chars());
    }
    virtual CharStringT& Assign(const wchar_t* chars) {
        this->clear();
        this->Append(chars);
        return *this;
    }
    virtual CharStringT& Assign(const wchar_t* chars, size_t length) {
        this->clear();
        this->Append(chars, length);
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual CharStringT& Assign(const char* chars) {
        this->clear();
        this->Append(chars);
        return *this;
    }
    virtual CharStringT& Assign(const char* chars, size_t length) {
        this->clear();
        this->Append(chars, length);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharStringT& Append(const CharStringT& s) {
        return this->Append(s.chars());
    }
    virtual CharStringT& Append(const wchar_t* chars) {
        this->Append(chars, wchars_t::count(chars));
        return *this;
    }
    virtual CharStringT& Append(const wchar_t* chars, size_t length) {
        if ((chars) && (length)) {
            for (Char c = 0; length; --length, ++chars) {
                c = ((Char)(*chars));
                this->append(&c, 1);
            }
        }
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual CharStringT& Append(const char* chars) {
        this->Append(chars, chars_t::count(chars));
        return *this;
    }
    virtual CharStringT& Append(const char* chars, size_t length) {
        if ((chars) && (length)) {
            for (Char c = 0; length; --length, ++chars) {
                c = ((Char)(*chars));
                this->append(&c, 1);
            }
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Char* HasChars(size_t& length) const {
        return this->has_chars(length);
    }
    virtual const Char* HasChars() const {
        return this->has_chars();
    }
    virtual const Char* Chars(size_t& length) const {
        return this->chars(length);
    }
    virtual const Char* Chars() const {
        return this->chars();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CharStringT<char> CharString;
typedef CharStringT<tchar_t> TCharString;
typedef CharStringT<wchar_t> WCharString;

///////////////////////////////////////////////////////////////////////
///  Class: CharsWrappedT
///////////////////////////////////////////////////////////////////////
template
<typename TChar,
 typename TChars = nadir::charst<TChar>,
 class TExtends = nadir::wrappedt<const TChar*> >

class _EXPORT_CLASS CharsWrappedT: public TExtends {
public:
    typedef TExtends Extends;
    typedef typename Extends::wrapped_t wrapped_t;
    typedef TChars Chars;
    typedef TChar Char;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CharsWrappedT(const Char* chars): Extends(chars) {
    }
    CharsWrappedT(const CharsWrappedT& copy): Extends(copy) {
    }
    CharsWrappedT(): Extends(0) {
    }
    virtual ~CharsWrappedT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wrapped_t SetWrapped(wrapped_t to) {
        return this->wrapped_ = to;
    }
    virtual wrapped_t Wrapped() const {
        return this->wrapped_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CharsWrappedT<char> CharsWrapped;
typedef CharsWrappedT<tchar_t> TCharsWrapped;
typedef CharsWrappedT<wchar_t> WCharsWrapped;

} // namespace porta

#endif // _PORTA_BASE_BASE_HPP 
