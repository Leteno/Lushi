
#include "TestUtils.h"
#include "Utils.h"

using namespace misc;
using namespace UT;

static Report testStr2Int();

Report TestUtils::testUtils()
{
    Report report;
    report.mergeReport(testStr2Int());
    return report;
}

static Report testStr2Int()
{
    Report report;
    report.addTest(Test::assertEquals(
        Utils::str2int("1"), 1
    ));
    report.addTest(Test::assertEquals(
        Utils::str2int("12345678"), 12345678
    ));
    report.addTest(Test::assertEquals(
        Utils::str2int("-123"), -123
    ));
    report.addTest(Test::assertEquals(
        Utils::str2int("abcded"), -1
    ));
    report.addTest(Test::assertEquals(
        Utils::str2int("0"), 0
    ));
    return report;
}
