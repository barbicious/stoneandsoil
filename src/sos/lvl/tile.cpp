#include "tile.hpp"

#include <iostream>

#include "../texture_atlas.hpp"

#define UV(u0, v0, u1, v1)\
    u0 = (u1 * texture_width) / static_cast<f32>(TextureAtlas::get().width());\
    v0 = (v1 * texture_height) / static_cast<f32>(TextureAtlas::get().height());

namespace sos::lvl {
    Tile::Tile(Type type) : type_{type} {
        switch (type) {
            case Type::air: {
            }
            break;
            case Type::grass: {
                UV(this->u, this->v, 0, 0);
            }
            break;
            case Type::stone: {
                UV(this->u, this->v, 1, 0);
            }
            break;
            case Type::water: {
                UV(this->u, this->v, 2, 0);
            }
            break;
            case Type::bark: {
                UV(this->u, this->v, 3, 0);
            }
            break;
            case Type::leaf: {
                UV(this->u, this->v, 4, 0);
            }
            break;
        }
    }

    std::array<f32, 36> Tile::vertices(Face face, i32 x, i32 y, i32 z) const {
        if (type_ == Type::air) {
            std::cerr << "Attempted to get air vertices." << std::endl;
        }

        UV(f32 u_full, f32 v_full, 1.0, 1.0);

        u_full += u;
        v_full += v;

        f32 xf{static_cast<f32>(x)};
        f32 yf{static_cast<f32>(y)};
        f32 zf{static_cast<f32>(z)};

        f32 world_xf{xf + 1.0f};
        f32 world_yf{yf + 1.0f};
        f32 world_zf{zf + 1.0f};

        switch (face) {
            case Face::back: {
                return std::array{
                    xf, world_yf, zf, u_full, v_full, 0.75f,
                    world_xf, world_yf, zf, u, v_full, 0.75f,
                    world_xf, yf, zf, u, v, 0.75f,
                    world_xf, yf, zf, u, v, 0.75f,
                    xf, yf, zf, u_full, v, 0.75f,
                    xf, world_yf, zf, u_full, v_full, 0.75f,
                };
            }
            break;
            case Face::front: {
                return std::array{
                    xf, world_yf, world_zf, u_full, v_full, 0.9f,
                    world_xf, yf, world_zf, u, v, 0.9f,
                    world_xf, world_yf, world_zf, u, v_full, 0.9f,
                    world_xf, yf, world_zf, u, v, 0.9f,
                    xf, world_yf, world_zf, u_full, v_full, 0.9f,
                    xf, yf, world_zf, u_full, v, 0.9f,
                };
            }
            break;
            case Face::left: {
                return std::array{
                    xf, yf, zf, u, v, 0.7f,
                    xf, yf, world_zf, u_full, v, 0.7f,
                    xf, world_yf, world_zf, u_full, v_full, 0.7f,
                    xf, world_yf, world_zf, u_full, v_full, 0.7f,
                    xf, world_yf, zf, u, v_full, 0.7f,
                    xf, yf, zf, u, v, 0.7f,
                };
            }
            break;
            case Face::right: {
                return std::array{
                    world_xf, yf, zf, u, v, 1.25f,
                    world_xf, world_yf, world_zf, u_full, v_full, 1.25f,
                    world_xf, yf, world_zf, u_full, v, 1.25f,
                    world_xf, world_yf, world_zf, u_full, v_full, 1.25f,
                    world_xf, yf, zf, u, v, 1.25f,
                    world_xf, world_yf, zf, u, v_full, 1.25f,
                };
            }
            break;
            case Face::top: {
                return std::array{
                    xf, world_yf, zf, u, v, 1.45f,
                    xf, world_yf, world_zf, u_full, v, 1.45f,
                    world_xf, world_yf, world_zf, u_full, v_full, 1.45f,
                    world_xf, world_yf, world_zf, u_full, v_full, 1.45f,
                    world_xf, world_yf, zf, u, v_full, 1.45f,
                    xf, world_yf, zf, u, v, 1.45f,
                };
            }
            break;
            case Face::bottom: {
                return std::array{
                    xf, yf, zf, u, v, 0.25f,
                    world_xf, yf, world_zf, u_full, v_full, 0.25f,
                    xf, yf, world_zf, u_full, v, 0.25f,
                    world_xf, yf, world_zf, u_full, v_full, 0.25f,
                    xf, yf, zf, u, v, 0.25f,
                    world_xf, yf, zf, u, v_full, 0.25f,
                };
            }
            break;
        }


        std::abort();
    }
} // sos::lvl
