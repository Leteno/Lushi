#pragma once
#include <gtk/gtk.h>

namespace CardTools {
    class CardEffectListZone {
        public:
            CardEffectListZone(GtkWidget* window);
            GtkWidget* getRoot();
        private:
            GtkWidget* mWindow;
            GtkWidget* mRoot;
    };
}