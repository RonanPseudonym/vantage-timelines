/*
    MAP DISPLAY WIDGET
    PART OF PIPELINE : shp >> viewer >> ui
*/

#include <gtk/gtk.h>
#include "viewer.h"
#include "../utils/vector.h"
#include "../shp/read.h"
#include "../shp/types.h"

gboolean viewer_callback(GtkWidget* widget, cairo_t* cr, gpointer data) {
    guint width, height;
    GdkRGBA color;
    GtkStyleContext* context;

    context = gtk_widget_get_style_context(widget);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, width, height);

    // print width and height

    /* cairo_rectangle(cr, width / 2 - 50, height / 2 - 50, 100, 100);

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke_preserve(cr);

    cairo_set_source_rgb(cr, 255.0, 0.0, 255.0);
    cairo_fill(cr);

    gtk_style_context_get_color(context, gtk_style_context_get_state(context), &color);
    gdk_cairo_set_source_rgba(cr, &color);

    cairo_fill(cr); */

    Vector    *shapes = shp_read("data/2022");
    ShpHeader *header = vector_index(shapes, 0);

    for (int i = 1; i < shapes->size; i++) {
        switch (header->shape_type) {
            case 5: {// Polygon
                Polygon *shp = vector_index(shapes, i);

                for (int j = 0; j < shp->num_parts - 1; j++) {
                    int start = ((int *)shp->parts)[j];
                    int end = j > shp->num_parts ? ((int *)shp->parts)[j + 1] : shp->num_points;

                    for (int k = start; k < end; k++) {
                        Point current = ((Point *)shp->points)[k];
                        Point next    = ((Point *)shp->points)[k + 1];

                        cairo_move_to(cr, current.x + 200, current.y + 200);
                        cairo_line_to(cr, next.x + 200, next.y + 200);
                        cairo_stroke(cr);
                    }
                }

                free(shp);
                break;
            }
        }
    }

    free(shapes);

    return FALSE;
}
