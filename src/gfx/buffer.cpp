#include "buffer.hpp"

namespace gfx {
    Buffer::~Buffer() {
        glDeleteBuffers(1, &id);
    }

    void Buffer::bind() {
        glBindBuffer(type, id);
    }

    void Buffer::unbind() {
        glBindBuffer(type, 0);
    }
} // gfx