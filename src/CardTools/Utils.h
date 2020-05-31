#pragma once

#include <gtk/gtk.h>
#include <string.h>

namespace Utils {

/**
 * return the text in TextView.
 * please execute g_free(char*) when you finish.
 */
char* getTextViewContent(GtkWidget* textView);
const char* getEntryContent(GtkWidget* textView);
void setTextViewContent(GtkWidget* textView, std::string content);

void showMessageDialog(GtkWidget *window, char* message);

int str2int(const char* str);

}