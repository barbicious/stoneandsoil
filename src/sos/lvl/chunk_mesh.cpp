#include "chunk_mesh.hpp"

#include <iostream>

#include "chunk.hpp"
#include "level.hpp"
#include "tile.hpp"

namespace sos::lvl {
    ChunkMesh::ChunkMesh(const Chunk* chunk) : chunk_{chunk} {
        vertex_array_.attribute<f32>(vertex_buffer_, 0, 3, GL_FLOAT, 6, 0);
        vertex_array_.attribute<f32>(vertex_buffer_, 1, 2, GL_FLOAT, 6, 3);
        vertex_array_.attribute<f32>(vertex_buffer_, 2, 1, GL_FLOAT, 6, 5);
    }

    void ChunkMesh::generateMesh(Level& level) {
        opaque_vertices_.clear();
        transparent_vertices_.clear();

        for (i32 i{0}; i < Chunk::WIDTH * Chunk::HEIGHT * Chunk::DEPTH; ++i) {
            i32 y{(i / static_cast<i32>(Chunk::WIDTH)) % static_cast<i32>(Chunk::WIDTH)};

            if (isLayerSkippable(y, level)) {
                continue;
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
                if (chunk_->isTileTransparent(x - 1, y, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                    addVertices(tile.vertices(Tile::Face::left, world_x, world_y, world_z), tile.type());
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(-1, 0, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(Chunk::WIDTH - 1, y, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                        addVertices(tile.vertices(Tile::Face::left, world_x, world_y, world_z), tile.type());
                    }
                }
            }

            if (x < Chunk::WIDTH - 1) {
                if (chunk_->isTileTransparent(x + 1, y, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                    addVertices(tile.vertices(Tile::Face::right, world_x, world_y, world_z), tile.type());
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(1, 0, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(0, y, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                        addVertices(tile.vertices(Tile::Face::right, world_x, world_y, world_z), tile.type());
                    }
                }
            }

            if (y > 0) {
                if (chunk_->isTileTransparent(x, y - 1, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                    addVertices(tile.vertices(Tile::Face::bottom, world_x, world_y, world_z), tile.type());
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, -1, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, Chunk::HEIGHT - 1, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                        addVertices(tile.vertices(Tile::Face::bottom, world_x, world_y, world_z), tile.type());
                    }
                }
            }

            if (y < Chunk::HEIGHT - 1) {
                if (chunk_->isTileTransparent(x, y + 1, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                    addVertices(tile.vertices(Tile::Face::top, world_x, world_y, world_z), tile.type());
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 1, 0))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, 0, z, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                        addVertices(tile.vertices(Tile::Face::top, world_x, world_y, world_z), tile.type());
                    }
                }
            }

            if (z > 0) {
                if (chunk_->isTileTransparent(x, y, z - 1, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                    addVertices(tile.vertices(Tile::Face::back, world_x, world_y, world_z), tile.type());
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 0, -1))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, y, Chunk::DEPTH - 1, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                        addVertices(tile.vertices(Tile::Face::back, world_x, world_y, world_z), tile.type());
                    }
                }
            }

            if (z < Chunk::DEPTH - 1) {
                if (chunk_->isTileTransparent(x, y, z + 1, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                    addVertices(tile.vertices(Tile::Face::front, world_x, world_y, world_z), tile.type());
                }
            } else {
                if (const Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 0, 1))}; chunk != nullptr) {
                    if (chunk->isTileTransparent(x, y, 0, TileRegistry::get()[chunk_->tileAt(x, y, z)].type())) {
                        addVertices(tile.vertices(Tile::Face::front, world_x, world_y, world_z), tile.type());
                    }
                }
            }
        }
    }

    void ChunkMesh::blitTransparent() const {
        vertex_array_.bind();
        vertex_buffer_.bind();

        glDrawArrays(GL_TRIANGLES, static_cast<i32>(opaque_vertices_.size() / 6), static_cast<i32>(transparent_vertices_.size() / 6));
    }

    void ChunkMesh::blitOpaque() const {
        vertex_array_.bind();
        vertex_buffer_.bind();

        glDrawArrays(GL_TRIANGLES, 0, static_cast<i32>(opaque_vertices_.size() / 6));
    }

    void ChunkMesh::uploadData() {
        vertex_array_.bind();
        vertex_buffer_.bind();
        vertex_buffer_.uploadData(0, sizeof(f32) * opaque_vertices_.size(), opaque_vertices_.data());
        vertex_buffer_.uploadData(sizeof(f32) * opaque_vertices_.size(), sizeof(f32) * transparent_vertices_.size(), transparent_vertices_.data());
    }

    void ChunkMesh::addVertices(const std::array<f32, 36>& vertices, Tile::Type tile_type) {
        if (tile_type == Tile::Type::water or tile_type == Tile::Type::leaf) {
            transparent_vertices_.insert(transparent_vertices_.end(), vertices.begin(), vertices.end());
        } else {
            opaque_vertices_.insert(opaque_vertices_.end(), vertices.begin(), vertices.end());
        }
    }

    bool ChunkMesh::isLayerSkippable(i32 y, Level& level) const {
        bool skippable{true};

        if (!(y < Chunk::HEIGHT - 1 and y > 0 and chunk_->layer(y + 1).isCompletelyOpaque() and chunk_->layer(y - 1).
              isCompletelyOpaque())) {
            skippable = false;
        }

        if (y == 0 and level.chunkAt(chunk_->relativePosition(0, -1, 0))) {
            Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, -1, 0))};

            if (!chunk->layer(Chunk::HEIGHT - 1).isCompletelyOpaque()) {
                skippable = false;
            }
        }

        if (y == Chunk::HEIGHT - 1 and level.chunkAt(chunk_->relativePosition(0, 1, 0))) {
            Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 1, 0))};

            if (!chunk->layer(0).isCompletelyOpaque()) {
                skippable = false;
            }
        }

        if (level.chunkAt(chunk_->relativePosition(0, 0, 1))) {
            Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 0, 1))};

            if (!chunk->layer(y).isCompletelyOpaque()) {
                skippable = false;
            }
        }

        if (level.chunkAt(chunk_->relativePosition(0, 0, -1))) {
            Chunk* chunk{level.chunkAt(chunk_->relativePosition(0, 0, -1))};

            if (!chunk->layer(y).isCompletelyOpaque()) {
                skippable = false;
            }
        }

        if (level.chunkAt(chunk_->relativePosition(1, 0, 0))) {
            Chunk* chunk{level.chunkAt(chunk_->relativePosition(1, 0, 0))};

            if (!chunk->layer(y).isCompletelyOpaque()) {
                skippable = false;
            }
        }

        if (level.chunkAt(chunk_->relativePosition(-1, 0, 0))) {
            Chunk* chunk{level.chunkAt(chunk_->relativePosition(-1, 0, 0))};

            if (!chunk->layer(y).isCompletelyOpaque()) {
                skippable = false;
            }
        }

        return skippable;
    }
} // sos::lvl
