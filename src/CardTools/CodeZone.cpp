#include "CodeZone.h"

using namespace CardTools;

CodeZone::CodeZone()
{
    mRoot = gtk_frame_new(nullptr);
    gtk_widget_set_size_request(mRoot, 200, 200);

    mTextView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(mRoot), mTextView);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, "Code Zone", -1);
}

GtkWidget* CodeZone::getRoot()
{
    return mRoot;
}