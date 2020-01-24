#include "assert.h"
#include <iostream>
#include "string.h"

#include "Sequence.h"
#include "../unit_test/UT.h"

UT::Report testSequenceAcceptType();
UT::Report testSequenceRead();

int main()
{
    UT::Report report;
    report.mergeReport(testSequenceAcceptType());
    report.mergeReport(testSequenceRead());
    std::cout << report.getResult().toString() << std::endl;
    return 0;
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

    // ADD 1
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::ADD);
    Sequence::Value one {.type = Sequence::Value::INT};
    one.intVal = 1;
    pBuffer = Sequence::writeValue(pBuffer, one);

    // SAY "hello world"
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::SAY);
    Sequence::Value hello {.type = Sequence::Value::STRING};
    hello.stringVal = "hello world";
    pBuffer = Sequence::writeValue(pBuffer, hello);

    // JMP
    pBuffer = Sequence::writeCode(pBuffer, Sequence::Code::JMP);
    Sequence::Value jumpDest {.type = Sequence::Value::INT};
    jumpDest.intVal = 12306;
    pBuffer = Sequence::writeValue(pBuffer, jumpDest);

    Sequence seq(type, buffer);
    std::list<Sequence::Pair> pairList = seq.getSequence();
    assert(pairList.size() == 3);
    auto it = pairList.begin();

    Sequence::Pair add1 = *it; it++;
    report.addTest(UT::Test::assertEquals(add1.code, Sequence::Code::ADD));
    report.addTest(UT::Test::assertEquals(add1.value.intVal, 1));

    Sequence::Pair sayHello = *it; it++;
    report.addTest(UT::Test::assertEquals(sayHello.code, Sequence::Code::SAY));
    report.addTest(UT::Test::assertEquals(sayHello.value.stringVal, "hello world"));

    Sequence::Pair jmp = *it; it++;
    report.addTest(UT::Test::assertEquals(jmp.code, Sequence::Code::JMP));
    report.addTest(UT::Test::assertEquals(jmp.value.intVal, 12306));

    return report;
}