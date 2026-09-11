#pragma once

namespace gfx {
    class IBindable {
    public:
        virtual ~IBindable() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
} // gfx