
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
    Parcel parcel(1024);
    card.writeToParcel(&parcel);

    Card another;
    card.readFromParcel(&parcel);
    report.addTest(UT::Test::assertTrue(parcel.meetEnd()));
    report.addTest(UT::Test::assertEquals(another.name, "juzhen"));

    return report;
}