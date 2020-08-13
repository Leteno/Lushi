
#include <string>

#include "Utils.h"

using namespace misc;

int Utils::str2int(const char* str)
{
    try {
        return std::stoi(str);
    } catch (std::exception& e) {
        return -1;
    }
}