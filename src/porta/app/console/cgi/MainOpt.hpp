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
///   File: MainOpt.hpp
///
/// Author: $author$
///   Date: 1/2/2019
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_APP_CONSOLE_CGI_MAINOPT_HPP
#define _PORTA_APP_CONSOLE_CGI_MAINOPT_HPP

#include "porta/console/getopt/Main.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define PORTA_APP_CONSOLE_CGI_NULL_OPTARG 0
#define PORTA_APP_CONSOLE_CGI_NULL_OPTUSE 0
#define PORTA_APP_CONSOLE_CGI_NULL_OPTVAL_C 0

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define PORTA_APP_CONSOLE_CGI_OPTIONS_CHARS \
    PORTA_CONSOLE_GETOPT_MAIN_OPTIONS_CHARS

#define PORTA_APP_CONSOLE_CGI_OPTIONS_OPTIONS \
    PORTA_CONSOLE_GETOPT_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define PORTA_APP_CONSOLE_CGI_ARGS 0
#define PORTA_APP_CONSOLE_CGI_ARGV

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace porta {
namespace app {
namespace console {
namespace cgi {

typedef porta::console::getopt::Main::Implements MainOptTImplements;
typedef porta::console::getopt::Main MainOptTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainOptT
///////////////////////////////////////////////////////////////////////
template <class TImplements = MainOptTImplements, class TExtends = MainOptTExtends>

class _EXPORT_CLASS MainOptT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainOptT() {
    }
    virtual ~MainOptT() {
    }
private:
    MainOptT(const MainOptT& copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnNullOption
    (int optval, const char_t* optarg, const char_t* optname, int optind, 
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char_t* optarg, const char_t* optname, int optind, 
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case PORTA_APP_CONSOLE_CGI_NULL_OPTVAL_C:
            err = OnNullOption(optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::OnOption(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* OptionUsage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case PORTA_APP_CONSOLE_CGI_NULL_OPTVAL_C:
            optarg = PORTA_APP_CONSOLE_CGI_NULL_OPTARG;
            chars = PORTA_APP_CONSOLE_CGI_NULL_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char_t* Options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = PORTA_APP_CONSOLE_CGI_OPTIONS_CHARS;
        static struct option optstruct[]= {
            PORTA_APP_CONSOLE_CGI_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* Arguments(const char_t**& argv) {
        static const char_t* _args = PORTA_APP_CONSOLE_CGI_ARGS;
        static const char_t* _argv[] = {
            PORTA_APP_CONSOLE_CGI_ARGV
            0};
        argv = _argv;
        return _args;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS MainOptT
typedef MainOptT<> MainOpt;

} // namespace cgi 
} // namespace console 
} // namespace app 
} // namespace porta 

#endif // _PORTA_APP_CONSOLE_CGI_MAINOPT_HPP 
