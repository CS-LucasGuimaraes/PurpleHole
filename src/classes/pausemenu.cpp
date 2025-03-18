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

#include "classes/pausemenu.hpp"

namespace PurpleHole {


    PauseMenu::PauseMenu(SDL_Renderer* renderer) : renderer(renderer), selectedIndex(0) {
        TTF_Init();
        font = TTF_OpenFont("../../assets/fonts/Kenney Blocks.ttf", 24);
        options = {"Sound: ON", "Controls", "Main Menu", "Quit", "Back"};
    }
    
    PauseMenu::~PauseMenu() {
        TTF_CloseFont(font);
        TTF_Quit();
    }
    
    void PauseMenu::render() {
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
    
int PauseMenu::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return 3;  // Quit the game
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_UP:
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                    break;
                case SDLK_DOWN:
                    selectedIndex = (selectedIndex + 1) % options.size();
                    break;
                case SDLK_RETURN:
                    //Mix_PlayChannel(-1, PurpleHole::assets::sounds["UI_press"], 0);
                    //Carregar SDL Mixer 
                    if (selectedIndex == 0) {  // Toggle sound
                        options[0] = (options[0] == "Sound: ON") ? "Sound: OFF" : "Sound: ON";
                    } else if (selectedIndex == 2) {  // Main Menu
                        return 2;
                    } else if (selectedIndex == 3) {  // Quit
                        return 3;
                    } else if (selectedIndex == 4) {  // Back
                        return 4;
                    }
                    break;
            }
        }
    }
    return -1;
}
    
    int PauseMenu::show() {
        bool running = true;
        while (running) {
            handleInput();
            render();
            SDL_Delay(100);
        }
        return selectedIndex;
    }


}  // namespace PurpleHole