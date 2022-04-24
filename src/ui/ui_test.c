#include <gtk/gtk.h>

static void btn_msg(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Hello, world!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new (app);
    gtk_window_set_title(GTK_WINDOW(window), "Test Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    button = gtk_button_new_with_label("Click Me!");
    g_signal_connect(button, "clicked", G_CALLBACK(btn_msg), NULL);
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), button);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
