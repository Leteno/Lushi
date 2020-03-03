
#include <gtk/gtk.h>

namespace CardTools {
    class StackZone {
        public:
            StackZone();
            GtkWidget* getRoot();
        private:
            GtkWidget* mRoot;
            GtkWidget* mTextView;
    };
}