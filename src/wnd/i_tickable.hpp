#pragma once

namespace wnd {
    class ITickable {
    public:
        virtual ~ITickable() = default;

        virtual void tick() = 0;
    };
} // wnd