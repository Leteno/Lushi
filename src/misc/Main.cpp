
#include <iostream>

#include "../unit_test/UT.h"
#include "TestMessageException.h"
#include "TestStringSeperator.h"
#include "TestUtils.h"

using namespace UT;
using namespace misc;

int main()
{
    Report report;
    report.mergeReport(TestMessageException::testMessageException());
    report.mergeReport(testStringSeperator());
    report.mergeReport(TestUtils::testUtils());
    Result result = report.getResult();
    if (!result.totalPass())
    {
        std::cout << result.toString() << std::endl;
    }
    else
    {
        std::cout << "Pass!" << std::endl;
    }
    return result.totalPass() ? 0 : 1;
}