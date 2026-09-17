#include "chunk.hpp"

#include "level.hpp"

namespace sos::lvl {
    Chunk::Chunk(ChunkPosition chunk_position, Level* level) : chunk_mesh_{this},
                                                               chunk_position_{chunk_position},
                                                               level_{level} {
        generateTerrain();
    }

    void Chunk::generateTerrain() {
        for (i32 i{0}; i < WIDTH * HEIGHT * DEPTH; ++i) {
            i32 x{i % static_cast<i32>(WIDTH)};
            i32 y{i / static_cast<i32>(WIDTH) % static_cast<i32>(WIDTH)};
            i32 z{i / (static_cast<i32>(WIDTH) * static_cast<i32>(WIDTH))};

            const i32 value{
                static_cast<i32>(level_->noise().GetNoise(
                                     static_cast<f32>(x + chunk_position_.x * static_cast<i32>(WIDTH)),
                                     static_cast<f32>(z + chunk_position_.z * static_cast<i32>(DEPTH)) + 1.0f) * 16.0f +
                                 static_cast<f32>(y + chunk_position_.y * static_cast<i32>(HEIGHT)))
            };

            if (value == 1 and x == 0 and z == 0) {
                spawnTree(x, y, z);
            } else if (value == 0) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["grass"];
                layers_[y].addOpaque();
            } else if (value < 0) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["stone"];
                layers_[y].addOpaque();
            } else if (y + chunk_position_.y * static_cast<i32>(HEIGHT) < -5) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["water"];
                layers_[y].removeOpaque();
            }
        }
    }

    void Chunk::spawnTree(i32 x, i32 y, i32 z) {
        for (i32 tree_z{-3 + z}; tree_z < 3 + z; ++tree_z) {
            for (i32 tree_y{-2 + y}; tree_y < 2 + y; ++tree_y) {
                if (tree_z > 1 + x and tree_y > -1 + y) {
                    continue;
                }

                for (i32 tree_x{-3 + x}; tree_x < 3 + x; ++tree_x) {
                    if (tree_x > 1 + x and tree_y > -1 + y) {
                        continue;
                    }
                    unsafeAddBlock(tree_x, tree_y + 4, tree_z, TileRegistry::get()["leaf"]);
                }
            }
        }

        unsafeAddBlock(x, y, z, TileRegistry::get()["bark"]);
        unsafeAddBlock(x, y + 1, z, TileRegistry::get()["bark"]);
        unsafeAddBlock(x, y + 2, z, TileRegistry::get()["bark"]);
        unsafeAddBlock(x, y + 3, z, TileRegistry::get()["bark"]);
    }

    void Chunk::unsafeAddBlock(i32 x, i32 y, i32 z, usize tile_idx) {
        if (x < 0 or x > WIDTH - 1 or y < 0 or y > HEIGHT - 1 or z < 0 or z > DEPTH - 1) {

        } else {
            tiles_[x + WIDTH * (y + HEIGHT * z)] = tile_idx;
            if (tile_idx == TileRegistry::get()["leaf"]) {
                layers_[y].removeOpaque();
            } else {
                layers_[y].addOpaque();
            }
        }
    }
} // sos::lvl
