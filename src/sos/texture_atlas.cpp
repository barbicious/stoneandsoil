#include "texture_atlas.hpp"

namespace sos {
    void TextureAtlas::bind() const {
        image_texture_.bind();
    }

    void TextureAtlas::unbind() const {
        image_texture_.unbind();
    }
} // sos