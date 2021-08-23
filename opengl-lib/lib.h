//
// Created by bczhc on 8/23/21.
//

#ifndef OPENGL_LIB_H
#define OPENGL_LIB_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "lib/types.h"
#include "lib/exception.h"
#include "error_check.h"

namespace opengl_lib {
    class GLFWException : public Exception {
    public:
        explicit GLFWException(const std::string &message);
    };

    class GLEWException : public Exception {
    public:
        explicit GLEWException(const std::string &message);
    };

    GLFWwindow* glfwCreateWindow(i32 width, i32 height, const char* title);

    void initGLEW();

    GLFWwindow* initAndCreateWindow(i32 width, i32 height, const char* title);

    void setAutoViewportWhenWindowSizeChanged(GLFWwindow *window);

    void setQuitWhenKeyListened(GLFWwindow *window);
}

#endif //OPENGL_LIB_H
