
#include "TestCardEffectList.h"
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
    CardEffect* newOne = model.addNew();
    report.addTest(UT::Test::assertTrue(
        newOne != nullptr
    ));
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        1
    ));
    if (newOne != nullptr)
    {
        newOne->setName("juzhen");
        newOne->setOriginalCode("Hello world");
        std::list<CardEffect*> cardEffects = model.getCardEffectList();
        if (cardEffects.size() == 1)
        {
            CardEffect* firstOne = *cardEffects.begin();
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
    }
    model.remove(newOne);
    report.addTest(UT::Test::assertEquals(
        model.getCardEffectList().size(),
        0
    ));

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
