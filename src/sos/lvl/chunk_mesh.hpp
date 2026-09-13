#pragma once
#include <vector>

#include "i_blittable.hpp"
#include "../../types.hpp"
#include "../../gfx/vertex_array.hpp"
#include "../../gfx/vertex_buffer.hpp"

namespace sos::lvl {
    class Level;
    class Chunk;

    class ChunkMesh : public IBlittable {
    public:
        explicit ChunkMesh(const Chunk *chunk);

        void generateMesh(Level &level);

        void blit() const override;
        void uploadData();

    private:
        std::vector<f32> vertices_;
        gfx::VertexArray vertex_array_{};
        gfx::VertexBuffer vertex_buffer_{GL_DYNAMIC_DRAW, std::array<f32, 180 * 16 * 16 * 16>{}};
        const Chunk *chunk_;

        void addVertices(const std::array<f32, 30> &vertices);
    };
} // sos::lvl
