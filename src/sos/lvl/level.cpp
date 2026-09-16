#include "level.hpp"

#include <future>
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
                    mesh_queue_.push_back(chunk->chunkMesh());
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
        if (!mesh_queue_.empty()) {
            ChunkMesh* mesh{mesh_queue_.back()};
            mesh_queue_.pop_back();
            mesh->generateMesh(*this);
            mesh->uploadData();
        } else {
            if (chunk_queue_.empty()) {
                return;
            }
            ChunkPosition chunk_position{chunk_queue_.back()};
            chunk_queue_.pop_back();

            Chunk* chunk{new Chunk{chunk_position, this}};
            chunks_[chunk_position] = chunk;
            chunk->chunkMesh()->generateMesh(*this);
            chunk->chunkMesh()->uploadData();
        }
    }

    void Level::pushMesh(ChunkMesh* chunk_mesh) {
        chunk_mesh->generateMesh(*this);
        chunk_mesh->uploadData();
    }

    void Level::crossBoundaries(const ChunkPosition& player_position) {
        for (Chunk* const & chunk : chunks_ | std::views::values) {
            chunk->dirty(true);
        }

        constexpr i32 R = RENDER_DISTANCE;
        constexpr i32 SIZE = 2 * R + 1;
        constexpr i32 TOTAL = SIZE * SIZE * SIZE;

        for (i32 i = 0; i < TOTAL; ++i) {
            i32 x = (i % SIZE) - R + player_position.x;
            i32 y = ((i / SIZE) % SIZE) - R + player_position.y;
            i32 z = (i / (SIZE * SIZE)) - R + player_position.z;

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

        std::erase_if(chunks_, [](const auto& entry) {
            return entry.second->dirty();
        });
    }
} // sos::lvl
