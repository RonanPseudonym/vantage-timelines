/*
    HANDLES FILE AND DIRECTORY READING FOR SHAPEFILES
*/

#include <stdio.h>
#include <string.h>
#include "read.h"

void shp_read(char* dir) {
    char* shp = strcat(dir, "/World_Countries.shp");

    printf("%s", shp);
}
