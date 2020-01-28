#pragma once

#include "../unit_test/UT.h"
#include "Sequence.h"

UT::Report testMachine();
Sequence::Instruction buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val);