
#include <list>
#include <string>
#include <string.h>

#include "StringSeperator.h"

static bool notIn(const char* datas, int len, char test)
{
    for (int i = 0; i < len; i++)
    {
        if (datas[i] == test)
        {
            return false;
        }
    }
    return true;
}

std::list<std::string> StringSeperator::split(char* const str, char* const seperators)
{
    std::list<std::string> ret;

    int sepLen = strlen(seperators);

    char* pStart = str;
    int len = 0;
    while (*pStart)
    {
        // skip the seperator from beginning
        len = 0;
        while (*(pStart + len) && !notIn(seperators, sepLen, *(pStart + len)))
            ++len;
        pStart += len;

        // counting the chars before meet seperator
        len = 0;
        while (*(pStart + len) && notIn(seperators, sepLen, *(pStart + len)))
            ++len;

        ret.push_back(std::string(pStart, len));
        pStart += len;
    }

    return ret;
}
