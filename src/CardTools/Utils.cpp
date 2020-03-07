
#include <string>

#include "Utils.h"

char* Utils::getContent(GtkWidget* textView)
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

int Utils::str2int(const char* str)
{
    return std::stoi(str);
}
