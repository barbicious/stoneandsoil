#include "player_component.hpp"

#include <iostream>
#include <glm/ext/vector_common.hpp>

#include "../types.hpp"
#include "../math/core.hpp"
#include "../math/ray.hpp"
#include "../wnd/window.hpp"
#include "lvl/chunk.hpp"
#include "lvl/level.hpp"

namespace sos {
    PlayerComponent::PlayerComponent(const wnd::Window &window, lvl::Level &level) : window_{window}, level_{level} {
    }

    void PlayerComponent::tick(f32 delta_time) {
        const float speed{2.5f * delta_time};

        constexpr f32 SENSITIVITY{0.1};

        if (window_.keyboard().isKeyDown(GLFW_KEY_W)) {
            position_ += speed * front_;
        }

        if (window_.keyboard().isKeyDown(GLFW_KEY_S)) {
            position_ -= speed * front_;
        }

        if (window_.keyboard().isKeyDown(GLFW_KEY_D)) {
            position_ += glm::normalize(glm::cross(front_, UP)) * speed;
        }

        if (window_.keyboard().isKeyDown(GLFW_KEY_A)) {
            position_ -= glm::normalize(glm::cross(front_, UP)) * speed;
        }

        f32 mouse_delta_x{std::get<0>(window_.mouse().delta()) * SENSITIVITY}, mouse_delta_y{std::get<1>(window_.mouse().delta()) * SENSITIVITY};

        if (mouse_delta_x != 0 or mouse_delta_y != 0) {
            yaw_ += mouse_delta_x;
            pitch_ = glm::clamp(pitch_ + mouse_delta_y, -89.0f, 89.0f);

            dir_.x += mouse_delta_x;
            dir_.y += mouse_delta_y;

            front_ = glm::normalize(glm::vec3{
                cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)),
                sin(glm::radians(pitch_)),
                sin(glm::radians(yaw_)) * cos(glm::radians(pitch_))
            });
        }

        if (window_.mouse().isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            math::Ray ray{position_, dir_};

            while (ray.distance() < 6.0) {
                ray.step(0.05);

                lvl::ChunkPosition chunk_position{
                    lvl::ChunkPosition::fromTileCoordinates(
                    static_cast<i32>(ray.end().x),
                    static_cast<i32>(ray.end().y),
                    static_cast<i32>(ray.end().z)
                )};

                lvl::Chunk *chunk{level_.chunkAt(chunk_position)};

                //std::cout << chunk_position.x << ", " << chunk_position.y << ", " << chunk_position.z << std::endl;

                usize tile_x{static_cast<usize>(math::remEuclid(static_cast<i32>(std::floor(ray.end().x)), static_cast<i32>(lvl::Chunk::WIDTH)))};
                usize tile_y{static_cast<usize>(math::remEuclid(static_cast<i32>(std::floor(ray.end().y)), static_cast<i32>(lvl::Chunk::HEIGHT)))};
                usize tile_z{static_cast<usize>(math::remEuclid(static_cast<i32>(std::floor(ray.end().z)), static_cast<i32>(lvl::Chunk::DEPTH)))};

                if (lvl::TileRegistry::get()[chunk->tileAt(tile_x, tile_y, tile_z)].type() == lvl::Tile::Type::air) {
                    continue;
                }
                std::cout << tile_x << ", " << tile_y << ", " << tile_z << std::endl;

                chunk->setTile(tile_x, tile_y, tile_z, 0);
                level_.pushMesh(chunk->chunkMesh());
                break;
            }
        }
    }
} // sos