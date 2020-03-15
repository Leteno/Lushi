
#include "assert.h"

#include "State.h"

using namespace machine;

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

bool State::movePCPointer(int offset)
{
    int dest = offset + std::distance(m_InstructionList.begin(), m_InstructionIt);
    assert(dest >= 0);
    assert(dest <= m_InstructionList.size());
    std::advance(m_InstructionIt, offset);
    return true;
}

void State::resetGameListIterator()
{
    m_GameObjectIt = m_GameObjectList.begin();
}