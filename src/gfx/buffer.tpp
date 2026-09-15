#include <glad/glad.h>

namespace gfx {
    template <typename T, usize N>
    Buffer::Buffer(u32 type, u32 draw_mode, const std::array<T, N>& data) : type{type} {
        glGenBuffers(1, &id);

        Buffer::bind();

        glBufferData(type, sizeof(T) * N, data.data(), draw_mode);

        Buffer::unbind();
    }
} // gfx
