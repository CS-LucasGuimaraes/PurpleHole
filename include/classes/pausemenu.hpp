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


#ifndef PURPLEHOLE_CLASSES_PAUSE_MENU_HPP_
#define PURPLEHOLE_CLASSES_PAUSE_MENU_HPP_

#include "core/engine.hpp"
namespace PurpleHole {

class PauseMenu {
    public:
     PauseMenu(SDL_Renderer* renderer);
     ~PauseMenu();
 
     /**
      * Renders the options menu.
      */
     void render();
 
     /**
      * Handles user input for navigating the options menu.
      * @param running A reference to the running state.
      */
     int handleInput();
 
     /**
      * Displays the options menu and waits for user selection.
      * @returns The selected option index.
      */
     int show();
 
    private:
     SDL_Renderer* renderer;
     TTF_Font* font;
     std::vector<std::string> options;
     int selectedIndex;

 };
 
} // namespace PurpleHole

#endif  // PURPLEHOLE_CLASSES_PAUSE_MENU_HPP_
