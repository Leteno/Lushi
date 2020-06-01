
#include "malloc.h"
#include <stdio.h>

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

    int current_size = 1024;
    char *buffer = (char*) malloc(current_size * sizeof(char));
    if (!buffer)
    {
        *retCode = -2;
        return "";
    }
    int read_size = 16;
    int used_size = 0;
    int read = 0;
    while((read = fread(buffer + used_size, sizeof(char), read_size, fd)) != 0)
    {
        used_size += read;
        if (read < read_size)
        {
            // this is finish.
            break;
        }
        if (current_size < used_size + read_size)
        {
            // not enough space for next fread
            char *old = buffer;
            int newSize = current_size * 2 * sizeof(char);
            char *newBuffer = (char*) realloc(old, newSize);
            if (!newBuffer)
            {
                free(buffer);
                *retCode = -3;
                return "";
            }
            current_size = newSize;
            buffer = newBuffer;
        }
    }

    std::string result(buffer, used_size);

    free(buffer);
    fclose(fd);

    return result;
}