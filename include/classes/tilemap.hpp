// Copyright (C) 2024 Lucas Guimarães
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef PURPLEHOLE_CLASSES_TILEMAP_HPP_
#define PURPLEHOLE_CLASSES_TILEMAP_HPP_

#include "classes/animation.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/utils.hpp"

namespace PurpleHole {
struct tile {
    std::string type;
    short variant;
    iCord pos;
    std::string category;
    std::string render;
};

namespace tilemap {
const iCord NEIGHBOR_OFFSETS[9] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {0, 0},
                                  {1, 0},  {-1, -1}, {0, -1}, {1, -1}};

}  // namespace tilemap

class Tilemap {
   public:
    int tile_size = 32;

    Tilemap(std::string ID);
    ~Tilemap() {
        this->save();
    }

    /**
     *  Render the tilemap onto the renderer surface.
     *
     * \returns (void): This function does not return a value.
     */
    void render(fCord offset, std::string mode = "game");

    std::vector<SDL_FRect *> tilerects_around(iCord pos, std::string type);
    std::vector<SDL_FRect *> tilerects_around(fCord pos, std::string type);

    void load(int lvl = 0);

    void save(int lvl = 0);

    std::map<std::string, tile> tilemap;

    iCord spawn;
   private:
    std::string ID;
    SDL_FRect dstR;
    std::set<std::string> updated;
};
}  // namespace PurpleHole

#endif  // PURPLEHOLE_CLASSES_TILEMAP_HPP_