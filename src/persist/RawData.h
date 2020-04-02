#pragma once
#include <string>

namespace persist {
    class RawData {
    public:
        RawData(int byteCount);
        RawData(std::string from);
        void read(void* out, int sizeOfElement, int size);
        void write(void* in, int sizeOfElement, int size);
        std::string toString();
    private:
        char* mData;
    };
}