
#include <gtk/gtk.h>

#include "CardEffectsModel.h"
#include "CardEffectListZone.h"
#include "Constant.h"

#include <iostream>

using namespace card;
using namespace CardTools;

static GtkWidget* sLastClickedView;
static GdkColor sColorOnNormal;
static GdkColor sColorOnSelected;
static void onItemClicked(GtkWidget* view, CardEffect* effect);

CardEffectListZone::CardEffectListZone(GtkWidget* window) :
    mWindow(window) {

    mModel.readFromFile(Constant::path::cardEffectFile);

    mRoot = gtk_table_new(1, 16, TRUE);
    mListView = gtk_table_new(12, 12, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mListView, 0, 16, 0, 1);

    gdk_color_parse("white", &sColorOnNormal);
    gdk_color_parse("yellow", &sColorOnSelected);

    update();
}

static void removeWidget(GtkWidget* child, GtkContainer* parent)
{
    gtk_container_remove(parent, child);
    gtk_widget_destroy(child);
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
        GtkWidget *button = gtk_button_new_with_label(effect->getName().c_str());
        gtk_table_attach_defaults(
            GTK_TABLE(mListView),
            button,
            0, 12, i, i+1
        );
        g_signal_connect(
            button,
            "clicked",
            G_CALLBACK(onItemClicked),
            effect
        );
        gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &sColorOnNormal);
        gtk_widget_modify_bg(button, GTK_STATE_PRELIGHT, &sColorOnNormal);
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

void onItemClicked(GtkWidget* view, CardEffect* effect)
{
    std::cout << "itemClicked: " << effect->getName() << std::endl;

    gtk_widget_modify_bg(view, GTK_STATE_NORMAL, &sColorOnSelected);
    gtk_widget_modify_bg(view, GTK_STATE_PRELIGHT, &sColorOnSelected);

    if (sLastClickedView != nullptr)
    {
        gtk_widget_modify_bg(sLastClickedView, GTK_STATE_NORMAL, &sColorOnNormal);
        gtk_widget_modify_bg(sLastClickedView, GTK_STATE_PRELIGHT, &sColorOnNormal);
    }
    sLastClickedView = view;
}