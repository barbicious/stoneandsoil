#include "screen.hpp"

#include "../wnd/window.hpp"

namespace gfx {
    Screen::Screen(const wnd::Window& window) : window{window} {
        vertex_array_.attribute<f32>(vertex_buffer_, 0, 2, GL_FLOAT, 4, 0);
        vertex_array_.attribute<f32>(vertex_buffer_, 1, 2, GL_FLOAT, 4, 2);
    }

    void Screen::bind() const {
        render_texture_.open();
        glViewport(0, 0, Width, Height);
    }

    void Screen::unbind() const {
        render_texture_.close();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.viewport();

        shader_.bind();
        vertex_array_.bind();
        vertex_buffer_.bind();
        render_texture_.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
} // gfx