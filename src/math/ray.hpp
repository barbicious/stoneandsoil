#pragma once

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "../types.hpp"

namespace math {
    class Ray {
    public:
        Ray(glm::vec3 position, glm::vec3 direction);

        void step(f32 scale);

        [[nodiscard]] f32 distance() const noexcept {
            return glm::distance(start_, end_);
        }

        [[nodiscard]] glm::vec3 end() const noexcept {
            return end_;
        }

    private:
        glm::vec3 start_{};
        glm::vec3 end_{};
        glm::vec3 dir_{};
    };
} // math