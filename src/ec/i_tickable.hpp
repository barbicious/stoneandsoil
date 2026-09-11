#pragma once
#include "../types.hpp"

namespace ec {
    class ITickable {
    public:
        virtual ~ITickable() = default;

        virtual void tick(f32 delta_time) = 0;
    };
} // ec