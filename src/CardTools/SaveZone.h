#pragma once

#include <gtk/gtk.h>

#include "../card/CardEffect.h"
#include "CodeZone.h"
#include "TestZone.h"

using namespace card;

namespace CardTools {
    class SaveZone {
        public:
            SaveZone(GtkWidget* window);
            GtkWidget* getRoot();
            void bind(CodeZone* codeZone, TestZone* testZone) { mCodeZone = codeZone; mTestZone = testZone; }
            void save();
        private:
            void saveToFile(CardEffect cardEffect);

            GtkWidget* mWindow;
            GtkWidget* mRoot;
            GtkWidget* mNameText;

            CodeZone* mCodeZone;
            TestZone* mTestZone;
    };
}