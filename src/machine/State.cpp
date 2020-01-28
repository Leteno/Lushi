
#include "assert.h"

#include "State.h"

void State::reset()
{
    m_InstructionIt = m_InstructionList.begin();
    m_GameObjectIt = m_GameObjectList.begin();
    m_CurrentGameObject = nullptr;
    m_LocalVariables.clear();
}

bool State::instructionMeetEnd()
{
    return m_InstructionIt == m_InstructionList.end();
}

bool State::gameObjectMeetEnd()
{
    return m_GameObjectIt == m_GameObjectList.end();
}

bool State::movePCPointer(int dest)
{
    assert(dest >= 0);
    assert(dest <= m_InstructionList.size());
    auto newIt = m_InstructionList.begin();
    std::advance(newIt, dest);
    m_InstructionIt = newIt;
    return true;
}

void State::resetGameListIterator()
{
    m_GameObjectIt = m_GameObjectList.begin();
}