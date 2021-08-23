//
// Created by bczhc on 8/23/21.
//

#include "lib.h"

opengl_lib::GLFWException::GLFWException(const std::string &message) : Exception(message) {}

opengl_lib::GLEWException::GLEWException(const std::string &message) : Exception(message) {}

GLFWwindow *opengl_lib::glfwCreateWindow(i32 width, i32 height, const char *title) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = ::glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw GLFWException("glfwCreateWindow(...) failed");
    }

    glfwMakeContextCurrent(window);
    return window;
}

void opengl_lib::initGLEW() {
    if (glewInit() != GLEW_OK) {
        throw GLEWException("glewInit() failed");
    }
}

GLFWwindow *opengl_lib::initAndCreateWindow(i32 width, i32 height, const char *title) {
    auto window = glfwCreateWindow(width, height, title);
    try {
        initGLEW();
    } catch (const GLEWException &e) {
        glfwTerminate();
        throw GLEWException(e.what());
    }
    return window;
}

void opengl_lib::setAutoViewportWhenWindowSizeChanged(GLFWwindow *window) {
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *, i32 width, i32 height) {
        GL_CALL(glViewport(0, 0, width, height))
    });
}
