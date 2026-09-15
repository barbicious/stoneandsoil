#pragma once
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "i_tickable.hpp"
#include "../types.hpp"

namespace wnd {
    class Window;

    class Keyboard : public ITickable {
    public:
        explicit Keyboard(const Window* window);

        ~Keyboard() override = default;

        void tick() override;

        [[nodiscard]] bool isKeyDown(i32 key) const;
        [[nodiscard]] bool isKeyPressed(i32 key) const;

    private:
        std::array<bool, GLFW_KEY_LAST> current_keys_{};
        std::array<bool, GLFW_KEY_LAST> previous_keys_{};

        const Window* window;
    };
} // wnd