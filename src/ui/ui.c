#include <gtk/gtk.h>
#include "ui.h"

/* static void btn_msg(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Hello, world! 2");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
} */

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;

    GtkWidget *toolbar_box;
    GtkWidget *slider_box;
    // GtkWidget *button;
    // GtkWidget *button_box;

    GtkWidget *grid;

    // ===

    GtkWidget *toolbar;

    GtkToolItem *zoom_in_tb;
    GtkToolItem *zoom_out_tb;

    // ===

    GtkWidget *slider;

    // ====================

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Vantage");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);

    grid = gtk_grid_new();
    // set window to grid
    gtk_container_add(GTK_CONTAINER(window), grid);

    // ====================

    toolbar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach(GTK_GRID(grid), toolbar_box, 0, 0, 1, 1);

    /* button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);
    button = gtk_button_new_with_label("Click Me!");
    g_signal_connect(button, "clicked", G_CALLBACK(btn_msg), NULL);
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), button); */

    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_orientable_set_orientation(GTK_ORIENTABLE(toolbar), GTK_ORIENTATION_VERTICAL);

    zoom_in_tb  = gtk_tool_button_new_from_stock(GTK_STOCK_ZOOM_IN);
    zoom_out_tb = gtk_tool_button_new_from_stock(GTK_STOCK_ZOOM_OUT);

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), zoom_in_tb, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), zoom_out_tb, -1);

    gtk_box_pack_start(GTK_BOX(toolbar_box), toolbar, FALSE, FALSE, 5);

    // ====================

    slider_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(grid), slider_box, 1, 0, 1, 1);
    gtk_widget_set_vexpand(slider_box, TRUE);

    slider = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, 0, 2022, 1); // TODO: Make this update dynamically [2022 >>]
    // make slider fill entire comlumn
    // gtk_widget_set_valign(slider, GTK_ALIGN_FILL);
    // printf("%d\n", (int)gtk_widget_get_valign(slider));
    gtk_box_pack_start(GTK_BOX(slider_box), slider, FALSE, FALSE, 5);

    gtk_scale_set_value_pos(GTK_SCALE(slider), GTK_POS_BOTTOM);
    gtk_scale_set_has_origin(GTK_SCALE(slider), FALSE);
    gtk_range_set_inverted(GTK_RANGE(slider), TRUE);
    gtk_range_set_value(GTK_RANGE(slider), 2022); // TODO: Same as todo above

    // ====================

    gtk_widget_show_all(window);
}

int ui_init(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
