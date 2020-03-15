#pragma once

#include "../unit_test/UT.h"
#include "Sequence.h"

namespace machine {

UT::Report testMachine();
Sequence::Instruction buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val);

}
