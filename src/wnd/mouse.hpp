#pragma once

#include <tuple>

#include "../types.hpp"

namespace wnd {
    class Window;

    class Mouse {
    public:
        explicit Mouse(const Window *window);

        [[nodiscard]] std::tuple<f32, f32> delta() const {
            return std::tuple{delta_x, delta_y};
        }

        friend class Window;

    private:
        const Window *window;

        f32 x{}, y{};

        f32 delta_x{}, delta_y{};

        bool first_{true};
    };
} // wnd