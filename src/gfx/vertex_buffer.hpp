#pragma once

#include "buffer.hpp"

namespace gfx {
    class VertexBuffer : public Buffer {
    public:
        template<typename T, usize N>
        VertexBuffer(u32 draw_mode, const std::array<T, N> &data);
    };
} // gfx

#include "vertex_buffer.tpp"
