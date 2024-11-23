#include "Page1.h"

void on_name_entry_changed(GtkEntry *entry, gpointer user_data)
{
    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    g_print("Name Entry Updated: %s\n", text);
}

void on_phone_entry_changed(GtkEntry *entry, gpointer user_data)
{
    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    g_print("Phone Entry Updated: %s\n", text);
}

GtkWidget* create_page1()
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
	gtk_editable_set_text(GTK_EDITABLE(name_entry), "John Doe");
	g_signal_connect(name_entry, "changed", G_CALLBACK(on_name_entry_changed), NULL);
    gtk_box_append(GTK_BOX(vbox), name_entry);

    // Create a label for the "Phone Number" field
    GtkWidget *phone_label = gtk_label_new("Phone Number:");
	gtk_widget_set_halign(phone_label, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(vbox), phone_label);

    // Create an entry for the user to input their phone number
    GtkWidget *phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Enter your phone number");
	gtk_editable_set_text(GTK_EDITABLE(phone_entry), "123-456-7890");
	g_signal_connect(phone_entry, "changed", G_CALLBACK(on_phone_entry_changed), NULL);
    gtk_box_append(GTK_BOX(vbox), phone_entry);

    return vbox;
}