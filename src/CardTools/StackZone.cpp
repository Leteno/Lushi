#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "StackZone.h"
#include "TestZone.h"
#include "Utils.h"

#include "../machine/Sequence.h"
#include "../misc/StringSeperator.h"

using namespace CardTools;
using namespace machine;

static std::list<Sequence::Instruction> getSequenceInstruction(char *ch);

StackZone::StackZone(TestZone *testZone)
    : mTestZone(testZone)
{
    mRoot = gtk_frame_new(nullptr);
    gtk_widget_set_size_request(mRoot, 200, 200);

    mTextView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(mRoot), mTextView);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, "Stack Zone", -1);
}

GtkWidget* StackZone::getRoot()
{
    return mRoot;
}

void StackZone::update(char* data)
{
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, data, -1);
    mTestZone->setInstruction(getSequenceInstruction(data));
}

static std::list<Sequence::Instruction> getSequenceInstruction(char *ch)
{
    std::map<std::string, Sequence::Code> seqMap = {
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

    std::list<Sequence::Instruction> instList;
    std::list<std::string> slist = StringSeperator::split(
        ch, " \n"
    );

    bool gotCode = false;
    Sequence::Code code;
    for (auto s : slist)
    {
        if (s.empty()) continue;
        auto f = seqMap.find(s);
        if (f != seqMap.end())
        {
            if (gotCode)
            {
                instList.push_back(Sequence::buildInstruction(
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
            instList.push_back(Sequence::buildInstruction(
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
        instList.push_back(Sequence::buildInstruction(
            code,
            Sequence::Value::NONE,
            -1
        ));
        std::cout << "record: " << code << " " << -1 << std::endl;
    }
    return instList;
}