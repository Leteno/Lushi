#pragma once

#include "State.h"
#include <iostream>
#include <memory>

namespace machine {

class Machine
{
public:
    enum BOOL {
        M_TRUE = 1,
        M_FALSE = 0,
    };
    bool executeOneInstruction(State* state);
    bool setStream(ostream*);
private:
    bool mathCalculate(State* state, Sequence::Code code);
    bool logicCalculate(State* state, Sequence::Code code);
    bool jump(State* state, Sequence::Value value);
    bool jump_if_false(State* state, Sequence::Value value);
    bool push(State* state, Sequence::Value value);
    bool pop(State* state);
    bool load(State* state, Sequence::Value value);
    bool store(State* state, Sequence::Value value);
    bool print(State* state);

    // GameObject related
    bool meetEndObj(State* state);
    bool loadObj(State* state);
    bool moveOnObj(State* state);
    bool resetObj(State* state);
    bool getObjHealth(State* state);
    bool setObjHealth(State* state, Sequence::Value value);
    bool getObjAttack(State* state);
    bool setObjAttack(State* state, Sequence::Value value);

    ostream* p_ostream;
};

}