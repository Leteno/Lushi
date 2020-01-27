#include "assert.h"
#include <iostream>
#include "string.h"

#include "Sequence.h"
#include "../unit_test/UT.h"

UT::Report testSequenceAcceptType();
UT::Report testSequenceRead();

UT::Report testSequence()
{
    UT::Report report;
    report.mergeReport(testSequenceAcceptType());
    report.mergeReport(testSequenceRead());
    return report;
}

UT::Report testSequenceAcceptType()
{
    UT::Report report;

    int type = Sequence::AcceptType::PLAYER;
    Sequence seq1(type, nullptr);
    report.addTest(UT::Test::assertEquals(type, seq1.getAcceptType()));

    type = Sequence::AcceptType::PLAYER | Sequence::AcceptType::My_MONSTER | Sequence::AcceptType::ALL_MONSTER;
    Sequence seq2(type, nullptr);
    report.addTest(UT::Test::assertEquals(type, seq2.getAcceptType()));

    return report;
}

UT::Report testSequenceRead()
{
    UT::Report report;
    int type = Sequence::AcceptType::PLAYER;
    int buffer[256];
    int* pBuffer = buffer;

    // PUSH 1
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::PUSH);
    Sequence::Value one {.type = Sequence::Value::INT};
    one.intVal = 1;
    pBuffer = Sequence::writeValue(pBuffer, one);

    // SAY "hello world"
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::SAY);
    Sequence::Value hello {.type = Sequence::Value::STRING};
    hello.stringVal = "hello world";
    pBuffer = Sequence::writeValue(pBuffer, hello);

    // ADD NON
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::GT);
    Sequence::Value gtNone {.type = Sequence::Value::NONE};
    pBuffer = Sequence::writeValue(pBuffer, gtNone);

    // JMP_IF_FALSE
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::JMP_IF_FALSE);
    Sequence::Value jumpDest {.type = Sequence::Value::INT};
    jumpDest.intVal = 12306;
    pBuffer = Sequence::writeValue(pBuffer, jumpDest);

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

    return report;
}