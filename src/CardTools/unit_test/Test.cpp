
#include <iostream>

#include "../../unit_test/UT.h"
#include "TestCardEffectList.h"

using namespace CardTools::unit_test;

int main()
{
    UT::Report report;
    report.mergeReport(testCardEffectsModelNormalOps());
    report.mergeReport(testCardEffectsModelReadAndWrite());
    report.mergeReport(testCardEffectsModelFile());

    std::cout << report.getResult().toString() << std::endl;
    return report.getResult().totalPass() ? 0 : 1;
}