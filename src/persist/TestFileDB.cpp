
#include "FileDB.h"
#include "Parcel.h"
#include "Parcellable.h"
#include "TestParcellable.h"

#include "TestFileDB.h"
using namespace persist;

UT::Report simpleTest();
UT::Report testWithParcel();
UT::Report persist::testFileDB()
{
    UT::Report report;
    report.mergeReport(simpleTest());
    report.mergeReport(testWithParcel());
    return report;
}

UT::Report simpleTest()
{
    UT::Report report;

    std::string filename("simpleTest.tmp");
    std::string content("Hello world, Mr zheng");
    int retCode = -1;
    FileDB::saveToFile(filename, content, &retCode);
    report.addTest(UT::Test::assertEquals(retCode, 0));

    std::string another = FileDB::readFromFile(filename, &retCode);
    report.addTest(UT::Test::assertEquals(retCode, 0));
    report.addTest(UT::Test::assertEquals(content, another));

    return report;
}

UT::Report testWithParcel()
{
    UT::Report report;

    std::string filename("testWithParcel.tmp");

    TestParcellableChild child(23, 45);
    TestParcellable item(1, 2.0, "Hello", child, 666);
    Parcel encode(2048);
    item.writeToParcel(&encode);
    std::string content = encode.toString();

    int retCode = -1;
    FileDB::saveToFile(filename, content, &retCode);
    report.addTest(UT::Test::assertEquals(retCode, 0));

    std::string newContent = FileDB::readFromFile(filename, &retCode);
    report.addTest(UT::Test::assertEquals(retCode, 0));
    Parcel decode(newContent);
    report.addTest(UT::Test::assertFalse(decode.meetEnd()));
    if (!decode.meetEnd())
    {
        TestParcellable newItem;
        newItem.readFromParcel(&decode);
        report.addTest(UT::Test::assertEquals(1, newItem.i));
        report.addTest(UT::Test::assertEquals(2.0, newItem.d));
        report.addTest(UT::Test::assertEquals("Hello", newItem.s));
        report.addTest(UT::Test::assertEquals(23, newItem.tc.a));
        report.addTest(UT::Test::assertEquals(45, newItem.tc.b));
        report.addTest(UT::Test::assertEquals(666, newItem.iAgain));
    }

    return report;
}