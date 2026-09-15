#include "window.hpp"

#include <iostream>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace wnd {
    Window::Window(const std::string_view& title, i32 width, i32 height) : keyboard_{this},
                                                                           mouse_{this},
                                                                           width_{width},
                                                                           height_{height} {
        if (!glfwInit()) {
            const char* error_buffer;
            glfwGetError(&error_buffer);

            std::cerr << error_buffer << std::endl;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

        glfw_window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (glfw_window_ == nullptr) {
            const char* error_buffer;
            glfwGetError(&error_buffer);

            std::cerr << error_buffer << std::endl;
        }

        glfwMakeContextCurrent(glfw_window_);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cerr << "Failed to laod opengl procedures" << std::endl;
        }

        glfwSetWindowUserPointer(glfw_window_, this);

        glfwSetFramebufferSizeCallback(glfw_window_, [](GLFWwindow* wnd_handle, i32 w, i32 h) {
            Window* window{static_cast<Window*>(glfwGetWindowUserPointer(wnd_handle))};

            window->width_ = w;
            window->height_ = h;

            window->viewport();
        });

        glfwSetCursorPosCallback(glfw_window_, [](GLFWwindow* wnd_handle, f64 x, f64 y) {
            Window* window{static_cast<Window*>(glfwGetWindowUserPointer(wnd_handle))};

            if (window->mouse_.first_) {
                window->mouse_.x = static_cast<f32>(x);
                window->mouse_.y = static_cast<f32>(y);
                window->mouse_.first_ = false;
            }

            window->mouse_.delta_x = static_cast<f32>(x) - window->mouse_.x;
            window->mouse_.delta_y = window->mouse_.y - static_cast<f32>(y);

            window->mouse_.x = static_cast<f32>(x);
            window->mouse_.y = static_cast<f32>(y);
        });

        glfwSetInputMode(glfw_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    bool Window::isGood() {
        mouse_.delta_x = mouse_.delta_y = 0;

        glfwPollEvents();

        keyboard_.tick();

        return !glfwWindowShouldClose(glfw_window_);
    }

    void Window::splat() {
        glfwSwapBuffers(glfw_window_);
    }

    void Window::viewport() const {
        glViewport(0, 0, width_, height_);
    }
} // wnd
