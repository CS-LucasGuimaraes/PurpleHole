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

#ifndef PURPLEHOLE_CLASSES_PAUSE_MENU_HPP_
#define PURPLEHOLE_CLASSES_PAUSE_MENU_HPP_

#include "core/engine.hpp"

namespace PurpleHole {

    class PauseMenu {
    public:
        explicit PauseMenu(SDL_Renderer* renderer);
        ~PauseMenu();

        /**
         * Renders the pause menu.
         */
        void render();

        /**
         * Handles input and returns the selected option.
         * @returns Index of the selected option or -1 if none.
         */
        int handleInput();

        /**
         * Displays the menu loop until a valid option is selected.
         * @returns Index of selected option.
         */
        int show();

    private:
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::vector<std::string> options;
        int selectedIndex;
    };

}  // namespace PurpleHole

#endif  // PURPLEHOLE_CLASSES_PAUSE_MENU_HPP_
