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

#include "core/keybinds.hpp"

namespace PurpleHole {
namespace keybinds {

std::map<std::string, __keymap> keymap;

bool init() {
    keymap = {
        {"jump", {SDLK_SPACE, SDLK_W, SDL_GAMEPAD_BUTTON_SOUTH} },
        {"left", {SDLK_A, SDLK_LEFT, SDL_GAMEPAD_BUTTON_DPAD_LEFT} },
        {"right", {SDLK_D, SDLK_RIGHT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT} },
        {"previous", {SDLK_Q, SDLK_UNKNOWN, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER} },
        {"next", {SDLK_E, SDLK_UNKNOWN, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER} },
    };

    return true;
}

}  // namespace keybinds
}  // namespace PurpleHole