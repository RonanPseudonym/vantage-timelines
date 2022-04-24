#ifndef MAP_CANVAS
#define MAP_CANVAS

#include <gtk/gtk.h>

#define MAP_CANVAS_CONTAINER                 (map_canvas_container_get_type ())
#define MAP_CANVAS_CONTAINER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAP_CANVAS_CONTAINER, MapCanvasContainer))
#define MAP_CANVAS_CLASS(klass)              (G_TYPE_CHECK_CLASS_CAST ((klass), MAP_CANVAS_CONTAINER, MapCanvasContainerClass))
#define MAP_IS_CANVAS_CONTAINER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MAP_CANVAS_CONTAINER))
#define MAP_IS_CANVAS_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MAP_CANVAS_CONTAINER))
#define MAP_CANVAS_CONTAINER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), MAP_CANVAS_CONTAINER, MapCanvasContainerClass))

typedef struct _MapCanvasContainer      MapCanvasContainer;
typedef struct _MapCanvasContainerClass MapCanvasContainerClass;

struct _MapCanvasContainer {
    GtkDrawingArea parent_instance;
};

struct _MapCanvasContainerClass {
    GtkDrawingAreaClass parent_class;
};

GType map_canvas_container_get_type(void);

#endif
