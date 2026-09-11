#include "keyboard.hpp"

#include <cstring>

#include "window.hpp"

namespace wnd {
    Keyboard::Keyboard(const Window *window) : window{window} {

    }

    void Keyboard::tick() {
        memcpy(previous_keys_.data(), current_keys_.data(), sizeof(bool) * GLFW_KEY_LAST);
        for (usize i{0}; i < GLFW_KEY_LAST; ++i) {
            current_keys_[i] = glfwGetKey(window->glfwWindow(), i) == GLFW_PRESS;
        }
    }

    bool Keyboard::isKeyDown(i32 key) const {
        return current_keys_[key] and previous_keys_[key];
    }

    bool Keyboard::isKeyPressed(i32 key) const {
        return current_keys_[key] and !previous_keys_[key];
    }
} // wnd