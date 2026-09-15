#include "mouse.hpp"

#include "window.hpp"

namespace wnd {
    Mouse::Mouse(const Window* window) : window{window} {
    }

    bool Mouse::isButtonDown(i32 button) const {
        return glfwGetMouseButton(window->glfwWindow(), button) == GLFW_PRESS;
    }
} // wnd
