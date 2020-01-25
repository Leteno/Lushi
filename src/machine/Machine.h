#pragma once

#include "State.h"

class Machine
{
public:
    bool executeOneInstruction(State* state);
private:
    bool mathCalculate(State* state, Sequence::Code code);
};