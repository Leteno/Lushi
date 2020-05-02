
#include <iostream>
#include "../unit_test/UT.h"

#include "TestCard.h"
#include "TestCardPool.h"
#include "TestCardEffect.h"

using namespace card;

int main()
{
    UT::Report report;
    report.mergeReport(testCard());
    report.mergeReport(testCardPool());
    report.mergeReport(testCardEffect());
    UT::Result result = report.getResult();
    std::cout << result.toString() << std::endl;
    return 0;
}