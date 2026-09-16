#include "level.hpp"

#include <future>
#include <iostream>
#include <ranges>
#include <thread>

#include "chunk.hpp"
#include "../../thread_pool.hpp"

namespace sos::lvl {
    Level::Level() {
        for (i32 z{-RENDER_DISTANCE}; z <= RENDER_DISTANCE; ++z) {
            for (i32 y{-RENDER_DISTANCE}; y <= RENDER_DISTANCE; ++y) {
                for (i32 x{-RENDER_DISTANCE}; x <= RENDER_DISTANCE; ++x) {
                    const ChunkPosition chunk_position{
                        .x = x,
                        .y = y,
                        .z = z
                    };

                    Chunk* chunk{new Chunk{chunk_position, this}};
                    chunks_[chunk_position] = chunk;
                    mesh_queue_.emplace_back(chunk->chunkMesh());
                }
            }
        }
    }

    Level::~Level() {
        for (Chunk* chunk : chunks_ | std::views::values) {
            delete chunk;
        }
    }

    void Level::blit() const {
        for (const Chunk* const & chunk : chunks_ | std::views::values) {
            chunk->chunkMesh().blit();
        }
    }

    void Level::doChunkWork() {
        if (chunk_queue_.empty()) {
            if (mesh_queue_.empty()) {
                return;
            }

            ChunkMesh* chunk_mesh{mesh_queue_.back()};
            mesh_queue_.pop_back();

            chunk_mesh->generateMesh(*this);
            chunk_mesh->uploadData();

            return;
        }

        ChunkPosition chunk_position{chunk_queue_.back()};
        chunk_queue_.pop_back();

        Chunk* chunk{new Chunk{chunk_position, this}};
        chunks_[chunk_position] = chunk;

        mesh_queue_.emplace_back(chunk->chunkMesh());
    }

    void Level::pushMesh(ChunkMesh* chunk_mesh) {
        mesh_queue_.emplace_back(chunk_mesh);
    }

    void Level::crossBoundaries(const ChunkPosition& player_position) {
        for (Chunk* const & chunk : chunks_ | std::views::values) {
            chunk->dirty(true);
        }

        for (i32 z{-RENDER_DISTANCE + player_position.z}; z <= RENDER_DISTANCE + player_position.z; ++z) {
            for (i32 y{-RENDER_DISTANCE + player_position.y}; y <= RENDER_DISTANCE + player_position.y; ++y) {
                for (i32 x{-RENDER_DISTANCE + player_position.x}; x <= RENDER_DISTANCE + player_position.x; ++x) {
                    const ChunkPosition chunk_position{
                        .x = x,
                        .y = y,
                        .z = z
                    };

                    if (chunks_.contains(chunk_position)) {
                        chunks_[chunk_position]->dirty(false);
                    } else {
                        chunk_queue_.push_back(chunk_position);
                    }
                }
            }
        }

        std::erase_if(chunks_, [](const auto& entry) {
            return entry.second->dirty();
        });
    }
} // sos::lvl
