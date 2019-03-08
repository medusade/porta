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

#include "porta/protocol/http/cgi/environment/variables/Writer.hpp"
#include "porta/protocol/http/cgi/environment/variables/Reader.hpp"
#include "porta/protocol/http/cgi/environment/variables/Values.hpp"
#include "porta/protocol/http/cgi/environment/variable/Value.hpp"
#include "porta/protocol/http/cgi/environment/variable/Name.hpp"
#include "porta/protocol/http/cgi/environment/variable/Which.hpp"
#include "porta/protocol/http/message/header/field/Line.hpp"
#include "porta/protocol/http/message/header/field/Name.hpp"
#include "porta/protocol/http/message/header/field/Which.hpp"
#include "porta/protocol/http/content/type/Name.hpp"
#include "porta/protocol/http/content/type/Which.hpp"
#include "porta/protocol/http/content/Reader.hpp"
#include "porta/protocol/http/url/encoded/Reader.hpp"
#include "porta/protocol/http/form/Writer.hpp"
#include "porta/protocol/http/form/Reader.hpp"
#include "porta/protocol/http/form/Fields.hpp"
#include "porta/protocol/http/form/Field.hpp"
#include "porta/io/os/crt/file/Attached.hpp"
#include "porta/io/crt/file/Writer.hpp"
#include "porta/io/crt/file/Reader.hpp"
#include "porta/console/getopt/Main.hpp"

namespace porta {
namespace app {
namespace console {
namespace cgi {

typedef porta::protocol::http::content::ReadObserver MainTContentReadObserver;
typedef porta::console::getopt::MainImplements MainTImplements;
typedef porta::console::getopt::Main MainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TContentReadObserver = MainTContentReadObserver,
 class TImplements = MainTImplements, class TExtends = MainTExtends>
class _EXPORT_CLASS MainT
: virtual public TContentReadObserver,
  virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT()
    : m_cr('\r'), m_lf('\n'),
      m_catchArgumentsFileLabel("arguments"),
      m_catchArgumentsFileName("cgicatch-argv.txt"),
      m_catchEnvironmentFileLabel("environment"),
      m_catchEnvironmentFileName("cgicatch-env.txt"),
      m_catchInputFileLabel("stdin"),
      m_catchInputFileName("cgicatch-stdin.txt"),
      m_catchFormFileLabel("form"),
      m_catchFormFileName("cgicatch-form.txt"),
      m_contentType
      (porta::protocol::http::message::header::field::ContentType,
       porta::protocol::http::content::type::Name::OfWhich
       (porta::protocol::http::content::type::Text)),
      m_outContentType(0),
      m_outWriter(*this)  {
    }
    virtual ~MainT() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = OutForm(argc, argv, env))) {
            if (!(err = OutEnvironment(argc, argv, env))) {
                if (!(err = OutArguments(argc, argv, env))) {
                    if (!(err = OutInput(argc, argv, env))) {
                    }
                }
            }
        }
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
    virtual int OutEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        porta::protocol::http::cgi::environment::variable::Which e;

        this->OutLn();
        this->Out(m_catchEnvironmentFileLabel.Chars());
        this->Out(": ");
        this->OutLn(m_catchEnvironmentFileName.Chars());
        this->OutLn();
        for (e = porta::protocol::http::cgi::environment::variable::First;
             e <= porta::protocol::http::cgi::environment::variable::Last; ++e) {
            const char* name = porta::protocol::http::cgi::environment::variable::Name::OfWhich(e);
            if (name) {
                const char* value = m_environment[e];
                this->Out(name);
                this->Out(" = ");
                if (value) {
                    this->Out("\"");
                    this->Out(value);
                    this->Out("\"");
                } else {
                    this->Out("0");
                }
                this->OutLn();
            }
        }
        return err;
    }
    virtual int OutArguments(int argc, char** argv, char** env) {
        int err = 0;
        const char* chars = 0;
        this->OutLn();
        this->Out(m_catchArgumentsFileLabel.Chars());
        this->Out(": ");
        this->OutLn(m_catchArgumentsFileName.Chars());
        this->OutLn();
        for (int a = 0; a < argc; ++a) {
            this->Out("[");
            this->Out(int_to_string(a).chars());
            this->Out("] = ");
            if ((chars = argv[a])) {
                this->Out("\"");
                this->Out(chars);
                this->OutLn("\"");
            } else {
                this->OutLn("0");
            }
        }
        return err;
    }
    virtual int OutInput(int argc, char** argv, char** env) {
        int err = 0;
        this->OutLn();
        this->Out(m_catchInputFileLabel.Chars());
        this->Out(": ");
        this->OutLn(m_catchInputFileName.Chars());
        this->OutLn();
        return err;
    }
    virtual int OutForm(int argc, char** argv, char** env) {
        int err = 0;
        porta::protocol::http::form::Fields::const_iterator e, i;

        this->OutLn();
        this->Out(m_catchFormFileLabel.Chars());
        this->Out(": ");
        this->OutLn(m_catchFormFileName.Chars());
        this->OutLn();
        for (e = m_form.end(), i = m_form.begin(); i != e; ++i) {
            const porta::protocol::http::form::Field& f = (*i);
            const char *name = 0, *value = 0;
            if ((name = f.Name().HasChars()) && (value = f.Value().Chars())) {
                this->Out(name);
                this->Out(" = \"");
                this->Out(value);
                this->OutLn("\"");
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
            if ((this->FileWriter().OpenSafe(name, pattern))) {
                if (!(err = WriteEnvironment(this->FileWriter(), argc, argv, env))) {
                }
                this->FileWriter().Close();
            }
        }
        return err;
    }
    virtual int WriteArguments(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchArgumentsFileName.Chars())
             && (pattern = this->m_catchArgumentsFileLabel.Chars())) {
            if ((this->FileWriter().OpenSafe(name, pattern))) {
                if (!(err = WriteArguments(this->FileWriter(), argc, argv, env))) {
                }
                this->FileWriter().Close();
            }
        }
        return err;
    }
    virtual int WriteForm(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchFormFileName.Chars())
             && (pattern = this->m_catchFormFileLabel.Chars())) {
            if ((this->FileWriter().OpenSafe(name, pattern))) {
                if (!(err = WriteForm(this->FileWriter(), argc, argv, env))) {
                }
                this->FileWriter().Close();
            }
        }
        return err;
    }
    virtual int WriteInput(int argc, char** argv, char** env) {
        int err = 0;
        const char *name = 0, *pattern = 0;
        if ((name = this->m_catchInputFileName.Chars())
             && (pattern = this->m_catchInputFileLabel.Chars())) {
            if ((this->FileWriter().OpenSafe(name, pattern))) {
                if (!(err = WriteInput(this->FileWriter(), argc, argv, env))) {
                }
                this->FileWriter().Close();
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
            writer.Write(this->Content().elements(), this->Content().length());
        }
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
    virtual int CgiFormRun(int argc, char** argv, char** env) {
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
    virtual int ConsoleFormRun(int argc, char_t** argv, char_t** env) {
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
                if (!(err = GetArgv(argc, argv, env))) {
                    if (!(err = BeforeGetContent(argc, argv, env))) {
                        if (!(err = CgiFormRun(argc, argv, env))) {
                        }
                        if ((err2 = AfterGetContent(argc, argv, env)) && (!err)) {
                            err = err2;
                        }
                    }
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
                if (!(err = ReadArgv(argc, argv, env))) {
                    if (!(err = BeforeReadContent(argc, argv, env))) {
                        if (!(err = ConsoleFormRun(argc, argv, env))) {
                        }
                        if ((err2 = AfterReadContent(argc, argv, env)) && (!err)) {
                            err = err2;
                        }
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
    virtual int GetArgv(int argc, char** argv, char** env) {
        int err = 0;
        m_arguments.Assign(argc, argv);
        return err;
    }
    virtual int ReadArgv(int argc, char** argv, char** env) {
        int err = 0;
        m_arguments.Assign(argc, argv);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        m_environment.Get();
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
        const char* chars = 0;
        if ((chars = m_catchEnvironmentFileName.HasChars())) {
            io::crt::file::Reader reader;
            if ((reader.Open(chars))) {
                if (0 < (reader.ReadLn())) {
                    protocol::http::cgi::environment::variables::Reader eReader;
                    eReader.Read(m_environment, reader);
                }
                reader.Close();
            }
        }
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
    virtual int BeforeGetContent(int argc, char** argv, char** env) {
        int err = 0;
        m_fileReader.Attach(this->StdIn());
        return err;
    }
    virtual int AfterGetContent(int argc, char** argv, char** env) {
        int err = 0;
        m_fileReader.Detach();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeReadContent(int argc, char** argv, char** env) {
        int err = 0;
        if ((m_fileReader.Open(m_catchInputFileName.Chars()))) {
            if (0 >= (m_fileReader.ReadLn())) {
                m_fileReader.Close();
            }
        }
        return err;
    }
    virtual int AfterReadContent(int argc, char** argv, char** env) {
        int err = 0;
        m_fileReader.Close();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadForm(int argc, char** argv, char** env) {
        int err = 0;
        m_form.clear();
        if (!(err = ReadQueryFormData(argc, argv, env))) {
            if (!(err = ReadFormData(argc, argv, env))) {
            }
        }
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
        protocol::http::cgi::environment::variable::Value& queryString
        = m_environment[protocol::http::cgi::environment::variable::QUERY_STRING];
        const char* chars = 0;
        size_t length = 0;
        int err = 0;
        if (!(chars)) {
            chars = queryString.HasValue(length);
        }
        if ((chars)) {
            io::CharsReader charsReader(chars, length);
            protocol::http::url::encoded::Reader encodedReader(charsReader);
            protocol::http::form::Reader formReader(m_form);
            formReader.ReadMore(encodedReader);
        }
        return err;
    }
    virtual int ReadFormData(int argc, char** argv, char** env) {
        protocol::http::cgi::environment::variable::Value& contentLength
        = m_environment[protocol::http::cgi::environment::variable::CONTENT_LENGTH];
        const char* chars = 0;
        size_t length = 0;
        int err = 0;
        if ((chars = contentLength.HasValue(length))) {
            if (0 < (length = Chars::ToUnsigned(chars, length))) {
                err = ReadFormData(length, argc, argv, env);
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadFormData
    (size_t contentLength, int argc, char** argv, char** env) {
        protocol::http::cgi::environment::variable::Value& contentType
        = m_environment[protocol::http::cgi::environment::variable::CONTENT_TYPE];
        const char* chars = 0;
        size_t length = 0;
        int err = 0;

        if ((chars = contentType.HasValue(length))) {
            protocol::http::content::type::Which which
            = protocol::http::content::type::Name::WhichOf(chars);

            switch(which) {
            case protocol::http::content::type::UrlEncodedFormData:
                CRONO_LOG_DEBUG("ReadUrlencodedFormData(contentLength = " << contentLength << ", argc, argv, env)...");
                err = ReadUrlencodedFormData(contentLength, argc, argv, env);
                break;

            case protocol::http::content::type::MultipartFormData:
                CRONO_LOG_DEBUG("ReadMutipartFormData(contentLength = " << contentLength << ", argc, argv, env)...");
                err = ReadMultipartFormData(contentLength, argc, argv, env);
                break;
            }
        }
        return err;
    }
    virtual int BeforeReadFormData
    (size_t contentLength, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterReadFormData
    (size_t contentLength, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadUrlencodedFormData
    (size_t contentLength, int argc, char** argv, char** env) {
        porta::protocol::http::content::Reader charsReader(*this, m_fileReader, contentLength);
        protocol::http::url::encoded::Reader encodedReader(charsReader);
        protocol::http::form::Reader formReader(m_form);
        int err = 0;
        this->OnBeginReadContent(contentLength);
        formReader.ReadMore(encodedReader);
        this->OnEndReadContent(contentLength);
        return err;
    }
    virtual int ReadMultipartFormData
    (size_t contentLength, int argc, char_t** argv, char_t** env) {
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
    virtual const char* SetContentTypeToText() {
        const char* to = porta::protocol::http::content::type::Name::OfWhich
          (porta::protocol::http::content::type::Text);
        return SetContentType(to);
    }
    virtual const char* SetContentTypeToHtml() {
        const char* to = porta::protocol::http::content::type::Name::OfWhich
          (porta::protocol::http::content::type::Html);
        return SetContentType(to);
    }
    virtual const char* SetContentTypeToXml() {
        const char* to = porta::protocol::http::content::type::Name::OfWhich
          (porta::protocol::http::content::type::Xml);
        return SetContentType(to);
    }
    virtual const char* SetContentType(const char* to) {
        if ((to) && (to[0])) {
            m_contentType.SetValue(to);
        }
        return m_contentType.Value().Chars();
    }
    virtual const char* OutContentType() {
        if (!(m_outContentType)) {
            size_t length = 0;
            if ((m_outContentType = m_contentType.HasChars(length))) {
                this->Out(m_outContentType, length);
                this->OutLn();
            }
        }
        return m_outContentType;
    }
    virtual FILE* OutStdOut() {
        this->OutContentType();
        return this->StdOut();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetFileModeIsBinary
    (FILE* file, bool modeIsBinary = true) const {
        if (file) {
            io::os::crt::file::Attached f(file);
            if (f.SetModeIsBinary()) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    const char* FindFormValue(const char* name) const {
        return m_form.FindValue(name);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual porta::console::OutIOWriter& OutWriter() const {
        return (porta::console::OutIOWriter&)m_outWriter;
    }
    virtual porta::io::crt::file::CharWriter& FileWriter() const {
        return (porta::io::crt::file::CharWriter&)m_fileWriter;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharArray& Content() const {
        return (CharArray&)m_content;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char m_cr, m_lf;
    CharString m_catchArgumentsFileLabel, m_catchArgumentsFileName,
               m_catchEnvironmentFileLabel, m_catchEnvironmentFileName,
               m_catchInputFileLabel, m_catchInputFileName,
               m_catchFormFileLabel, m_catchFormFileName;
    porta::protocol::http::message::header::field::Line m_contentType;
    const char* m_outContentType;
    porta::console::OutIOWriter m_outWriter;
    porta::io::crt::file::CharWriter m_fileWriter;
    porta::io::crt::file::Reader m_fileReader;
    porta::protocol::http::form::Fields m_form;
    porta::protocol::http::cgi::environment::variables::Values m_environment;
    porta::console::Argv m_arguments;
    CharArray m_content;
};
typedef MainT<> Main;

} // namespace cgi
} // namespace console 
} // namespace app 
} // namespace porta 

#endif // _PORTA_APP_CONSOLE_CGI_MAIN_HPP 
