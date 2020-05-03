#include <assert.h>
#include <list>
#include <string>
#include "stdlib.h"
#include "string.h"

#include "Sequence.h"

using namespace machine;


Sequence::Instruction::Instruction() {}
Sequence::Instruction::~Instruction() {}

void Sequence::Instruction::readFromParcel(Parcel* parcel)
{
    code = Code(parcel->readInt());
    int type = parcel->readInt();
    switch(type)
    {
    case Value::Type::INT:
        value.type = Value::Type::INT;
        value.intVal = parcel->readInt();
        break;
    case Value::Type::STRING:
        value.type = Value::Type::STRING;
        value.stringVal = parcel->readString();
        break;
    case Value::Type::NONE:
        value.type = Value::Type::NONE;
        break;
    default:
        // Fail Delibery
        assert(type == Value::INT);
    }
}

void Sequence::Instruction::writeToParcel(Parcel* parcel)
{
    parcel->writeInt(code);
    parcel->writeInt(value.type);
    switch(value.type)
    {
    case Value::INT:
        parcel->writeInt(value.intVal);
        break;
    case Value::STRING:
        parcel->writeString(value.stringVal);
        break;
    case Value::NONE:
        break;
    default:
        // Fail Delibery
        assert(value.type == Value::INT);
    }
}

Sequence::Instruction Sequence::Instruction::buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val)
{
    Sequence::Instruction inst;
    inst.code = code;
    inst.value.type = valType;
    inst.value.intVal = val;
    return inst;
}