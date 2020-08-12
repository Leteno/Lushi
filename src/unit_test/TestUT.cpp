#include <assert.h>
#include <iostream>
#include "UT.h"

using namespace std;
using namespace UT;

class TestUT_T {
public:
    int a, b;

    inline bool operator == (const TestUT_T& other) {
        return a == other.a && b == other.b;
    }

    friend ostream& operator << (ostream& os, const TestUT_T& t){
        os << t.a << "/" << t.b;
        return os;
    }
};

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

    TestUT_T one; one.a = 1; one.b = 2;
    TestUT_T two; two.a = 1; two.b = 2;
    TestUT_T three; three.a = 1; three.b = 3;
    t = Test::assertEquals(one, two);
    report.addTest(t);
    assert(t.isPass() == true);
    t = Test::assertEquals(one, three);
    report.addTest(t);
    assert(t.isPass() == false);

    Result r = report.getResult();
    assert(r.getPassCount() == 8);
    assert(r.getTotalCount() == 16);

    Report another;
    another.mergeReport(report);
    Result anotherResult = another.getResult();
    assert(r.getPassCount() == anotherResult.getPassCount());
    assert(r.getTotalCount() == anotherResult.getTotalCount());

    printf("pass!\n");
    return 0;
}