#include <assert.h>
#include "RawData.h"

using namespace persist;

void strncpy(char* dest, char* source, int size);

RawData::RawData(int byteCount) :
    mWriteOffset(0), mReadOffset(0),
    mCapacity(byteCount)
{
    mData = new char[byteCount];
}

RawData::RawData(std::string from)
{
    int len = from.length();
    mWriteOffset = len;
    mReadOffset = 0;
    mCapacity = len * 2;
    mData = new char[mCapacity];

    from.copy(mData, len, 0);
}

RawData::~RawData()
{
    delete mData;
}

void RawData::read(void* out, int sizeOfElement, int size)
{
    printf("read mReadOffset %d, mWriteOffset %d\n", mReadOffset, mWriteOffset);
    assert(mReadOffset < mWriteOffset);

    int retriveSize = sizeOfElement * size;
    assert(mWriteOffset - mReadOffset >= retriveSize);

    strncpy((char*)out, mData + mReadOffset, retriveSize);
    mReadOffset += retriveSize;
}

void RawData::write(void* in, int sizeOfElement, int size)
{
    assert(mWriteOffset < mCapacity);

    int writeSize = sizeOfElement * size;
    assert(mCapacity > mWriteOffset + writeSize);

    strncpy(mData + mWriteOffset, (char*)in, writeSize);
    mWriteOffset += writeSize;
}

bool RawData::meetEnd()
{
    return mWriteOffset == mReadOffset;
}

std::string RawData::toString()
{
    return std::string(mData, mWriteOffset + 1);
}

void strncpy(char* dest, char* source, int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = source[i];
    }
}