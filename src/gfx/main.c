#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/vector.h"
#include "../shp/read.h"
#include "../shp/types.h"
#include "../gfx/triangle.h"

const char* vertexSource = "\
    #version 150 core\n\
    in vec2 position;\
    in vec3 color;\
    out vec3 Color;\
    void main()\
    {\
        Color = color;\
        gl_Position = vec4(position, 0.0, 1.0);\
    }";

const char* fragmentSource = "\
    #version 150 core\n\
    in vec3 Color;\
    out vec4 outColor;\
    void main()\
    {\
        outColor = vec4(Color, 1.0);\
    }";

void gfx_main_loop(Vector *triangles, Vector *shapes, double width, double height, int ignore_edge_artifacts, int fill) {
    GLFWwindow* window; // = NULL ???

    if ( !glfwInit() ) {
        fprintf( stderr, "ERROR: could not start GLFW3\n" );
        return;
    }

    /* Version 4.1 Core is a good default that should run on just about everything. Adjust later to suit project requirements. */
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    window = glfwCreateWindow( 640, 480, "Vantage", NULL, NULL );
    if ( !window ) {
        fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent( window );

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    int n_parts  = 0;
    int n_points = 0;

    for (int i = 0; i < shapes->size; i ++) {
        Polygon *shape = vector_index(shapes, i);

        n_parts  += shape->num_parts;
        n_points += shape->num_points;
    }

    Vector *vvertices = VECTOR_NEW();
    GLuint elements[triangles->size * 3];
    unsigned int element_count = 0;

    #define VAL_TO_POINTER(val) memcpy(malloc(sizeof(val)), &val, sizeof(val))

    for (int i = 0; i < triangles->size; i ++) {
        Triangle *t = vector_index(triangles, i);

        for (int j = 0; j < 3; j ++) {
            Point vertex;

            switch (j) {
                case 0: vertex = t->a; break;
                case 1: vertex = t->b; break;
                case 2: vertex = t->c; break;
            }

            if ((ignore_edge_artifacts) && (vertex.x == 0 || vertex.x == width || vertex.y == 0 || vertex.y == width)) break;

            int vindex = vector_find(vvertices, &vertex, compare_points);

            if (vindex == -1) {
                vector_push(vvertices, VAL_TO_POINTER(vertex));
                vindex = vvertices->size - 1;
            }

            elements[element_count++] = vindex;
        }
    }

    GLfloat vertices[vvertices->size * 5];

    for (int i = 0; i < vvertices->size; i ++) {
        Point *c = vector_index(vvertices, i); // might be a cast mismatch with double != glfloat, but it's fine now
        vertices[i * 5    ] = (c->x - (width / 2 )) / 10;
        vertices[i * 5 + 1] = (c->y - (height / 2)) / 10;
        vertices[i * 5 + 2] = 1   * ((i + 0) % 3) / 2;
        vertices[i * 5 + 3] = 1   * ((i + 1) % 3) / 2;
        vertices[i * 5 + 4] = 1   * ((i + 2) % 3) / 2;
    }

    // print out vertices and elements
    /* for (int i = 0; i < vvertices->size; i += 5) {
        printf("%f, %f, %f, %f, %f\n",
            vertices[i], vertices[i + 1], vertices[i + 2],
            vertices[i + 3], vertices[i + 4]);
    }
    for (int i = 0; i < sizeof(elements) / sizeof(GLuint); i ++) {
        printf("%d\n", elements[i]);
    } */

    printf("Triangles: \n");
    for (int i = 0; i < triangles->size; i ++) {
        Triangle *t = vector_index(triangles, i);
        printf(" %d: {%f, %f}, {%f, %f}, {%f, %f}\n", i,
            t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y);
    }

    // print out vertices and elements
    printf("\nVertices: \n");
    for (int i = 0; i < vvertices->size * 5; i += 5) {
        printf(" %d : {%lf, %lf}\n", i / 5, vertices[i], vertices[i + 1]);
    }

    printf("\nElements: \n");
    for (int i = 0; i < sizeof(elements) / sizeof(GLuint); i += 3) {
        printf(" %d : {%d, %d, %d}\n", i / 3, elements[i], elements[i + 1], elements[i + 2]);
    }

    int num_parts  = 0;
    int num_points = 0;

    for (int i = 1; i < shapes->size; i ++) {
        Polygon *c = vector_index(shapes, i);

        num_parts  += c->num_parts;
        num_points += c->num_points;
    }

    printf("\nSummary\n");
    printf(" Countries: %ld\n", shapes->size - 1);
    printf(" Polygons:  %d\n", num_parts);
    printf(" Points:    %d\n", num_points);
    printf(" Triangles: %ld\n", triangles->size);
    printf(" Vertices:  %ld\n", vvertices->size);
    printf(" Elements:  %ld\n", sizeof(elements) / sizeof(GLuint));

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    while (!glfwWindowShouldClose(window)) {

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!fill) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, sizeof(elements) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers( window );

        /* for (int i = 1; i < sizeof(elements) / sizeof(GLuint); i ++) {
            Point a = *(Point*)vector_index(vvertices, elements[i - 1]);
            Point b = *(Point*)vector_index(vvertices, elements[i]);

            // draw line between a and b
            glBegin(GL_LINES);
            glVertex2f(a.x, a.y);
            glVertex2f(b.x, b.y);
            glEnd();
        } */
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
}
