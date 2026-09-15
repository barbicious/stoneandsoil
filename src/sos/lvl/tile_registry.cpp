#include "tile_registry.hpp"

namespace sos::lvl {
    TileRegistry::TileRegistry() {
        addTile("air", Tile{Tile::Type::air});
        addTile("grass", Tile{Tile::Type::grass});
        addTile("stone", Tile{Tile::Type::stone});
    }

    void TileRegistry::addTile(const std::string& name, Tile tile) {
        names_[name] = tiles_.size();
        tiles_.push_back(tile);
    }
} // sos::lvl
