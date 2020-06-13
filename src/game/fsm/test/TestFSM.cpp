
#include <string>

#include "../FSM.h"
#include "TestFSM.h"

typedef std::string str;

UT::Report fsm::test::testFSM()
{
    UT::Report report;

    fsm::FSM<std::string, std::string> machine("Animal");
    report.addTest(UT::Test::assertTrue(
        machine.addPath("Animal", "wing", "Bird")
    ));
    report.addTest(UT::Test::assertTrue(
        machine.addPath("Animal", "foot", "Walker")
    ));
    report.addTest(UT::Test::assertTrue(
        machine.addPath("Bird", "yellow", "Chiken")
    ));
    report.addTest(UT::Test::assertTrue(
        machine.addPath("Walker", "fur", "Cat")
    ));
    report.addTest(UT::Test::assertTrue(
        machine.addPath("Walker", "bark", "Dog")
    ));

    report.addTest(UT::Test::assertEquals(
        machine.getCurrentState(), "Animal"
    ));

    report.addTest(UT::Test::assertFalse(
        machine.accept("nothing")
    ));
    report.addTest(UT::Test::assertTrue(
        machine.accept("wing")
    ));

    report.addTest(UT::Test::assertEquals(
        machine.getCurrentState(), "Bird"
    ));

    report.addTest(UT::Test::assertFalse(
        machine.accept("bark")
    ));
    report.addTest(UT::Test::assertTrue(
        machine.accept("yellow")
    ));

    report.addTest(UT::Test::assertEquals(
        machine.getCurrentState(), "Chiken"
    ));

    return report;
}