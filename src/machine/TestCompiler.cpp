
#include "TestCompiler.h"

#include "Compiler.h"
using namespace machine;
using namespace machine::Sequence;
using namespace UT;

UT::Report testCompile();
UT::Report testToString();

UT::Report machine::testCompiler()
{
    UT::Report report;
    report.mergeReport(testCompile());
    report.mergeReport(testToString());
    return report;
}

UT::Report testCompile()
{
    UT::Report report;
    std::string testCode = "a = 1 + 2;";
    auto insts = Compiler::compile(testCode);
    std::list<Instruction> expect;
    expect.push_back(Instruction::buildInstruction(
        Code::PUSH, Value::Type::INT,
        0
    ));
    expect.push_back(Instruction::buildInstruction(
        Code::PUSH, Value::Type::INT,
        1
    ));
    expect.push_back(Instruction::buildInstruction(
        Code::PUSH, Value::Type::INT,
        2
    ));
    expect.push_back(Instruction::buildInstruction(
        Code::ADD, Value::Type::NONE,
        -1
    ));
    expect.push_back(Instruction::buildInstruction(
        Code::STORE, Value::Type::INT,
        0
    ));
    expect.push_back(Instruction::buildInstruction(
        Code::POP, Value::Type::NONE,
        -1
    ));
    report.addTest(Test::assertEquals((int)expect.size(), insts.size()));

    int size = std::min(expect.size(), insts.size());
    auto e = expect.begin();
    auto inst = insts.begin();
    for (int i = 0; i < size; ++i, ++e, ++inst)
    {
        report.addTest(Test::assertEquals(
            *e, *inst
        ));
    }

    return report;
}

UT::Report testToString()
{
    UT::Report report;
    std::list<Instruction> insts;
    insts.push_back(Instruction::buildInstruction(
        Code::PUSH, Value::Type::INT,
        0
    ));
    insts.push_back(Instruction::buildInstruction(
        Code::PUSH, Value::Type::INT,
        1
    ));
    insts.push_back(Instruction::buildInstruction(
        Code::PUSH, Value::Type::INT,
        2
    ));
    insts.push_back(Instruction::buildInstruction(
        Code::ADD, Value::Type::NONE,
        -1
    ));
    insts.push_back(Instruction::buildInstruction(
        Code::STORE, Value::Type::INT,
        0
    ));
    insts.push_back(Instruction::buildInstruction(
        Code::POP, Value::Type::NONE,
        -1
    ));

    std::string got = Compiler::toString(insts);
    std::string expect = "PUSH 0\nPUSH 1\nPUSH 2\nADD\nSTORE 0\nPOP\n";
    report.addTest(Test::assertEquals(got, expect));
    return report;
}