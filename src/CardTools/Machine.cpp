
#include <iostream>

#include "CodeZone.h"
#include "StackZone.h"
#include "TestZone.h"

using namespace CardTools;

int main(int argc, char *argv[])
{

    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Card Tool");
    gtk_widget_set_size_request(window, 900, 400);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    TestZone testZone;
    StackZone stackZone;
    CodeZone codeZone(window, &stackZone);

    GtkWidget* table = gtk_table_new(1, 3, TRUE);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_table_attach_defaults(GTK_TABLE(table), codeZone.getRoot(), 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), stackZone.getRoot(), 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), testZone.getRoot(), 2, 3, 0, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}