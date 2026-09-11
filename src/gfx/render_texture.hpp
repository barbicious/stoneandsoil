#pragma once
#include "raw_texture.hpp"

namespace gfx {
    class RenderTexture  : public RawTexture {
    public:
        RenderTexture(i32 width, i32 height);
        ~RenderTexture() override;

        void open() const;
        void close() const;

    private:
        u32 fbo_{};
    };
} // gfx