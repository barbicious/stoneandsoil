#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <glm/fwd.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <stb/stb_image.h>

#include "types.hpp"
#include "ec/entity.hpp"
#include "gfx/buffer.hpp"
#include "gfx/image_texture.hpp"
#include "gfx/screen.hpp"
#include "gfx/shader.hpp"
#include "gfx/vertex_array.hpp"
#include "gfx/vertex_buffer.hpp"
#include "sos/player_component.hpp"
#include "wnd/window.hpp"

i32 main() {
    stbi_set_flip_vertically_on_load(true);

    wnd::Window window{"stone and soil.", 1280, 720};

    gfx::Shader shader{gfx::Shader::Desc{
        .path = "res/shaders/cube.frag",
        .type = GL_FRAGMENT_SHADER,
    }, gfx::Shader::Desc{
        .path = "res/shaders/cube.vert",
        .type = GL_VERTEX_SHADER
    }};

    gfx::ImageTexture texture_atlas{"res/textureatlas.png"};

    const glm::mat4 proj{glm::perspective(glm::radians(60.0f32), 256.0f32 / 144.0f32, 0.01f32, 1000.0f32)};

    std::array vertices{
        0.0f32, 0.0f32, -2.0f32, 0.0f32,            0.0f32,
        1.0f32, 0.0f32, -2.0f32, 8.0f32 / 256.0f32, 0.0f32,
        1.0f32, 1.0f32, -2.0f32, 8.0f32 / 256.0f32, 8.0f32 / 256.0f32,
        1.0f32, 1.0f32, -2.0f32, 8.0f32 / 256.0f32, 8.0f32 / 256.0f32,
        0.0f32, 1.0f32, -2.0f32, 0.0f32,            8.0f32 / 256.0f32,
        0.0f32, 0.0f32, -2.0f32, 0.0f32,            0.0f32,
    };

    gfx::VertexArray vao{};
    gfx::VertexBuffer vbo{GL_STATIC_DRAW, vertices};

    vao.attribute<f32>(vbo, 0, 3, GL_FLOAT, 5, 0);
    vao.attribute<f32>(vbo, 1, 2, GL_FLOAT, 5, 3);

    gfx::Screen screen{window};

    ec::Entity player_entity{sos::PlayerComponent{window}};

    f32 last_time{static_cast<f32>(glfwGetTime())};

    while (window.isGood()) {
        if (window.keyboard().isKeyDown(GLFW_KEY_ESCAPE)) {
            break;
        }

        f32 delta_time{static_cast<f32>(glfwGetTime()) - last_time};
        player_entity.tick(delta_time);
        last_time = static_cast<f32>(glfwGetTime());

        screen.bind();

        glClearColor(0.2f32, 0.25f32, 0.65f32, 1.0f32);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        shader.setMat4("u_proj", proj);
        shader.setMat4("u_view", player_entity.getComponent<sos::PlayerComponent>()->view());

        vao.bind();
        vbo.bind();
        texture_atlas.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        screen.unbind();

        window.splat();
    }
}
