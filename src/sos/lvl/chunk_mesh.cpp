#include "chunk_mesh.hpp"

#include <iostream>

#include "chunk.hpp"
#include "level.hpp"
#include "tile.hpp"

namespace sos::lvl {
    ChunkMesh::ChunkMesh(const Chunk* chunk) : chunk_{chunk} {
        vertex_array_.attribute<f32>(vertex_buffer_, 0, 3, GL_FLOAT, 5, 0);
        vertex_array_.attribute<f32>(vertex_buffer_, 1, 2, GL_FLOAT, 5, 3);
    }

    void ChunkMesh::generateMesh(Level& level) {
        vertices_.clear();

        for (i32 i{0}; i < Chunk::WIDTH * Chunk::HEIGHT * Chunk::DEPTH; ++i) {
            i32 y{(i / static_cast<i32>(Chunk::WIDTH)) % static_cast<i32>(Chunk::WIDTH)};

            if (y < Chunk::HEIGHT - 1 and y > 0 and chunk_->layer(y + 1).isCompletelyOpaque() and chunk_->layer(y - 1).isCompletelyOpaque()) {
                continue;
            }

            if (y == 0 and level.chunkAt(chunk_->relativePosition(0, -1, 0))) {
                Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, -1, 0))};

                if (chunk->layer(Chunk::HEIGHT - 1).isCompletelyOpaque()) {
                    continue;
                }
            }

            if (y == Chunk::HEIGHT - 1 and level.chunkAt(chunk_->relativePosition(0, 1, 0))) {
                Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 1, 0))};

                if (chunk->layer(0).isCompletelyOpaque()) {
                    continue;
                }
            }

            i32 z{i / (static_cast<i32>(Chunk::WIDTH) * static_cast<i32>(Chunk::WIDTH))};
            i32 x{i % static_cast<i32>(Chunk::WIDTH)};

            Tile tile{TileRegistry::get()[chunk_->tileAt(x, y, z)]};

            if (tile.type() == Tile::Type::air) {
                continue;
            }

            i32 world_x{static_cast<i32>(x + chunk_->chunkPosition().x * Chunk::WIDTH)};
            i32 world_y{static_cast<i32>(y + chunk_->chunkPosition().y * Chunk::HEIGHT)};
            i32 world_z{static_cast<i32>(z + chunk_->chunkPosition().z * Chunk::DEPTH)};

            if (x > 0) {
                if (chunk_->isTileTransparent(x - 1, y, z)) {
                    addVertices(tile.vertices(Tile::Face::left, world_x, world_y, world_z));
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(-1, 0, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(Chunk::WIDTH - 1, y, z)) {
                        addVertices(tile.vertices(Tile::Face::left, world_x, world_y, world_z));
                    }
                }
            }

            if (x < Chunk::WIDTH - 1) {
                if (chunk_->isTileTransparent(x + 1, y, z)) {
                    addVertices(tile.vertices(Tile::Face::right, world_x, world_y, world_z));
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(1, 0, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(0, y, z)) {
                        addVertices(tile.vertices(Tile::Face::right, world_x, world_y, world_z));
                    }
                }
            }

            if (y > 0) {
                if (chunk_->isTileTransparent(x, y - 1, z)) {
                    addVertices(tile.vertices(Tile::Face::bottom, world_x, world_y, world_z));
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, -1, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, Chunk::HEIGHT - 1, z)) {
                        addVertices(tile.vertices(Tile::Face::bottom, world_x, world_y, world_z));
                    }
                }
            }

            if (y < Chunk::HEIGHT - 1) {
                if (chunk_->isTileTransparent(x, y + 1, z)) {
                    addVertices(tile.vertices(Tile::Face::top, world_x, world_y, world_z));
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 1, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, 0, z)) {
                        addVertices(tile.vertices(Tile::Face::top, world_x, world_y, world_z));
                    }
                }
            }

            if (z > 0) {
                if (chunk_->isTileTransparent(x, y, z - 1)) {
                    addVertices(tile.vertices(Tile::Face::back, world_x, world_y, world_z));
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 0, -1))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, y, 0)) {
                        addVertices(tile.vertices(Tile::Face::back, world_x, world_y, world_z));
                    }
                }
            }

            if (z < Chunk::DEPTH - 1) {
                if (chunk_->isTileTransparent(x, y, z + 1)) {
                    addVertices(tile.vertices(Tile::Face::front, world_x, world_y, world_z));
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 0, 1))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, y, Chunk::DEPTH - 1)) {
                        addVertices(tile.vertices(Tile::Face::front, world_x, world_y, world_z));
                    }
                }
            }
        }
    }

    void ChunkMesh::blit() const {
        vertex_array_.bind();
        vertex_buffer_.bind();

        glDrawArrays(GL_TRIANGLES, 0, static_cast<i32>(vertices_.size() / 5));
    }

    void ChunkMesh::uploadData() {
        vertex_array_.bind();
        vertex_buffer_.bind();
        vertex_buffer_.uploadData(0, sizeof(f32) * vertices_.size(), vertices_.data());
    }

    void ChunkMesh::addVertices(const std::array<f32, 30>& vertices) {
        vertices_.insert(vertices_.end(), vertices.begin(), vertices.end());
    }
} // sos::lvl
