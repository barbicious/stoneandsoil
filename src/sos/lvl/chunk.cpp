#include "chunk.hpp"

#include <iostream>
#include <noise/FastNoiseLite.h>

namespace sos::lvl {
    Chunk::Chunk(ChunkPosition chunk_position, Level* level) : chunk_mesh_{this},
                                                               chunk_position_{chunk_position},
                                                               level_{level} {
        generateTerrain();
    }

    void Chunk::generateTerrain() {
        FastNoiseLite fast_noise_lite{};
        fast_noise_lite.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        fast_noise_lite.SetFrequency(0.01);
        fast_noise_lite.SetFractalGain(0.72);
        fast_noise_lite.SetFractalType(FastNoiseLite::FractalType_FBm);
        fast_noise_lite.SetFractalLacunarity(2.80);

        for (i32 i{0}; i < WIDTH * HEIGHT * DEPTH; ++i) {
            i32 x{i % static_cast<i32>(WIDTH)};
            i32 y{i / static_cast<i32>(WIDTH) % static_cast<i32>(WIDTH)};
            i32 z{i / (static_cast<i32>(WIDTH) * static_cast<i32>(WIDTH))};

            const i32 value{
                static_cast<i32>(fast_noise_lite.GetNoise(
                                     static_cast<f32>(x + chunk_position_.x * static_cast<i32>(WIDTH)),
                                     static_cast<f32>(z + chunk_position_.z * static_cast<i32>(DEPTH)) + 1.0f) * 16.0f +
                                 static_cast<f32>(y + chunk_position_.y * static_cast<i32>(HEIGHT)))
            };

            if (value == 0) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["grass"];
                layers_[y].addOpaque();
            } else if (value < 0) {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["stone"];
                layers_[y].addOpaque();
            } else {
                tiles_[x + WIDTH * (y + HEIGHT * z)] = TileRegistry::get()["air"];
                layers_[y].removeOpaque();
            }
        }
    }
} // sos::lvl
