#pragma once

#include <gtk/gtk.h>

#include "TesterData.h"

namespace CardTools {
    class TesterItem {
    public:
        TesterItem(TesterData* data);
        GtkWidget* getView();
        void update();
    private:
        TesterData*  mData;
        GtkWidget* mRoot;
        GtkWidget* mLabelHealth;
        GtkWidget* mLabelAttack;
    };
}
