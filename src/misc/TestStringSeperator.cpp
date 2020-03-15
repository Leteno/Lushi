
#include <list>
#include <string>

#include "../unit_test/UT.h"

#include "TestStringSeperator.h"
#include "StringSeperator.h"

using namespace UT;

static std::string strAt(std::list<std::string>::iterator it, int index);

Report testStringSeperator()
{
    Report report;

    std::list<std::string> res01 = StringSeperator::split(
        "hello world",
        " "
    );
    report.addTest(Test::assertEquals(res01.size(), 2));
    if (res01.size() == 2)
    {
        report.addTest(Test::assertEquals(
            strAt(res01.begin(), 0), "hello"
        ));
        report.addTest(Test::assertEquals(
            strAt(res01.begin(), 1), "world"
        ));
    }

    std::list<std::string> res02 = StringSeperator::split(
        "Hello World! My dear friends.",
        " !"
    );
    report.addTest(Test::assertEquals(res02.size(), 5));
    if (res02.size() == 5)
    {
        report.addTest(Test::assertEquals(
            strAt(res02.begin(), 1), "World"
        ));
        report.addTest(Test::assertEquals(
            strAt(res02.begin(), 4), "friends."
        ));
    }

    return report;
}

static std::string strAt(std::list<std::string>::iterator it, int index)
{
    auto ret = it;
    std::advance(ret, index);
    return *ret;
}