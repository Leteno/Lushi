
#include <assert.h>
#include <string>

#include "CardEffect.h"

using namespace card;

CardEffect::CardEffect() {}
CardEffect::~CardEffect()
{
    instructionList.clear();
}

void CardEffect::readFromParcel(Parcel* parcel)
{
    originalCode = parcel->readString();
    instructionList.clear();
    int size = parcel->readInt();
    for (int i = 0; i < size; ++i)
    {
        Sequence::Instruction instruction;
        instruction.readFromParcel(parcel);
        instructionList.push_back(instruction);
    }
}

void CardEffect::writeToParcel(Parcel* parcel)
{
    parcel->writeString(originalCode);
    parcel->writeInt(instructionList.size());
    for (auto it = instructionList.begin();
        it != instructionList.end();
        ++it)
    {
        it->writeToParcel(parcel);
    }
}