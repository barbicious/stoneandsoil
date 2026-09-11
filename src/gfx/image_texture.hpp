#pragma once
#include <filesystem>

#include "raw_texture.hpp"

namespace gfx {
    class ImageTexture : public RawTexture {
    public:
        explicit ImageTexture(const std::filesystem::path &image_path);
        ~ImageTexture() override = default;

    private:
        i32 width_{}, height_{}, channels_{};
    };
} // gfx