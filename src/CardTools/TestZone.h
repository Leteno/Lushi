#pragma once

#include <gtk/gtk.h>
#include <list>

#include "../machine/Sequence.h"

#include "TesterItem.h"

namespace CardTools {
    class TestZone {
    public:
        TestZone();
        void setInstruction(std::list<Sequence::Instruction> iList);
        GtkWidget* getRoot();
        void addSample(int health, int attach);
        void runTest();
        GtkWidget* mHealthText;
        GtkWidget* mAttachText;
    private:
        std::list<TesterItem*> mTesterItemList;
        std::list<Sequence::Instruction> mInstList;
        GtkWidget* mRoot;
        GtkWidget* mTestList;
    };
}