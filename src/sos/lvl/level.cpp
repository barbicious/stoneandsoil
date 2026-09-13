#include "level.hpp"

#include <ranges>

#include "chunk.hpp"

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
        for (Chunk *chunk: chunks_ | std::views::values) {
            delete chunk;
        }
    }

    void Level::blit() const {
        for (const Chunk* const &chunk: chunks_ | std::views::values) {
            chunk->chunkMesh().blit();
        }
    }

    void Level::doChunkWork() {
        if (mesh_queue_.empty()) {
            return;
        }

        ChunkMesh* chunk_mesh{mesh_queue_.back()};
        chunk_mesh->generateMesh(*this);
        mesh_queue_.pop_back();
    }

    void Level::pushMesh(ChunkMesh *chunk_mesh) {
        mesh_queue_.push_back(chunk_mesh);
    }
} // sos::lvl
