#pragma once
#include "i_bindable.hpp"
#include "../types.hpp"

namespace gfx {
    class RawTexture : public IBindable {
    public:
        explicit RawTexture(u32 target);
        ~RawTexture() override = 0;

        void bind() const override;
        void unbind() const override;

    protected:
        [[nodiscard]] u32 target() const {
            return target_;
        }

        [[nodiscard]] u32 id() const {
            return id_;
        }

    private:
        u32 id_{}, target_{};
    };
} // gfx