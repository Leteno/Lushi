
#include "TestEvent.h"

UT::Report frame::test::testEvent()
{
    UT::Report report;

    sf::Event e1;
    e1.type = sf::Event::KeyPressed;
    e1.key.code = sf::Keyboard::Left;
    Event r1 = Event::from(e1);
    report.addTest(UT::Test::assertEquals(
        r1.type, Event::Type::PRESSED
    ));
    report.addTest(UT::Test::assertEquals(
        r1.code, Event::Code::LEFT
    ));

    sf::Event e2;
    e2.type = sf::Event::KeyReleased;
    e2.key.code = sf::Keyboard::Up;
    Event r2 = Event::from(e2);
    report.addTest(UT::Test::assertEquals(
        r2.type, Event::Type::RELEASED
    ));
    report.addTest(UT::Test::assertEquals(
        r2.code, Event::Code::UP
    ));

    sf::Event e3;
    e3.type = sf::Event::MouseEntered;
    e3.key.code = sf::Keyboard::End;
    Event r3 = Event::from(e3);
    report.addTest(UT::Test::assertEquals(
        r3.type, Event::Type::NONE_TYPE
    ));
    report.addTest(UT::Test::assertEquals(
        r3.code, Event::Code::NONE_CODE
    ));

    return report;
}