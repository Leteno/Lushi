#include "assert.h"
#include <iostream>
#include "string.h"

#include "Sequence.h"
#include "../unit_test/UT.h"

using namespace machine;

UT::Report testSequenceReadAndWrite();

UT::Report testSequence()
{
    UT::Report report;
    report.mergeReport(testSequenceReadAndWrite());
    return report;
}

UT::Report testSequenceReadAndWrite()
{
    UT::Report report;

/*    

    // PUSH 1
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::PUSH);
    Sequence::Value one;
    one.type = Sequence::Value::INT;
    one.intVal = 1;
    pBuffer = Sequence::writeValue(pBuffer, one);

    // SAY "hello world"
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::SAY);
    Sequence::Value hello;
    hello.type = Sequence::Value::STRING;
    hello.stringVal = "hello world";
    pBuffer = Sequence::writeValue(pBuffer, hello);

    // GT NON
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::GT);
    Sequence::Value gtNone;
    gtNone.type = Sequence::Value::NONE;
    pBuffer = Sequence::writeValue(pBuffer, gtNone);

    // JMP_IF_FALSE
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::JMP_IF_FALSE);
    Sequence::Value jumpDest;
    jumpDest.type = Sequence::Value::INT;
    jumpDest.intVal = 12306;
    pBuffer = Sequence::writeValue(pBuffer, jumpDest);

    *pBuffer = '\0'; // add end

    Sequence seq(type, buffer);
    std::list<Sequence::Instruction> instructionList = seq.getSequence();
    assert(instructionList.size() == 4);
    auto it = instructionList.begin();

    Sequence::Instruction add1 = *it; it++;
    report.addTest(UT::Test::assertEquals(add1.code, Sequence::Code::PUSH));
    report.addTest(UT::Test::assertEquals(add1.value.intVal, 1));

    Sequence::Instruction sayHello = *it; it++;
    report.addTest(UT::Test::assertEquals(sayHello.code, Sequence::Code::SAY));
    report.addTest(UT::Test::assertEquals(sayHello.value.stringVal, "hello world"));

    Sequence::Instruction gtNoneTest = *it; it++;
    report.addTest(UT::Test::assertEquals(gtNoneTest.code, Sequence::Code::GT));
    report.addTest(UT::Test::assertEquals(gtNoneTest.value.type, Sequence::Value::Type::NONE));

    Sequence::Instruction jmp = *it; it++;
    report.addTest(UT::Test::assertEquals(jmp.code, Sequence::Code::JMP_IF_FALSE));
    report.addTest(UT::Test::assertEquals(jmp.value.intVal, 12306));
*/
    return report;
}