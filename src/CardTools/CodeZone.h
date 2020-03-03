
#include <gtk/gtk.h>

namespace CardTools {
    class CodeZone {
        public:
            CodeZone();
            GtkWidget* getRoot();
        private:
            GtkWidget* mRoot;
            GtkWidget* mTextView;
    };
}
