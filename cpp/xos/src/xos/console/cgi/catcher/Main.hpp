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
///   Date: 10/7/2017
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CONSOLE_CGI_CATCHER_MAIN_HPP
#define _XOS_CONSOLE_CGI_CATCHER_MAIN_HPP

#include "xos/console/cgi/Main.hpp"

namespace xos {
namespace console {
namespace cgi {
namespace catcher {

typedef console::cgi::MainImplements MainImplements;
typedef console::cgi::Main MainExtends;
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
    MainT(): m_fileReaderAttached(0), m_fileWriterAttached(0) {
    }
    virtual ~MainT() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OutResponse(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = this->WriteEnvironment(argc, argv, env))) {
            if (!(err = this->WriteArguments(argc, argv, env))) {
                if (!(err = this->WriteForm(argc, argv, env))) {
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::WriteEnvironment;
    virtual int WriteEnvironment(int argc, char** argv, char** env) {
        int err = 0;
        io::crt::file::CharWriter& writer = m_fileWriter;
        if (!(err = this->BeforeWriteEnvironment(writer, argc, argv, env))) {
            int err2 = 0;
            if ((err2 = this->WriteEnvironment(writer, argc, argv, env))) {
                if (!err) err = err2;
            }
            if ((err2 = this->AfterWriteEnvironment(writer, argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeWriteEnvironment
    (io::crt::file::CharWriter& writer, int argc, char** argv, char** env) {
        String &name = this->m_catchEnvName, &label = this->m_catchEnvLabel;
        int err = 0;
        FILE* attached = 0;
        if ((attached = writer.AttachedTo()) && (!m_fileWriterAttached)) {
            m_fileWriterAttached = attached;
            XOS_LOG_DEBUG("writer.OpenPatterned(name = \"" << name << "\", label = \"" << label << "\")...");
            if (!(writer.OpenPatterned(name, label))) {
                XOS_LOG_DEBUG("...failed on writer.OpenPatterned(name = \"" << name << "\", label = \"" << label << "\")");
                writer.Attach(m_fileWriterAttached);
                m_fileWriterAttached = 0;
            }
        }
        return err;
    }
    virtual int AfterWriteEnvironment
    (io::crt::file::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        FILE* attached = 0;
        if ((attached = writer.AttachedTo()) && (m_fileWriterAttached)) {
            if ((m_fileWriterAttached != attached)) {
                writer.Closed();
                writer.Attach(m_fileWriterAttached);
            }
            m_fileWriterAttached = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::WriteArguments;
    virtual int WriteArguments(int argc, char** argv, char** env) {
        int err = 0;
        io::crt::file::CharWriter& writer = m_fileWriter;
        if (!(err = this->BeforeWriteArguments(writer, argc, argv, env))) {
            int err2 = 0;
            if ((err2 = this->WriteArguments(writer, argc, argv, env))) {
                if (!err) err = err2;
            }
            if ((err2 = this->AfterWriteArguments(writer, argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeWriteArguments
    (io::crt::file::CharWriter& writer, int argc, char** argv, char** env) {
        String &name = this->m_catchArgvName, &label = this->m_catchArgvLabel;
        int err = 0;
        FILE* attached = 0;
        if ((attached = writer.AttachedTo()) && (!m_fileWriterAttached)) {
            m_fileWriterAttached = attached;
            XOS_LOG_DEBUG("writer.OpenPatterned(name = \"" << name << "\", label = \"" << label << "\")...");
            if (!(writer.OpenPatterned(name, label))) {
                XOS_LOG_DEBUG("...failed on writer.OpenPatterned(name = \"" << name << "\", label = \"" << label << "\")");
                writer.Attach(m_fileWriterAttached);
                m_fileWriterAttached = 0;
            }
        }
        return err;
    }
    virtual int AfterWriteArguments
    (io::crt::file::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        FILE* attached = 0;
        if ((attached = writer.AttachedTo()) && (m_fileWriterAttached)) {
            if ((m_fileWriterAttached != attached)) {
                writer.Closed();
                writer.Attach(m_fileWriterAttached);
            }
            m_fileWriterAttached = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::WriteForm;
    virtual int WriteForm(int argc, char** argv, char** env) {
        int err = 0;
        io::crt::file::CharWriter& writer = m_fileWriter;
        if (!(err = this->BeforeWriteForm(writer, argc, argv, env))) {
            int err2 = 0;
            if ((err2 = this->WriteForm(writer, argc, argv, env))) {
                if (!err2) err = err2;
            }
            if ((err2 = this->AfterWriteForm(writer, argc, argv, env))) {
                if (!err2) err = err2;
            }
        }
        return err;
    }
    virtual int BeforeWriteForm
    (io::crt::file::CharWriter& writer, int argc, char** argv, char** env) {
        String &name = this->m_catchFormName, &label = this->m_catchFormLabel;
        int err = 0;
        FILE* attached = 0;
        if ((attached = writer.AttachedTo()) && (!m_fileWriterAttached)) {
            m_fileWriterAttached = attached;
            XOS_LOG_DEBUG("writer.OpenPatterned(name = \"" << name << "\", label = \"" << label << "\")...");
            if (!(writer.OpenPatterned(name, label))) {
                XOS_LOG_DEBUG("...failed on writer.OpenPatterned(name = \"" << name << "\", label = \"" << label << "\")");
                writer.Attach(m_fileWriterAttached);
                m_fileWriterAttached = 0;
            }
        }
        return err;
    }
    virtual int AfterWriteForm
    (io::crt::file::CharWriter& writer, int argc, char** argv, char** env) {
        int err = 0;
        FILE* attached = 0;
        if ((attached = writer.AttachedTo()) && (m_fileWriterAttached)) {
            if ((m_fileWriterAttached != attached)) {
                writer.Closed();
                writer.Attach(m_fileWriterAttached);
            }
            m_fileWriterAttached = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    FILE *m_fileReaderAttached, *m_fileWriterAttached;
    io::crt::file::CharWriter m_fileWriter;
};
typedef  MainT<> Main;

} // namespace catcher
} // namespace cgi 
} // namespace console 
} // namespace xos 

#endif // _XOS_CONSOLE_CGI_CATCHER_MAIN_HPP
