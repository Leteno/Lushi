#pragma once
#include <string>

namespace persist {
    class RawData {
    public:
        RawData(int byteCount);
        RawData(std::string from);
        void read(void* out, int sizeOfElement, int size);
        void write(void* in, int sizeOfElement, int size);
        bool meetEnd();
        std::string toString();
        ~RawData();
    private:
        char* mData;
        int mCapacity, mWriteOffset, mReadOffset;
    };
}