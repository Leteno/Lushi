
#include "assert.h"

#include "Machine.h"
#include "Sequence.h"
#include "State.h"

bool Machine::executeOneInstruction(State* state)
{
    assert(state);
    if (state->instructionMeetEnd()) return false;
    Sequence::Instruction instruction = *(state->m_InstructionIt);
    switch(instruction.code)
    {
        case Sequence::Code::ADD:
        case Sequence::Code::MINUS:
        case Sequence::Code::MUL:
        case Sequence::Code::DIV:
            mathCalculate(state, instruction.code);
            break;
    }
    return true;
}

bool Machine::mathCalculate(State* state, Sequence::Code code)
{
    assert(state->m_LocalVariables.size() >= 2);
    // Note position of a, b
    int b = state->m_LocalVariables.back();
    state->m_LocalVariables.pop_back();
    int a = state->m_LocalVariables.back();
    state->m_LocalVariables.pop_back();
    switch (code)
    {
        case Sequence::Code::ADD:
            state->m_LocalVariables.push_back(a + b);
            break;
        case Sequence::Code::MINUS:
            state->m_LocalVariables.push_back(a - b);
            break;
        case Sequence::Code::MUL:
            state->m_LocalVariables.push_back(a * b);
            break;
        case Sequence::Code::DIV:
            assert(b);
            state->m_LocalVariables.push_back(a / b);
            break;
        default:
            assert(false);
    }
    state->m_InstructionIt++;
    return true;
}