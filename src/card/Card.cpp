
#include "Card.h"

using namespace card;

Card::Card() {}

Card::~Card() {}

void Card::readFromParcel(Parcel* parcel)
{
    this->name = parcel->readString();
    this->cardEffect.readFromParcel(parcel);
}

void Card::writeToParcel(Parcel* parcel)
{
    parcel->writeString(this->name);
    this->cardEffect.writeToParcel(parcel);
}