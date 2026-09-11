#pragma once
#include <array>

#include "i_bindable.hpp"
#include "../types.hpp"

namespace gfx {
    class Buffer : public IBindable {
    public:
        template <typename T, usize N>
        Buffer(u32 type, u32 draw_mode, const std::array<T, N> &data);
        ~Buffer() override = 0;

        void bind() override;
        void unbind() override;

    private:
        u32 id{}, type{};

    };
} // gfx

#include "buffer.tpp"