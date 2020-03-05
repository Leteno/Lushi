#include <memory>
#include <stdlib.h>
#include <cstring>

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "CodeZone.h"

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

    table = gtk_table_new(5, 5, TRUE);
    gtk_container_add(GTK_CONTAINER(mRoot), table);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mTextView));
    gtk_text_buffer_set_text(buffer, text, -1);
    gtk_table_attach_defaults(GTK_TABLE(table), mTextView, 0, 5, 0, 4);

    button = gtk_button_new_with_label("Compile");
    g_signal_connect(button, "clicked", G_CALLBACK(triggerOnCompile), this);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 5, 4, 5);
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

    int success = 0;
    char reason[100];
    char out[1024 * 4];
    compile(content, &success, reason, out);
    if (success)
    {
        mStackZone->update(out);
    }
    else
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new (
            GTK_WINDOW (mWindow),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK_CANCEL,
            reason
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

static void compile(const char* content, int *success, char* reason, char* out)
{
    commandline("python3 ../../tools/CodeGenerator/buildInstructionCode.py", content, success, out, reason);
}

static void commandline(const char* command, const char* input, int* success, char* out, char* err)
{

    // cat > /tmp/juzhen-CodeZone.tmp
    char* tempFile = "/tmp/juzhen-CodeZone.tmp";
    char catCommand[100];
    strcpy(catCommand, "cat > ");
    strcat(catCommand, tempFile);
    FILE *fpCat = popen(catCommand, "w");
    if (!fpCat)
    {
        *success = 0;
        strcpy(err, "cannot store content to ");
        strcat(err, tempFile);
        return;
    }
    fputs(input, fpCat);
    pclose(fpCat);

    char realCommand[100];
    strcpy(realCommand, "cat ");
    strcat(realCommand, tempFile);
    strcat(realCommand, " | ");
    strcat(realCommand, command);
    FILE *fp = popen(realCommand, "r");

    if (!fp)
    {
        *success = 0;
        strcpy(err, "cannot open: ");
        strcat(err, command);
        return;
    }

    char buff[1024];
    while (memset(buff, 0, sizeof(buff)), fgets(buff, sizeof(buff) - 1, fp) != 0)
    {
        strcat(out, buff);
    }
    *success = 1;

    // TODO the case when command return error

    pclose(fp);
}