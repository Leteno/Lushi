
#include <gtk/gtk.h>

#include "CardEffectsModel.h"
#include "CardEffectListZone.h"
#include "Constant.h"

using namespace card;
using namespace CardTools;

CardEffectListZone::CardEffectListZone(GtkWidget* window) :
    mWindow(window) {

    mModel.readFromFile(Constant::path::cardEffectFile);

    mRoot = gtk_table_new(16, 1, TRUE);
    GtkWidget* textView = gtk_text_view_new();
    gtk_table_attach_defaults(GTK_TABLE(mRoot), textView, 0, 1, 0, 1);

    mListView = gtk_table_new(12, 12, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mListView, 2, 15, 0, 1);

    update();
}

static void removeWidget(GtkWidget* child, GtkContainer* parent)
{
    gtk_container_remove(parent, child);
}

void CardEffectListZone::update()
{
    gtk_container_foreach(
        GTK_CONTAINER(mListView),
        (GtkCallback)removeWidget,
        GTK_CONTAINER(mListView)
    );
    auto effectsList = mModel.getCardEffectList();
    int i = 0;
    for (auto it = effectsList.begin();
        it != effectsList.end(); ++it, ++i)
    {
        CardEffect* effect = *it;
        GtkWidget *label = gtk_label_new_with_mnemonic(effect->getName().c_str());
        gtk_table_attach_defaults(
            GTK_TABLE(mListView),
            label,
            i, i+1, 0, 12
        );
    }
    gtk_widget_show_all(mListView);
}

void CardEffectListZone::save(CardEffect cardEffect)
{
    CardEffect* cardE = mModel.add(cardEffect);
    mModel.saveToFile(Constant::path::cardEffectFile);
    update();
}

GtkWidget* CardEffectListZone::getRoot()
{
    return mRoot;
}