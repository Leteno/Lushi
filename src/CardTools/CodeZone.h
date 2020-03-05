
#include <gtk/gtk.h>

namespace CardTools {
    class CodeZone {
        public:
            CodeZone(GtkWidget* window);
            GtkWidget* getRoot();
            void onCompile();
        private:
            GtkWidget* mWindow;
            GtkWidget* mRoot;
            GtkWidget* mTextView;
    };
}
