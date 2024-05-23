#pragma once

#include <neonc.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

namespace neonc {
    const std::string get_cwd(); 
    const std::string get_root();
}
