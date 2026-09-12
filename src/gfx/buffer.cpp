#include "buffer.hpp"

namespace gfx {
    Buffer::~Buffer() {
        glDeleteBuffers(1, &id);
    }

    void Buffer::uploadData(u32 offset, u32 size, void *data) const {
        glBufferSubData(type, offset, size, data);
    }

    void Buffer::bind() {
        glBindBuffer(type, id);
    }

    void Buffer::unbind() {
        glBindBuffer(type, 0);
    }
} // gfx