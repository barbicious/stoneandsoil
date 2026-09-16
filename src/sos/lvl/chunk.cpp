#include "chunk.hpp"

namespace sos::lvl {
    Chunk::Chunk(ChunkPosition chunk_position, Level* level) : chunk_mesh_{this},
                                                               chunk_position_{chunk_position},
                                                               level_{level} {
        generateTerrain();
    }

    void Chunk::generateTerrain() {
        for (i32 i{0}; i < WIDTH * HEIGHT * DEPTH; ++i) {
            i32 x{i % static_cast<i32>(WIDTH)};
            i32 y{(i / static_cast<i32>(WIDTH)) % static_cast<i32>(WIDTH)};
            i32 z{i / (static_cast<i32>(WIDTH) * static_cast<i32>(WIDTH))};

            if (y < 11) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["stone"];
                layers_[y].addOpaque();
            } else if (y < 12) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["grass"];
                layers_[y].addOpaque();
            } else {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["air"];
                layers_[y].removeOpaque();
            }
        }
    }
} // sos::lvl