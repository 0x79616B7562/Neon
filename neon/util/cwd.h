#pragma once

#include <stdio.h>
#include <filesystem>
#include <regex>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif
#include <string>

const std::string get_cwd(); 
const std::string get_root();
