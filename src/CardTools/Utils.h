#pragma once

#include <gtk/gtk.h>

namespace Utils {

/**
 * return the text in TextView.
 * please execute g_free(char*) when you finish.
 */
char* getTextViewContent(GtkWidget* textView);
const char* getEntryContent(GtkWidget* textView);

int str2int(const char* str);

}