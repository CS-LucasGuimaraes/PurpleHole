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

#ifndef PURPLEHOLE_CLASSES_INTERFACE_HPP_
#define PURPLEHOLE_CLASSES_INTERFACE_HPP_

#include "classes/animation.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/utils.hpp"

namespace PurpleHole {

class UserInterface {
   public:
    UserInterface();
    
    void render_text(std::string text, SDL_FRect *dst, SDL_Color color, TTF_Font *font);
    
    void render();
};

}  // namespace PurpleHole

#endif  // PURPLEHOLE_CLASSES_INTERFACE_HPP_