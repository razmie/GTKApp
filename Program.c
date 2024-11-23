#include <gtk/gtk.h>
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

	// Create a new window.
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window with Stack");

	// Set the window size.
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

	// A vertical container box splits the window into two parts: the switcher (top) and the page area (bottom).
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Holds the different pages (e.g., page1, page2) to switch between them.
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_NONE);

    // Displays buttons for switching between the pages in the GtkStack.
    GtkWidget *stack_switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(stack));
    gtk_box_append(GTK_BOX(vbox), stack_switcher);

    // Add pages to the stack

    GtkWidget *page1 = createPage1();
    gtk_stack_add_titled(GTK_STACK(stack), page1, "page1", "Page 1");

    GtkWidget *page2 = createPage2();
    gtk_stack_add_titled(GTK_STACK(stack), page2, "page2", "Page 2");

    GtkWidget *page3 = createPage3();
    gtk_stack_add_titled(GTK_STACK(stack), page3, "page3", "Page 3");

    // Append the stack to the vbox
    gtk_box_append(GTK_BOX(vbox), stack);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.cms", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
