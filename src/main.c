#include "ui/ui.h"
#include "shp/types.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    Point p1 = NEW_POINT();
    printf("%d %d\n", p1.x, p1.y);

    // return ui_init(argc, argv);
}
