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

#ifndef PURPLEHOLE_CORE_ASSETS_HPP_
#define PURPLEHOLE_CORE_ASSETS_HPP_

#include "classes/animation.hpp"
#include "engine.hpp"
#include "imageHandle.hpp"

namespace PurpleHole {
namespace assets {

extern std::map<std::string, Animation*> animations;
extern std::map<std::string, std::vector<SDL_Texture *>> tiles;

/**
 * Initializes the game assets.
 *
 * This function loads and stores animation data for different player states.
 *
 * @returns (bool): This function returns true on success, or false on failure
 * (e.g., loading errors).
 */
bool init();

}  // namespace assets
}  // namespace PurpleHole

#endif  // PURPLEHOLE_CORE_ASSETS_HPP_