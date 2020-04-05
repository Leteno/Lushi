
#include "Parcel.h"

using namespace persist;

Parcel::Parcel(int byteCount) : mData(byteCount)
{
}

Parcel::Parcel(std::string rawstring) : mData(rawstring) {}

void Parcel::writeInt(int val)
{
    mData.write(&val, sizeof(int), 1);
}

void Parcel::writeLong(long val)
{
    mData.write(&val, sizeof(long), 1);
}

void Parcel::writeFloat(float val)
{
    mData.write(&val, sizeof(float), 1);
}

void Parcel::writeDouble(double val)
{
    mData.write(&val, sizeof(val), 1);
}

void Parcel::writeString(string val)
{
    int size = val.length();
    mData.write(&size, sizeof(int), 1);
    char *data = const_cast<char*>(val.c_str());
    mData.write(data, sizeof(char), size);
}

int Parcel::readInt()
{
    int out = 0;
    mData.read(&out, sizeof(int), 1);
    return out;
}

long Parcel::readLong()
{
    long out = 0;
    mData.read(&out, sizeof(long), 1);
    return out;
}

float Parcel::readFloat()
{
    float out = 0;
    mData.read(&out, sizeof(float), 1);
    return out;
}

double Parcel::readDouble()
{
    double out = 0;
    mData.read(&out, sizeof(double), 1);
    return out;
}

string Parcel::readString()
{
    int size = 0;
    mData.read(&size, sizeof(int), 1);
    char* data = new char[size];
    mData.read(data, sizeof(char), size);
    std::string out(data);
    delete data;
    return out;
}

string Parcel::toString() { return mData.toString(); }

bool Parcel::meetEnd() { return false; }
