#pragma once

#include <list>
#include <string>
#include <iostream>

#include "../persist/Parcel.h"
#include "../persist/Parcellable.h"

using namespace persist;
using namespace std;

namespace machine {

namespace Sequence
{
    enum Code {

        // player related
        SAY = -10000,

        // object related
        GET_ATTACK = -107, // getAttack and push to localStack
        SET_ATTACK = -106, // setAttack(localStack.top())
        GET_HEALTH = -105, // State::currentGameObject->getHealth() push it to localStack
        SET_HEALTH = -104, // State::currentGameObject->setHealth(localVariable.top())
        RESET_OBJ = -103, // State::m_gameObjectIt = list.begin()
        MEET_END_OBJ = -102, // State::m_GameObjectIt == list.end(), push result to localStack
        LOAD_OBJ = -101,  // load State::m_GameObjectIt to State::currentGameObject
        MOVE_ON_OBJ = -100, // State::m_gameObjectIt++

        NOP = 0,

        // + - * /
        ADD = 1,
        MINUS = 2,
        MUL = 3,
        DIV = 4,
        // CMP
        GT = 5,
        GTE = 6,
        LT = 7,
        LTE = 8,
        // JMP
        JMP = 100,
        JMP_IF_FALSE = 101,
        // PUSH POP
        PUSH = 300,
        POP = 301,
        // LOAD STORE
        LOAD = 400,
        STORE = 401,
    };

    struct Value
    {
        enum Type {
            NONE = 0,
            INT = 1,
            STRING = 2,
        } type;
        int intVal;
        std::string stringVal;

        inline bool operator== (const Value& other)
        {
            return type == other.type &&
                (type == STRING ? stringVal == other.stringVal :
                    intVal == other.intVal);
        }

        friend ostream& operator<< (ostream& os, const Value& val)
        {
            os << "type: " << val.type << " ";
            if (val.type == STRING)
            {
                os << "val: " << val.stringVal;
            }
            else
            {
                os << "val: " << val.intVal;
            }
            return os;
        }
    };

    class Instruction : Parcellable
    {
    public:
        Instruction();
        ~Instruction();
        void readFromParcel(Parcel*);
        void writeToParcel(Parcel*);
        static Instruction buildInstruction(Sequence::Code code,
            Sequence::Value::Type valType, int val);

        Code code;
        Value value;

        inline bool operator== (Instruction& other)
        {
            return other.code == code && other.value == value;
        }

        friend ostream& operator<< (ostream& os, const Instruction& me)
        {
            os << me.code << " " << me.value;
            return os;
        }
    };
};

}