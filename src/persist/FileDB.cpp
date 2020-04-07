
#include <stdio.h>
#include <sstream>

#include "FileDB.h"

using namespace persist;

void FileDB::saveToFile(std::string name, std::string content, int * retCode)
{
    FILE *fd = fopen(name.c_str(), "w");
    if (!fd)
    {
        *retCode = -1;
        return;
    }

    int writed = fwrite(content.c_str(), sizeof(char), content.length(), fd);
    *retCode = writed == content.length() ? 0 : -2;
    fclose(fd);
}

std::string FileDB::readFromFile(std::string name, int *retCode)
{
    FILE *fd = fopen(name.c_str(), "r");
    if (!fd)
    {
        *retCode = -1;
        return "";
    }
    std::stringstream ss;

    const int BUF_SIZE = 16;
    char buffer[BUF_SIZE];
    int read = 0;
    while((read = fread(buffer, sizeof(char), BUF_SIZE, fd)) != 0)
    {
        if (read < BUF_SIZE)
            ss << std::string(buffer, read);
        else
            ss << buffer;
    }

    fclose(fd);

    return ss.str();
}