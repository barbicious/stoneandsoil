namespace gfx {
    template <typename T>
    void VertexArray::attribute(Buffer& buffer, u32 index, i32 size, GLenum type, usize stride, u32 offset) const {
        this->bind();
        buffer.bind();

        glVertexAttribPointer(index, size, type, false, stride * sizeof(T),
                              reinterpret_cast<void*>(offset * sizeof(T)));
        glEnableVertexAttribArray(index);
    }
} // gfx