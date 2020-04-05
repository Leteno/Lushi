
#include "string.h"

#include "TestRawData.h"
#include "RawData.h"

using namespace UT;

UT::Report persist::testRawData()
{
    UT::Report report;

    // Prepare test data
    RawData raw(1024);
    char* text = "hello world";
    raw.write(text, sizeof(char), strlen(text));
    int age = 12;
    raw.write(&age, sizeof(int), 1);
    double score = 59.5;
    raw.write(&score, sizeof(double), 1);

    // test read
    char dupText[1024];
    int dupAge = 0;
    double dupScore = 0;
    raw.read(dupText, sizeof(char), strlen(text));
    raw.read(&dupAge, sizeof(int), 1);
    raw.read(&dupScore, sizeof(double), 1);

    report.addTest(Test::assertEquals(text, dupText));
    report.addTest(Test::assertEquals(age, dupAge));
    report.addTest(Test::assertEquals(score, dupScore));

    // test toString and RawData(string)
    RawData dupRawData(raw.toString());
    char dupText2[1024];
    int dupAge2 = 0;
    double dupScore2 = 0;
    dupRawData.read(dupText2, sizeof(char), strlen(text));
    dupRawData.read(&dupAge2, sizeof(int), 1);
    dupRawData.read(&dupScore2, sizeof(double), 1);

    report.addTest(Test::assertEquals(text, dupText2));
    report.addTest(Test::assertEquals(age, dupAge2));
    report.addTest(Test::assertEquals(score, dupScore2));

    return report;
}