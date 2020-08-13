
#include <assert.h>
#include <cstring>
#include <iostream>
#include <list>
#include <memory>
#include <stdlib.h>

using namespace std;

#include "../misc/StringSeperator.h"
#include "../misc/Utils.h"
#include "Compiler.h"

using namespace machine;
using namespace machine::Sequence;
using namespace misc;

const static std::map<std::string, Sequence::Code> str2code = {
    { "SAY", Sequence::Code::SAY },
    { "GET_ATTACK", Sequence::Code::GET_ATTACK },
    { "SET_ATTACK", Sequence::Code::SET_ATTACK },
    { "GET_HEALTH", Sequence::Code::GET_HEALTH },
    { "SET_HEALTH", Sequence::Code::SET_HEALTH },
    { "RESET_OBJ", Sequence::Code::RESET_OBJ },
    { "MEET_END_OBJ", Sequence::Code::MEET_END_OBJ },
    { "LOAD_OBJ", Sequence::Code::LOAD_OBJ },
    { "MOVE_ON_OBJ", Sequence::Code::MOVE_ON_OBJ },
    { "NOP", Sequence::Code::NOP },
    { "ADD", Sequence::Code::ADD },
    { "MINUS", Sequence::Code::MINUS },
    { "MUL", Sequence::Code::MUL },
    { "DIV", Sequence::Code::DIV },
    { "GT", Sequence::Code::GT },
    { "GTE", Sequence::Code::GTE },
    { "LT", Sequence::Code::LT },
    { "LTE", Sequence::Code::LTE },
    { "JMP", Sequence::Code::JMP },
    { "JMP_IF_FALSE", Sequence::Code::JMP_IF_FALSE },
    { "PUSH", Sequence::Code::PUSH },
    { "POP", Sequence::Code::POP },
    { "LOAD", Sequence::Code::LOAD },
    { "STORE", Sequence::Code::STORE },
};

static void compileInternal(const char* content, char* out);
static void commandline(const char* command, const char* input, int* success, char* out, char* err);
static std::list<Instruction> getInstruction(char* instructionString);

std::list<Sequence::Instruction> Compiler::compile(std::string& code)
{
    char out[1024 * 4];
    compileInternal(code.c_str(), out);
    const std::list<Sequence::Instruction>& result = getInstruction(out);
    return result;
}

std::string Compiler::toString(std::list<Sequence::Instruction>& instructions)
{
    return "";
}

static void compileInternal(const char* content, char* out)
{
    int success = 0;
    char reason[100];
    commandline("python3 ../../tools/CodeGenerator/buildInstructionCode.py", content, &success, out, reason);
    if (!success)
    {
        cout << "compile fail: " << reason << endl;
        assert(false);
    }
}

static void commandline(const char* command, const char* input, int* success, char* out, char* err)
{

    // cat > /tmp/juzhen-CodeZone.tmp
    char* tempFile = "/tmp/juzhen-CodeZone.tmp";
    char catCommand[100];
    strcpy(catCommand, "cat > ");
    strcat(catCommand, tempFile);
    FILE *fpCat = popen(catCommand, "w");
    if (!fpCat)
    {
        *success = 0;
        strcpy(err, "cannot store content to ");
        strcat(err, tempFile);
        return;
    }
    fputs(input, fpCat);
    pclose(fpCat);

    char realCommand[100];
    strcpy(realCommand, "cat ");
    strcat(realCommand, tempFile);
    strcat(realCommand, " | ");
    strcat(realCommand, command);
    FILE *fp = popen(realCommand, "r");

    if (!fp)
    {
        *success = 0;
        strcpy(err, "cannot open: ");
        strcat(err, command);
        return;
    }

    char buff[1024];
    while (memset(buff, 0, sizeof(buff)), fgets(buff, sizeof(buff) - 1, fp) != 0)
    {
        strcat(out, buff);
    }
    *success = 1;

    // TODO the case when command return error

    pclose(fp);
}

static std::list<Instruction> getInstruction(char* instructionString)
{
    std::list<Sequence::Instruction> instList;
    std::list<std::string> slist = StringSeperator::split(
        instructionString, " \n"
    );

    bool gotCode = false;
    Sequence::Code code;
    for (auto s : slist)
    {
        if (s.empty()) continue;
        auto f = str2code.find(s);
        if (f != str2code.end())
        {
            if (gotCode)
            {
                instList.push_back(Sequence::Instruction::buildInstruction(
                    code,
                    Sequence::Value::NONE,
                    -1
                ));
                std::cout << "record: " << code << " " << -1 << std::endl;
            }
            std::cout << s << " isCode " << code << std::endl;
            code = f->second;
            gotCode = true;
        }
        else
        {
            // it should be number
            int num = Utils::str2int(s.c_str());
            instList.push_back(Sequence::Instruction::buildInstruction(
                code,
                Sequence::Value::INT,
                num
            ));
            std::cout << s << " isNum " << num << std::endl;
            std::cout << "record: " << code << " " << num << std::endl;
            gotCode = false;
        }
    }
    if (gotCode)
    {
        instList.push_back(Sequence::Instruction::buildInstruction(
            code,
            Sequence::Value::NONE,
            -1
        ));
        std::cout << "record: " << code << " " << -1 << std::endl;
    }
    return instList;
}