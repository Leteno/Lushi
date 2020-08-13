#pragma once

#include <map>
#include <list>
#include <string>

#include "Sequence.h"

using namespace machine;

namespace machine {
namespace Compiler
{
    std::list<Sequence::Instruction> compile(std::string&);
    std::string toString(std::list<Sequence::Instruction>&);
}
}