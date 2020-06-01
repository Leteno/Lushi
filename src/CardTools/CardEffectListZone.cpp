
#include <gtk/gtk.h>

#include "CardEffectsModel.h"
#include "CardEffectListZone.h"
#include "Utils.h"
#include "Constant.h"

#include <iostream>

using namespace card;
using namespace CardTools;

static CardEffect* sSelectedCardEffect;
static GdkColor sColorOnNormal;
static GdkColor sColorOnSelected;
static void onItemClicked(GtkWidget* view, CardEffectListAdapter* adapter);
static void onNewButtonClicked(GtkWidget* view, CardEffectListZone* zone);
static void onDeleteButtonClicked(GtkWidget* view, CardEffectListZone* zone);

CardEffectListZone::CardEffectListZone(GtkWidget* window) :
    mWindow(window), mAdapter(nullptr), mSaveZone(nullptr),
    mStackZone(nullptr), mCodeZone(nullptr) {

    mModel.readFromFile(Constant::path::cardEffectFile);

    mRoot = gtk_table_new(16, 16, TRUE);
    mListView = gtk_table_new(12, 12, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mListView, 0, 15, 0, 15);

    GtkWidget *newButton = gtk_button_new_with_label("New");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), newButton, 1, 6, 14, 15);
    g_signal_connect(
        newButton,
        "clicked",
        G_CALLBACK(onNewButtonClicked),
        this
    );

    GtkWidget *deleteButton = gtk_button_new_with_label("Delete");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), deleteButton, 10, 15, 14, 15);
    g_signal_connect(
        deleteButton,
        "clicked",
        G_CALLBACK(onDeleteButtonClicked),
        this
    );

    gdk_color_parse("white", &sColorOnNormal);
    gdk_color_parse("yellow", &sColorOnSelected);

    updateUI();
}

static void removeWidget(GtkWidget* child, GtkContainer* parent)
{
    gtk_container_remove(parent, child);
    gtk_widget_destroy(child);
}

void CardEffectListZone::updateUI()
{
    gtk_container_foreach(
        GTK_CONTAINER(mListView),
        (GtkCallback)removeWidget,
        GTK_CONTAINER(mListView)
    );
    if (mAdapter != nullptr) delete mAdapter;

    auto effectsList = mModel.getCardEffectList();
    if (effectsList.size() > 0)
    {
        mAdapter = new CardEffectListAdapter[effectsList.size()];
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
            mAdapter[i].effect = effect;
            mAdapter[i].zone = this;
            g_signal_connect(
                button,
                "clicked",
                G_CALLBACK(onItemClicked),
                mAdapter + i
            );
            if (sSelectedCardEffect == effect)
            {
                gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &sColorOnSelected);
                gtk_widget_modify_bg(button, GTK_STATE_PRELIGHT, &sColorOnSelected);
            }
            else
            {
                gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &sColorOnNormal);
                gtk_widget_modify_bg(button, GTK_STATE_PRELIGHT, &sColorOnNormal);
            }
        }
    }

    gtk_widget_show_all(mListView);
}

CardEffect* CardEffectListZone::addNewCard()
{
    CardEffect* cardE = mModel.addNew();
    return cardE;
}

void CardEffectListZone::save()
{
    mModel.saveToFile(Constant::path::cardEffectFile);
}

void CardEffectListZone::deleteItem(CardEffect* cardEffect)
{
    if (cardEffect == nullptr)
    {
        Utils::showMessageDialog(mWindow, "deleteItem on empty one");
        return;
    }
    if (mModel.remove(cardEffect))
    {
        std::cout << "deleteItem " << cardEffect->getName() << std::endl;
        updateUI();
    }
    else
    {
        Utils::showMessageDialog(mWindow, "DeleteItem fail");
    }
}

void CardEffectListZone::updateCurrentCard(CardEffect* card)
{
    if (mCodeZone != nullptr)
    {
        mCodeZone->setCode(card->getOriginalCode());
    }
    if (mStackZone != nullptr)
    {
        mStackZone->updateInstruction(card->getInstructionList());
    }
    if (mSaveZone != nullptr)
    {
        mSaveZone->setCard(card);
    }
}

GtkWidget* CardEffectListZone::getRoot()
{
    return mRoot;
}

void onItemClicked(GtkWidget* view, CardEffectListAdapter* adapter)
{
    CardEffectListZone* zone = adapter->zone;
    CardEffect* effect = adapter->effect;
    zone->updateCurrentCard(effect);
    std::cout << "itemClicked: " << effect->getName() << std::endl;
    sSelectedCardEffect = effect;
    zone->updateUI();
}

void onNewButtonClicked(GtkWidget* view, CardEffectListZone* zone)
{
    CardEffect* newCard = zone->addNewCard();
    sSelectedCardEffect = newCard;
    zone->updateCurrentCard(newCard);
    zone->updateUI();
}

void onDeleteButtonClicked(GtkWidget* view, CardEffectListZone* zone)
{
    zone->deleteItem(sSelectedCardEffect);
    sSelectedCardEffect = nullptr;
    zone->updateUI();
}
