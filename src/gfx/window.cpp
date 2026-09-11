#include "window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gfx {
    Window::Window(const std::string_view &title, i32 width, i32 height) {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

        glfw_window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (glfw_window == nullptr) {
            const char* error_buffer;
            glfwGetError(&error_buffer);

            std::cerr << error_buffer << std::endl;
        }

        glfwMakeContextCurrent(glfw_window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cerr << "Failed to laod opengl procedures" << std::endl;
        }
    }

    bool Window::isGood() {
        glfwPollEvents();
        return !glfwWindowShouldClose(glfw_window);
    }

    void Window::splat() {
        glfwSwapBuffers(glfw_window);
    }
} // gfx