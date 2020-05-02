
#include "../unit_test/UT.h"

#include "../persist/Parcel.h"

#include "Card.h"
#include "TestCard.h"

using namespace card;

UT::Report testCard_BasicReadWrite();

UT::Report card::testCard()
{
    UT::Report report;
    report.mergeReport(testCard_BasicReadWrite());
    return report;
}

UT::Report testCard_BasicReadWrite()
{
    UT::Report report;

    Card card;
    card.name = "juzhen";
    card.cardEffect.setOriginalCode("Hello world");
    std::list<Sequence::Instruction> instructionList;
    Sequence::Instruction instruction;
    instruction.code = Sequence::Code::SAY;
    instruction.value.type = Sequence::Value::STRING;
    instruction.value.stringVal = "Love you, Leslie";
    Sequence::Instruction instruction1;
    instruction1.code = Sequence::Code::STORE;
    instruction1.value.type = Sequence::Value::INT;
    instruction1.value.intVal = 1;
    instructionList.push_back(instruction);
    instructionList.push_back(instruction1);
    card.cardEffect.setInstructionList(instructionList);
    Parcel parcel(1024);
    card.writeToParcel(&parcel);

    Card another;
    another.readFromParcel(&parcel);
    report.addTest(UT::Test::assertTrue(parcel.meetEnd()));
    report.addTest(UT::Test::assertEquals(another.name, "juzhen"));
    CardEffect effect = another.cardEffect;
    report.addTest(UT::Test::assertEquals(
        effect.getOriginalCode(),
        "Hello world"
    ));
    std::list<Sequence::Instruction> newInstructionList = effect.getInstructionList();
    report.addTest(UT::Test::assertEquals(
        newInstructionList.size(),
        2
    ));
    if (newInstructionList.size() == 2)
    {
        auto it = newInstructionList.begin();
        Sequence::Instruction firstInstruction = *it;
        Sequence::Instruction secondInstruction = *(++it);
        report.addTest(UT::Test::assertEquals(
            firstInstruction.code,
            Sequence::Code::SAY
        ));
        report.addTest(UT::Test::assertEquals(
            firstInstruction.value.type,
            Sequence::Value::STRING
        ));
        report.addTest(UT::Test::assertEquals(
            firstInstruction.value.stringVal,
            "Love you, Leslie"
        ));
        report.addTest(UT::Test::assertEquals(
            secondInstruction.code,
            Sequence::Code::STORE
        ));
        report.addTest(UT::Test::assertEquals(
            secondInstruction.value.type,
            Sequence::Value::INT
        ));
        report.addTest(UT::Test::assertEquals(
            secondInstruction.value.intVal,
            1
        ));
    }

    return report;
}