
#include <iostream>

#include "CardEffectListZone.h"
#include "CodeZone.h"
#include "StackZone.h"
#include "TestZone.h"
#include "SaveZone.h"

using namespace CardTools;

int main(int argc, char *argv[])
{

    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Card Tool");
    gtk_widget_set_size_request(window, 900, 800);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    TestZone testZone;
    StackZone stackZone(&testZone);
    CodeZone codeZone(window, &stackZone);
    CardEffectListZone cardEffectZone(window);
    SaveZone saveZone(window);

    saveZone.bind(&codeZone, &testZone, &cardEffectZone);
    cardEffectZone.bind(&codeZone, &stackZone, &saveZone);

    GtkWidget* table = gtk_table_new(2, 3, TRUE);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_table_attach_defaults(GTK_TABLE(table), cardEffectZone.getRoot(), 0, 1, 0, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), codeZone.getRoot(), 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), stackZone.getRoot(), 2, 3, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), testZone.getRoot(), 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), saveZone.getRoot(), 2, 3, 1, 2);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}