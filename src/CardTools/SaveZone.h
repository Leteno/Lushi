#pragma once

#include <gtk/gtk.h>

#include "../card/CardEffect.h"
#include "CodeZone.h"
#include "TestZone.h"
#include "CardEffectListZone.h"

using namespace card;

namespace CardTools {
    class CardEffectListZone;
    class SaveZone {
        public:
            SaveZone(GtkWidget* window);
            GtkWidget* getRoot();
            void bind(CodeZone* codeZone, TestZone* testZone, CardEffectListZone* cardEffectListZone)
            {
                mCodeZone = codeZone;
                mTestZone = testZone;
                mCardEffectListZone = cardEffectListZone;
            }
            void save();

            void setName(std::string newName);
        private:
            void saveToFile(CardEffect cardEffect);

            GtkWidget* mWindow;
            GtkWidget* mRoot;
            GtkWidget* mNameText;

            CodeZone* mCodeZone;
            TestZone* mTestZone;
            CardEffectListZone* mCardEffectListZone;
    };
}