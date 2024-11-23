// Include the GTK library to access GTK types and functions.
#include <gtk/gtk.h>

// Include the headers for Page1, Page2, and Page3 to use their createPage functions.
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"

// Callback function that runs when the GTK application is activated.
static void activate(GtkApplication *app, gpointer user_data)
{
    // Declare a widget to represent the main application window.
    GtkWidget *window;

    // Create a new application window associated with the given GtkApplication instance.
    window = gtk_application_window_new(app);

    // Set the title of the application window.
    gtk_window_set_title(GTK_WINDOW(window), "Window with Stack");

    // Set the default size of the application window to 800x600 pixels.
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a vertical box container to split the window into two parts:
    // a stack switcher at the top and the stack itself below.
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Set the vertical box as the child of the main window.
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Create a GtkStack widget to manage multiple pages in a single view.
    GtkWidget *stack = gtk_stack_new();

    // Set the transition type for the stack to "none" (no animation when switching pages).
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_NONE);

    // Create a stack switcher widget that displays buttons to switch between stack pages.
    GtkWidget *stack_switcher = gtk_stack_switcher_new();

    // Associate the stack switcher with the GtkStack so it can control the stack.
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(stack));

    // Add the stack switcher to the top of the vertical box.
    gtk_box_append(GTK_BOX(vbox), stack_switcher);

    // Add pages to the stack.

    // Create Page 1 and add it to the stack with the title "Page 1".
    GtkWidget *page1 = createPage1();
    gtk_stack_add_titled(GTK_STACK(stack), page1, "page1", "Page 1");

    // Create Page 2 and add it to the stack with the title "Page 2".
    GtkWidget *page2 = createPage2();
    gtk_stack_add_titled(GTK_STACK(stack), page2, "page2", "Page 2");

    // Create Page 3 and add it to the stack with the title "Page 3".
    GtkWidget *page3 = createPage3();
    gtk_stack_add_titled(GTK_STACK(stack), page3, "page3", "Page 3");

    // Add the stack (which contains all the pages) to the vertical box below the switcher.
    gtk_box_append(GTK_BOX(vbox), stack);

    // Present the main window to the user (make it visible).
    gtk_window_present(GTK_WINDOW(window));
}

// Main function to initialize and run the GTK application.
int main(int argc, char **argv)
{
    // Declare a GtkApplication pointer to manage the application instance.
    GtkApplication *app;

    // Declare a variable to hold the exit status of the application.
    int status;

    // Create a new GtkApplication instance with the ID "org.gtk.cms" and default flags.
    app = gtk_application_new("org.gtk.cms", G_APPLICATION_DEFAULT_FLAGS);

    // Connect the "activate" signal of the GtkApplication to the activate callback function.
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application, passing in command-line arguments, and store the exit status.
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // Free the memory used by the GtkApplication instance.
    g_object_unref(app);

    // Return the application's exit status to the operating system.
    return status;
}
