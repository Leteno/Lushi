#pragma once

#include <list>
#include <string>

namespace StringSeperator {
    std::list<std::string> split(const char* str, const char* seperators);
}
