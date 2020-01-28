
#include "assert.h"
#include <list>

#include "../base/GameObject.h"
#include "../unit_test/UT.h"

#include "Machine.h"
#include "Sequence.h"
#include "TestMachine.h"
#include "TestMachine_OBJ.h"

UT::Report testTravalGameObject();

UT::Report testMachineGameObject()
{
    UT::Report report;
    report.mergeReport(testTravalGameObject());
    return report;
}

UT::Report testTravalGameObject()
{
    GameObject lilei(23, 34), hanmeimei(45, 56);
    std::list<GameObject*> gList;
    gList.push_back(&lilei);
    gList.push_back(&hanmeimei);

    /**
    calculate the total health of GameObject

    [0] sum

    0)  PUSH 0
    1)  MEET_END_OBJ
    2)  JMP_IF_FALSE 4
    3)  JMP 12

    // calculate health
    4)  LOAD_OBJ
    5)  GET_HEALTH
    6)  LOAD 0
    7)  ADD
    8)  STORE 0
    9)  POP
    10) MOVE_ON_OBJ
    11) JMP 1
    12)

    **/
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::MEET_END_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 4));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 12));
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MOVE_ON_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 1));

    State state(iList, gList);
    Machine machine;
    while(machine.executeOneInstruction(&state));

    assert(state.m_LocalVariables.size());
    int sum = *state.m_LocalVariables.begin();

    // self calculate:
    int selfCalSum = 0;
    for (auto it = gList.begin();
        it != gList.end();
        it++)
    {
        GameObject* obj = *it;
        selfCalSum += obj->getHealth();
    }

    UT::Report report;
    report.addTest(UT::Test::assertEquals(sum, selfCalSum));
    return report;
}