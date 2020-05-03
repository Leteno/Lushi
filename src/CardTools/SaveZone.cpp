
#include "SaveZone.h"

using namespace CardTools;

SaveZone::SaveZone(GtkWidget* window)
    : mWindow(window)
{
    mRoot = gtk_table_new(1, 1, TRUE);
    GtkWidget* textView = gtk_label_new_with_mnemonic("Save Zone");
    gtk_container_add(GTK_CONTAINER(mRoot), textView);
}

GtkWidget* SaveZone::getRoot()
{
    return mRoot;
}