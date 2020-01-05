#include <assert.h>
#include "UT.h"

using namespace UT;

int main()
{
    Report report;

    // assertEquals
    Test t = Test::assertEquals((char*)"a", (char*)"a");
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertEquals((char*)"a", (char*)"b");
    report.addTest(t);
    assert(t.isPass() == false);

    t = Test::assertEquals(std::string("a"), std::string("a"));
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertEquals(std::string("a"), std::string("b"));
    report.addTest(t);
    assert(t.isPass() == false);

    t = Test::assertEquals(1, 1);
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertEquals(1, 2);
    report.addTest(t);
    assert(t.isPass() == false);

    t = Test::assertEquals(1.f, 1.f);
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertEquals(1.f, 2.f);
    report.addTest(t);
    assert(t.isPass() == false);

    t = Test::assertEquals(1.0, 1.0);
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertEquals(1.0, 2.0);
    report.addTest(t);
    assert(t.isPass() == false);

    t = Test::assertTrue(true);
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertTrue(false);
    report.addTest(t);
    assert(t.isPass() == false);

    t = Test::assertFalse(false);
    report.addTest(t);
    assert(t.isPass() == true);

    t = Test::assertFalse(true);
    report.addTest(t);
    assert(t.isPass() == false);

    Result r = report.getResult();
    assert(r.getPassCount() == 7);
    assert(r.getTotalCount() == 14);

    printf("pass!\n");
    return 0;
}