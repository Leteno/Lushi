
#include "SaveZone.h"

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
    GtkWidget* nameText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(mRoot), nameText, 7, 10, 2, 3);

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
    printf("onSaveButton clicked\n");
}

void SaveZone::saveToFile(CardEffect cardEffect)
{}

static void onSaveButtonClicked(GtkWidget* view, SaveZone* saveZone)
{
    saveZone->save();
}