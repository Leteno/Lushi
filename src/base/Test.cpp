
#include <iostream>

#include "../unit_test/UT.h"
#include "TestEffectMachine.h"

int main()
{
    UT::Report report;
    report.mergeReport(testEffectMachine());
    UT::Result result = report.getResult();
    std::cout << result.toString() << std::endl;
    return result.totalPass() ? 0 : 1;
}