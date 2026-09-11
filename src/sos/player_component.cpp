#include "player_component.hpp"

#include <iostream>
#include <glm/ext/vector_common.hpp>

#include "../types.hpp"
#include "../wnd/window.hpp"

namespace sos {
    PlayerComponent::PlayerComponent(const wnd::Window &window) : window_{window} {
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

            front_ = glm::normalize(glm::vec3{
                cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)),
                sin(glm::radians(pitch_)),
                sin(glm::radians(yaw_)) * cos(glm::radians(pitch_))
            });
        }
    }
} // sos