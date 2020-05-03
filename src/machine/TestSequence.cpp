#include "assert.h"
#include <iostream>
#include "string.h"

#include "Sequence.h"
#include "../unit_test/UT.h"

using namespace machine::Sequence;

UT::Report testSequenceReadAndWrite();

UT::Report testSequence()
{
    UT::Report report;
    report.mergeReport(testSequenceReadAndWrite());
    return report;
}

UT::Report testSequenceReadAndWrite()
{
    UT::Report report;

    struct TestData {
        Code code;
        Value value;
    };
    TestData tests[] = {
        {
            Code::PUSH,
            {
                Value::INT, 1
            }
        },
        {
            Code::SAY,
            {
                Value::STRING, 0, "hello world"
            }
        },
        {
            Code::GT,
            {
                Value::NONE, 0
            }
        },
        {
            Code::JMP_IF_FALSE,
            {
                Value::INT, 123
            }
        }
    };

    for (int i = 0, size = sizeof(tests) / sizeof(TestData); i < size; ++i)
    {
        Code code = tests[i].code;
        Value value = tests[i].value;

        Instruction instruction;
        instruction.code = code;
        instruction.value = value;

        Parcel parcel(1024);
        instruction.writeToParcel(&parcel);
        Instruction newInst;
        newInst.readFromParcel(&parcel);
        report.addTest(UT::Test::assertTrue(
            parcel.meetEnd()
        ));

        report.addTest(UT::Test::assertEquals(
            newInst.code, code
        ));
        report.addTest(UT::Test::assertEquals(
            newInst.value.type, value.type
        ));
        switch (value.type)
        {
        case Value::INT:
            report.addTest(UT::Test::assertEquals(
                newInst.value.intVal, value.intVal
            ));
            break;
        case Value::STRING:
            report.addTest(UT::Test::assertEquals(
                newInst.value.stringVal, value.stringVal
            ));
            break;
        case Value::NONE:
            break;
        default:
            // Fail Delibery
            report.addTest(UT::Test::assertEquals(
                value.type, Value::INT
            ));
        }
    }

    return report;
}
