// This is an include guard. It prevents multiple inclusions of this header file in a single compilation unit.
#ifndef PAGE2_H
#define PAGE2_H

// Includes the GTK library header to provide access to GTK types and functions,
// required for creating and managing GTK widgets.
#include <gtk/gtk.h>

GtkWidget* createPage2();
void updatePage2();

// Marks the end of the include guard, ensuring the file is only included once.
#endif // PAGE2_H