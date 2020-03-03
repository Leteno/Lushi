
#include <iostream>

#include "CodeZone.h"
#include "StackZone.h"

using namespace CardTools;

int main(int argc, char *argv[])
{

    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Card Tool");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    StackZone stackZone;
    CodeZone codeZone;

    gtk_container_add(GTK_CONTAINER(window), stackZone.getRoot());
    gtk_container_add(GTK_CONTAINER(window), codeZone.getRoot());

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}