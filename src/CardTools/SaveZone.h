#pragma once

#include <gtk/gtk.h>

namespace CardTools {
    class SaveZone {
        public:
            SaveZone(GtkWidget* window);
            GtkWidget* getRoot();
        private:
            GtkWidget* mWindow;
            GtkWidget* mRoot;
    };
}