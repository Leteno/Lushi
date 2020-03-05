#include <memory>
#include <stdlib.h>
#include <cstring>

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "CodeZone.h"

using namespace CardTools;

static void triggerOnCompile(GtkWidget* widget, CodeZone* codeZone)
{
    codeZone->onCompile();
}

static void compile(const char* content, int *success /* 0 for fail*/, char* reason, char* out);

CodeZone::CodeZone(GtkWidget* window, StackZone* stackZone)
{
    mWindow = window;
    mStackZone = stackZone;
    mRoot = gtk_frame_new(nullptr);
    mTextView = gtk_text_view_new();

    GtkWidget* table;
    GtkWidget* button;
    GtkTextBuffer *buffer;

    table = gtk_table_new(5, 5, TRUE);
    gtk_container_add(GTK_CONTAINER(mRoot), table);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, "Code Zone", -1);
    gtk_table_attach_defaults(GTK_TABLE(table), mTextView, 0, 5, 0, 4);

    button = gtk_button_new_with_label("Compile");
    g_signal_connect(button, "clicked", G_CALLBACK(triggerOnCompile), this);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 5, 4, 5);
}

void CodeZone::onCompile()
{
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    char* content;
    gint response;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    g_assert(mWindow);

    int success = 0;
    char reason[100];
    char out[1024 * 4];
    compile(content, &success, reason, out);
    if (success)
    {
        mStackZone->update(out);
    }
    else
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new (
            GTK_WINDOW (mWindow),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK_CANCEL,
            reason
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    g_free(content);
}

GtkWidget* CodeZone::getRoot()
{
    return mRoot;
}

static void compile(const char* content, int *success, char* reason, char* out)
{
    if (strcmp(content, "Code Zone") == 0)
    {
        *success = 1;
        strcpy(out, "Wonderful");
    }
    else
    {
        *success = 0;
        strcpy(reason, "Text in Code Zone should be 'Code Zone'");
    }
}