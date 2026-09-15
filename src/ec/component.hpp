#pragma once

namespace ec {
    class Entity;

    class Component {
    public:
        virtual ~Component() = default;

        friend class Entity;

    private:
        Entity* entity_;
    };
} // ec
