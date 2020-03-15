#pragma once
#include <gtk/gtk.h>

#include "TestZone.h"

namespace CardTools {
    class StackZone {
        public:
            StackZone(TestZone *testZone);
            GtkWidget* getRoot();
            void update(char* data);
        private:
            TestZone* mTestZone;
            GtkWidget* mRoot;
            GtkWidget* mTextView;
    };
}