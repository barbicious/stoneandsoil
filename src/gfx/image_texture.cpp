#include "image_texture.hpp"

#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace gfx {
    ImageTexture::ImageTexture(const std::filesystem::path &image_path) : RawTexture{GL_TEXTURE_2D} {
        u8* data{stbi_load(image_path.c_str(), &width_, &height_, &channels_, 4)};
        if (data == nullptr) {
            std::cerr << stbi_failure_reason() << std::endl;
        } else {
            glTexImage2D(target(), 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(target());
        }
    }
} // gfx