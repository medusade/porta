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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/10/2017
///////////////////////////////////////////////////////////////////////
#ifndef _PORTA_APP_CONSOLE_CGI_CATCHER_MAIN_HPP
#define _PORTA_APP_CONSOLE_CGI_CATCHER_MAIN_HPP

#include "porta/app/console/cgi/Main.hpp"

namespace porta {
namespace app {
namespace console {
namespace cgi {
namespace catcher {

typedef cgi::MainTContentReadObserver MainTContentReadObserver;
typedef cgi::MainTImplements MainTImplements;
typedef cgi::Main MainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TContentReadObserver = MainTContentReadObserver,
 class TImplements = MainTImplements, class TExtends = MainTExtends>
class _EXPORT_CLASS MainT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename TContentReadObserver::sized_t sized_t;
    typedef typename TContentReadObserver::what_t what_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT() {
    }
    virtual ~MainT() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRunCgi(int argc, char** argv, char** env) {
        int err = 0;
        this->OutLn("catching:");
        return err;
    }
    virtual int AfterRunCgi(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = this->WriteForm(argc, argv, env))) {
            if (!(err = this->WriteEnvironment(argc, argv, env))) {
                if (!(err = this->WriteArguments(argc, argv, env))) {
                    if (!(err = this->WriteInput(argc, argv, env))) {
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunConsole(int argc, char** argv, char** env) {
        int err = this->RunCgi(argc, argv, env);
        return err;
    }
    virtual int BeforeRunConsole(int argc, char** argv, char** env) {
        int err = 0;
        this->OutLn("caught:");
        return err;
    }
    virtual int AfterRunConsole(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = this->WriteForm(this->OutWriter(), argc, argv, env))) {
            if (!(err = this->WriteEnvironment(this->OutWriter(), argc, argv, env))) {
                if (!(err = this->WriteArguments(this->OutWriter(), argc, argv, env))) {
                    if (!(err = this->WriteInput(this->OutWriter(), argc, argv, env))) {
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnReadContent
    (const what_t* what, const sized_t* sized, size_t size) {
        this->Content().Append(sized, size);
    }
    virtual void OnBeginReadContent(size_t size) {
        this->Content().set_size(size);
        this->Content().set_length(0);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef MainT<> Main;

} // namespace catcher
} // namespace cgi 
} // namespace console 
} // namespace app 
} // namespace porta 

#endif // _PORTA_APP_CONSOLE_CGI_CATCHER_MAIN_HPP 
