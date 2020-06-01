
#include <assert.h>

#include "string.h"
#include <iostream>

#include "SaveZone.h"
#include "Utils.h"
#include "Constant.h"

#include "../persist/FileDB.h"

using namespace CardTools;
using namespace card;

static void onSaveButtonClicked(GtkWidget* view, SaveZone* saveZone);

SaveZone::SaveZone(GtkWidget* window)
    : mWindow(window), mCard(nullptr)
{
    mRoot = gtk_table_new(12, 12, TRUE);

    GtkWidget* title = gtk_label_new_with_mnemonic("Save Zone");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), title, 4, 8, 0, 1);

    GtkWidget* nameLabel = gtk_label_new_with_mnemonic("Name:");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), nameLabel, 0, 3, 2, 3);
    mNameText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mNameText, 4, 10, 2, 3);

    GtkWidget* descLabel = gtk_label_new_with_mnemonic("Description:");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), descLabel, 0, 4, 3, 5);
    mDescText = gtk_text_view_new();
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mDescText, 4, 10, 3, 5);

    GtkWidget* saveButton = gtk_button_new_with_label("Save");
    g_signal_connect(saveButton, "clicked", G_CALLBACK(onSaveButtonClicked), this);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), saveButton, 7, 10, 6, 7);
}

GtkWidget* SaveZone::getRoot()
{
    return mRoot;
}

void SaveZone::save()
{
    auto name = Utils::getEntryContent(mNameText);
    if (strlen(name) == 0)
    {
        Utils::showMessageDialog(mWindow, "Name should not be empty");
        return;
    }
    auto originalCode = mCodeZone->getAllCode();
    std::string desc = Utils::getTextViewContent(mDescText);
    auto instructions = mTestZone->getInstructions();
    if (instructions.size() == 0)
    {
        Utils::showMessageDialog(mWindow, "Instruction is empty. Please run \"compile\" to generate it");
        return;
    }
    if (mCard == nullptr)
    {
        mCard = mCardEffectListZone->addNewCard();
    }
    mCard->setName(name);
    mCard->setOriginalCode(originalCode);
    mCard->setDescription(desc);
    mCard->setInstructionList(instructions);
    mCardEffectListZone->save();
    mCardEffectListZone->updateUI();
}

void SaveZone::setCard(CardEffect* newCard)
{
    Utils::setEntryContent(mNameText, newCard->getName());
    Utils::setTextViewContent(mDescText, newCard->getDescription());
    mCard = newCard;
}

static void onSaveButtonClicked(GtkWidget* view, SaveZone* saveZone)
{
    saveZone->save();
}