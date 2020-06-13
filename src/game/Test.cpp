
#include <iostream>

#include "../unit_test/UT.h"
#include "frame/test/TestEvent.h"
#include "fsm/test/TestFSM.h"

int main()
{
    UT::Report report;

    report.mergeReport(frame::test::testEvent());
    report.mergeReport(fsm::test::testFSM());

    std::cout << (report.getResult().totalPass() ? "pass" : "fail")
        << report.getResult().toString();
}