#include "Page1.h"
#include "Page2.h"
#include "Cms.h"

// Callback to handle adding the contact
void onAddContactButtonClicked(GtkButton *button, gpointer user_data)
{
    GtkWidget **entries = (GtkWidget **)user_data;
    const char *name = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
    const char *phone = gtk_editable_get_text(GTK_EDITABLE(entries[1]));

    g_print("Adding Contact:\n");
    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);

	CMSResult result = addContact(name, phone); 
	if (!result.success) {
        // Show an error dialog if adding the contact fails
        GtkWidget *dialog = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
            "Error: %s", result.error
        );

        // Connect the "response" signal to close the dialog
        g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);

        // Show the dialog
        gtk_window_present(GTK_WINDOW(dialog));
	}
	else {
		// Recreate page2 to show new contact.
		updatePage2();
	}
}

GtkWidget* createPage1()
{
	// Create a vertical box to hold the form elements
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_widget_set_margin_start(vbox, 20);
    gtk_widget_set_margin_end(vbox, 20);

    // Create a label for the "Name" field
    GtkWidget *name_label = gtk_label_new("Name:");
	gtk_widget_set_halign(name_label, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(vbox), name_label);

    // Create an entry for the user to input their name
    GtkWidget *name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Enter your name");
	gtk_editable_set_text(GTK_EDITABLE(name_entry), "Tipah");
    gtk_box_append(GTK_BOX(vbox), name_entry);

    // Create a label for the "Phone Number" field
    GtkWidget *phone_label = gtk_label_new("Phone Number:");
	gtk_widget_set_halign(phone_label, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(vbox), phone_label);

    // Create an entry for the user to input their phone number
    GtkWidget *phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Enter your phone number");
	gtk_editable_set_text(GTK_EDITABLE(phone_entry), "+441111111111");
    gtk_box_append(GTK_BOX(vbox), phone_entry);

   // Create a button to add the contact
    GtkWidget *add_button = gtk_button_new_with_label("Add Contact");
    gtk_widget_set_margin_top(add_button, 10);
    gtk_widget_set_hexpand(add_button, TRUE);

    // Dynamically allocate the entries array and store the entry widgets
    GtkWidget **entries = g_new(GtkWidget *, 2);
    entries[0] = name_entry;
    entries[1] = phone_entry;

    // Connect the button signal and pass the entries array
    g_signal_connect(add_button, "clicked", G_CALLBACK(onAddContactButtonClicked), entries);

    gtk_box_append(GTK_BOX(vbox), add_button);

    return vbox;
}