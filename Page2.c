#include "Page2.h"
#include "Cms.h"

// Global variable to hold the root box for Page2.
GtkWidget *rootBox = NULL;

// Global variable to hold the content box where the page content will be dynamically added.
GtkWidget *contentBox = NULL;

// Callback function to handle deletion of a row after confirmation
void confirmDelete(GtkDialog *dialog, int response_id, gpointer user_data) {
    if (response_id == GTK_RESPONSE_YES) {
        // Retrieve the row widget and its associated ID
        GtkWidget *row = GTK_WIDGET(user_data);
        int contact_id = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "contact_id"));

        // Call removeContact with the ID
        CMSResult result = removeContact(contact_id);

        if (result.success) {
            updatePage2();
        } else {
            g_print("Error removing contact: %s\n", result.error);
        }
    }

    // Destroy the confirmation dialog to clean up
    gtk_window_destroy(GTK_WINDOW(dialog));
}

// Callback function to show a confirmation dialog when a "Delete" button is clicked.
void showConfirmationDialog(GtkButton *button, gpointer user_data) {
    // Retrieve the row widget associated with the delete button.
    GtkWidget *row = GTK_WIDGET(user_data);

    // Create a modal dialog asking the user for confirmation.
    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
        "Are you sure you want to delete this item?"
    );

    // Connect the dialog's response signal to the confirmDelete function.
    g_signal_connect(dialog, "response", G_CALLBACK(confirmDelete), row);

    // Display the dialog to the user.
    gtk_window_present(GTK_WINDOW(dialog));
}

// Function to populate the content box with a scrollable list of contacts.
void addPageContent() {
    // If the content box hasn't been initialized, return early.
    if (contentBox == NULL) {
        return;
    }

    // Create a scrolled window to allow scrolling through the content.
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolled_window, TRUE); // Allow vertical expansion.
    gtk_widget_set_hexpand(scrolled_window, TRUE); // Allow horizontal expansion.
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Create a vertical box to hold the list of names and phone numbers.
    GtkWidget *list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_start(list_box, 10);
    gtk_widget_set_margin_end(list_box, 10);
    gtk_widget_set_margin_top(list_box, 10);
    gtk_widget_set_margin_bottom(list_box, 10);

    // Get the total number of contacts and the contact list from CMS.
    int contactCount = getContactCount();
    const Contact *contacts = getContacts();

    // Loop through each contact to add them to the list box.
    for (int i = 0; i < contactCount; i++) {
        // Retrieve the current contact.
        const Contact contact = contacts[i];

        // Create a horizontal box for the name, phone number, and delete button.
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

        // Create a label to display the contact's id.
        char id_str[10];
        snprintf(id_str, sizeof(id_str), "%d", contact.id);
        GtkWidget *id_label = gtk_label_new(id_str);

        // Create a label to display the contact's name.
        GtkWidget *name_label = gtk_label_new(contact.name);

        // Create a label to display the contact's phone number.
        GtkWidget *phone_label = gtk_label_new(contact.phone);

        // Align the labels to the start (left).
		gtk_widget_set_halign(id_label, GTK_ALIGN_START);
        gtk_widget_set_halign(name_label, GTK_ALIGN_START);
        gtk_widget_set_halign(phone_label, GTK_ALIGN_START);

        // Add the labels to the horizontal box.
		gtk_box_append(GTK_BOX(row), id_label);
        gtk_box_append(GTK_BOX(row), name_label);
        gtk_box_append(GTK_BOX(row), phone_label);

		// Associate the contact's ID with the row widget
		g_object_set_data(G_OBJECT(row), "contact_id", GINT_TO_POINTER(contact.id));

        // Create a "Delete" button for the contact.
        GtkWidget *delete_button = gtk_button_new_with_label("Delete");

        // Connect the button's clicked signal to showConfirmationDialog.
        g_signal_connect(delete_button, "clicked", G_CALLBACK(showConfirmationDialog), row);

        // Add the delete button to the horizontal box.
        gtk_box_append(GTK_BOX(row), delete_button);

        // Add the horizontal box (row) to the list box.
        gtk_box_append(GTK_BOX(list_box), row);
    }

    // Set the list box as the child of the scrolled window.
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), list_box);

    // Add the scrolled window to the content box.
    gtk_box_append(GTK_BOX(contentBox), scrolled_window);
}

// Function to create Page2 and its layout.
GtkWidget* createPage2() {
    // Create the root vertical box to hold the content.
    rootBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Create the content box to hold dynamic content.
    contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add the content box to the root box.
    gtk_box_append(GTK_BOX(rootBox), contentBox);

    // Populate the content box with contacts.
    addPageContent();

    // Return the root box as the widget representing Page2.
    return rootBox;
}

// Function to update Page2 by recreating its content.
void updatePage2() {
    // If the root box hasn't been initialized, return early.
    if (rootBox == NULL) {
        return;
    }

    // Remove the existing content box from the root box.
    gtk_box_remove(GTK_BOX(rootBox), contentBox);

    // Create a new content box with updated margins.
    contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Add the new content box to the root box.
    gtk_box_append(GTK_BOX(rootBox), contentBox);

    // Repopulate the content box with the updated list of contacts.
    addPageContent();
}
