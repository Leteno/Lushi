
#include <string>
#include <exception>

#include "TestMessageException.h"

#include "MessageException.h"

using namespace UT;
using namespace misc;

static Report testThrow();
static void throwMessage(std::string);

Report TestMessageException::testMessageException()
{
    Report report;
    report.mergeReport(testThrow());
    return report;
}

static Report testThrow()
{
    Report report;
    bool gotException = false;
    try {
        throwMessage("Hello world");
    } catch (std::exception& e) {
        gotException = true;
        report.addTest(Test::assertEquals(
            e.what(), "Hello world"
        ));
    }
    report.addTest(Test::assertTrue(gotException));
    return report;
}

static void throwMessage(std::string message)
{
    throw MessageException(message);
}