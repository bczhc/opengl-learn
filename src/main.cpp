#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "def.h"
#include "exception.h"
#include "option.hpp"
#include <cstdlib>
#include <cassert>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

using namespace std;

#define SHADER_FILE_PATH ("/home/bczhc/code/opengl/res/basic.glsl")

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        cout << "glfwInit() failed" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        cout << "glfwCreateWindow(...) failed" << endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "glewInit() failed" << endl;
        return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    {
        glfwSwapInterval(1);

        f32 vertices[] = {
                -0.5F, -0.5F, // 0
                0.5F, -0.5F, // 1
                0.5F, 0.5F, // 2
                -0.5F, 0.5F, // 3
        };

        GLuint vertexIndices[] = {
                0, 1, 2,
                2, 3, 0
        };

        VertexArray va;

        VertexBuffer vb(vertices, sizeof(vertices));

        VertexBufferLayout vl;
        vl.push<f32>(2);
        va.addBuffer(vb, vl);
        IndexBuffer ib(vertexIndices, sizeof(vertexIndices) / sizeof(vertexIndices[0]));
        
        Shader shader(SHADER_FILE_PATH);
        const ShaderLocation &shaderColorLocation = shader.findLocation("u_Color");
        shader.bind();

        GL_CALL(glBindVertexArray(0))
        GL_CALL(glUseProgram(0))
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))

        f32 r = 0;
        f32 increment = 0.05;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            if (r > 1.0) {
                increment = -0.05;
            } else if (r < 0.0) {
                increment = 0.05;
            }
            r += increment;

            shader.bind();
            shaderColorLocation.setUniform4f(r, 0.3F, 0.8F, 1.0F);

            va.bind();
            // also works without the ibo binding
//        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo))
            GL_CALL(glDrawElements(GL_TRIANGLES, sizeof(vertexIndices) / sizeof(vertexIndices[0]), GL_UNSIGNED_INT,
                                   nullptr))

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}