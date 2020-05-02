
#include "../unit_test/UT.h"

#include "CardEffect.h"
#include "TestCardEffect.h"

using namespace card;

UT::Report testCardEffectReadAndWrite();

UT::Report card::testCardEffect() {
    UT::Report report;
    report.mergeReport(testCardEffectReadAndWrite());
    return report;
}

UT::Report testCardEffectReadAndWrite()
{
    CardEffect cardEffect;
    cardEffect.setOriginalCode("ABC");

    Sequence::Instruction instruction;
    instruction.value.type = Sequence::Value::INT;
    instruction.value.intVal = 123;
    instruction.code = Sequence::Code::NOP;
    std::list<Sequence::Instruction> instList;
    instList.push_back(instruction);
    cardEffect.setInstructionList(instList);

    Parcel parcel(1024);
    cardEffect.writeToParcel(&parcel);
    CardEffect newOne;
    newOne.readFromParcel(&parcel);

    UT::Report report;
    report.addTest(UT::Test::assertTrue(parcel.meetEnd()));
    report.addTest(UT::Test::assertEquals(
        newOne.getOriginalCode(),
        "ABC"
    ));
    std::list<Sequence::Instruction> newInstructionList;
    newInstructionList = newOne.getInstructionList();
    report.addTest(UT::Test::assertEquals(
        newInstructionList.size(),
        1
    ));
    if (newInstructionList.size() == 1)
    {
        Sequence::Instruction instruction = *newInstructionList.begin();
        report.addTest(UT::Test::assertEquals(
            instruction.value.type,
            Sequence::Value::INT
        ));
        report.addTest(UT::Test::assertEquals(
            instruction.value.intVal,
            123
        ));
        report.addTest(UT::Test::assertEquals(
            instruction.code,
            Sequence::Code::NOP
        ));
    }
    return report;
}
