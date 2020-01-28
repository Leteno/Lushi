
#include "GameObject.h"
#include "TestGameObject.h"

UT::Report testHealth();
UT::Report testAttack();

UT::Report testGameObject()
{
    UT::Report report;
    report.mergeReport(testHealth());
    report.mergeReport(testAttack());
    return report;
}

UT::Report testHealth()
{
    UT::Report report;

    GameObject mouse(1, 1);
    report.addTest(UT::Test::assertEquals(1, mouse.getHealth()));
    mouse.setHealth(12);
    report.addTest(UT::Test::assertEquals(12, mouse.getHealth()));
    mouse.setAttack(13);
    report.addTest(UT::Test::assertEquals(12, mouse.getHealth()));
    mouse.reset();
    report.addTest(UT::Test::assertEquals(1, mouse.getHealth()));

    return report;
}

UT::Report testAttack()
{
    UT::Report report;

    GameObject mouse(1, 1);
    report.addTest(UT::Test::assertEquals(1, mouse.getAttack()));
    mouse.setHealth(12);
    report.addTest(UT::Test::assertEquals(1, mouse.getAttack()));
    mouse.setAttack(13);
    report.addTest(UT::Test::assertEquals(13, mouse.getAttack()));
    mouse.reset();
    report.addTest(UT::Test::assertEquals(1, mouse.getAttack()));

    return report;
}