/*
    MAP DISPLAY WIDGET
    PART OF PIPELINE : shp >> viewer >> ui
*/

#include <gtk/gtk.h>
#include "viewer.h"

gboolean viewer_callback(GtkWidget* widget, cairo_t* cr, gpointer data) {
    guint width, height;
    GdkRGBA color;
    GtkStyleContext* context;

    context = gtk_widget_get_style_context(widget);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, width, height);

    // print width and height
    g_print("%d %d\n", width, height);

    cairo_rectangle(cr, width / 2 - 50, height / 2 - 50, 100, 100);

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke_preserve(cr);

    cairo_set_source_rgb(cr, 255.0, 0.0, 255.0);
    cairo_fill(cr);

    gtk_style_context_get_color(context, gtk_style_context_get_state(context), &color);
    gdk_cairo_set_source_rgba(cr, &color);

    cairo_fill(cr);

    return FALSE;
}
