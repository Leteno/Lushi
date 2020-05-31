#pragma once
#include <gtk/gtk.h>

#include "CardEffectsModel.h"
#include "../card/CardEffect.h"

using namespace card;

namespace CardTools {
    class CardEffectListAdapter;
    class CardEffectListZone {
        public:
            CardEffectListZone(GtkWidget* window);
            GtkWidget* getRoot();

            CardEffectsModel* getModel() { return &mModel; }
            void update();
            void save(CardEffect);
            void deleteItem(CardEffect*);

        private:
            GtkWidget* mWindow;
            GtkWidget* mRoot;
            GtkWidget* mListView;
            CardEffectListAdapter* mAdapter;

            CardEffectsModel mModel;
    };
    class CardEffectListAdapter {
    public:
        CardEffect *effect;
        CardEffectListZone *zone;
    };
}