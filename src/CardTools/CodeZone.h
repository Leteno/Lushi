#pragma once
#include <gtk/gtk.h>

#include "StackZone.h"

namespace CardTools {
    class CodeZone {
        public:
            CodeZone(GtkWidget* window, StackZone* stackZone);
            GtkWidget* getRoot();
            void onCompile();
        private:
            GtkWidget* mWindow;
            StackZone* mStackZone;
            GtkWidget* mRoot;
            GtkWidget* mTextView;
    };
}
