#pragma once
#include <unordered_map>
#include <vector>

#include "tile.hpp"

namespace sos::lvl {
    class TileRegistry {
    public:
        TileRegistry(const TileRegistry&) = delete;

        TileRegistry& operator=(const TileRegistry&) = delete;

        TileRegistry(TileRegistry&&) = delete;

        TileRegistry& operator=(TileRegistry&&) = delete;

        [[nodiscard]] static TileRegistry& get() {
            static TileRegistry tile_registry;
            return tile_registry;
        }

        const Tile& operator[](const usize index) const noexcept {
            return tiles_[index];
        }

        const usize& operator[](const std::string& name) const noexcept {
            return names_.at(name);
        }

    private:
        std::unordered_map<std::string, usize> names_{};
        std::vector<Tile> tiles_{};

        TileRegistry();

        void addTile(const std::string& name, Tile tile);
    };
} // sos::lvl
