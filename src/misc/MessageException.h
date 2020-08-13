#pragma once

#include <exception>
#include <string>

namespace misc {
    struct MessageException : std::exception {

    public:
        std::string message;
        MessageException(std::string& message)
            : message(message)
        {
        }

        const char* what() {
            return message.c_str();
        }
    };
}