#pragma once

#include "wlang.hpp"

const char * const regexStrings[]= {
    "^Say\\s", // 0 - Print statement 
    "^Let\\s", // 1 - Declaration
    "^Store\\s", // 2 - Assignment
};

const std::map<string, regex> regexEscape= {
    {string("\""), regex("\\\\\"")},
    {string("\n"), regex("\\\\n")},
    {string("\\"), regex("\\\\\\\\")},
    {string("\r"), regex("\\\\r")},
    {string("\t"), regex("\\\\t")}
};