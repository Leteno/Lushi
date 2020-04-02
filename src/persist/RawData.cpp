#include <string>
#include "RawData.h"

using namespace persist;

RawData::RawData(int byteCount) {}
RawData::RawData(std::string from) {}

void RawData::read(void* out, int sizeOfElement, int size) {}
void RawData::write(void* in, int sizeOfElement, int size) {}
std::string RawData::toString() { return ""; }