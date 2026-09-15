#include "chunk_position.hpp"

#include "chunk.hpp"
#include "../../math/core.hpp"

namespace sos::lvl {
    ChunkPosition ChunkPosition::fromTileCoordinates(i32 x, i32 y, i32 z) {
        return ChunkPosition{
            .x = math::divEuclid(x, static_cast<i32>(Chunk::WIDTH)),
            .y = math::divEuclid(y, static_cast<i32>(Chunk::HEIGHT)),
            .z = math::divEuclid(z, static_cast<i32>(Chunk::DEPTH))
        };
    }
} // sos::lvl
