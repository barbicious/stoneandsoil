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

    private:
        GLFWwindow* glfw_window;

    };
} // gfx