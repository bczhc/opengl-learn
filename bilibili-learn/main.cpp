#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "lib/types.h"

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "opengl-lib/shader.h"
#include "texture.h"

using namespace std;

void frameBufferSizeCallback(GLFWwindow *, int width, int height) {
    GL_CALL(glViewport(0, 0, width, height))
}

void cursorCallback(GLFWwindow *, f64 x, f64 y) {
    cout << x << ' ' << y << endl;
}

void keyCallback(GLFWwindow *window, i32 key, i32, i32, i32) {
    if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void configure(GLFWwindow *window) {
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetKeyCallback(window, keyCallback);
}

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

    configure(window);

    {

        f32 vertexBufferBytes[] = {
                -0.5F, -0.5F, 0.0F, 0.0F, // 0
                0.5F, -0.5F, 1.0F, 0.0F, // 1
                0.5F, 0.5F, 1.0F, 1.0F, // 2
                -0.5F, 0.5F, 0.0F, 1.0F, // 3
        };

        GLuint vertexIndices[] = {
                0, 1, 2,
                2, 3, 0
        };

        VertexArray va;

        VertexBuffer vb(vertexBufferBytes, sizeof(vertexBufferBytes));

        VertexBufferLayout vl;
        vl.push<f32>(2);
        vl.push<f32>(2);
        va.addBuffer(vb, vl);
        IndexBuffer ib(vertexIndices, sizeof(vertexIndices) / sizeof(vertexIndices[0]));

        Shader shader(OPENGL_SHADER_FILE_PATH);
        shader.bind();
        const ShaderLocation &shaderColorLocation = shader.findLocation("u_Color");
        const ShaderLocation &shaderTextureLocation = shader.findLocation("u_Texture");

        Texture texture(OPENGL_TEXTURE_FILE_PATH);
        texture.bind();
        shaderTextureLocation.setUniform1i(0);

        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        f32 r = 0;
        f32 increment = 0.05;

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.clear();

            if (r > 1.0) {
                increment = -0.05;
            } else if (r < 0.0) {
                increment = 0.05;
            }
            r += increment;

            shader.bind();
            shaderColorLocation.setUniform4f(r, 0.3F, 0.8F, 1.0F);

            renderer.draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}