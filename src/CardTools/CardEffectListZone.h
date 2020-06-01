#pragma once
#include <gtk/gtk.h>

#include "CardEffectsModel.h"
#include "../card/CardEffect.h"

#include "CodeZone.h"
#include "StackZone.h"
#include "SaveZone.h"

using namespace card;

namespace CardTools {
    class SaveZone;
    class CardEffectListAdapter;
    class CardEffectListZone {
        public:
            CardEffectListZone(GtkWidget* window);
            GtkWidget* getRoot();

            CardEffectsModel* getModel() { return &mModel; }
            void update();
            void save();
            CardEffect* addNewCard();
            void deleteItem(CardEffect*);

            void bind(CodeZone* code, StackZone* stack, SaveZone* save)
            {
                mCodeZone = code;
                mStackZone = stack;
                mSaveZone = save;
            }
            void updateCurrentCard(CardEffect* cardEffect);

        private:
            GtkWidget* mWindow;
            GtkWidget* mRoot;
            GtkWidget* mListView;
            CardEffectListAdapter* mAdapter;

            CardEffectsModel mModel;

            CodeZone* mCodeZone;
            StackZone* mStackZone;
            SaveZone* mSaveZone;
    };
    class CardEffectListAdapter {
    public:
        CardEffect *effect;
        CardEffectListZone *zone;
    };
}