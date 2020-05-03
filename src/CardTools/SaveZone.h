#pragma once

#include <gtk/gtk.h>

#include "../card/CardEffect.h"

using namespace card;

namespace CardTools {
    class SaveZone {
        public:
            SaveZone(GtkWidget* window);
            GtkWidget* getRoot();
            void save();
        private:
            void saveToFile(CardEffect cardEffect);

            GtkWidget* mWindow;
            GtkWidget* mRoot;
    };
}