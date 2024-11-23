#include "Page1.h"
#include "Page2.h"
#include "Cms.h"

// Callback function for handling the "Add Contact" button click event.
void onAddContactButtonClicked(GtkButton *button, gpointer user_data)
{
    // Cast the user_data pointer back to an array of GtkWidget pointers (entries).
    GtkWidget **entries = (GtkWidget **)user_data;

    // Get the text input from the name entry field.
    const char *name = gtk_editable_get_text(GTK_EDITABLE(entries[0]));

    // Get the text input from the phone entry field.
    const char *phone = gtk_editable_get_text(GTK_EDITABLE(entries[1]));

    // Print debug information for the contact being added.
    g_print("Adding Contact:\n");
    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);

    // Call the addContact function to add the contact and store the result.
    CMSResult result = addContact(name, phone);

    // Check if the operation was unsuccessful.
    if (!result.success) {
        // Create an error dialog to display the failure message.
        GtkWidget *dialog = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
            "Error: %s", result.error
        );

        // Connect the "response" signal to destroy the dialog window when a button is clicked.
        g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);

        // Show the dialog to the user.
        gtk_window_present(GTK_WINDOW(dialog));
    }
    else {
        // If the operation was successful, update Page2 to reflect the new contact.
        updatePage2();
    }
}

// Function to create the first page of the application.
GtkWidget* createPage1()
{
    // Create a vertical box container with spacing of 10 pixels between children.
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Set margins around the vertical box for better spacing in the UI.
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_widget_set_margin_start(vbox, 20);
    gtk_widget_set_margin_end(vbox, 20);

    // Create a label for the "Name" field.
    GtkWidget *name_label = gtk_label_new("Name:");
    gtk_widget_set_halign(name_label, GTK_ALIGN_START); // Align the label to the start (left).
    gtk_box_append(GTK_BOX(vbox), name_label); // Add the label to the vertical box.

    // Create a text entry widget for the user to input their name.
    GtkWidget *name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Enter your name"); // Set placeholder text.
    gtk_editable_set_text(GTK_EDITABLE(name_entry), "Tipah"); // Pre-fill the entry with example text.
    gtk_box_append(GTK_BOX(vbox), name_entry); // Add the entry to the vertical box.

    // Create a label for the "Phone Number" field.
    GtkWidget *phone_label = gtk_label_new("Phone Number:");
    gtk_widget_set_halign(phone_label, GTK_ALIGN_START); // Align the label to the start (left).
    gtk_box_append(GTK_BOX(vbox), phone_label); // Add the label to the vertical box.

    // Create a text entry widget for the user to input their phone number.
    GtkWidget *phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Enter your phone number"); // Set placeholder text.
    gtk_editable_set_text(GTK_EDITABLE(phone_entry), "+441111111111"); // Pre-fill the entry with example text.
    gtk_box_append(GTK_BOX(vbox), phone_entry); // Add the entry to the vertical box.

    // Create a button labeled "Add Contact" for submitting the form.
    GtkWidget *add_button = gtk_button_new_with_label("Add Contact");
    gtk_widget_set_margin_top(add_button, 10); // Add top margin for spacing.
    gtk_widget_set_hexpand(add_button, TRUE); // Allow the button to expand horizontally.

    // Dynamically allocate an array to hold the name and phone entry widgets.
    GtkWidget **entries = g_new(GtkWidget*, 2);
    entries[0] = name_entry; // Store the name entry in the first position.
    entries[1] = phone_entry; // Store the phone entry in the second position.

    // Connect the "clicked" signal of the button to the onAddContactButtonClicked callback function,
    // passing the entries array as user data.
    g_signal_connect(add_button, "clicked", G_CALLBACK(onAddContactButtonClicked), entries);

    // Add the button to the vertical box.
    gtk_box_append(GTK_BOX(vbox), add_button);

    // Return the completed vertical box widget.
    return vbox;
}
