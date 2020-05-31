
#include <assert.h>

#include "string.h"
#include "SaveZone.h"
#include "Utils.h"
#include "Constant.h"

#include "../persist/FileDB.h"

using namespace CardTools;
using namespace card;

static void onSaveButtonClicked(GtkWidget* view, SaveZone* saveZone);

SaveZone::SaveZone(GtkWidget* window)
    : mWindow(window)
{
    mRoot = gtk_table_new(12, 12, TRUE);

    GtkWidget* title = gtk_label_new_with_mnemonic("Save Zone");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), title, 4, 8, 0, 1);

    GtkWidget* nameLabel = gtk_label_new_with_mnemonic("Name:");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), nameLabel, 2, 5, 2, 3);
    mNameText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mNameText, 7, 10, 2, 3);

    GtkWidget* saveButton = gtk_button_new_with_label("Save");
    g_signal_connect(saveButton, "clicked", G_CALLBACK(onSaveButtonClicked), this);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), saveButton, 7, 10, 5, 6);
}

GtkWidget* SaveZone::getRoot()
{
    return mRoot;
}

void SaveZone::save()
{
    CardEffect cardEffect;
    auto name = Utils::getEntryContent(mNameText);
    if (strlen(name) == 0)
    {
        Utils::showMessageDialog(mWindow, "Name should not be empty");
        return;
    }
    cardEffect.setName(name);
    cardEffect.setOriginalCode(mCodeZone->getAllCode());
    auto instructions = mTestZone->getInstructions();
    if (instructions.size() == 0)
    {
        Utils::showMessageDialog(mWindow, "Instruction is empty. Please run \"compile\" to generate it");
        return;
    }
    cardEffect.setInstructionList(instructions);
    mCardEffectListZone->save(cardEffect);
}

void SaveZone::saveToFile(CardEffect cardEffect)
{
    printf("cardEffect: \nname: %s\noriginalCode: %s\nInstructionSize: %d\n",
        cardEffect.getName().c_str(),
        cardEffect.getOriginalCode().c_str(),
        cardEffect.getInstructionList().size());
    std::string filePath = Constant::path::cardEffectFile;
    Parcel parcel(10 * 1024);
    cardEffect.writeToParcel(&parcel);
    int retCode = -1;
    FileDB::saveToFile(filePath, parcel.toString(), &retCode);
    assert(retCode == 0);
}

static void onSaveButtonClicked(GtkWidget* view, SaveZone* saveZone)
{
    saveZone->save();
}