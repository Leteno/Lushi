
#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>

#include "../unit_test/UT.h"
#include "Machine.h"
#include "State.h"
#include "TestMachine.h"

UT::Report testMath();
Sequence::Instruction buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val);

UT::Report testMachine()
{
    return testMath();
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

Sequence::Instruction buildInstruction(Sequence::Code code,
    Sequence::Value::Type valType, int val)
{
    Sequence::Instruction inst {.code = code};
    inst.value = Sequence::Value {.type = valType};
    inst.value.intVal = val;
    return inst;
}