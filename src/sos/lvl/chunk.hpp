#pragma once
#include "chunk_mesh.hpp"
#include "chunk_position.hpp"
#include "tile_registry.hpp"

namespace sos::lvl {
    class Level;

    class Chunk {
    public:
        static constexpr u32 WIDTH{16}, HEIGHT{16}, DEPTH{16};

        Chunk(ChunkPosition chunk_position, Level *level);

        [[nodiscard]] const ChunkMesh &chunkMesh() const noexcept {
            return chunk_mesh_;
        }

        [[nodiscard]] ChunkMesh *chunkMesh() noexcept {
            return &chunk_mesh_;
        }

        [[nodiscard]] const ChunkPosition &chunkPosition() const noexcept {
            return chunk_position_;
        }

        [[nodiscard]] bool isTileTransparent(usize x, usize y, usize z) const noexcept {
            return TileRegistry::get()[tiles_[x + WIDTH * (y + HEIGHT * z)]].type() == Tile::Type::air;
        }

        [[nodiscard]] usize tileAt(usize x, usize y, usize z) const noexcept {
            return tiles_[x + WIDTH * (y + HEIGHT * z)];
        }

        [[nodiscard]] ChunkPosition relativePosition(i32 x, i32 y, i32 z) const noexcept {
            return ChunkPosition{
                .x = chunk_position_.x + x,
                .y = chunk_position_.y + y,
                .z = chunk_position_.z + z
            };
        }

        void setTile(usize x, usize y, usize z, usize idx) {
            tiles_[x + WIDTH * (y + HEIGHT * z)] = idx;
        }

    private:
        std::array<usize, WIDTH * HEIGHT * DEPTH> tiles_{};

        ChunkMesh chunk_mesh_;
        ChunkPosition chunk_position_;

        Level *level_;
    };
} // sos::lvl
