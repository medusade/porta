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
///   Date: 9/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CONSOLE_CGI_MAIN_HPP
#define _XOS_CONSOLE_CGI_MAIN_HPP

#include "xos/console/cgi/MainOpt.hpp"
#include "xos/console/getopt/Main.hpp"
#include "xos/protocol/http/cgi/environment/variables/Reader.hpp"
#include "xos/protocol/http/cgi/environment/variables/Values.hpp"
#include "xos/protocol/http/form/Fields.hpp"
#include "xos/protocol/http/content/type/header/Field.hpp"
#include "xos/protocol/http/url/encoded/Reader.hpp"
#include "xos/io/microsoft/windows/crt/file/Attached.hpp"
#include "xos/io/crt/file/Reader.hpp"

namespace xos {
namespace console {
namespace cgi {

typedef console::getopt::MainImplements MainImplements;
typedef console::getopt::Main MainExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TOptImplements = MainOpt,
 class TImplements = MainImplements, class TExtends = MainExtends>

class _EXPORT_CLASS MainT
: virtual public TOptImplements,
  virtual public TImplements, public TExtends {
public:
    typedef TOptImplements OptImplements;
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    /// Constructor: MainT
    ///////////////////////////////////////////////////////////////////////
    MainT()
    : m_catchArgvLabel("arguments"), m_catchArgvName("cgicatch-argv.txt"),
      m_catchEnvLabel("environment"), m_catchEnvName("cgicatch-env.txt"),
      m_catchInLabel("stdin"), m_catchInName("cgicatch-stdin.txt"),
      m_catchFormLabel("form"), m_catchFormName("cgicatch-form.txt"),
      m_contentType(0), m_outContentType(0) {
    }
    virtual ~MainT() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OutResponse(int argc, char** argv, char** env) {
        int err = 0;
        //this->OutL("\r\nHello ", m_gatewayInterface.Chars(), "\r\n", NULL);
        this->OutForm(argc, argv, env);
        this->OutEnvironment(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OutForm(int argc, char** argv, char** env) {
        int err = 0;
        const char *nameChars = 0, *valueChars = 0;
        const protocol::http::form::Field* f = 0;
        protocol::http::form::Fields::const_iterator e, i;

        for (e = m_form.End(), i = m_form.Begin(); i != e; ++i) {
            if ((f = (*i))) {
                const protocol::xttp::message::Part& name = f->Name();
                const protocol::xttp::message::Part& value = f->Value();

                if ((nameChars = name.HasChars()) && (valueChars = value.Chars())) {
                    this->OutL(nameChars, " = \"", valueChars, "\"", NULL);
                    this->OutLn();
                }
            }
        }
        this->OutLn();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OutEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        protocol::http::cgi::environment::variable::Which e;

        for (e = protocol::http::cgi::environment::variable::First;
             e <= protocol::http::cgi::environment::variable::Last; ++e) {
            const char* name = protocol::http::cgi::environment::variable::Name::OfWhich(e);

            if (name) {
                const char* value = m_environment[e];

                this->OutL(name, " = ", NULL);
                if (value) {
                    this->OutL("\"", value, "\"", NULL);
                } else {
                    this->Out("0");
                }
                this->OutLn();
            }
        }
        this->OutLn();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;
        err = this->OutResponse(argc, argv, env);
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

        if (!(err = this->BeforeRunCgi(argc, argv, env))) {

            err = this->RunCgi(argc, argv, env);

            if ((err2 = this->AfterRunCgi(argc, argv, env))) {
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
                    if ((err2 = AfterRunCgi(argc, argv, env))) {
                        if (!err) err = err2;
                    }
                }
            }
            if ((err2 = AfterReadForm(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeCgiFormRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;

        if (!(err = BeforeGetEnvironment(argc, argv, env))) {

            if (!(err = GetEnvironment(argc, argv, env))) {

                if (!(err = BeforeGetArgv(argc, argv, env))) {

                    if (!(err = GetArgv(argc, argv, env))) {

                        if (!(err = BeforeGetContent(argc, argv, env))) {
                        }
                    }
                    if ((err2 = AfterGetArgv(argc, argv, env))) {
                        if (!err) err = err2;
                    }
                }
            }
            if ((err2 = AfterGetEnvironment(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int AfterCgiFormRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if (!(err = AfterGetContent(argc, argv, env))) {
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ConsoleFormRun(int argc, char_t** argv, char_t** env) {
        int err = 0, err2 = 0;

        if (!(err = BeforeReadForm(argc, argv, env))) {

            if (!(err = ReadForm(argc, argv, env))) {

                if (!(err = BeforeRunConsole(argc, argv, env))) {

                    if ((err = RunConsole(argc, argv, env))) {
                    }
                    if ((err2 = AfterRunConsole(argc, argv, env))) {
                        if (!err) err = err2;
                    }
                }
            }
            if ((err2 = AfterReadForm(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeConsoleFormRun(int argc, char_t** argv, char_t** env) {
        int err = 0, err2 = 0;

        if (!(err = BeforeReadEnvironment(argc, argv, env))) {

            if (!(err = ReadEnvironment(argc, argv, env))) {

                if (!(err = BeforeReadArgv(argc, argv, env))) {

                    if (!(err = ReadArgv(argc, argv, env))) {

                        if (!(err = BeforeReadContent(argc, argv, env))) {
                        }
                    }
                    if ((err2 = AfterReadArgv(argc, argv, env))) {
                        if (!err) err = err2;
                    }
                }
            }
            if ((err2 = AfterReadEnvironment(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int AfterConsoleFormRun(int argc, char_t** argv, char_t** env) {
        int err = 0, err2 = 0;
        if (!(err = AfterReadContent(argc, argv, env))) {
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int CgiRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;

        if (!(err = BeforeCgiFormRun(argc, argv, env))) {

            err = CgiFormRun(argc, argv, env);

            if ((err2 = AfterCgiFormRun(argc, argv, env))) {
                if (!err) err = err2;
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

        if (!(err = BeforeConsoleFormRun(argc, argv, env))) {

            err = ConsoleFormRun(argc, argv, env);

            if ((err2 = AfterConsoleFormRun(argc, argv, env))) {
                if (!err) err = err2;
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
    virtual int CgiOrConsoleRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;

        if ((this->GetEnvGatewayInterface(argc, argv, env))) {

            if (!(err = this->BeforeCgiRun(argc, argv, env))) {

                err = this->CgiRun(argc, argv, env);

                if ((err2 = this->AfterCgiRun(argc, argv, env))) {
                    if (!err) err = err2;
                }
            }
        } else {
            if (!(err = this->BeforeConsoleRun(argc, argv, env))) {

                err = this->ConsoleRun(argc, argv, env);

                if ((err2 = this->AfterConsoleRun(argc, argv, env))) {
                    if (!err) err = err2;
                }
            }
        }
        return err;
    }
    virtual int BeforeCgiOrConsoleRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        return err;
    }
    virtual int AfterCgiOrConsoleRun(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;

        if (!(err = this->BeforeCgiOrConsoleRun(argc, argv, env))) {

            err = this->CgiOrConsoleRun(argc, argv, env);

            if ((err2 = this->AfterCgiOrConsoleRun(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }

    ///
    /// Get
    ///

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char*
    GetEnvGatewayInterface(int argc, char** argv, char** env) {
        const char* chars = 0;
        protocol::http::cgi::environment::variable::Value
            gatewayInterface(protocol::http::cgi::environment::variable::GATEWAY_INTERFACE);

        if ((chars = gatewayInterface.HasValue()) && (chars[0])) {
            m_gatewayInterface.Assign(chars);
            chars = m_gatewayInterface.HasChars();
            return chars;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int GetEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        m_environment.GetAll();
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
    virtual int GetArgv(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeGetArgv(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterGetArgv(int argc, char** argv, char** env) {
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

    ///
    /// Read
    ///

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        const char* chars = 0;
        size_t length = 0;

        XOS_LOG_DEBUG("m_catchEnvName.HasChars(length)...");
        if ((chars = m_catchEnvName.HasChars(length))) {
            io::crt::file::CharReader reader;

            XOS_LOG_DEBUG("...\"" << chars << "\" = m_catchEnvName.HasChars(length = " << length << ")...");
            XOS_LOG_DEBUG("reader.Open(chars = \"" << chars << "\")...");
            if ((reader.Open(chars))) {
                XOS_LOG_DEBUG("...reader.Open(chars = \"" << chars << "\")");
                XOS_LOG_DEBUG("reader.ReadLn()...");
                if (0 < (reader.ReadLn())) {
                    protocol::http::cgi::environment::variables::Reader environment(m_environment);
                    ssize_t count = 0;

                    XOS_LOG_DEBUG("...reader.ReadLn()");
                    XOS_LOG_DEBUG("environment.Read(count, reader)...");
                    if ((environment.Read(count, reader))) {
                        XOS_LOG_DEBUG("...environment.Read(count = " << count << ", reader)");
                    } else {
                        XOS_LOG_ERROR("...failed on environment.Read(count = " << count << ", reader)");
                    }
                } else {
                    XOS_LOG_ERROR("...failed on reader.ReadLn()");
                }
                XOS_LOG_DEBUG("reader.Close()...");
                if ((reader.Close())) {
                    XOS_LOG_DEBUG("...reader.Close()");
                } else {
                    XOS_LOG_ERROR("...failed on reader.Close()");
                }
            } else {
                XOS_LOG_ERROR("...failed on reader.Open(chars = \"" << chars << "\")");
            }
        } else {
            XOS_LOG_DEBUG("...0 = m_catchEnvName.HasChars(length)...");
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
    virtual int ReadArgv(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeReadArgv(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterReadArgv(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeReadContent(int argc, char** argv, char** env) {
        int err = 0;
        XOS_LOG_DEBUG("m_fileReader.Open(m_catchInName = \"" << m_catchInName << "\")...");
        if ((m_fileReader.Open(m_catchInName))) {
            XOS_LOG_DEBUG("...m_fileReader.Open(m_catchInName = \"" << m_catchInName << "\")");
            XOS_LOG_DEBUG("m_fileReader.ReadLn()...");
            if (0 >= (m_fileReader.ReadLn())) {
                XOS_LOG_ERROR("...failed on m_fileReader.ReadLn()");
                m_fileReader.Close();
            } else {
                XOS_LOG_DEBUG("...m_fileReader.ReadLn()");
            }
        } else {
            XOS_LOG_ERROR("...failed on m_fileReader.Open(m_catchInName = \"" << m_catchInName << "\")");
        }
        return err;
    }
    virtual int AfterReadContent(int argc, char** argv, char** env) {
        int err = 0;
        XOS_LOG_DEBUG("m_fileReader.Closed()...");
        if ((m_fileReader.Closed())) {
            XOS_LOG_DEBUG("...m_fileReader.Closed()");
        } else {
            XOS_LOG_ERROR("...failed on m_fileReader.Closed()");
        }
        return err;
    }

    ///
    /// ReadForm
    ///

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ReadForm(int argc, char** argv, char** env) {
        int err = 0;

        m_form.Clear();
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

        XOS_LOG_DEBUG("queryString.HasValue(length)...");
        if ((chars = queryString.HasValue(length))) {
            io::CharsReader charsReader(chars, length);
            protocol::http::url::encoded::CharReader encodedReader(charsReader);
            ssize_t count = 0;
            char c = 0;

            XOS_LOG_DEBUG("...\"" << chars << "\" = queryString.HasValue(length = " << length << ")");
            XOS_LOG_DEBUG("m_form.ReadMore(count, c, encodedReader)...");
            if ((m_form.ReadMore(count, c, encodedReader))) {
                XOS_LOG_DEBUG("...m_form.ReadMore(count = " << count << ", c, encodedReader)...");
            } else {
                XOS_LOG_DEBUG("...failed on m_form.ReadMore(count = " << count << ", c, encodedReader)...");
            }
        } else {
            XOS_LOG_DEBUG("...0 = queryString.HasValue(length)");
        }
        return err;
    }
    virtual int ReadFormData(int argc, char** argv, char** env) {
        protocol::http::cgi::environment::variable::Value& contentLength
        = m_environment[protocol::http::cgi::environment::variable::CONTENT_LENGTH];
        const char* chars = 0;
        size_t length = 0;
        int err = 0;

        XOS_LOG_DEBUG("contentLength.HasValue(length)...");
        if ((chars = contentLength.HasValue(length))) {
            size_t contentLen = 0;

            XOS_LOG_DEBUG("...\"" << chars << "\" = contentLength.HasValue(length = " << length << ")");
            XOS_LOG_DEBUG("CharsBase::to_unsigned(chars = \"" << chars << "\", length = " << length << ")...");
            if (0 < (contentLen = CharsBase::to_unsigned(chars, length))) {
                XOS_LOG_DEBUG("..." << contentLen << " = CharsBase::to_unsigned(chars = \"" << chars << "\", length = " << length << ")");
                err = ReadFormData(contentLen, argc, argv, env);
            } else {
                XOS_LOG_DEBUG("...failed " << contentLen << " = CharsBase::to_unsigned(chars = \"" << chars << "\", length = " << length << ")");
            }
        } else {
            XOS_LOG_DEBUG("...0 = contentLength.HasValue(length)");
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

        XOS_LOG_DEBUG("contentType.HasValue(length)...");
        if ((chars = contentType.HasValue(length))) {
            protocol::http::content::type::Which which
            = protocol::http::content::type::Name::WhichOf(chars);

            XOS_LOG_DEBUG("...\"" << chars << "\" = contentType.HasValue(length = " << length << ")");
            switch(which) {
            case protocol::http::content::type::UrlEncodedFormData:
                XOS_LOG_DEBUG("ReadUrlencodedFormData(contentLength = " << contentLength << ", argc, argv, env)...");
                err = ReadUrlencodedFormData(contentLength, argc, argv, env);
                break;

            case protocol::http::content::type::MultipartFormData:
                XOS_LOG_DEBUG("ReadMutipartFormData(contentLength = " << contentLength << ", argc, argv, env)...");
                err = ReadMultipartFormData(contentLength, argc, argv, env);
                break;
            }
        } else {
            XOS_LOG_DEBUG("...0 = contentType.HasValue(length)");
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
        int err = 0;
        io::SizedCharReader charsReader(m_fileReader, contentLength);
        protocol::http::url::encoded::CharReader encodedReader(charsReader);
        ssize_t count = 0;
        char c = 0;

        XOS_LOG_DEBUG("m_form.ReadMore(count, c, encodedReader)...");
        if ((m_form.ReadMore(count, c, encodedReader))) {
            XOS_LOG_DEBUG("...m_form.ReadMore(count = " << count << ", c, encodedReader)...");
        } else {
            XOS_LOG_DEBUG("...failed on m_form.ReadMore(count = " << count << ", c, encodedReader)...");
        }
        return err;
    }
    virtual int ReadMultipartFormData
    (size_t contentLength, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///
    ///
    ///

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const protocol::http::content::type::header::Field* SetContentTypeToText() {
        const protocol::http::content::type::header::Field* to = 0;
        if ((to = SetContentType(&m_contentTypeText))) {
            return to;
        }
        return 0;
    }
    virtual const protocol::http::content::type::header::Field* SetContentTypeToHtml() {
        const protocol::http::content::type::header::Field* to = 0;
        if ((to = SetContentType(&m_contentTypeHtml))) {
            return to;
        }
        return 0;
    }
    virtual const protocol::http::content::type::header::Field* SetContentTypeToXml() {
        const protocol::http::content::type::header::Field* to = 0;
        if ((to = SetContentType(&m_contentTypeXml))) {
            return to;
        }
        return 0;
    }
    virtual const protocol::http::content::type::header::Field*
    SetContentType(const protocol::http::content::type::header::Field* to) {
        if ((to) && (to->HasChars())) {
            m_contentType = to;
            return m_contentType;
        }
        return 0;
    }
    virtual const protocol::http::content::type::header::Field* OutContentType() {
        if (!(m_outContentType) && !(m_contentType)) {
            m_contentType = DefaultContentType();
        }
        if (!(m_outContentType) && (m_contentType)) {
            const char* chars = 0;
            size_t length = 0;

            if ((chars = m_contentType->HasChars(length))) {
                FILE* stdOut = 0;
                m_outContentType = m_contentType;
                if ((stdOut = this->StdOut())) {
                    this->Out(stdOut, chars, length);
                    this->Out(stdOut, "\r\n");
                }
            }
        }
        return m_outContentType;
    }
    virtual const protocol::http::content::type::header::Field* DefaultContentType() {
        return &m_contentTypeText;
    }
    virtual bool OutHeaders() {
        if (!(m_outContentType)) {
            if ((this->OutContentType())) {
                FILE* stdOut = 0;
                if ((stdOut = this->StdOut())) {
                    this->Out(stdOut, "\r\n");
                    return true;
                }
            }
            return false;
        }
        return true;
    }
    virtual FILE* OutStdOut() {
        if ((this->OutHeaders())) {
            return this->StdOut();
        }
        return 0;
    }


    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetFileModeIsBinary(FILE* file, bool to = true) const {
        if (file) {
            io::microsoft::windows::crt::file::Attached f(file);
            if (f.SetModeIsBinary(to)) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_catchArgvLabel, m_catchArgvName,
           m_catchEnvLabel, m_catchEnvName,
           m_catchInLabel, m_catchInName,
           m_catchFormLabel, m_catchFormName;
    const protocol::http::content::type::header::Field *m_contentType, *m_outContentType;
    const protocol::http::content::type::text::header::Field m_contentTypeText;
    const protocol::http::content::type::html::header::Field m_contentTypeHtml;
    const protocol::http::content::type::xml::header::Field m_contentTypeXml;
    const protocol::http::content::type::octetstream::header::Field m_contentTypeOctetStream;
    const protocol::http::content::type::urlencodedformdata::header::Field m_contentTypeUrlEncodedFormData;
    const protocol::http::content::type::multipartformdata::header::Field m_contentTypeMultipartFormData;
    protocol::http::cgi::environment::variables::Values m_environment;
    protocol::http::form::Fields m_form;
    io::crt::file::CharReader m_fileReader;
    String m_gatewayInterface;
};
typedef  MainT<> Main;

} // namespace cgi
} // namespace console 
} // namespace xos 

#endif // _XOS_CONSOLE_CGI_MAIN_HPP
