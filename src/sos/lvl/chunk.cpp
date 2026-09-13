#include "chunk.hpp"

namespace sos::lvl {
    Chunk::Chunk(ChunkPosition chunk_position, Level *level) : chunk_mesh_{this}, chunk_position_{chunk_position}, level_{level} {
        for (i32 i{0}; i < WIDTH * HEIGHT * DEPTH; ++i) {
            i32 x{i % 16};
            i32 y{(i / 16) % 16};
            i32 z{i / (16 * 16)};

            if (y < 11) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["stone"];
            } else if (y < 12) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["grass"];
            } else {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["air"];
            }
        }
    }
} // sos::lvl