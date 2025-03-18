//    Copyright 2025 Lucas Guimarães Fernandes
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#include "classes/tilemap.hpp"

namespace PurpleHole {

// public:

Tilemap::Tilemap(std::string ID, int lvl) : ID(ID), curr_lvl(lvl) {
    this->spawn = {0, 0};
    
    this->load(curr_lvl);

    this->dstR.h = this->tile_size;
    this->dstR.w = this->tile_size;

    this->updated = std::set<std::string>();
}

Tilemap::~Tilemap() {
    this->save(curr_lvl);
    std::clog << "Tilemap class (" << this->ID << ") successfully destroyed!\n";
}

void Tilemap::render(fCord offset, std::string mode) {
    std::map<std::string, tile>::iterator tile;

    // this->updated.clear();

    for (int x = DivFloor(offset.x, this->tile_size);
         x < DivFloor(offset.x + kDisplaySize.x, this->tile_size) + 1; x++) {
        for (int y = DivFloor(offset.y, this->tile_size);
             y < DivFloor(offset.y + kDisplaySize.y, this->tile_size) + 1;
             y++) {
            std::string loc = std::to_string(x) + ';' + std::to_string(y);
            if ((tile = this->tilemap.find(loc)) != this->tilemap.end()) {
                if (tile->second.render == "EditorOnly" && mode != "editor")
                    continue;
                else if (tile->second.render == "animated") {
                    this->dstR.x = x * this->tile_size - offset.x;
                    this->dstR.y = y * this->tile_size - offset.y;
                    SDL_RenderTexture(
                        renderer,
                        assets::animated_tiles[tile->second.type]->img(),
                        NULL, &this->dstR);

                    if (this->updated.count(tile->second.type) == 0) {
                        updated.insert(tile->second.type);
                        assets::animated_tiles[tile->second.type]->update();
                    }
                }
                else {
                    this->dstR.x = x * this->tile_size - offset.x;
                    this->dstR.y = y * this->tile_size - offset.y;
                    SDL_RenderTexture(
                        renderer,
                        assets::tiles[tile->second.type][tile->second.variant],
                        NULL, &this->dstR);
                }
            }
        }
    }
}

std::vector<SDL_FRect *> Tilemap::tilerects_around(iCord pos, std::string type) {
    std::vector<tile *> tiles;
    std::map<std::string, tile>::iterator tile;
    iCord tile_loc = {pos.x / this->tile_size, pos.y / this->tile_size};

    for (auto offset : tilemap::NEIGHBOR_OFFSETS) {
        std::string loc = std::to_string(tile_loc.x + offset.x) + ';' +
                          std::to_string(tile_loc.y + offset.y);
        if ((tile = this->tilemap.find(loc)) != this->tilemap.end()) {
            tiles.push_back(&tile->second);
        }
    }

    std::vector<SDL_FRect *> rects;

    for (auto rect : tiles) {
        if (rect->category == type) {
            rects.push_back(new SDL_FRect( {
                float(rect->pos.x * this->tile_size),
                float(rect->pos.y * this->tile_size),
                float(this->tile_size),
                float(this->tile_size)
            } ) );
        }
    }

    return rects;
}

std::vector<SDL_FRect *> Tilemap::tilerects_around(fCord pos, std::string type) {
    iCord _pos = {int(pos.x), int(pos.y)};
    std::vector<tile *> tiles;
    std::map<std::string, tile>::iterator tile;
    iCord tile_loc = {_pos.x / this->tile_size, _pos.y / this->tile_size};

    for (auto offset : tilemap::NEIGHBOR_OFFSETS) {
        std::string loc = std::to_string(tile_loc.x + offset.x) + ';' + std::to_string(tile_loc.y + offset.y);
        if ((tile = this->tilemap.find(loc)) != this->tilemap.end()) {
            tiles.push_back(&tile->second);
        }
    }

    std::vector<SDL_FRect *> rects;

    for (auto rect : tiles) {
        if (rect->category == type) {
            rects.push_back(new SDL_FRect({float(rect->pos.x * this->tile_size),
                                           float(rect->pos.y * this->tile_size),
                                           float(this->tile_size),
                                           float(this->tile_size)}));
        }
    }

    return rects;
}

void Tilemap::load(int lvl) {
    try {
        
        std::string path = (ASSETS_PATH + "levels/level" + std::to_string(lvl) + "-" + this->ID + ".lvl");

        if (!std::filesystem::exists(path)) {
            std::cerr << "[WARNING!] LEVEL " << lvl << "-" << this->ID << " NOT FOUND!\n";
            return;
        }

        std::ifstream f(path);
        nlohmann::json data = nlohmann::json::parse(f);

        for (auto [k, v] : data.items()) {
            if (v["category"] == "spawn") {
                this->spawn = {
                    (int(v["pos"][0]) * tile_size) + (tile_size/2),
                    (int(v["pos"][1]) * tile_size) + (tile_size/2)
                };
            }
            this->tilemap[k] = {
                v["type"],
                v["variant"],
                {v["pos"][0], v["pos"][1]},
                v["category"],
                v["render"]
            };
        }
    }
    catch(const std::exception& e) {
        std::cerr
                << "[WARNING!] ERROR DURING LEVEL "<< lvl << "-" << this->ID << " LOADING \n"
                << "     " << e.what() << '\n';
    }
    
}

void Tilemap::save(int lvl) {
    std::ofstream out(ASSETS_PATH + "levels/level" + std::to_string(lvl) + "-" + this->ID + ".lvl");

    nlohmann::json j;

    for (auto [k, v] : this->tilemap) {
        j[k] = {
            { "type", v.type },
            { "variant", v.variant },
            { "pos", {v.pos.x, v.pos.y} },
            { "category", v.category },
            { "render", v.render }
            };
    }
    out << j;

    std::clog << "Level " << lvl << "-" << this->ID << " saved!\n";
}
}  // namespace PurpleHole