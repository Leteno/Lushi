#pragma once

#include <list>

#include "Sequence.h"
#include "../base/GameObject.h"

class State
{
public:
    State(std::list<Sequence::Instruction> iList, std::list<GameObject> gList):
        m_InstructionList(iList), m_GameObjectList(gList),
        m_InstructionIt(iList.begin()), m_GameObjectIt(gList.begin()) {}
    State() {}
    void reset();
    bool instructionMeetEnd();
private:
    std::list<Sequence::Instruction> m_InstructionList;
    std::list<GameObject> m_GameObjectList;
public:
    std::list<Sequence::Instruction>::iterator m_InstructionIt;
    std::list<GameObject>::iterator m_GameObjectIt;
    GameObject *currentGameObject;
    std::list<int> m_LocalVariables;
};