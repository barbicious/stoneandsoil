#define STB_IMAGE_IMPLEMENTATION
#include <glm/fwd.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <stb/stb_image.h>
#include <glad/glad.h>

#include "types.hpp"
#include "ec/entity.hpp"
#include "gfx/screen.hpp"
#include "gfx/shader.hpp"
#include "sos/player_component.hpp"
#include "sos/texture_atlas.hpp"
#include "sos/lvl/level.hpp"
#include "wnd/window.hpp"

i32 main() {
    stbi_set_flip_vertically_on_load(true);

    wnd::Window window{"stone and soil.", 1280, 720};

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

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

    const sos::TextureAtlas& texture_atlas{sos::TextureAtlas::get()};

    const glm::mat4 proj{glm::perspective(glm::radians(60.0f), 256.0f / 144.0f, 0.01f, 1000.0f)};

    sos::lvl::Level level;

    gfx::Screen screen{window};

    ec::Entity player_entity{sos::PlayerComponent{window, level}};

    f32 last_time{static_cast<f32>(glfwGetTime())};

    while (window.isGood()) {
        if (window.keyboard().isKeyDown(GLFW_KEY_ESCAPE)) {
            break;
        }

        level.doChunkWork();

        f32 delta_time{static_cast<f32>(glfwGetTime()) - last_time};
        player_entity.tick(delta_time);
        last_time = static_cast<f32>(glfwGetTime());

        //std::cout << 1.0f / delta_time << std::endl;

        screen.bind();

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f32, 0.25f32, 0.65f32, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        shader.setMat4("u_proj", proj);
        shader.setMat4("u_view", player_entity.getComponent<sos::PlayerComponent>()->view());

        texture_atlas.bind();

        level.blit();

        glDisable(GL_DEPTH_TEST);

        screen.unbind();

        window.splat();
    }
}
