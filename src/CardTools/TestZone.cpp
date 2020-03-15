#include <gtk/gtk.h>

#include "../base/GameObject.h"
#include "../machine/Machine.h"

#include "TestZone.h"
#include "Utils.h"

#include "stdio.h"

#include "TesterData.h"
#include "TesterItem.h"

using namespace CardTools;
using namespace machine;

static void onAddClick(GtkWidget* view, TestZone* testZone);
static void onRunClick(GtkWidget* view, TestZone* testZone);

TestZone::TestZone()
{
    mRoot = gtk_table_new(4, 4, TRUE);
    mTestList = gtk_vbox_new(FALSE, 10);
    //gtk_widget_set_vexpand(mTestList, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), mTestList, 2, 4, 0, 4);

    GtkWidget *table;
    GtkWidget *labelHealth, *textHealth;
    GtkWidget *labelAttach, *textAttach;
    GtkWidget *buttonAdd, *buttonRun;

    table = gtk_table_new(12, 12, TRUE);
    gtk_table_attach_defaults(GTK_TABLE(mRoot), table, 0, 2, 0, 4);

    labelHealth = gtk_label_new_with_mnemonic("Health: ");
    mHealthText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), labelHealth, 0, 4, 1, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), mHealthText, 5, 8, 1, 4);

    labelAttach = gtk_label_new_with_mnemonic("Attach: ");
    mAttachText = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), labelAttach, 0, 4, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), mAttachText, 5, 8, 4, 5);

    buttonAdd = gtk_button_new_with_label("Add");
    g_signal_connect(buttonAdd, "clicked", G_CALLBACK(onAddClick), this);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonAdd, 1, 8, 6, 7);

    buttonRun = gtk_button_new_with_label("Run");
    g_signal_connect(buttonRun, "clicked", G_CALLBACK(onRunClick), this);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonRun, 1, 8, 7, 8);
}

void TestZone::addSample(int health, int attack)
{
    if (health < 0 || attack < 0)
    {
        return;
    }
    printf("Add Sample %d %d\n", health, attack);
    auto data = new TesterData(health, attack);
    auto item = new TesterItem(data);
    gtk_box_pack_start(GTK_BOX(mTestList), item->getView(), FALSE, FALSE, 0);
    gtk_widget_show_all(mTestList);
    mTesterItemList.push_back(item);
}

void TestZone::setInstruction(std::list<Sequence::Instruction> iList)
{
    printf("setInstruction\n");
    mInstList = iList;
}

void TestZone::runTest()
{
    printf("runTest\n");

    // prepare GameObjects
    std::list<GameObject*> gList;
    for (auto it = mTesterItemList.begin();
        it != mTesterItemList.end();
        ++it)
    {
        auto item = *it;
        GameObject* obj = new GameObject(0, 0);
        g_assert(obj);
        item->toGameObject(obj);
        gList.push_back(obj);
    }

    // run test
    State state(mInstList, gList);
    Machine machine;
    while(machine.executeOneInstruction(&state));

    // apply glist changes back to itemList
    g_assert(gList.size() == mTesterItemList.size());
    auto gIt = gList.begin();
    auto mIt = mTesterItemList.begin();
    for (;
        gIt != gList.end() && mIt != mTesterItemList.end();
        ++gIt, ++mIt)
    {
        auto pItem = *mIt;
        auto pGObj = *gIt;
        pItem->applyFrom(*pGObj);
        pItem->update();
    }

    // free memory
    for (auto obj : gList)
    {
        delete obj;
    }
}

GtkWidget* TestZone::getRoot()
{
    return mRoot;
}

static void onAddClick(GtkWidget* view, TestZone* testZone)
{
    const char* healthStr = Utils::getEntryContent(testZone->mHealthText);
    const char* attachStr = Utils::getEntryContent(testZone->mAttachText);
    int healthInt = Utils::str2int(healthStr);
    int attachInt = Utils::str2int(attachStr);
    testZone->addSample(healthInt, attachInt);
}

static void onRunClick(GtkWidget* view, TestZone* testZone)
{
    testZone->runTest();
}