#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "def.h"

using namespace std;

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        cout << "glfwInit() failed" << endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "glewInit() failed" << endl;
        return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    f32 vertices[6] = {
            -0.5F, -0.5F,
            0.0F, 0.5F,
            0.5F, -0.5F
    };

    u32 buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClearColor(.3F, .76F, .29F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}