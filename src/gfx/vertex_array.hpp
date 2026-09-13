#pragma once

#include "buffer.hpp"

#include "i_bindable.hpp"
#include "../types.hpp"

namespace gfx {
    class VertexArray : public IBindable {
    public:
        VertexArray();
        ~VertexArray() override;

        void bind() const override;
        void unbind() const override;

        template <typename T>
        void attribute(Buffer &buffer, u32 index, i32 size, GLenum type, usize stride, u32 offset) const;

    private:
        u32 id{};
    };
} // gfx

#include "vertex_array.tpp"