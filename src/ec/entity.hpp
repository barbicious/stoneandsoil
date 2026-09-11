#pragma once
#include <concepts>
#include <memory>
#include <vector>

#include "component.hpp"
#include "i_blittable.hpp"
#include "i_tickable.hpp"

namespace ec {
    template <typename C>
    concept ComponentSubclass = std::derived_from<C, Component>;

    class Entity : public ITickable, public IBlittable {
    public:
        template <ComponentSubclass... Components>
        explicit Entity(Components... components) {
            (operator+=(std::make_unique<Components>(components)), ...);
        }

        template<ComponentSubclass C>
        C* getComponent() {
            for (std::unique_ptr<Component>& component : components_) {
                if (auto* c{dynamic_cast<C*>(component.get())}) {
                    return c;
                }
            }

            return nullptr;
        }

        void operator+=(std::unique_ptr<Component> component);

        void tick(f32 delta_time) override;
        void blit() override;

    private:
        std::vector<std::unique_ptr<Component>> components_{};
        std::vector<ITickable*> tickables_{};
        std::vector<IBlittable*> blittables_{};
    };
} // ec