
#include "Card.h"

using namespace card;

Card::Card() {}

Card::~Card() {}

void Card::readFromParcel(Parcel* parcel)
{
    this->name = parcel->readString();
}

void Card::writeToParcel(Parcel* parcel)
{
    parcel->writeString(this->name);
}