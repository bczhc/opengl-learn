//
// Created by bczhc on 8/23/21.
//

#include "opengl-lib/lib.h"
#include "opengl-lib/shader.h"

using namespace std;

int main() {
    auto window = opengl_lib::initAndCreateWindow(500, 500, "Window");

    opengl_lib::setAutoViewportWhenWindowSizeChanged(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}