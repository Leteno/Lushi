#pragma once

#include <gtk/gtk.h>
#include <list>

#include "TesterItem.h"

namespace CardTools {
    class TestZone {
    public:
        TestZone();
        void setInstruction();
        GtkWidget* getRoot();
        void addSample(int health, int attach);
        void runTest();
        GtkWidget* mHealthText;
        GtkWidget* mAttachText;
    private:
        std::list<TesterItem*> mTesterItemList;
        GtkWidget* mRoot;
        GtkWidget* mTestList;
    };
}