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
#ifndef _PORTA_CONSOLE_MAIN_HPP
#define _PORTA_CONSOLE_MAIN_HPP

#include "porta/base/Base.hpp"
#include "crono/console/Main.hpp"

namespace porta {
namespace console {

typedef crono::console::Main Main;
typedef crono::console::InIOReader InIOReader;
typedef crono::console::OutIOWriter OutIOWriter;
typedef crono::console::IO IO;

typedef crono::console::Argv Argv;
typedef crono::console::ArgvWriter ArgvWriter;

} // namespace console
} // namespace porta 

#endif // _PORTA_CONSOLE_MAIN_HPP 
        

