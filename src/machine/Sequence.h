#pragma once

#include <list>

class Sequence
{
public:
    enum Code {

        // player related
        SAY = -10000,

        // object related
        FETCH_OBJ = -100, // FETCH_OBJ jmp_f, mCurrentObj=mStack.pop(), if null, jmp_f
        GET_HEALTH = -2,
        SET_HEALTH = -1,

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
        JMP = 9, // if true
    };

    /**
     *  This Sequence accept what type of objs, will read the obj queue in this order:
     *  
     *  PLAYER/NULL/
     *  ALL_MONSTER/NULL/
     *  MY_MONSTER/NULL/
     *  ENEMY_MONSTER/NULL/
     * 
     *  Any type must end with NULL.
     * 
     * 
     *  MY_MONSTER/ENEMY_MONSTER  vs ALL_MONSTER.
     *  we may have this situation:
     *  * increase all monster 1 attack, increase my monster 1 health, decrease enemy monster 1 health.
     */
    enum AcceptType{
        PLAYER = 0x1,
        ALL_MONSTER = 0x10,
        My_MONSTER = 0x100,
        ENEMY_MONSTER = 0x1000,
    };

    struct Value
    {
        enum Type {
            INT = 1,
            STRING = 2,
        } type;
        union {
            int intVal;
            char* stringVal;
        };
    };

    struct Instruction
    {
        Code code;
        Value value;
    };

private:
    const int m_AcceptType;
    const int* m_Sequence;

public:
    Sequence(int type, int* sequence):
        m_AcceptType(type), m_Sequence(sequence) {}
    Sequence(): m_AcceptType(0), m_Sequence(nullptr) {}
    int getAcceptType()
    {
        return m_AcceptType;
    }
    std::list<Instruction> getSequence();

    static int* writeCode(int* p_dest, Code code);
    static int* writeValue(int* p_dest, Value value);

private:
    const int* readCode(const int* p_seq, Code* codeRet);
    const int* readValue(const int* p_seq, Code code, Value* valRet);
};