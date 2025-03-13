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

#include "classes/interface.hpp"

namespace PurpleHole {

// public:

UserInterface::UserInterface() {
    font::init();
}

void UserInterface::render_text(std::string text, SDL_FRect* dst, SDL_Color color, TTF_Font *font) {
    SDL_Texture *texture;
    
    SDL_Surface *txt = TTF_RenderText_Blended(font::text, text.c_str(), 0, color);
    if (txt) {
        texture = SDL_CreateTextureFromSurface(renderer, txt);
        SDL_DestroySurface(txt);
    }
    if (!texture) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    }

    // SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}

void UserInterface::render() {
    SDL_FRect dst = {0, 0, 100, 100};
    SDL_Color color = {255, 255, 255, 255};

    render_text("Hello, World!", &dst, color, font::text);
}




}  // namespace PurpleHole