#include <memory>
#include <stdlib.h>
#include <string>
#include <cstring>

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "../machine/Compiler.h"

using namespace machine;

#include "CodeZone.h"
#include "Utils.h"

using namespace CardTools;

static void triggerOnCompile(GtkWidget* widget, CodeZone* codeZone)
{
    codeZone->onCompile();
}

static void compile(const char* content, int *success /* 0 for fail*/, char* reason, char* out);
static void commandline(const char* command, const char* input, int* success, char* stdout, char* stderr);

CodeZone::CodeZone(GtkWidget* window, StackZone* stackZone)
{
    mWindow = window;
    mStackZone = stackZone;
    mRoot = gtk_frame_new(nullptr);
    mTextView = gtk_text_view_new();

    GtkWidget* table;
    GtkWidget* button;
    GtkTextBuffer *buffer;
    char* text = "sum = 0;\n"
"count = 0;\n"
"foreach_obj obj {\n"
"    sum = sum + obj.getHealth();\n"
"    count = count + 1;\n"
"}\n"
"\n"
"average = sum / count;\n"
"\n"
"foreach_obj obj {\n"
"    k = obj.getHealth();\n"
"    if (k < average) {\n"
"        obj.setHealth(k + 10);\n"
"    }\n"
"    else if (k > average){\n"
"        obj.setHealth(k - 10);\n"
"    }\n"
"}\n";
    text = "enter code here, see this for detail:\n  tools/CodeGenerator/buildInstructionCode.py";

    table = gtk_table_new(10, 10, TRUE);
    gtk_container_add(GTK_CONTAINER(mRoot), table);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, text, -1);
    gtk_table_attach_defaults(GTK_TABLE(table), mTextView, 0, 10, 0, 9);

    button = gtk_button_new_with_label("Compile");
    g_signal_connect(button, "clicked", G_CALLBACK(triggerOnCompile), this);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 7, 10, 9, 10);
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

    char out[1024 * 4];
    try {
        std::string contentStr(content);
        auto instructionList = Compiler::compile(contentStr);
        mStackZone->updateInstruction(instructionList);
    } catch (exception& e) {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new (
            GTK_WINDOW (mWindow),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK_CANCEL,
            out
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

std::string CodeZone::getAllCode()
{
    std::string out = Utils::getTextViewContent(mTextView);
    return out;
}

void CodeZone::setCode(std::string newCode)
{
    Utils::setTextViewContent(mTextView, newCode);
}
