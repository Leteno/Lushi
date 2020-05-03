
#include "CardEffectListZone.h"

using namespace CardTools;

CardEffectListZone::CardEffectListZone(GtkWidget* window) :
    mWindow(window) {

    mRoot = gtk_frame_new(nullptr);
    GtkWidget* textView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(mRoot), textView);
}

GtkWidget* CardEffectListZone::getRoot()
{
    return mRoot;
}