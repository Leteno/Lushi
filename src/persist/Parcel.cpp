
#include "Parcel.h"

using namespace persist;

Parcel::Parcel(int byteCount) : data(byteCount) {}

Parcel::Parcel(std::string rawstring) : data(rawstring) {}

void Parcel::writeInt(int) {}

void Parcel::writeLong(long) {}

void Parcel::writeFloat(float){}

void Parcel::writeDouble(double){}

void Parcel::writeString(string){}

int Parcel::readInt() { return -1; }

long Parcel::readLong() { return 0; }

float Parcel::readFloat() { return 0.1f; }

double Parcel::readDouble() { return 0.2; }

string Parcel::readString() { return ""; }

string Parcel::toString() { return ""; }

bool Parcel::meetEnd() { return false; }
