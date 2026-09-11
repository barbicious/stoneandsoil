#include "render_texture.hpp"

#include <iostream>
#include <glad/glad.h>

namespace gfx {
    RenderTexture::RenderTexture(i32 width, i32 height) : RawTexture{GL_TEXTURE_2D} {
        glGenFramebuffers(1, &fbo_);

        open();

        RawTexture::bind();

        glTexImage2D(target(), 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        RawTexture::unbind();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id(), 0);

        close();

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Error creating frame buffer!" << std::endl;
        }
    }

    RenderTexture::~RenderTexture() {
        glDeleteFramebuffers(1, &fbo_);
    }

    void RenderTexture::open() const {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    }

    void RenderTexture::close() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
} // gfx