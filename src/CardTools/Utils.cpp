
#include <string>

#include "Utils.h"

char* Utils::getTextViewContent(GtkWidget* textView)
{
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    char* content;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    return content;
}

void Utils::setTextViewContent(GtkWidget* textView, std::string newContent)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(textView)
    );
    gtk_text_buffer_set_text(buffer, newContent.c_str(), -1);
    gtk_widget_show_all(textView);
}

const char* Utils::getEntryContent(GtkWidget* entry)
{
    GtkEntryBuffer *buffer;
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    return gtk_entry_buffer_get_text(buffer);
}

void Utils::setEntryContent(GtkWidget* entry, std::string newContent)
{
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buffer, newContent.c_str(), -1);
}

void Utils::showMessageDialog(GtkWidget* window, char* message)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new (
        GTK_WINDOW (window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        message
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int Utils::str2int(const char* str)
{
    try {
        return std::stoi(str);
    } catch (std::exception& e) {
        return -1;
    }
}
