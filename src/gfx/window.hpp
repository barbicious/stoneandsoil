#pragma once
#include <string_view>

#include "../types.hpp"

struct GLFWwindow;

namespace gfx {
    class Window {
    public:
        Window(const std::string_view& title, i32 width, i32 height);

        bool isGood();
        void splat();

        void viewport() const;

    private:
        GLFWwindow* glfw_window_;

        i32 width_, height_;
    };
} // gfx