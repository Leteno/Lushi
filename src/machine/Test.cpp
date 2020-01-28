
#include <iostream>

#include "../unit_test/UT.h"
#include "TestMachine.h"
#include "TestMachine_OBJ.h"
#include "TestSequence.h"

int main()
{
    UT::Report report;
    report.mergeReport(testMachine());
    report.mergeReport(testMachineGameObject());
    report.mergeReport(testSequence());

    std::cout << report.getResult().toString() << std::endl;
    return report.getResult().totalPass() ? 0 : -1;
}