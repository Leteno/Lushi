
#include "assert.h"
#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>

#include "../unit_test/UT.h"
#include "Compiler.h"
#include "Machine.h"
#include "Sequence.h"
#include "State.h"
#include "TestMachine.h"

using namespace machine;
using namespace UT;

UT::Report testMath();
UT::Report testLogic();
UT::Report testPushAndPop();
UT::Report testJump();
UT::Report testLoadAndStore();
Report testOStream();
Report testRunner();

UT::Report machine::testMachine()
{
    UT::Report report;
    report.mergeReport(testMath());
    report.mergeReport(testLogic());
    report.mergeReport(testPushAndPop());
    report.mergeReport(testJump());
    report.mergeReport(testLoadAndStore());
    report.mergeReport(testOStream());
    report.mergeReport(testRunner());
    return report;
}

UT::Report testMath()
{
    UT::Report report;
    std::list<Sequence::Instruction> iList;
    std::list<GameObject*> gList;
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
    std::list<GameObject*> emptyGList;
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(code,
        Sequence::Value::Type::NONE, 0));
    State test(iList, emptyGList);
    test.m_LocalVariables.push_back(a);
    test.m_LocalVariables.push_back(b);

    Machine machine;
    while(machine.executeOneInstruction(&test));
    assert(test.m_LocalVariables.size());
    return UT::Test::assertEquals(test.m_LocalVariables.back() == Machine::M_TRUE, pass);
}

UT::Report testPushAndPop()
{
    UT::Report report;

    std::list<GameObject*> gListEmpty;
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

    // Instruction should be finished at here.
    report.addTest(UT::Test::assertFalse(machine.executeOneInstruction(&state)));

    return report;
}
UT::Report testIfJump();
UT::Report testIfJumpInternal(int input);
UT::Report testForJump();
UT::Report testForJumpInternal(int num, int loop);
UT::Report testJump()
{
    UT::Report report;
    report.mergeReport(testIfJump());
    report.mergeReport(testForJump());
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
    3)  JMP_IF_FALSE 5
    4)  PUSH input
    5)  PUSH 1
    6)  ADD _
    7)  JMP 4
    8)  PUSH input
    9)  PUSH -1
    10) ADD _
    11)
    */
    UT::Report report;

    std::list<GameObject*> gList;
    std::list<Sequence::Instruction> iList;

    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, input));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::GT,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE,
        Sequence::Value::INT, 5));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, input));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP,
        Sequence::Value::INT, 4));
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

UT::Report testForJump()
{
    UT::Report report;
    report.mergeReport(testForJumpInternal(0, 100));
    report.mergeReport(testForJumpInternal(2, 10));
    report.mergeReport(testForJumpInternal(-2, 10));
    return report;
}

UT::Report testForJumpInternal(int num, int loop)
{
    /*
    for (int i = 0, result = 0; i < loop; i++)
    {
        result += num;
    }

    [0]    i
    [1]    result

    0)  PUSH    0
    1)  PUSH    0
    2)  LOAD    0
    3)  PUSH    loop
    4)  LT      _
    5)  JMP_IF_FALSE 12
    6)  LOAD    1         // result += num
    7)  PUSH    num
    8)  ADD     _
    9)  STORE   1
    10) POP     _
    11) LOAD    0         // i++
    12) PUSH    1
    13) ADD     _
    14) STORE   0
    15) POP
    16) JMP     -14
    16)

    */
    std::list<GameObject*> gList;
    std::list<Sequence::Instruction> iList;
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, loop));
    iList.push_back(buildInstruction(Sequence::Code::LT,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP_IF_FALSE,
        Sequence::Value::INT, 12));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, num));
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::POP,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::LOAD,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::PUSH,
        Sequence::Value::INT, 1));
    iList.push_back(buildInstruction(Sequence::Code::ADD,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::STORE,
        Sequence::Value::INT, 0));
    iList.push_back(buildInstruction(Sequence::Code::POP,
        Sequence::Value::NONE, -1));
    iList.push_back(buildInstruction(Sequence::Code::JMP,
        Sequence::Value::INT, -14));

    State state(iList, gList);
    Machine machine;
    while(machine.executeOneInstruction(&state));
    assert(state.m_LocalVariables.size() > 1);
    auto it = state.m_LocalVariables.begin();
    std::advance(it, 1);
    int calResult = *it;
    int expectedResult = 0;
    for (int i = 0; i < loop; i++)
    {
        expectedResult += num;
    }

    UT::Report report;
    report.addTest(UT::Test::assertEquals(expectedResult, calResult));
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
    std::list<GameObject*> gList;
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

    std::list<GameObject*> gList;
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

Report testOStream()
{
    Report report;

    std::string code = "print(1+3);";
    auto instructionList = Compiler::compile(code);
    std::list<GameObject*> gList;
    State state(instructionList, gList);
    Machine machine;
    stringstream ss;
    machine.setStream(&ss);
    while(machine.executeOneInstruction(&state));

    stringstream expectSS;
    expectSS << "4" << std::endl;
    report.addTest(Test::assertEquals(ss.str(), expectSS.str()));
    report.addTest(Test::assertTrue(state.m_LocalVariables.size() == 0));

    return report;
}

Report testRunner()
{
    Report report;

    std::string code = "a=1+2;b=3+4;";
    auto instructionList = Compiler::compile(code);
    std::list<GameObject*> gameObjectList;
    State state(instructionList, gameObjectList);
    Machine machine;
    while(machine.executeOneInstruction(&state));
    assert(state.m_LocalVariables.size() > 1);
    report.addTest(Test::assertEquals(
        state.m_LocalVariables.size(),
        2
    ));
    auto first = state.m_LocalVariables.begin();
    if (state.m_LocalVariables.size() > 0) {
        report.addTest(Test::assertEquals(
            *first,
            3
        ));
    }
    if (state.m_LocalVariables.size() > 1) {
        report.addTest(Test::assertEquals(
            *(++first),
            7
        ));
    }

    return report;
}

Sequence::Instruction machine::buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val)
{
    Sequence::Instruction inst;
    inst.code = code;
    inst.value.type = valType;
    inst.value.intVal = val;
    return inst;
}