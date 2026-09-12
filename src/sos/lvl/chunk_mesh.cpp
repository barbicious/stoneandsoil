#include "chunk_mesh.hpp"

#include "tile.hpp"

namespace sos::lvl {
    ChunkMesh::ChunkMesh() {
        Tile tile{Tile::Type::grass};
        Tile stone_tile{Tile::Type::stone};

        for (i32 i{0}; i < (16 * 16 * 16); ++i) {
            i32 x{i % 16};
            i32 y{(i / 16) % 16};
            i32 z{i / (16 * 16)};

            if (y > 14) {
                addVertices(tile.vertices(Tile::Face::back, x, y, z));
                addVertices(tile.vertices(Tile::Face::front, x, y, z));
                addVertices(tile.vertices(Tile::Face::left, x, y, z));
                addVertices(tile.vertices(Tile::Face::right, x, y, z));
                addVertices(tile.vertices(Tile::Face::top, x, y, z));
                addVertices(tile.vertices(Tile::Face::bottom, x, y, z));
            } else {
                addVertices(stone_tile.vertices(Tile::Face::back, x, y, z));
                addVertices(stone_tile.vertices(Tile::Face::front, x, y, z));
                addVertices(stone_tile.vertices(Tile::Face::left, x, y, z));
                addVertices(stone_tile.vertices(Tile::Face::right, x, y, z));
                addVertices(stone_tile.vertices(Tile::Face::top, x, y, z));
                addVertices(stone_tile.vertices(Tile::Face::bottom, x, y, z));
            }
        }
        
        vertex_array_.attribute<f32>(vertex_buffer_, 0, 3, GL_FLOAT, 5, 0);
        vertex_array_.attribute<f32>(vertex_buffer_, 1, 2, GL_FLOAT, 5, 3);

        vertex_buffer_.uploadData(0, sizeof(f32) * vertices_.size(), vertices_.data());
    }

    void ChunkMesh::blit() {
        vertex_array_.bind();
        vertex_buffer_.bind();

        glDrawArrays(GL_TRIANGLES, 0, static_cast<i32>(vertices_.size()));
    }

    void ChunkMesh::addVertices(const std::array<f32, 30> &vertices) {
        vertices_.insert(vertices_.end(), vertices.begin(), vertices.end());
    }
} // sos::lvl