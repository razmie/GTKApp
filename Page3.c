#include "Page3.h"

// Function to create the third page of the application.
GtkWidget* createPage3()
{
    // Create a simple label widget with the text "This is Page 3".
    GtkWidget *page = gtk_label_new("This is Page 3");

    // Return the label widget, which represents the entire content of Page 3.
    return page;
}
