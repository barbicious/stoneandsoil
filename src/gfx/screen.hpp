#pragma once

#include "render_texture.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"

namespace gfx {
    class Window;

    class Screen : public IBindable {
    public:
        Screen(Window &window);
        ~Screen() override = default;

        void bind() override;
        void unbind() override;

    private:
        static constexpr u32 Width{256}, Height{144};

        Window &window;

        Shader shader_{Shader::Desc{
            .path = "res/shaders/screen.vert",
            .type = GL_VERTEX_SHADER
        }, Shader::Desc{
            .path = "res/shaders/screen.frag",
            .type = GL_FRAGMENT_SHADER
        }};
        VertexArray vertex_array_{};
        VertexBuffer vertex_buffer_{GL_STATIC_DRAW, std::array{
            -1.0f32, -1.0f32, 0.0f32, 0.0f32,
            1.0f32, -1.0f32, 1.0f32, 0.0f32,
            1.0f32, 1.0f32, 1.0f32, 1.0f32,
            1.0f32, 1.0f32, 1.0f32, 1.0f32,
            -1.0f32, 1.0f32, 0.0f32, 1.0f32,
            -1.0f32, -1.0f32, 0.0f32, 0.0f32,
        }};
        RenderTexture render_texture_{Width, Height};
    };
} // gfx