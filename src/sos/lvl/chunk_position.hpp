#pragma once
#include <compare>
#include <functional>

#include "../../types.hpp"

namespace sos::lvl {
    struct ChunkPosition {
        i32 x{}, y{}, z{};

        friend usize hash_value(const ChunkPosition& obj) {
            usize seed = 0x5BFB5C52;
            seed ^= (seed << 6) + (seed >> 2) + 0x57F3F3D1 + static_cast<usize>(obj.x);
            seed ^= (seed << 6) + (seed >> 2) + 0x7056563B + static_cast<usize>(obj.z);
            seed ^= (seed << 6) + (seed >> 2) + 0x4FED8F48 + static_cast<usize>(obj.y);
            return seed;
        }

        auto operator<=>(const ChunkPosition&) const = default;

        static ChunkPosition fromTileCoordinates(i32 x, i32 y, i32 z);
    };
} // sos::lvl

namespace std {
    template <>
    struct hash<sos::lvl::ChunkPosition> {
        usize operator()(const sos::lvl::ChunkPosition& obj) const noexcept {
            return hash_value(obj);
        }
    };
}
