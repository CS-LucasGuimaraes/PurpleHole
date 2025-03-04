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

#include "core/assets.hpp"

namespace PurpleHole {
namespace assets {

std::map<std::string, Animation*> animations;
std::map<std::string, Animation*> animated_tiles;
std::map<std::string, std::vector<SDL_Texture *>> tiles;

bool init() {
    animations = {
        {"player/idle", new Animation(load_images("entities/player/idle"), 16)},
    };

    animated_tiles = {
        {"coin", new Animation (load_images("tiles/coin"))},

    };

    tiles = {
        {"decor", load_images("tiles/decor")},
        {"grass", load_images("tiles/grass")},
        {"large_decor", load_images("tiles/large_decor")},
        {"snow", load_images("tiles/snow")},
        {"cloud_platform", load_images("tiles/cloud_plataform")},
        {"scaffolding", load_images("tiles/scaffolding")},
        {"boxes", load_images("tiles/boxes")},
        {"heart", load_images("tiles/hearts")},
        {"diamond", load_images("tiles/diamond")},
        {"crates", load_images("tiles/crates")},
        {"key_door", load_images("tiles/key_door")},
        {"door", load_images("tiles/door")},
        {"fence", load_images("tiles/fence")},
        {"flag", load_images("tiles/flag")},
        {"flag_pole", load_images("tiles/flag_pole")},
        {"blue_flag", load_images("tiles/blue_flag")},
        {"blue_flag_pole", load_images("tiles/blue_flag_pole")},
        {"ice1", load_images("tiles/ice1")},
        {"ice2", load_images("tiles/ice2")},
        {"tree", load_images("tiles/tree")},
        {"leaves", load_images("tiles/leaves")},
        {"lever", load_images("tiles/lever")},
        {"mushroom", load_images("tiles/mushroom")},
        {"path", load_images("tiles/path")},
        {"pipe", load_images("tiles/pipe")},
        {"ropes", load_images("tiles/ropes")},
        {"signs", load_images("tiles/signs")},
        {"stairs", load_images("tiles/stairs")},
        {"water", load_images("tiles/water")},
        {"key", load_images("tiles/key")},
        {"water_surface", load_images("tiles/water_surface")},
        {"spike", load_images("tiles/spike")},
        {"snowman", load_images("tiles/snowman")},
        {"beams", load_images("tiles/beams")},
        {"box_industrial", load_images("tiles/box_industrial")},
        {"chest", load_images("tiles/chests")},
        {"gears", load_images("tiles/gears")},
        
        {"stone", load_images("tiles/boxes")},
    };

    return true;
}

}  // namespace assets
}  // namespace PurpleHole