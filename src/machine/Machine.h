#pragma once

#include "State.h"

class Machine
{
public:
    enum BOOL {
        TRUE = 1,
        FALSE = 0,
    };
    bool executeOneInstruction(State* state);
private:
    bool mathCalculate(State* state, Sequence::Code code);
    bool logicCalculate(State* state, Sequence::Code code);
    bool jump_if_false(State* state, Sequence::Value value);
};