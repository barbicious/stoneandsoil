#include "entity.hpp"

namespace ec {
    void Entity::operator+=(std::unique_ptr<Component> component) {
        component->entity_ = this;

        if (auto* blittable{dynamic_cast<IBlittable*>(component.get())}) {
            blittables_.push_back(blittable);
        }

        if (auto* tickable{dynamic_cast<ITickable*>(component.get())}) {
            tickables_.push_back(tickable);
        }

        components_.push_back(std::move(component));
    }

    void Entity::tick(f32 delta_time) {
        for (ITickable* tickable : tickables_) {
            tickable->tick(delta_time);
        }
    }

    void Entity::blit() {
        for (IBlittable* blittable : blittables_) {
            blittable->blit();
        }
    }
} // ec