#pragma once
#include <vector>

#include "i_blittable.hpp"
#include "tile.hpp"
#include "../../types.hpp"
#include "../../gfx/vertex_array.hpp"
#include "../../gfx/vertex_buffer.hpp"

namespace sos::lvl {
    class Level;
    class Chunk;

    class ChunkMesh {
    public:
        explicit ChunkMesh(const Chunk* chunk);

        void generateMesh(Level& level);

        void blitTransparent() const;
        void blitOpaque() const;
        void uploadData();

    private:
        std::vector<f32> opaque_vertices_;
        std::vector<f32> transparent_vertices_;


        gfx::VertexArray vertex_array_{};
        gfx::VertexBuffer vertex_buffer_{GL_DYNAMIC_DRAW, std::array<f32, 216 * 16 * 16 * 16>{}};
        const Chunk* chunk_;

        void addVertices(const std::array<f32, 36>& vertices, Tile::Type tile_type);
        bool isLayerSkippable(i32 y, Level& level) const;
    };
} // sos::lvl
