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

#ifndef PURPLEHOLE_CORE_KEYBINDS_HPP_
#define PURPLEHOLE_CORE_KEYBINDS_HPP_

#include "classes/animation.hpp"
#include "engine.hpp"
#include "imageHandle.hpp"

namespace PurpleHole {
namespace keybinds {

struct __keymap {
    unsigned int main;
    unsigned int secondary;
    SDL_GamepadButton controller;
};

extern std::map<std::string, __keymap> keymap;

bool init();

}  // namespace keybinds
}  // namespace PurpleHole

#endif  // PURPLEHOLE_CORE_KEYBINDS_HPP_