
#include "State.h"

void State::reset()
{
    m_InstructionIt = m_InstructionList.begin();
    m_GameObjectIt = m_GameObjectList.begin();
    currentGameObject = nullptr;
    m_LocalVariables.clear();
}

bool State::instructionMeetEnd()
{
    return m_InstructionIt == m_InstructionList.end();
}
