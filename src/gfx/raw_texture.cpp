#include "raw_texture.hpp"

#include <glad/glad.h>

namespace gfx {
    RawTexture::RawTexture(u32 target) : target_{target} {
        glGenTextures(1, &id_);

        RawTexture::bind();

        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    RawTexture::~RawTexture() {
        glDeleteTextures(1, &id_);
    }

    void RawTexture::bind() const {
        glBindTexture(target_, id_);
    }

    void RawTexture::unbind() const {
        glBindTexture(target_, 0);
    }
} // gfx
