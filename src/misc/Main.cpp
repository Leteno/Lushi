
#include <iostream>

#include "../unit_test/UT.h"
#include "TestStringSeperator.h"

using namespace UT;

int main()
{
    Report report;
    report.mergeReport(testStringSeperator());
    Result result = report.getResult();
    if (!result.totalPass())
    {
        std::cout << result.toString() << std::endl;
    }
    return result.totalPass() ? 0 : 1;
}