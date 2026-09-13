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
        }
    }

    std::array<f32, 30> Tile::vertices(Face face, i32 x, i32 y, i32 z) const {
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
                    xf, world_yf, zf, u_full, v_full,
                    world_xf, world_yf, zf, u, v_full,
                    world_xf, yf, zf, u, v,
                    world_xf, yf, zf, u, v,
                    xf, yf, zf, u_full, v,
                    xf, world_yf, zf, u_full, v_full,
                };
            }
            break;
            case Face::front: {
                return std::array{
                    xf, world_yf, world_zf, u_full, v_full,
                    world_xf, world_yf, world_zf, u, v_full,
                    world_xf, yf, world_zf, u, v,
                    world_xf, yf, world_zf, u, v,
                    xf, yf, world_zf, u_full, v,
                    xf, world_yf, world_zf, u_full, v_full,
                };
            }
            break;
            case Face::left: {
                return std::array{
                    xf, yf, zf, u, v,
                    xf, yf, world_zf, u_full, v,
                    xf, world_yf, world_zf, u_full, v_full,
                    xf, world_yf, world_zf, u_full, v_full,
                    xf, world_yf, zf, u, v_full,
                    xf, yf, zf, u, v,
                };
            }
            break;
            case Face::right: {
                return std::array{
                    world_xf, yf, zf, u, v,
                    world_xf, yf, world_zf, u_full, v,
                    world_xf, world_yf, world_zf, u_full, v_full,
                    world_xf, world_yf, world_zf, u_full, v_full,
                    world_xf, world_yf, zf, u, v_full,
                    world_xf, yf, zf, u, v,
                };
            }
            break;
            case Face::top: {
                return std::array{
                    xf, world_yf, zf, u, v,
                    xf, world_yf, world_zf, u_full, v,
                    world_xf, world_yf, world_zf, u_full, v_full,
                    world_xf, world_yf, world_zf, u_full, v_full,
                    world_xf, world_yf, zf, u, v_full,
                    xf, world_yf, zf, u, v,
                };
            }
            break;
            case Face::bottom: {
                return std::array{
                    xf, yf, zf, u, v,
                    xf, yf, world_zf, u_full, v,
                    world_xf, yf, world_zf, u_full, v_full,
                    world_xf, yf, world_zf, u_full, v_full,
                    world_xf, yf, zf, u, v_full,
                    xf, yf, zf, u, v,
                };
            }
            break;
        }

        std::abort();
    }
} // sos::lvl
