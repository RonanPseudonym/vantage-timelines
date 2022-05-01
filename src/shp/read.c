/*
    HANDLES FILE AND DIRECTORY READING FOR SHAPEFILES
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "read.h"
#include "types.h"
#include "../utils/vector.h"

Vector *shp_read(char* dir) {
    char* shp = malloc(strlen(dir) + strlen("/World_Countries.shp"));

    strcpy(shp, dir);
    strcat(shp, "/World_Countries.shp");

    // Read byte stream from file shp
    FILE* fp = fopen(shp, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", shp);
    }

    unsigned int byte_counter = 0;

    /* #define I_INT_LITTLE_ENDIAN()   fgetc(fp) | (fgetc(fp) << 8) | (fgetc(fp) << 16) | (fgetc(fp) << 24); byte_counter += 4
    #define I_INT_BIG_ENDIAN()      (fgetc(fp) << 24) | (fgetc(fp) << 16) | (fgetc(fp) << 8) | fgetc(fp); byte_counter += 4
    #define I_DOUBLE_LITTLE_ENDIAN() fgetc(fp) | (fgetc(fp) << 8) | (fgetc(fp) << 16) | (fgetc(fp) << 24) | (fgetc(fp) << 32) | (fgetc(fp) << 40) | (fgetc(fp) << 48) | (fgetc(fp) << 56); byte_counter += 8
    #define I_DOUBLE_BIG_ENDIAN()   (fgetc(fp) << 56) | (fgetc(fp) << 48) | (fgetc(fp) << 40) | (fgetc(fp) << 32) | (fgetc(fp) << 24) | (fgetc(fp) << 16) | (fgetc(fp) << 8) | fgetc(fp); byte_counter += 8
    */

    #define I_INT_LITTLE_ENDIAN()    fgetc(fp) | (fgetc(fp) << 8) | (fgetc(fp) << 16) | (fgetc(fp) << 24)
    #define I_INT_BIG_ENDIAN()       (fgetc(fp) << 24) | (fgetc(fp) << 16) | (fgetc(fp) << 8) | fgetc(fp)
    #define I_DOUBLE_LITTLE_ENDIAN() I_INT_LITTLE_ENDIAN() | (((long)I_INT_LITTLE_ENDIAN()) << 32)
    #define I_DOUBLE_BIG_ENDIAN()    (((long)I_INT_BIG_ENDIAN()) << 32) | I_INT_BIG_ENDIAN()

    ShpHeader header = NEW_SHPHEADER(); // Bytes 0-100

    for (;;) {
        switch (byte_counter) {
            case 0: // Signature
                int sig = I_INT_BIG_ENDIAN();
                if (sig != SHP_SIGNATURE) {
                    fprintf(stderr, "Error: Invalid signature %d[provided]!=%d[requested]\n", sig, SHP_SIGNATURE);
                }
                byte_counter += 4;
                continue;
            case 24: // File length
                header.file_length = I_INT_BIG_ENDIAN();
                byte_counter += 4;
                continue;
            case 32: // Shape type
                header.shape_type = I_INT_LITTLE_ENDIAN();
                byte_counter += 4;
                continue;
            case 36: // Bounding box x_min
                header.x_min = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 44: // Bounding box y_min
                header.y_min = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 52: // Bounding box x_max
                header.x_max = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 60: // Bounding box y_max
                header.y_max = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 68: // Bounding box z_min
                header.z_min = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 76: // Bounding box z_max
                header.z_max = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 84: // Bounding box m_min
                header.m_min = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
            case 92: // Bounding box m_max
                header.m_max = I_DOUBLE_LITTLE_ENDIAN();
                byte_counter += 8;
                continue;
        }

        if (byte_counter == 100) {
            printf("\n");
            printf("Header:\n");
            printf("  File length: %d\n", header.file_length);
            printf("  Shape type: %d\n", header.shape_type);
            printf("  Bounding box x_min: %lf\n", header.x_min);
            printf("  Bounding box y_min: %lf\n", header.y_min);
            printf("  Bounding box x_max: %lf\n", header.x_max);
            printf("  Bounding box y_max: %lf\n", header.y_max);
            printf("  Bounding box z_min: %lf\n", header.z_min);
            printf("  Bounding box z_max: %lf\n", header.z_max);
            printf("  Bounding box m_min: %lf\n", header.m_min);
            printf("  Bounding box m_max: %lf\n", header.m_max);
            printf("\n");
            break;
        }

        I_INT_LITTLE_ENDIAN();
        byte_counter += 4;
    }

    Vector* shapes = VECTOR_NEW();

    for (;;) {
        int shape_type = I_INT_LITTLE_ENDIAN();
        byte_counter += 4;

        switch (shape_type) {
            case 5: {// Polygon
                double box[4];
                for (int i = 0; i < 4; i ++) {
                    box[i] = I_DOUBLE_LITTLE_ENDIAN();
                    byte_counter += 8;
                }

                int num_parts = I_INT_LITTLE_ENDIAN();
                byte_counter += 4;

                int num_points = I_INT_LITTLE_ENDIAN();
                byte_counter += 4;

                Polygon *polygon = NEW_POLYGON(num_parts, num_points);

                polygon->box[0] = box[0];
                polygon->box[1] = box[1];
                polygon->box[2] = box[2];
                polygon->box[3] = box[3];

                for (int i = 0; i < num_parts; i ++) {
                    ((int*)polygon->parts)[i] = I_INT_LITTLE_ENDIAN();
                    byte_counter += 4;
                }

                for (int i = 0; i < num_points; i ++) {
                    ((Point*)polygon->points)[i] = NEW_POINT();
                    double x = I_DOUBLE_LITTLE_ENDIAN();
                    ((Point*)polygon->points)[i].x = x;
                    byte_counter += 8;
                    ((Point*)polygon->points)[i].y = I_DOUBLE_LITTLE_ENDIAN();
                    byte_counter += 8;
                }

                printf("\n");
                printf("Polygon:\n");
                printf("  Box: %lf, %lf, %lf, %lf\n", polygon->box[0], polygon->box[1], polygon->box[2], polygon->box[3]);
                printf("  Num parts: %d\n", polygon->num_parts);
                printf("  Num points: %d\n", polygon->num_points);
                /* printf("  Parts: ");
                for (int i = 0; i < num_parts; i ++) {
                    printf("%d ", ((int*)polygon->parts)[i]);
                }
                printf("\n");
                printf("  Points: ");
                for (int i = 0; i < num_points; i ++) {
                   printf("(%lf, %lf) ", ((Point*)polygon->points)[i].x, ((Point*)polygon->points)[i].y);
                }
                */

                // sizeof(polygon) returning 8 no matter what, pretty funky if you ask me
                // but, uh, it seems to work? so fuck it i'm living *my* life i'll let it live its

                vector_push(shapes, polygon);

                break;
            }
        }

        if (byte_counter >= header.file_length * 2) {
            #undef I_INT_LITTLE_ENDIAN
            #undef I_DOUBLE_LITTLE_ENDIAN
            #undef I_INT_BIG_ENDIAN
            #undef I_DOUBLE_BIG_ENDIAN

            return shapes;
        }
    }
}
