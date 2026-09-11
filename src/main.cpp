#include <glad/glad.h>

#include "types.hpp"
#include "gfx/buffer.hpp"
#include "gfx/shader.hpp"
#include "gfx/vertex_array.hpp"
#include "gfx/vertex_buffer.hpp"
#include "gfx/window.hpp"

i32 main() {
    gfx::Window window{"stone and soil.", 1280, 720};

    gfx::Shader shader{gfx::Shader::Desc{
        .path = "res/shaders/cube.frag",
        .type = GL_FRAGMENT_SHADER,
    }, gfx::Shader::Desc{
        .path = "res/shaders/cube.vert",
        .type = GL_VERTEX_SHADER
    }};

    shader.bind();

    std::array vertices{
        -0.5f32, -0.5f32, 0.0f32,
        0.5f32, -0.5f32, 0.0f32,
        0.0f32, 0.5f32, 0.0f32,
    };

    gfx::VertexArray vao{};
    vao.bind();

    gfx::VertexBuffer vbo{GL_STATIC_DRAW, vertices};
    vbo.bind();

    vao.attribute<f32>(vbo, 0, 3, GL_FLOAT, 3, 0);

    while (window.isGood()) {
        glClearColor(0.2f32, 0.5f32, 0.65f32, 1.0f32);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.splat();
    }
}
