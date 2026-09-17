#include "level.hpp"

#include <future>
#include <ranges>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "chunk.hpp"
#include "../../thread_pool.hpp"

namespace sos::lvl {
    Level::Level() {
        noise_.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise_.SetFrequency(0.01);
        noise_.SetFractalGain(0.72);
        noise_.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise_.SetFractalLacunarity(2.80);

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

    void Level::blit(const glm::vec3& camera_position) const {
        std::vector<std::pair<ChunkPosition, Chunk*>> chunks{chunks_.begin(), chunks_.end()};

        std::sort(chunks.begin(), chunks.end(), [camera_position](const auto& a, const auto& b) {
            const glm::vec3 a_position{
                glm::vec3{
                    std::get<0>(a).x * Chunk::WIDTH + Chunk::WIDTH / 2.0f,
                    std::get<0>(a).y * Chunk::HEIGHT + Chunk::HEIGHT / 2.0f,
                    std::get<0>(a).z * Chunk::DEPTH + Chunk::DEPTH / 2.0f,
                } - camera_position
            };

            const glm::vec3 b_position{
                glm::vec3{
                    std::get<0>(b).x * Chunk::WIDTH + Chunk::WIDTH / 2.0f,
                    std::get<0>(b).y * Chunk::HEIGHT + Chunk::HEIGHT / 2.0f,
                    std::get<0>(b).z * Chunk::DEPTH + Chunk::DEPTH / 2.0f,
                } - camera_position
            };

            return glm::dot(a_position, a_position) >
                   glm::dot(b_position, b_position);
        });

        glDisable(GL_BLEND);

        for (const Chunk* const& chunk : chunks | std::views::values) {
            chunk->chunkMesh().blitOpaque();
        }

        glEnable(GL_BLEND);

        for (const Chunk* const& chunk : chunks | std::views::values) {
            chunk->chunkMesh().blitTransparent();
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
                        Chunk* chunk{chunks_[chunk_position]};
                        chunk->dirty(false);
                        mesh_queue_.emplace_back(chunk->chunkMesh());
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
