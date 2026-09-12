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
#include "sos/texture_atlas.hpp"
#include "sos/lvl/chunk_mesh.hpp"
#include "sos/lvl/tile.hpp"
#include "wnd/window.hpp"

i32 main() {
    stbi_set_flip_vertically_on_load(true);

    wnd::Window window{"stone and soil.", 1280, 720};

    gfx::Shader shader{
        gfx::Shader::Desc{
            .path = "res/shaders/cube.frag",
            .type = GL_FRAGMENT_SHADER,
        },
        gfx::Shader::Desc{
            .path = "res/shaders/cube.vert",
            .type = GL_VERTEX_SHADER
        }
    };

    sos::TextureAtlas& texture_atlas{sos::TextureAtlas::get()};

    const glm::mat4 proj{glm::perspective(glm::radians(60.0f), 256.0f / 144.0f, 0.01f, 1000.0f)};

    sos::lvl::ChunkMesh chunk_mesh{};

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

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f32, 0.25f32, 0.65f32, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        shader.setMat4("u_proj", proj);
        shader.setMat4("u_view", player_entity.getComponent<sos::PlayerComponent>()->view());

        texture_atlas.bind();

        chunk_mesh.blit();

        glDisable(GL_DEPTH_TEST);

        screen.unbind();

        window.splat();
    }
}
