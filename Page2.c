#include <gtk/gtk.h>
#include "Cms.h"

GtkWidget *rootBox = NULL;
GtkWidget *contentBox = NULL;

// Callback to delete a row after confirmation
static void confirmDelete(GtkDialog *dialog, int response_id, gpointer user_data) {
    if (response_id == GTK_RESPONSE_YES) {
        GtkWidget *row = GTK_WIDGET(user_data);
        gtk_widget_unparent(row);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

// Callback to show a confirmation dialog
static void showConfirmationDialog(GtkButton *button, gpointer user_data) {
    GtkWidget *row = GTK_WIDGET(user_data);

    // Create the dialog
    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
        "Are you sure you want to delete this item?"
    );

    // Connect the response signal
    g_signal_connect(dialog, "response", G_CALLBACK(confirmDelete), row);

    // Show the dialog
    gtk_window_present(GTK_WINDOW(dialog));
}

void addPageContent() {
	if (contentBox == NULL) {
		return;
	}

	// Create a scrolled window
	GtkWidget *scrolled_window = gtk_scrolled_window_new();
	gtk_widget_set_vexpand(scrolled_window, TRUE);
	gtk_widget_set_hexpand(scrolled_window, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	// Create a box to hold the list of names and phone numbers
	GtkWidget *list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_margin_start(list_box, 10);
	gtk_widget_set_margin_end(list_box, 10);
	gtk_widget_set_margin_top(list_box, 10);
	gtk_widget_set_margin_bottom(list_box, 10);

	int contactCount = getContactCount();
	const Contact *contacts = getContacts();

	// Add example data
	for (int i = 0; i < contactCount; i++) {

		const Contact contact = contacts[i];

		// Create a horizontal box for each name and phone number pair
		GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

		// Create labels for name and phone number
		GtkWidget *name_label = gtk_label_new(contact.name);
		GtkWidget *phone_label = gtk_label_new(contact.phone);

		// Set alignment for labels
		gtk_widget_set_halign(name_label, GTK_ALIGN_START);
		gtk_widget_set_halign(phone_label, GTK_ALIGN_START);

		// Add labels to the row
		gtk_box_append(GTK_BOX(row), name_label);
		gtk_box_append(GTK_BOX(row), phone_label);

		// Create a "Delete" button
		GtkWidget *delete_button = gtk_button_new_with_label("Delete");
		g_signal_connect(delete_button, "clicked", G_CALLBACK(showConfirmationDialog), row);

		// Add the delete button to the row
		gtk_box_append(GTK_BOX(row), delete_button);

		// Add the row to the list box
		gtk_box_append(GTK_BOX(list_box), row);
	}

	// Add the list box to the scrolled window
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), list_box);

	// Add the scrolled window to the main vertical box
    gtk_box_append(GTK_BOX(contentBox), scrolled_window);
}

// Function to create the page
GtkWidget* createPage2() {
    // Create a vertical box to hold the scrollable window and its content
    rootBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_append(GTK_BOX(rootBox), contentBox);

	addPageContent();

    return rootBox;
}

void updatePage2() {
	if (rootBox == NULL) {
		return;
	}

	// Recreate the page content buy removing the old content box and recreating it.
	gtk_box_remove(GTK_BOX(rootBox), contentBox);

	contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_box_append(GTK_BOX(rootBox), contentBox);

	addPageContent();
}