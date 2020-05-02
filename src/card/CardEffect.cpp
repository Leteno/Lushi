
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
        int type = parcel->readInt();
        switch (type)
        {
        case Sequence::Value::INT:
            instruction.value.type = Sequence::Value::INT;
            instruction.value.intVal = parcel->readInt();
            break;
        case Sequence::Value::STRING:
            instruction.value.type = Sequence::Value::STRING;
            instruction.value.stringVal = parcel->readString();
            break;
        case Sequence::Value::NONE:
            instruction.value.type = Sequence::Value::NONE;
            break;
        default:
            // Fail definitely
            assert(type == Sequence::Value::INT);
        }
        instruction.code = Sequence::Code(parcel->readInt());
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
        parcel->writeInt(it->value.type);
        switch (it->value.type)
        {
        case Sequence::Value::INT:
            parcel->writeInt(it->value.intVal);
            break;
        case Sequence::Value::STRING:
            parcel->writeString(it->value.stringVal);
            break;
        case Sequence::Value::NONE:
            break;
        default:
            // Fail definitely
            assert(it->value.type == Sequence::Value::INT);
        }
        parcel->writeInt(it->code);
    }
}