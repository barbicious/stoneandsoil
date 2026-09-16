#pragma once
#include "chunk_mesh.hpp"
#include "chunk_position.hpp"
#include "tile_registry.hpp"

namespace sos::lvl {
    class Level;

    class Chunk {
    public:
        static constexpr u32 WIDTH{16}, HEIGHT{16}, DEPTH{16};

        class Layer {
        public:
            Layer() = default;

            void addOpaque() {
                opaque_tile_count_++;
            }

            void removeOpaque() {
                opaque_tile_count_--;
            }

            [[nodiscard]] bool isCompletelyOpaque() const noexcept {
                return opaque_tile_count_ == WIDTH * DEPTH;
            }

        private:
            i32 opaque_tile_count_{};
        };

        Chunk(ChunkPosition chunk_position, Level* level);

        void generateTerrain();

        [[nodiscard]] const ChunkMesh& chunkMesh() const noexcept {
            return chunk_mesh_;
        }

        [[nodiscard]] ChunkMesh* chunkMesh() noexcept {
            return &chunk_mesh_;
        }

        [[nodiscard]] const ChunkPosition& chunkPosition() const noexcept {
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
            if (static_cast<Tile::Type>(idx) == Tile::Type::air) {
                layers_[y].removeOpaque();
            } else {
                layers_[y].addOpaque();
            }
            tiles_[x + WIDTH * (y + HEIGHT * z)] = idx;
        }

        void dirty(bool dirty) {
            dirty_ = dirty;
        }

        [[nodiscard]] bool dirty() const noexcept {
            return dirty_;
        }

        [[nodiscard]] const Layer& layer(const usize y) const noexcept {
            return layers_[y];
        }

    private:
        std::array<usize, WIDTH * HEIGHT * DEPTH> tiles_{};
        std::array<Layer, HEIGHT> layers_{};

        ChunkMesh chunk_mesh_;
        ChunkPosition chunk_position_;

        Level* level_;

        bool dirty_{false};
    };
} // sos::lvl
