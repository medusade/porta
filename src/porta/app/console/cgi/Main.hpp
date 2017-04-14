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
#ifndef _PORTA_APP_CONSOLE_CGI_MAIN_HPP
#define _PORTA_APP_CONSOLE_CGI_MAIN_HPP

#include "porta/protocol/http/cgi/environment/variable/Value.hpp"
#include "porta/protocol/http/cgi/environment/variable/Name.hpp"
#include "porta/protocol/http/cgi/environment/variable/Which.hpp"
#include "porta/console/getopt/Main.hpp"

namespace porta {
namespace app {
namespace console {
namespace cgi {

typedef porta::console::getopt::MainImplements MainTImplements;
typedef porta::console::getopt::Main MainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = MainTImplements, class TExtends = MainTExtends>
class _EXPORT_CLASS MainT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT() {
    }
    virtual ~MainT() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeRunCgi(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRunCgi(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunConsole(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if (!(err = BeforeRunCgi(argc, argv, env))) {
            err = RunCgi(argc, argv, env);
            if ((err2 = AfterRunCgi(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeRunConsole(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRunConsole(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int CgiMain(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if (!(err = BeforeReadForm(argc, argv, env))) {
            if (!(err = ReadForm(argc, argv, env))) {
                if (!(err = BeforeRunCgi(argc, argv, env))) {
                    if (!(err = RunCgi(argc, argv, env))) {
                    }
                    if ((err2 = AfterRunCgi(argc, argv, env)) && (!err)) {
                        err = err2;
                    }
                }
            }
            if ((err2 = AfterReadForm(argc, argv, env)) && (!err)) {
                err = err2;
            }
        }
        return err;
    }
    virtual int ConsoleMain(int argc, char_t** argv, char_t** env) {
        int err = 0, err2 = 0;
        if (!(err = BeforeReadForm(argc, argv, env))) {
            if (!(err = ReadForm(argc, argv, env))) {
                if (!(err = BeforeRunConsole(argc, argv, env))) {
                    if (!(err = RunConsole(argc, argv, env))) {
                    }
                    if ((err2 = AfterRunConsole(argc, argv, env)) && (!err)) {
                        err = err2;
                    }
                }
            }
            if ((err2 = AfterReadForm(argc, argv, env)) && (!err)) {
                err = err2;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int CgiRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if (!(err = BeforeGetEnvironment(argc, argv, env))) {
            if (!(err = GetEnvironment(argc, argv, env))) {
                if (!(err = CgiMain(argc, argv, env))) {
                }
            }
            if ((err2 = AfterGetEnvironment(argc, argv, env)) && (!err)) {
                err = err2;
            }
        }
        return err;
    }
    virtual int BeforeCgiRun(int argc, char** argv, char** env) {
        int err = 0;
        SetFileModeIsBinary(this->StdIn());
        SetFileModeIsBinary(this->StdOut());
        return err;
    }
    virtual int AfterCgiRun(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ConsoleRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if (!(err = BeforeReadEnvironment(argc, argv, env))) {
            if (!(err = ReadEnvironment(argc, argv, env))) {
                if (!(err = BeforeReadContent(argc, argv, env))) {
                    if (!(err = BeginReadContent(argc, argv, env))) {
                        if (!(err = ConsoleMain(argc, argv, env))) {
                        }
                        if ((err2 = EndReadContent(argc, argv, env)) && (!err)) {
                            err = err2;
                        }
                    }
                    if ((err2 = AfterReadContent(argc, argv, env)) && (!err)) {
                        err = err2;
                    }
                }
            }
            if ((err2 = AfterReadEnvironment(argc, argv, env)) && (!err)) {
                err = err2;
            }
        }
        return err;
    }
    virtual int BeforeConsoleRun(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterConsoleRun(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeGetEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterGetEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeReadEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterReadEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeginReadContent(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int EndReadContent(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeReadContent(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterReadContent(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadForm(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeReadForm(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterReadForm(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadQueryFormData(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int ReadFormData(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadFormData
    (size_t content_length, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeReadFormData
    (size_t content_length, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterReadFormData
    (size_t content_length, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadUrlencodedFormData
    (size_t content_length, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int ReadMultipartFormData
    (size_t content_length, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if ((GatewayInterface())) {
            if (!(err = BeforeCgiRun(argc, argv, env))) {
                err = CgiRun(argc, argv, env);
                if ((err2 = AfterCgiRun(argc, argv, env))) {
                    if (!err) err = err2;
                }
            }
        } else {
            if (!(err = BeforeConsoleRun(argc, argv, env))) {
                err = ConsoleRun(argc, argv, env);
                if ((err2 = AfterConsoleRun(argc, argv, env))) {
                    if (!err) err = err2;
                }
            }
        }
        return err;
    }
    virtual const char* GatewayInterface() const {
        protocol::http::cgi::environment::variable::Value
            gatewayInterface(protocol::http::cgi::environment::variable::GATEWAY_INTERFACE);
        return gatewayInterface.HasValue();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* OutStdOut() {
        return this->StdOut();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetFileModeIsBinary
    (FILE* file, bool modeIsBinary = true) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef MainT<> Main;

} // namespace cgi
} // namespace console 
} // namespace app 
} // namespace porta 

#endif // _PORTA_APP_CONSOLE_CGI_MAIN_HPP 
