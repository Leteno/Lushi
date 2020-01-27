
#include "assert.h"
#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>

#include "../unit_test/UT.h"
#include "Machine.h"
#include "State.h"
#include "TestMachine.h"

UT::Report testMath();
UT::Report testLogic();
UT::Report testPushAndPop();
UT::Report testJump();
UT::Report testLoadAndStore();
Sequence::Instruction buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val);

UT::Report testMachine()
{
    UT::Report report;
    report.mergeReport(testMath());
    report.mergeReport(testLogic());
    report.mergeReport(testPushAndPop());
    report.mergeReport(testJump());
    report.mergeReport(testLoadAndStore());
    return report;
}

UT::Report testMath()
{
    UT::Report report;
    std::list<Sequence::Instruction> iList;
    std::list<GameObject> gList;
    iList.push_back(buildInstruction(Sequence::Code::MINUS,
        Sequence::Value::Type::NONE, 0));;
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::Type::NONE, 0));;
    iList.push_back(buildInstruction(Sequence::Code::MUL,
        Sequence::Value::Type::NONE, 0));;
    iList.push_back(buildInstruction(Sequence::Code::DIV,
        Sequence::Value::Type::NONE, 0));;

    State state(iList, gList);
    Machine machine;

    int t = time(nullptr);
    int numCount = iList.size() + 1;
    for (int i = 0; i < 100; i++)
    {
        state.reset();
        srand(i + t);
        int r = rand();
        for (int n = 0; n < numCount; ++n)
        {
            int localVal = r >> n + 1; // make sure greater than 0
            state.m_LocalVariables.push_back(localVal);
        }
        // self calculate
        auto it = state.m_LocalVariables.crbegin();
        int calResult = *it; ++it;
        for (std::list<Sequence::Instruction>::iterator instIt = iList.begin();
             instIt != iList.end(); ++instIt)
        {
            int num = *it; ++it;
            switch((*instIt).code)
            {
                case Sequence::Code::ADD:
                    calResult = num + calResult;
                    break;
                case Sequence::Code::MINUS:
                    calResult = num - calResult;
                    break;
                case Sequence::Code::MUL:
                    calResult = num * calResult;
                    break;
                case Sequence::Code::DIV:
                    calResult = num / calResult;
                    break;
            }
        }

        // Machine calculate
        while(machine.executeOneInstruction(&state));
        int result = state.m_LocalVariables.back();
        report.addTest(UT::Test::assertEquals(result, calResult));
    }
    return report;
}

UT::Test testLogicInternal(Sequence::Code code, int a, int b, bool pass);
UT::Report testLogic()
{
    UT::Report report;
    // testGT
    report.addTest(testLogicInternal(Sequence::Code::GT, 2, 1, true));
    report.addTest(testLogicInternal(Sequence::Code::GT, 1, 2, false));
    report.addTest(testLogicInternal(Sequence::Code::GT, 2, 2, false));
    // testGTE
    report.addTest(testLogicInternal(Sequence::Code::GTE, 2, 1, true));
    report.addTest(testLogicInternal(Sequence::Code::GTE, 1, 2, false));
    report.addTest(testLogicInternal(Sequence::Code::GTE, 2, 2, true));
    // testLT
    report.addTest(testLogicInternal(Sequence::Code::LT, 2, 1, false));
    report.addTest(testLogicInternal(Sequence::Code::LT, 1, 2, true));
    report.addTest(testLogicInternal(Sequence::Code::LT, 2, 2, false));
    // testLTE
    report.addTest(testLogicInternal(Sequence::Code::LTE, 2, 1, false));
    report.addTest(testLogicInternal(Sequence::Code::LTE, 1, 2, true));
    report.addTest(testLogicInternal(Sequence::Code::LTE, 2, 2, true));
    return report;
}
UT::Test testLogicInternal(Sequence::Code code, int a, int b, bool pass)
{
    std::list<GameObject> emptyGList;
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(code,
        Sequence::Value::Type::NONE, 0));
    State test(iList, emptyGList);
    test.m_LocalVariables.push_back(a);
    test.m_LocalVariables.push_back(b);

    Machine machine;
    while(machine.executeOneInstruction(&test));
    assert(test.m_LocalVariables.size());
    return UT::Test::assertEquals(test.m_LocalVariables.back() == Machine::TRUE, pass);
}

UT::Report testPushAndPop()
{
    UT::Report report;

    std::list<GameObject> gListEmpty;
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 12306));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 12580));
    iList.push_back(buildInstruction(Sequence::Code::POP,
        Sequence::Value::NONE, -1));

    State state(iList, gListEmpty);
    Machine machine;

    report.addTest(UT::Test::assertEquals(0, state.m_LocalVariables.size()));
    machine.executeOneInstruction(&state);
    report.addTest(UT::Test::assertEquals(1, state.m_LocalVariables.size()));
    report.addTest(UT::Test::assertEquals(12306, state.m_LocalVariables.back()));
    machine.executeOneInstruction(&state);
    report.addTest(UT::Test::assertEquals(2, state.m_LocalVariables.size()));
    report.addTest(UT::Test::assertEquals(12580, state.m_LocalVariables.back()));
    machine.executeOneInstruction(&state);
    report.addTest(UT::Test::assertEquals(1, state.m_LocalVariables.size()));
    report.addTest(UT::Test::assertEquals(12306, state.m_LocalVariables.back()));

    return report;
}
UT::Report testIfJump();
UT::Report testIfJumpInternal(int input);
UT::Report testJump()
{
    UT::Report report;
    report.mergeReport(testIfJump());
    return report;
}

UT::Report testIfJump()
{
    UT::Report report;
    report.mergeReport(testIfJumpInternal(-1));
    report.mergeReport(testIfJumpInternal(2));
    return report;
}

UT::Report testIfJumpInternal(int input)
{
    /*
    if (a > 0)
    {
        a = a + 1;
    }
    else
    {
        a = a - 1;
    }

    0)  PUSH input
    1)  PUSH 0
    2)  GT _
    3)  JMP_IF_FALSE 8
    4)  PUSH input
    5)  PUSH 1
    6)  ADD _
    7)  JMP 11
    8)  PUSH input
    9)  PUSH -1
    10) ADD _
    11)
    */
    UT::Report report;

    std::list<GameObject> gList;
    std::list<Sequence::Instruction> iList;

    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, input));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::GT,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE,
        Sequence::Value::INT, 8));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, input));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP,
        Sequence::Value::INT, 11));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, input));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, -1));
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::NONE, -1));

    State state(iList, gList);
    Machine machine;

    while(machine.executeOneInstruction(&state));

    assert(state.m_LocalVariables.size() == 1);
    if (input > 0)
    {
        report.addTest(UT::Test::assertEquals(
            input + 1, state.m_LocalVariables.back()
        ));
    }
    else
    {
        report.addTest(UT::Test::assertEquals(
            input - 1, state.m_LocalVariables.back()
        ));
    }
    return report;
}

UT::Report testLoadInternal(int a, int b);
UT::Report testStoreInternal(int a, int b);
UT::Report testLoadAndStore()
{
    UT::Report report;

    report.mergeReport(testLoadInternal(12306, 12580));
    report.mergeReport(testLoadInternal(66666, 23333));
    report.mergeReport(testStoreInternal(123, 456));
    report.mergeReport(testStoreInternal(678, 890));

    return report;
}

UT::Report testLoadInternal(int a, int b)
{
    /**
     * return (a+b)/2,  (a-b)/2
     *
     * PUSH a
     * PUSH b
     *
     * LOAD 0
     * LOAD 1
     * ADD  _
     * PUSH 2
     * DIV  _
     *
     * LOAD 0
     * LOAD 1
     * MINUS _
     * PUSH 2
     * DIV  _
    **/
    std::list<GameObject> gList;
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, a));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, b));

    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::DIV,
        Sequence::Value::NONE, -1));

    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::MINUS,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 2));
    iList.push_back(buildInstruction(Sequence::Code::DIV,
        Sequence::Value::NONE, -1));

    State state(iList, gList);
    Machine machine;
    while(machine.executeOneInstruction(&state));
    int result2 = state.m_LocalVariables.back();
    state.m_LocalVariables.pop_back();
    int result1 = state.m_LocalVariables.back();
    int expectResult1 = (a + b) / 2;
    int expectResult2 = (a - b) / 2;

    UT::Report report;
    report.addTest(UT::Test::assertEquals(result1, expectResult1));
    report.addTest(UT::Test::assertEquals(result2, expectResult2));
    return report;
}

UT::Report testStoreInternal(int a, int b)
{
    /*
    swap a, b => b, a

    PUSH  a
    PUSH  b
    LOAD  0
    LOAD  1
    STORE 0
    POP   _
    STORE 1
    POP   _

    */

    std::list<GameObject> gList;
    std::list<Sequence::Instruction> iList;

    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, a));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, b));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::STORE,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::POP,
        Sequence::Value::NONE, -1));

    State state(iList, gList);
    Machine machine;

    while(machine.executeOneInstruction(&state));
    int result2 = state.m_LocalVariables.back();
    state.m_LocalVariables.pop_back();
    int result1 = state.m_LocalVariables.back();

    UT::Report report;
    report.addTest(UT::Test::assertEquals(a, result2));
    report.addTest(UT::Test::assertEquals(b, result1));
    return report;
}

Sequence::Instruction buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val)
{
    Sequence::Instruction inst {.code = code};
    inst.value = Sequence::Value {.type = valType};
    inst.value.intVal = val;
    return inst;
}