#include <assert.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "StackZone.h"
#include "TestZone.h"
#include "Utils.h"

#include "../machine/Sequence.h"
#include "../machine/Compiler.h"
#include "../misc/StringSeperator.h"

using namespace CardTools;
using namespace machine;
using namespace machine::Sequence;

StackZone::StackZone(TestZone *testZone)
    : mTestZone(testZone)
{
    mRoot = gtk_frame_new(nullptr);
    gtk_widget_set_size_request(mRoot, 200, 200);

    mTextView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(mRoot), mTextView);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, "StackZone, please run  Compile", -1);
}

GtkWidget* StackZone::getRoot()
{
    return mRoot;
}

void StackZone::updateInstruction(std::list<Sequence::Instruction> lst)
{
    std::cout << "updateInstruction" << std::endl;
    Utils::setTextViewContent(mTextView, Compiler::toString(lst));
    mTestZone->setInstruction(lst);
}