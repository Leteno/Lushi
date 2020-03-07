#include <gtk/gtk.h>

#include "TestZone.h"
#include "Utils.h"

using namespace CardTools;

static void onAddClick(GtkWidget* view, TestZone* testZone);
static void onRunClick(GtkWidget* view, TestZone* testZone);

TestZone::TestZone()
{
    mRoot = gtk_table_new(4, 4, TRUE);
    mTestList = gtk_scrolled_window_new(NULL, NULL);
    //gtk_widget_set_vexpand(mTestList, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mTestList, 3, 4, 0, 4);

    GtkWidget *table;
    GtkWidget *labelHealth, *textHealth;
    GtkWidget *labelAttach, *textAttach;
    GtkWidget *buttonAdd, *buttonRun;

    table = gtk_table_new(6, 6, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), table, 0, 3, 0, 4);

    labelHealth = gtk_label_new_with_mnemonic("Health: ");
    mHealthText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), labelHealth, 1, 3, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), mHealthText, 3, 4, 1, 2);

    labelAttach = gtk_label_new_with_mnemonic("Attach: ");
    mAttachText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), labelAttach, 1, 3, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), mAttachText, 3, 4, 2, 3);

    buttonAdd = gtk_button_new_with_label("Add");
    g_signal_connect(buttonAdd, "clicked", G_CALLBACK(onAddClick), this);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonAdd, 3, 4, 3, 4);

    buttonRun = gtk_button_new_with_label("Run");
    g_signal_connect(buttonRun, "clicked", G_CALLBACK(onRunClick), this);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonRun, 3, 4, 4, 5);
}

void TestZone::addSample(int health, int attach)
{
}

void TestZone::setInstruction()
{
}

void TestZone::runTest()
{
}

GtkWidget* TestZone::getRoot()
{
    return mRoot;
}

static void onAddClick(GtkWidget* view, TestZone* testZone)
{
    char* healthStr = Utils::getContent(testZone->mHealthText);
    char* attachStr = Utils::getContent(testZone->mAttachText);
    int healthInt = Utils::str2int(healthStr);
    int attachInt = Utils::str2int(attachStr);
    testZone->addSample(healthInt, attachInt);
    g_free(healthStr);
    g_free(attachStr);
}

static void onRunClick(GtkWidget* view, TestZone* testZone)
{
    testZone->runTest();
}