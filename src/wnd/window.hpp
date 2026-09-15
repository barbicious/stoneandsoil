#pragma once

#include <string_view>

#include "keyboard.hpp"
#include "mouse.hpp"
#include "../types.hpp"

namespace wnd {
    class Window {
    public:
        Window(const std::string_view& title, i32 width, i32 height);

        bool isGood();

        void splat();

        void viewport() const;

        [[nodiscard]] GLFWwindow* glfwWindow() const {
            return glfw_window_;
        }

        [[nodiscard]] const Keyboard& keyboard() const {
            return keyboard_;
        }

        [[nodiscard]] const Mouse& mouse() const {
            return mouse_;
        }

    private:
        Keyboard keyboard_;
        Mouse mouse_;

        GLFWwindow* glfw_window_;

        i32 width_, height_;
    };
} // wnd
