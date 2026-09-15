#pragma once
#include "../gfx/image_texture.hpp"

namespace sos {
    class TextureAtlas : public gfx::IBindable {
    public:
        TextureAtlas(const TextureAtlas&) = delete;
        TextureAtlas& operator=(const TextureAtlas&) = delete;

        TextureAtlas(TextureAtlas&&) = delete;
        TextureAtlas& operator=(TextureAtlas&&) = delete;

        static TextureAtlas& get() {
            static TextureAtlas texture_atlas;
            return texture_atlas;
        }

        [[nodiscard]] i32 width() const {
            return image_texture_.width();
        }

        [[nodiscard]] i32 height() const {
            return image_texture_.height();
        }

        void bind() const override;
        void unbind() const override;

    private:
        TextureAtlas() = default;

        gfx::ImageTexture image_texture_{"res/textureatlas.png"};
    };
} // sos
