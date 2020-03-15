#pragma once

#include <list>

#include "Sequence.h"
#include "../base/GameObject.h"

namespace machine {

class State
{
public:
    State(std::list<Sequence::Instruction> iList, std::list<GameObject*> gList):
        m_InstructionList(iList), m_GameObjectList(gList)
    {
        reset();
    }
    State() {}
    void reset();
    bool instructionMeetEnd();
    bool gameObjectMeetEnd();
    bool movePCPointer(int dest);
    void resetGameListIterator();
private:
    std::list<Sequence::Instruction> m_InstructionList;
    std::list<GameObject*> m_GameObjectList;
public:
    std::list<Sequence::Instruction>::iterator m_InstructionIt;
    std::list<GameObject*>::iterator m_GameObjectIt;
    GameObject *m_CurrentGameObject;
    std::list<int> m_LocalVariables;
};

}