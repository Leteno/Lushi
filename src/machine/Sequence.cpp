#include <assert.h>
#include <list>
#include "stdlib.h"
#include "string.h"

#include "Sequence.h"

std::list<Sequence::Instruction> Sequence::getSequence()
{
    std::list<Sequence::Instruction> result;
    const int* p = m_Sequence;
    while (*p)
    {
        Sequence::Instruction inst;
        p = readCode(p, &(inst.code));
        p = readValue(p, inst.code, &(inst.value));
        result.push_back(inst);
    }
    return result;
}

const int* Sequence::readCode(const int* p_seq, Code* codeRet)
{
    *codeRet = (Code)*p_seq;
    return p_seq + 1;
}

int* Sequence::writeCode(int* p_dest, Code code)
{
    *p_dest = code;
    return p_dest + 1;
}

const int* Sequence::readValue(const int* p_seq, Code code, Sequence::Value* valRet)
{
    const int* result = p_seq;
    valRet->type = (Sequence::Value::Type)*result; ++result;
    switch (valRet->type)
    {
        case Value::Type::NONE:
            // DO NOTHING
            break;
        case Value::Type::INT:
            valRet->intVal = *result; ++result;
            break;
        case Value::Type::STRING:
            int len = strlen((char*) result);
            valRet->stringVal = (char*) malloc(sizeof(char) * len);
            memcpy(valRet->stringVal, result, len);
            valRet->stringVal[len] = '\0';
            result += len * sizeof(char) / sizeof(int) + 1;
            break;
    }
    return result;
}

int* Sequence::writeValue(int* p_dest, Value value)
{
    int* result = p_dest;
    *result = value.type; ++result;
    switch (value.type)
    {
        case Value::Type::NONE:
            // DO NOTHING
            break;
        case Value::Type::INT:
            *result = value.intVal; ++result;
            break;
        case Value::Type::STRING:
            int len = strlen(value.stringVal);
            char* writeInChar = (char*)result;
            memcpy(writeInChar, value.stringVal, len);
            writeInChar[len] = '\0';
            int cpyLenInInt = len * sizeof(char) / sizeof(int) + 1;
            result += cpyLenInInt;
            break;
    }
    return result;
}

Sequence::Instruction Sequence::buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val)
{
    Sequence::Instruction inst;
    inst.code = code;
    inst.value.type = valType;
    inst.value.intVal = val;
    return inst;
}