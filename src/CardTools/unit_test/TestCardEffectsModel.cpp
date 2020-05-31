
#include "TestCardEffectsModel.h"
#include "../CardEffectsModel.h"

using namespace CardTools;

UT::Report CardTools::unit_test::testCardEffectsModelNormalOps()
{
    UT::Report report;

    CardEffectsModel model;
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        0
    ));
    CardEffect* firstOne = model.addNew();
    report.addTest(UT::Test::assertTrue(
        firstOne != nullptr
    ));
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        1
    ));
    if (firstOne != nullptr)
    {
        firstOne->setName("juzhen");
        firstOne->setOriginalCode("Hello world");
        std::list<CardEffect*> cardEffects = model.getCardEffectList();
        if (cardEffects.size() == 1)
        {
            CardEffect* one = *cardEffects.begin();
            report.addTest(UT::Test::assertTrue(
                one != nullptr
            ));
            if (one != nullptr)
            {
                report.addTest(UT::Test::assertEquals(
                    one->getName(),
                    "juzhen"
                ));
                report.addTest(UT::Test::assertEquals(
                    one->getOriginalCode(),
                    "Hello world"
                ));
            }
        }
    }

    CardEffect* secondOne = model.addNew();
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        2
    ));
    if (secondOne != nullptr)
    {
        secondOne->setName("second one");
        secondOne->setOriginalCode("become better");
    }
    model.remove(firstOne);
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        1
    ));
    if (model.getCardEffectList().size() == 1) {
        CardEffect* lastOne = *model.getCardEffectList().begin();
        report.addTest(UT::Test::assertEquals(
            lastOne->getName(),
            "second one"
        ));
        report.addTest(UT::Test::assertEquals(
            lastOne->getOriginalCode(),
            "become better"
        ));
    }
    model.remove(secondOne);
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        0
    ));

    CardEffect thirdOne;
    thirdOne.setName("juzhen");
    thirdOne.setOriginalCode("hello world");
    CardEffect* thirdOneP = model.add(thirdOne);
    report.addTest(UT::Test::assertTrue(
        thirdOneP != nullptr
    ));
    if (thirdOneP != nullptr)
    {
        report.addTest(UT::Test::assertEquals(
            thirdOne.getName(),
            thirdOneP->getName()
        ));
        report.addTest(UT::Test::assertEquals(
            thirdOne.getOriginalCode(),
            thirdOneP->getOriginalCode()
        ));
    }

    report.addTest(UT::Test::assertTrue(
        model.getCardEffectList().size() == 1
    ));
    if (model.getCardEffectList().size() == 1)
    {
        CardEffect* thirdOneInList = *(model.getCardEffectList().begin());
        report.addTest(UT::Test::assertEquals(
            thirdOne.getName(),
            thirdOneInList->getName()
        ));
        report.addTest(UT::Test::assertEquals(
            thirdOne.getOriginalCode(),
            thirdOneInList->getOriginalCode()
        ));
    }

    return report;
}

UT::Report CardTools::unit_test::testCardEffectsModelReadAndWrite()
{
    UT::Report report;

    CardEffectsModel model;
    CardEffect* newOne = model.addNew();
    if (newOne != nullptr)
    {
        newOne->setName("juzhen");
        newOne->setOriginalCode("Hello world");
    }

    Parcel parcel(1024);
    model.writeToParcel(&parcel);
    CardEffectsModel newModel;
    newModel.readFromParcel(&parcel);

    report.addTest(UT::Test::assertEquals(
        newModel.getCardEffectList().size(),
        1
    ));
    if (newModel.getCardEffectList().size() == 1)
    {
        CardEffect* firstOne = *newModel.getCardEffectList().begin();
        if (firstOne != nullptr)
        {
            report.addTest(UT::Test::assertEquals(
                firstOne->getName(),
                "juzhen"
            ));
            report.addTest(UT::Test::assertEquals(
                firstOne->getOriginalCode(),
                "Hello world"
            ));
        }
    }

    return report;
}

UT::Report CardTools::unit_test::testCardEffectsModelFile()
{
    UT::Report report;

    CardEffectsModel model;
    CardEffect* newOne = model.addNew();
    if (newOne != nullptr)
    {
        newOne->setName("juzhen");
        newOne->setOriginalCode("Hello world");
    }
    model.saveToFile("data.tmp");

    CardEffectsModel newModel;
    newModel.readFromFile("data.tmp");
    report.addTest(UT::Test::assertEquals(
        newModel.getCardEffectList().size(),
        1
    ));
    if (newModel.getCardEffectList().size() == 1)
    {
        CardEffect* firstOne = *newModel.getCardEffectList().begin();
        report.addTest(UT::Test::assertTrue(
            firstOne != nullptr
        ));
        if (firstOne != nullptr)
        {
            report.addTest(UT::Test::assertEquals(
                firstOne->getName(),
                "juzhen"
            ));
            report.addTest(UT::Test::assertEquals(
                firstOne->getOriginalCode(),
                "Hello world"
            ));
        }
    }

    return report;
}
