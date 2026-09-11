#include "vertex_array.hpp"

namespace gfx {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &id);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::bind() {
        glBindVertexArray(id);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }
} // gfx