#pragma once

namespace gfx {
    class IBindable {
    public:
        virtual ~IBindable() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
    };
} // gfx