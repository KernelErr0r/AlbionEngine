#include <memory>
#include "fmt/core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

constexpr uint32_t DEFAULT_WIDTH = 800;
constexpr uint32_t DEFAULT_HEIGHT = 600;

int main() {
    fmt::print("Hello, world!\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // TODO
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    std::unique_ptr<GLFWwindow, decltype(glfwDestroyWindow)*> glfwWindow {
        glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "AlbionEngine", nullptr, nullptr),
        &glfwDestroyWindow
    };

    if (glfwWindow.get() == nullptr) {
        fmt::print("Failed to create the window\n");
        return -1;
    }

    glfwMakeContextCurrent(glfwWindow.get());

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        fmt::print("Failed to load opengl function pointers\n");
        return -2;
    }

    float vertices[] = {
        -0.5, -0.5,
         0.5, -0.5,
         0.0,  0.5,
    };

    uint32_t vertexArrayObject, vertexBufferObject;

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(glfwWindow.get())) {
        glfwPollEvents();
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glfwSwapBuffers(glfwWindow.get());
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);

    return 0;
}