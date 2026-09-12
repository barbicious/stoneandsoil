#pragma once

namespace sos::lvl {
    class IBlittable {
    public:
        virtual ~IBlittable() = default;

        virtual void blit() = 0;
    };
} // sos::lvl