
#include <iostream>
#include "../unit_test/UT.h"
#include "TestParcellable.h"
#include "TestRawData.h"

using namespace persist;

int main()
{
    UT::Report report;
    report.mergeReport(testParcellable());
    report.mergeReport(testRawData());

    std::cout << report.getResult().toString() << std::endl;
    return report.getResult().totalPass() ? 0 : -1;
}