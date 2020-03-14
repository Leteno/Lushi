#include <gtk/gtk.h>
#include <stdio.h>

#include "TesterItem.h"
#include "TesterData.h"

using namespace CardTools;

TesterItem::TesterItem(TesterData* data)
{
    g_assert(data);
    mData = data;
    mRoot = gtk_table_new(1, 2, TRUE);
    mLabelHealth = gtk_label_new("A");
    mLabelAttack = gtk_label_new("B");
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mLabelHealth, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mLabelAttack, 0, 1, 1, 2);
}

GtkWidget* TesterItem::getView()
{
    update();
    return mRoot;
}

void TesterItem::update()
{
    char buffer[100];
    sprintf(buffer, "Health: %d", mData->mHealth);
    gtk_label_set_text(GTK_LABEL(mLabelHealth), buffer);
    sprintf(buffer, "Attack: %d", mData->mAttack);
    gtk_label_set_text(GTK_LABEL(mLabelAttack), buffer);
}