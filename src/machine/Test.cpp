
#include <iostream>

#include "../unit_test/UT.h"
#include "TestCompiler.h"
#include "TestMachine.h"
#include "TestMachine_OBJ.h"
#include "TestSequence.h"

using namespace machine;

int main()
{
    UT::Report report;
    report.mergeReport(testMachine());
    report.mergeReport(testMachineGameObject());
    report.mergeReport(testSequence());
    report.mergeReport(testCompiler());

    std::cout << report.getResult().toString() << std::endl;
    return report.getResult().totalPass() ? 0 : -1;
}