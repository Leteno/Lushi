#pragma once

#include <string>

#include "RawData.h"

using namespace std;

namespace persist {
    class Parcel {
    public:
        Parcel(int byteCount);
        Parcel(std::string);
        std::string toString();

        void writeInt(int);
        void writeLong(long);
        void writeFloat(float);
        void writeDouble(double);
        void writeString(string);

        int readInt();
        long readLong();
        float readFloat();
        double readDouble();
        string readString();

        bool meetEnd();

    private:
        RawData data;
    };
}