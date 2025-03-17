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

#ifndef PURPLEHOLE_CORE_MENU_HPP_
#define PURPLEHOLE_CORE_MENU_HPP_

#include "core/engine.hpp"

namespace PurpleHole {

class Menu {
    public:
        Menu(SDL_Renderer* renderer);
        ~Menu();
    
        int show(); // Returns user choice: 1 = Game, 2 = Editor, 0 = Exit
    
    private:
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::vector<std::string> options;
        int selectedIndex;
    
        void render();
        void handleInput(bool& running);
    };

}// namespace PurpleHole

#endif  // PURPLEHOLE_CLASSES_INTERFACE_HPP_