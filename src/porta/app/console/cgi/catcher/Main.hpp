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
#include "porta/protocol/http/cgi/environment/variables/Writer.hpp"
#include "porta/protocol/http/form/Writer.hpp"
#include "porta/io/crt/file/Writer.hpp"

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
    MainT(): m_out(*this) {
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
        if (!(err = this->WriteForm(m_out, argc, argv, env))) {
            if (!(err = this->WriteEnvironment(m_out, argc, argv, env))) {
                if (!(err = this->WriteArguments(m_out, argc, argv, env))) {
                    if (!(err = this->WriteInput(m_out, argc, argv, env))) {
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int WriteEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchEnvironmentFileName.Chars())
             && (pattern = this->m_catchEnvironmentFileLabel.Chars())) {
            if ((m_file.OpenSafe(name, pattern))) {
                if (!(err = WriteEnvironment(m_file, argc, argv, env))) {
                }
                m_file.Close();
            }
        }
        return err;
    }
    virtual int WriteArguments(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchArgumentsFileName.Chars())
             && (pattern = this->m_catchArgumentsFileLabel.Chars())) {
            if ((m_file.OpenSafe(name, pattern))) {
                if (!(err = WriteArguments(m_file, argc, argv, env))) {
                }
                m_file.Close();
            }
        }
        return err;
    }
    virtual int WriteForm(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchFormFileName.Chars())
             && (pattern = this->m_catchFormFileLabel.Chars())) {
            if ((m_file.OpenSafe(name, pattern))) {
                if (!(err = WriteForm(m_file, argc, argv, env))) {
                }
                m_file.Close();
            }
        }
        return err;
    }
    virtual int WriteInput(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchInputFileName.Chars())
             && (pattern = this->m_catchInputFileLabel.Chars())) {
            if ((m_file.OpenSafe(name, pattern))) {
                if (!(err = WriteInput(m_file, argc, argv, env))) {
                }
                m_file.Close();
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int WriteEnvironment
    (porta::io::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        if (0 <  (writer.WriteLn(this->m_catchEnvironmentFileLabel.Chars()))) {
            protocol::http::cgi::environment::variables::Writer eWriter(writer);
            eWriter.Write(this->m_environment);
        }
        return err;
    }
    virtual int WriteArguments
    (porta::io::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        if (0 <  (writer.WriteLn(this->m_catchArgumentsFileLabel.Chars()))) {
            porta::console::ArgvWriter aWriter(writer);
            aWriter.Write(this->m_arguments);
        }
        return err;
    }
    virtual int WriteForm
    (porta::io::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        if (0 <  (writer.WriteLn(this->m_catchFormFileLabel.Chars()))) {
            protocol::http::form::Writer fWriter(writer);
            fWriter.Write(this->m_form);
        }
        return err;
    }
    virtual int WriteInput
    (porta::io::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        if (0 <  (writer.WriteLn(this->m_catchInputFileLabel.Chars()))) {
            writer.Write(m_content.elements(), m_content.length());
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnReadContent
    (const what_t* what, const sized_t* sized, size_t size) {
        m_content.Append(sized, size);
    }
    virtual void OnBeginReadContent(size_t size) {
        m_content.set_size(size);
        m_content.set_length(0);
    }
    virtual void OnEndReadContent(size_t size) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    porta::console::OutIOWriter m_out;
    porta::io::crt::file::CharWriter m_file;
    CharArray m_content;
};
typedef MainT<> Main;

} // namespace catcher
} // namespace cgi 
} // namespace console 
} // namespace app 
} // namespace porta 

#endif // _PORTA_APP_CONSOLE_CGI_CATCHER_MAIN_HPP 
