
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
        case Sequence::Code::GT:
        case Sequence::Code::GTE:
        case Sequence::Code::LT:
        case Sequence::Code::LTE:
            logicCalculate(state, instruction.code);
            break;
        case Sequence::Code::JMP:
            jump(state, instruction.value);
            break;
        case Sequence::Code::JMP_IF_FALSE:
            jump_if_false(state, instruction.value);
            break;
        case Sequence::Code::PUSH:
            push(state, instruction.value);
            break;
        case Sequence::Code::POP:
            pop(state);
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
    }
    state->m_InstructionIt++;
    return true;
}

bool Machine::logicCalculate(State* state, Sequence::Code code)
{
    assert(state->m_LocalVariables.size() >= 2);
    int b = state->m_LocalVariables.back();
    state->m_LocalVariables.pop_back();
    int a = state->m_LocalVariables.back();
    state->m_LocalVariables.pop_back();
    bool pass = false;
    switch (code)
    {
        case Sequence::Code::GT:
            pass = a > b;
            break;
        case Sequence::Code::GTE:
            pass = a >= b;
            break;
        case Sequence::Code::LT:
            pass = a < b;
            break;
        case Sequence::Code::LTE:
            pass = a <= b;
            break;
    }
    state->m_LocalVariables.push_back(pass ? TRUE : FALSE);
    state->m_InstructionIt++;
    return true;
}

bool Machine::jump(State* state, Sequence::Value value)
{
    assert(value.type == Sequence::Value::INT);
    return state->movePCPointer(value.intVal);
}

bool Machine::jump_if_false(State* state, Sequence::Value value)
{
    assert(state->m_LocalVariables.size());
    int val = state->m_LocalVariables.back();
    state->m_LocalVariables.pop_back();
    if (val == Machine::FALSE)
    {
        assert(value.type == Sequence::Value::INT);
        return state->movePCPointer(value.intVal);
    }
    else
    {
        state->m_InstructionIt++;
    }
    return true;
}

bool Machine::push(State* state, Sequence::Value value)
{
    assert(value.type == Sequence::Value::INT);
    state->m_LocalVariables.push_back(value.intVal);
    state->m_InstructionIt++;
    return true;
}

bool Machine::pop(State* state)
{
    assert(state->m_LocalVariables.size());
    state->m_LocalVariables.pop_back();
    return true;
}