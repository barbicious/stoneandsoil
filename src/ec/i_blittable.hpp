#pragma once

namespace ec {
    class IBlittable {
    public:
        virtual ~IBlittable() = default;

        virtual void blit() = 0;
    };
} // ec