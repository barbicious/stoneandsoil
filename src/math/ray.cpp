#include "ray.hpp"

#include <glm/trigonometric.hpp>

namespace math {
    Ray::Ray(glm::vec3 position, glm::vec3 direction) : start_{position}, end_{position}, dir_{direction} {
    }

    void Ray::step(f32 scale) {
        f32 yaw{glm::radians(dir_.x + 90.0f)};
        f32 pitch{(-glm::radians(dir_.y))};

        end_.x -= glm::cos(yaw) * scale;
        end_.y -= glm::tan(pitch) * scale;
        end_.z -= glm::sin(yaw) * scale;
    }
} // math
