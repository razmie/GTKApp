#include <gtk/gtk.h>

// Callback to delete a row after confirmation
static void confirm_delete(GtkDialog *dialog, int response_id, gpointer user_data) {
    if (response_id == GTK_RESPONSE_YES) {
        GtkWidget *row = GTK_WIDGET(user_data);
        gtk_widget_unparent(row);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

// Callback to show a confirmation dialog
static void show_confirmation_dialog(GtkButton *button, gpointer user_data) {
    GtkWidget *row = GTK_WIDGET(user_data);

    // Create the dialog
    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
        "Are you sure you want to delete this item?"
    );

    // Connect the response signal
    g_signal_connect(dialog, "response", G_CALLBACK(confirm_delete), row);

    // Show the dialog
    gtk_window_present(GTK_WINDOW(dialog));
}

// Function to create the page
GtkWidget* create_page2() {
    // Create a vertical box to hold the scrollable window and its content
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

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

    // Add example data
    for (int i = 0; i < 10; i++) {
        char name[50];
        char phone[50];
        snprintf(name, sizeof(name), "Name %d", i + 1);
        snprintf(phone, sizeof(phone), "Phone %d", i + 1000);

        // Create a horizontal box for each name and phone number pair
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

        // Create labels for name and phone number
        GtkWidget *name_label = gtk_label_new(name);
        GtkWidget *phone_label = gtk_label_new(phone);

        // Set alignment for labels
        gtk_widget_set_halign(name_label, GTK_ALIGN_START);
        gtk_widget_set_halign(phone_label, GTK_ALIGN_START);

        // Add labels to the row
        gtk_box_append(GTK_BOX(row), name_label);
        gtk_box_append(GTK_BOX(row), phone_label);

        // Create a "Delete" button
        GtkWidget *delete_button = gtk_button_new_with_label("Delete");
        g_signal_connect(delete_button, "clicked", G_CALLBACK(show_confirmation_dialog), row);

        // Add the delete button to the row
        gtk_box_append(GTK_BOX(row), delete_button);

        // Add the row to the list box
        gtk_box_append(GTK_BOX(list_box), row);
    }

    // Add the list box to the scrolled window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), list_box);

    // Add the scrolled window to the main vertical box
    gtk_box_append(GTK_BOX(vbox), scrolled_window);

    return vbox;
}
