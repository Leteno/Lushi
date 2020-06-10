
#include <iostream>

#include "../unit_test/UT.h"
#include "frame/test/TestEvent.h"

int main()
{
    UT::Report report;

    report.mergeReport(frame::test::testEvent());

    std::cout << (report.getResult().totalPass() ? "pass" : "fail")
        << report.getResult().toString();
}