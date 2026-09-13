#include "vertex_array.hpp"

namespace gfx {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &id);
        VertexArray::bind();
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::bind() const {
        glBindVertexArray(id);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }
} // gfx