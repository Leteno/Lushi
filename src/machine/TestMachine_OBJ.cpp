
#include "assert.h"
#include <list>

#include "../base/GameObject.h"
#include "../unit_test/UT.h"

#include "Machine.h"
#include "Sequence.h"
#include "TestMachine.h"
#include "TestMachine_OBJ.h"

UT::Report testTravalGameObject();
UT::Report testBuffAll();
UT::Report testMachineObjectAttack();
UT::Report testCodeGenToolResult();

UT::Report testMachineGameObject()
{
    UT::Report report;
    report.mergeReport(testTravalGameObject());
    report.mergeReport(testBuffAll());
    report.mergeReport(testMachineObjectAttack());
    report.mergeReport(testCodeGenToolResult());
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
    2)  JMP_IF_FALSE 2
    3)  JMP 9

    // calculate health
    4)  LOAD_OBJ
    5)  GET_HEALTH
    6)  LOAD 0
    7)  ADD
    8)  STORE 0
    9)  POP
    10) MOVE_ON_OBJ
    11) JMP -10
    12)

    **/
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::MEET_END_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 9));
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MOVE_ON_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, -10));

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

UT::Report testBuffAll()
{
    GameObject lilei(23, 34), hanmeimei(45, 56), mrmiddle(34, 1);
    std::list<GameObject*> gList;
    gList.push_back(&lilei);
    gList.push_back(&hanmeimei);
    gList.push_back(&mrmiddle);

    /**
     * Card: Natrue balance
     *
     * if your health > average, then your health will -10
     * elif your health < average, then your health will +10
     * else do nothing
     *
     
     [0] sum
     [1] count
     [2] average
    
     0)  PUSH 0
     1)  PUSH 0
     2)  PUSH 0

     3)  MEET_END_OBJ
     4)  JMP_IF_FALSE 2
     5)  JMP 14
     6)  LOAD_OBJ

     // calculate sum of health
     7)  GET_HEALTH
     8)  LOAD 0
     9)  ADD
     10) STORE 0
     11) POP

     // count++
     12) LOAD 1
     13) PUSH 1
     14) ADD
     15) STORE 1
     16) POP

     // back to loop start
     17) MOVE_ON_OBJ
     18) JMP -15

     // calculate average
     19) LOAD 0
     20) LOAD 1
     21) DIV
     22) STORE 2
     23) POP

     // revisit GameObjectList and apply health if need
     24) RESET_OBJ
     25) MEET_END_OBJ
     26) JMP_IF_FALSE 2
     27) JMP 23
     28) LOAD_OBJ

     // if health > average, health - 10
     29) GET_HEALTH
     30) LOAD 2
     31) GT
     32) JMP_IF_FALSE 7
     33) GET_HEALTH
     34) PUSH -10
     35) ADD
     36) SET_HEALTH
     37) POP
     38) JMP 10

     // if health < average, health + 10
     39) GET_HEALTH
     40) LOAD 2
     41) LT
     42) JMP_IF_FALSE 6
     43) GET_HEALTH
     44) PUSH 10
     45) ADD
     46) SET_HEALTH
     47) POP

     48) MOVE_ON_OBJ
     49) JMP -24

     // loop end
     50)
     */
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::MEET_END_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 14));
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MOVE_ON_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, -15));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::DIV, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::RESET_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MEET_END_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 23));
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::GT, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 7));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, -10));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::SET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 10));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::LT, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 6));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 10));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::SET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MOVE_ON_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, -24));

    State state(iList, gList);
    Machine machine;
    while(machine.executeOneInstruction(&state));

    UT::Report report;
    report.addTest(UT::Test::assertEquals(33, lilei.getHealth()));
    report.addTest(UT::Test::assertEquals(35, hanmeimei.getHealth()));
    report.addTest(UT::Test::assertEquals(34, mrmiddle.getHealth()));
    return report;
}

UT::Report testMachineObjectAttack()
{
    UT::Report report;

    std::list<GameObject*> gList;
    GameObject lilei(1,1);
    gList.push_back(&lilei);

    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::GET_ATTACK, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 10));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::SET_ATTACK, Sequence::Value::NONE, -1));

    State state(iList, gList);
    Machine machine;

    while (machine.executeOneInstruction(&state));

    report.addTest(UT::Test::assertEquals(lilei.getAttack(), 11));

    return report;
}

UT::Report testCodeGenToolResult()
{
    GameObject lilei(23, 34), hanmeimei(45, 56), mrmiddle(34, 1);
    std::list<GameObject*> gList;
    gList.push_back(&lilei);
    gList.push_back(&hanmeimei);
    gList.push_back(&mrmiddle);

    /**
     * Card: Natrue balance
     *
     * if your health > average, then your health will -10
     * elif your health < average, then your health will +10
     * else do nothing
     * 
     * Generated by tools
     **/
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::RESET_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MEET_END_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 14));
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MOVE_ON_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, -15));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::DIV, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::RESET_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MEET_END_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, 23));
    iList.push_back(buildInstruction(Sequence::Code::LOAD_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::GET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE, Sequence::Value::INT, 3));
    iList.push_back(buildInstruction(Sequence::Code::POP, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 3));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::LT, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 5));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 3));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 10));
    iList.push_back(buildInstruction(Sequence::Code::ADD, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::SET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 3));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::GT, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE, Sequence::Value::INT, 5));
    iList.push_back(buildInstruction(Sequence::Code::LOAD, Sequence::Value::INT, 3));
    iList.push_back(buildInstruction(Sequence::Code::PUSH, Sequence::Value::INT, 10));
    iList.push_back(buildInstruction(Sequence::Code::MINUS, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::SET_HEALTH, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::MOVE_ON_OBJ, Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP, Sequence::Value::INT, -24));
    State state(iList, gList);
    Machine machine;
    while(machine.executeOneInstruction(&state));

    UT::Report report;
    report.addTest(UT::Test::assertEquals(33, lilei.getHealth()));
    report.addTest(UT::Test::assertEquals(35, hanmeimei.getHealth()));
    report.addTest(UT::Test::assertEquals(34, mrmiddle.getHealth()));
    return report;   
}