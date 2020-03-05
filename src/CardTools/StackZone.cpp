#include "StackZone.h"

using namespace CardTools;

StackZone::StackZone()
{
    mRoot = gtk_frame_new(nullptr);
    gtk_widget_set_size_request(mRoot, 200, 200);

    mTextView = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(mRoot), mTextView);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, "Stack Zone", -1);
}

GtkWidget* StackZone::getRoot()
{
    return mRoot;
}

void StackZone::update(char* data)
{
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, data, -1);
}