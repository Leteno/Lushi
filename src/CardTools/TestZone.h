#pragma once

#include <gtk/gtk.h>

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
        GtkWidget* mRoot;
        GtkWidget* mTestList;
    };
}