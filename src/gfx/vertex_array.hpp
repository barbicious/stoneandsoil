#pragma once

#include <glad/glad.h>
#include "buffer.hpp"

#include "i_bindable.hpp"
#include "../types.hpp"

namespace gfx {
    class VertexArray : public IBindable {
    public:
        VertexArray();
        ~VertexArray() override;

        void bind() override;
        void unbind() override;

        template <typename T>
        void attribute(Buffer &buffer, u32 index, i32 size, GLenum type, usize stride, u32 offset);

    private:
        u32 id{};
    };
} // gfx

#include "vertex_array.tpp"