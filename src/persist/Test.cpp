
#include <iostream>
#include "../unit_test/UT.h"
#include "TestParcellable.h"

int main()
{
    UT::Report report;
    report.mergeReport(testParcellable());

    std::cout << report.getResult().toString() << std::endl;
    return report.getResult().totalPass() ? 0 : -1;
}