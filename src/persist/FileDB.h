#pragma once

#include <string>

namespace persist {
    class FileDB {
    public:
        static void saveToFile(std::string name, std::string content, int *retCode);
        static std::string readFromFile(std::string name, int *retCode);
    };
}