#include "tile_registry.hpp"

#define REGISTER_TILE(name) addTile(#name, Tile{Tile::Type::name});

namespace sos::lvl {
    TileRegistry::TileRegistry() {
        REGISTER_TILE(air);
        REGISTER_TILE(grass);
        REGISTER_TILE(stone);
        REGISTER_TILE(water);
        REGISTER_TILE(bark);
        REGISTER_TILE(leaf);
    }

    void TileRegistry::addTile(const std::string& name, Tile tile) {
        names_[name] = tiles_.size();
        tiles_.push_back(tile);
    }
} // sos::lvl
