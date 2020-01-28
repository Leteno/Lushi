
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
            break;
        case Sequence::Code::LOAD:
            load(state, instruction.value);
            break;
        case Sequence::Code::STORE:
            store(state, instruction.value);
            break;

        // object related
        case Sequence::Code::MEET_END_OBJ:
            meetEndObj(state);
            break;
        case Sequence::Code::LOAD_OBJ:
            loadObj(state);
            break;
        case Sequence::Code::MOVE_ON_OBJ:
            moveOnObj(state);
            break;
        case Sequence::Code::RESET_OBJ:
            resetObj(state);
            break;
        case Sequence::Code::GET_HEALTH:
            getObjHealth(state);
            break;
        case Sequence::Code::SET_HEALTH:
            setObjHealth(state, instruction.value);
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
    state->m_InstructionIt++;
    return true;
}

bool Machine::load(State* state, Sequence::Value value)
{
    assert(value.type == Sequence::Value::INT);
    assert(0 <= value.intVal);
    assert(value.intVal < state->m_LocalVariables.size());
    int index = value.intVal;
    auto it = state->m_LocalVariables.begin();
    std::advance(it, index);
    state->m_LocalVariables.push_back(*it);
    state->m_InstructionIt++;
    return true;
}

bool Machine::store(State* state, Sequence::Value value)
{
    assert(value.type == Sequence::Value::INT);
    assert(0 <= value.intVal);
    assert(value.intVal <= state->m_LocalVariables.size());

    int index = value.intVal;
    int storeVal = state->m_LocalVariables.back();
    if (index < state->m_LocalVariables.size())
    {
        auto it = state->m_LocalVariables.begin();
        std::advance(it, index);
        *it = storeVal;
    }
    else
    { // index == state->m_LocalVariables.size()
        state->m_LocalVariables.push_back(storeVal);
    }
    state->m_InstructionIt++;
    return true;
}

bool Machine::meetEndObj(State* state)
{
    bool meetEnd = state->gameObjectMeetEnd();
    state->m_LocalVariables.push_back(meetEnd ? TRUE : FALSE);
    state->m_InstructionIt++;
    return true;
}

bool Machine::loadObj(State* state)
{
    assert(!state->gameObjectMeetEnd());
    state->m_CurrentGameObject = *state->m_GameObjectIt;
    state->m_InstructionIt++;
    return true;
}

bool Machine::moveOnObj(State* state)
{
    assert(!state->gameObjectMeetEnd());
    state->m_GameObjectIt++;
    state->m_InstructionIt++;
    return true;
}

bool Machine::resetObj(State* state)
{
    state->resetGameListIterator();
    state->m_InstructionIt++;
    return true;
}

bool Machine::getObjHealth(State* state)
{
    assert(state->m_CurrentGameObject);
    int health = state->m_CurrentGameObject->getHealth();
    state->m_LocalVariables.push_back(health);
    state->m_InstructionIt++;
    return true;
}

bool Machine::setObjHealth(State* state, Sequence::Value value)
{
    assert(state->m_CurrentGameObject);
    assert(state->m_LocalVariables.size());
    int health = state->m_LocalVariables.back();
    // do not pop_back here.
    state->m_CurrentGameObject->setHealth(health);
    state->m_InstructionIt++;
    return true;
}