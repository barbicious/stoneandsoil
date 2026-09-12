#include "texture_atlas.hpp"

namespace sos {
    void TextureAtlas::bind() {
        image_texture_.bind();
    }

    void TextureAtlas::unbind() {
        image_texture_.unbind();
    }
} // sos