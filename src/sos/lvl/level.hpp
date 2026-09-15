#pragma once

#include <future>
#include <unordered_map>
#include <vector>

#include "chunk_position.hpp"
#include "i_blittable.hpp"

namespace sos::lvl {
    class ChunkMesh;
    class Chunk;

    class Level : public IBlittable {
    public:
        Level();
        ~Level() override;

        void blit() const override;
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

    private:
        static constexpr i8 RENDER_DISTANCE{3};

        std::unordered_map<ChunkPosition, Chunk*> chunks_{};
        std::vector<ChunkMesh*> mesh_queue_{};
    };
} // sos::lvl
