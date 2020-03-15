#pragma once

#include <gtk/gtk.h>

#include "../base/GameObject.h"
#include "TesterData.h"

namespace CardTools {
    class TesterItem {
    public:
        TesterItem(TesterData* data);
        GtkWidget* getView();
        void update();
        void quickTest();
        void toGameObject(GameObject* obj);
        void applyFrom(GameObject obj);
    private:
        TesterData*  mData;
        GtkWidget* mRoot;
        GtkWidget* mLabelHealth;
        GtkWidget* mLabelAttack;
    };
}
