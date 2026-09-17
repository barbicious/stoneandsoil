#pragma once

#include <future>
#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>
#include <noise/FastNoiseLite.h>

#include "chunk_position.hpp"
#include "i_blittable.hpp"
#include "../../thread_pool.hpp"

namespace sos::lvl {
    class ChunkMesh;
    class Chunk;

    class Level {
    public:
        Level();
        ~Level();

        void blit(const glm::vec3& camera_position) const;
        void doChunkWork();

        [[nodiscard]] const Chunk* chunkAt(const ChunkPosition& chunk_position) const {
            if (!chunks_.contains(chunk_position)) {
                return nullptr;
            }

            return chunks_.at(chunk_position);
        }

        [[nodiscard]] Chunk* chunkAt(const ChunkPosition& chunk_position) {
            if (!chunks_.contains(chunk_position)) {
                return nullptr;
            }

            return chunks_.at(chunk_position);
        }

        void pushMesh(ChunkMesh* chunk_mesh);
        void crossBoundaries(const ChunkPosition& player_position);

        [[nodiscard]] const FastNoiseLite& noise() const noexcept {
            return noise_;
        }

    private:
        static constexpr i8 RENDER_DISTANCE{4};

        FastNoiseLite noise_{};

        std::unordered_map<ChunkPosition, Chunk*> chunks_{};
        std::vector<ChunkMesh*> mesh_queue_{};
        std::vector<ChunkPosition> chunk_queue_{};
    };
} // sos::lvl
