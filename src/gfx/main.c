#include <stdio.h>

#include <GLFW/glfw3.h>

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void gfx_main_loop() {
    if (!glfwInit()) return;

    glfwSetErrorCallback(error_callback);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window) return;

    glfwMakeContextCurrent(window);

    // =====

    while (!glfwWindowShouldClose(window)) {
    
    }

    // =====

    glfwDestroyWindow(window);
    glfwTerminate();
};
