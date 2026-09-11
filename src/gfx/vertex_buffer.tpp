#include "vertex_buffer.hpp"

namespace gfx {
    template<typename T, usize N>
    VertexBuffer::VertexBuffer(u32 draw_mode, const std::array<T, N> &data) : Buffer{GL_ARRAY_BUFFER, draw_mode, data}{
    }
} // gfx