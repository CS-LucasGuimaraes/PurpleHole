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

#include "main/menu.hpp"
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

namespace PurpleHole {

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), selectedIndex(0) {
    TTF_Init();
    //This is provisory, and only works on my computer. 
    font = TTF_OpenFont("/home/arss5/Documents/PurpleHole/assets/fonts/arial.ttf", 24);
    options = {"Start Game", "Editor", "Exit"};
}

Menu::~Menu() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void Menu::render() {
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    SDL_Color color;
    SDL_FRect textFRect;

    for (size_t i = 0; i < options.size(); ++i) {
        color = (i == selectedIndex) ? SDL_Color{255, 255, 0, 255} : SDL_Color{255, 255, 255, 255};

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, options[i].c_str(), 0, color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                
        textFRect = {200, static_cast<float>(150 + (int)i * 50), static_cast<float>(textSurface->w), static_cast<float>(textSurface->h)};
        SDL_RenderTexture(renderer, textTexture, nullptr, &textFRect);

        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    SDL_RenderPresent(renderer);
}

void Menu::handleInput(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
            selectedIndex = 2; // Exit
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_UP:
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                    break;
                case SDLK_DOWN:
                    selectedIndex = (selectedIndex + 1) % options.size();
                    break;
                case SDLK_RETURN:
                    running = false;
                    break;
            }
        }
    }
}

int Menu::show() {
    bool running = true;
    while (running) {
        handleInput(running);
        render();
        SDL_Delay(100);
    }
    return selectedIndex + 1;
}

}  // namespace PurpleHole