
#include <iostream>

#include "../unit_test/UT.h"
#include "TestEffectMachine.h"
#include "TestGameObject.h"

int main()
{
    UT::Report report;
    report.mergeReport(testEffectMachine());
    report.mergeReport(testGameObject());
    UT::Result result = report.getResult();
    std::cout << result.toString() << std::endl;
    return result.totalPass() ? 0 : 1;
}