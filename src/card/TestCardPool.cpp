
#include "../unit_test/UT.h"

#include "CardPool.h"
#include "TestCardPool.h"

using namespace card;

UT::Report testCardPool_AddWriteRead();

UT::Report card::testCardPool()
{
    UT::Report report;

    report.mergeReport(testCardPool_AddWriteRead());

    return report;
}

UT::Report testCardPool_AddWriteRead()
{
    UT::Report report;

    CardPool pool;
    report.addTest(UT::Test::assertEquals(pool.count(), 0));

    Card card1; card1.name = "card1";
    Card card2; card2.name = "card2";

    pool.addCard(card1);
    report.addTest(UT::Test::assertEquals(pool.count(), 1));
    pool.addCard(card2);
    report.addTest(UT::Test::assertEquals(pool.count(), 2));

    Parcel parcel(1024);
    pool.writeToParcel(&parcel);
    CardPool another;
    another.readFromParcel(&parcel);
    report.addTest(UT::Test::assertTrue(parcel.meetEnd()));

    report.addTest(UT::Test::assertEquals(another.count(), 2));
    if (another.count() == 2)
    {
        report.addTest(UT::Test::assertEquals("card1", another.get(0).name));
        report.addTest(UT::Test::assertEquals("card2", another.get(1).name));
    }

    return report;
}