#pragma once
#include <array>

#include "../texture_atlas.hpp"
#include "../../types.hpp"

namespace sos::lvl {
    class Tile {
    public:
        enum struct Type : u8 {
            air = 0,
            grass,
            stone,
        };

        enum struct Face : u8 {
            front = 0,
            back,
            left,
            right,
            top,
            bottom,
        };

        explicit Tile(Type type);

        [[nodiscard]] std::array<f32, 30> vertices(Face face, i32 x, i32 y, i32 z) const;

    private:
        const f32 texture_width{8.0f}, texture_height{8.0f};

        const f32 gl_texture_width{8.0f / static_cast<f32>(TextureAtlas::get().width())}, gl_texture_height{8.0f / static_cast<f32>(TextureAtlas::get().height())};

        f32 u{}, v{};

        Type type;

    };
} // sos::lvl