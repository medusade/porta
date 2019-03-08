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
///   File: Base.hpp
///
/// Author: $author$
///   Date: 1/2/2019
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_BASE_BASE_HPP
#define _PORTA_BASE_BASE_HPP

#include "nadir/base/base.hpp"
#include "nadir/base/wrapped.hpp"
#include "patrona/base/Base.hpp"
#include "patrona/base/Chars.hpp"
#include "crono/io/Logger.hpp"

namespace porta {

typedef ::nadir::pointer_t pointer_t;
typedef ::nadir::unsigned_t unsigned_t;
typedef ::nadir::signed_t signed_t;

inline const pointer_t& to_pointer(const pointer_t& v) { return v; }
inline const unsigned_t& to_unsigned(const unsigned_t& v) { return v; }
inline const signed_t& to_signed(const signed_t& v) { return v; }
inline const wchar_t& to_wchar(const wchar_t& v) { return v; }
inline const char& to_char(const char& v) { return v; }
inline const bool& to_bool(const bool& v) { return v; }

inline seconds_t mseconds_seconds
(mseconds_t mseconds) { return ::nadir::mseconds_seconds(mseconds); }

inline mseconds_t mseconds_mseconds
(mseconds_t mseconds) { return ::nadir::mseconds_mseconds(mseconds); }

inline useconds_t mseconds_useconds
(mseconds_t mseconds) { return ::nadir::mseconds_useconds(mseconds); }

inline nseconds_t mseconds_nseconds
(mseconds_t mseconds) { return ::nadir::mseconds_nseconds(mseconds); }

typedef ::nadir::implement_base ImplementBase;
typedef ::nadir::base Base;

///
/// Chars
///
typedef ::nadir::chars_t chars_t;
typedef ::nadir::tchars_t tchars_t;
typedef ::nadir::wchars_t wchars_t;

typedef patrona::Chars Chars;
typedef patrona::TChars TChars;
typedef patrona::WChars WChars;
///////////////////////////////////////////////////////////////////////
///  Class: CharsWrappedT
///////////////////////////////////////////////////////////////////////
template
<typename TChar,
 typename TChars = ::nadir::charst<TChar>,
 class TExtends = ::nadir::wrappedt<const TChar*> >

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

///
/// CharArray
///
typedef ::nadir::char_array char_array;
typedef ::nadir::tchar_array tchar_array;
typedef ::nadir::wchar_array wchar_array;
///////////////////////////////////////////////////////////////////////
/// Class CharArrayT
///////////////////////////////////////////////////////////////////////
template <typename TChar, class TExtends = ::nadir::arrayt<TChar> >
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

///
/// ChartSring
///
typedef ::nadir::char_string string_t;
typedef ::nadir::tchar_string tstring_t;
typedef ::nadir::wchar_string wstring_t;
///////////////////////////////////////////////////////////////////////
/// Class CharStringT
///////////////////////////////////////////////////////////////////////
template <typename TChar, class TExtends = ::nadir::char_stringt<TChar> >
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
    virtual size_t Length() const {
        return this->length();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CharStringT<char> CharString;
typedef CharStringT<tchar_t> TCharString;
typedef CharStringT<wchar_t> WCharString;

///
/// ToString
///
typedef ::nadir::chars_to_string chars_to_string;
typedef ::nadir::bool_to_string bool_to_string;
typedef ::nadir::int_to_string int_to_string;
typedef ::nadir::signed_to_string signed_to_string;
typedef ::nadir::unsigned_to_string unsigned_to_string;
typedef ::nadir::pointer_to_string pointer_to_string;

typedef ::patrona::CharsToString CharsToString;
typedef ::patrona::BoolToString BoolToString;
typedef ::patrona::IntToString IntToString;
typedef ::patrona::SignedToString SignedToString;
typedef ::patrona::UnsignedToString UnsignedToString;
typedef ::patrona::PointerToString PointerToString;

} // namespace porta

#endif // _PORTA_BASE_BASE_HPP 
