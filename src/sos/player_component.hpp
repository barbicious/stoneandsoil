#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../ec/component.hpp"
#include "../ec/i_tickable.hpp"

namespace wnd {
    class Window;
} // wnd

namespace sos {
    namespace lvl {
        class Level;
    } // lvl

    class PlayerComponent : public ec::Component, public ec::ITickable {
    public:
        PlayerComponent(const wnd::Window& window, lvl::Level& level);

        void tick(f32 delta_time) override;

        [[nodiscard]] glm::mat4 view() const {
            return glm::lookAt(position_, position_ + front_, UP);
        }

    private:
        static constexpr glm::vec3 UP{0.0f, 1.0f, 0.0f};

        glm::vec3 position_{0.0f, 0.0f, 0.0f};
        glm::vec3 front_{0.0f, 0.0f, -1.0f};
        glm::vec3 dir_{0.0f, 0.0f, 0.0f};

        const wnd::Window& window_;
        lvl::Level& level_;

        f32 yaw_{-90.0}, pitch_{};
    };
} // sos