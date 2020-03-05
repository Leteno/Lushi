#pragma once
#include <gtk/gtk.h>

namespace CardTools {
    class StackZone {
        public:
            StackZone();
            GtkWidget* getRoot();
            void update(char* data);
        private:
            GtkWidget* mRoot;
            GtkWidget* mTextView;
    };
}