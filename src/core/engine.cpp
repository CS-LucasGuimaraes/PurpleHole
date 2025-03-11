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

#include "core/engine.hpp"

namespace PurpleHole {

SDL_Window *screen = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *display = nullptr;
SDL_Texture *interface = nullptr;

const iCord kDisplaySize = {640, 360};
const iCord kScreenSize = {1280, 720};
const int kRenderScale = kScreenSize.x / kDisplaySize.x;
const int kIdSize = 8;

int curr_id = 1;

namespace font {
    TTF_Font *title = nullptr;
    TTF_Font *subtitle = nullptr;
    TTF_Font *text = nullptr;

    bool initialized = false;
    
    void init() {
        if (initialized) return;
        
        initialized = true;

        text = TTF_OpenFont("../../assets/fonts/Roboto-Regular.ttf", 16);
        if (text) {
            std::clog << "Font loaded successfully!\n";
        } else {
            std::cerr << "[WARNING!] FONT LOADING FAILED!\n"
                      << "     [SDL]: " << SDL_GetError() << '\n';
        }
    }
}  // namespace font

bool Init(const char *title, SDL_Rect window_features, bool fullscreen) {
    Uint32 screen_flags = 0;


    if (fullscreen) {
        screen_flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_InitSubSystem(SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_GAMEPAD)) {
        std::clog << "SDL3 initialized!...\n";

        screen = SDL_CreateWindow("Cpp Game Dev", 
                                  window_features.w,
                                  window_features.h, screen_flags);
        if (screen) {
            std::clog << "Window created sucessfully!\n";
        } else {
            std::cerr << "[WARNING!] WINDOW INITIALIZATION FAILED!\n"
                      << "     [SDL]: " << SDL_GetError() << '\n';
        }

        renderer = SDL_CreateRenderer(screen, "");
        if (renderer) {
            std::clog << "Redereer created sucessfully!\n";

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        } else {
            std::cerr << "[WARNING!] RENDERER INITIALIZATION FAILED!\n"
                      << "     [SDL]: " << SDL_GetError() << '\n';
        }

        display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, kDisplaySize.x,
                                    kDisplaySize.y);
        if (display) {
            std::clog << "Display (render target) created sucessfully!\n";
            // SDL_SetTextureScaleMode(display, SDL_SCALEMODE_NEAREST);

        } else {
            std::cerr
                << "[WARNING!] DISPLAY (RENDER TARGET) INITIALIZATION FAILED!\n"
                << "     [SDL]: " << SDL_GetError() << '\n';
        }

        interface = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, kScreenSize.x, kScreenSize.y);
        
        if (interface) {
        std::clog << "Interface (render target) created sucessfully!\n";
        // SDL_SetTextureScaleMode(display, SDL_SCALEMODE_NEAREST);

        } else {
        std::cerr
        << "[WARNING!] INTERFACE (RENDER TARGET) INITIALIZATION FAILED!\n"
        << "     [SDL]: " << SDL_GetError() << '\n';
        }
    } else {
        std::cerr << "[WARNING!] SDL3 INITIALIZATION FAILED!\n";
        return false;
    }

    if (TTF_Init()) {
        std::clog << "SDL_ttf initialized!...\n";
    } else {
        std::cerr << "[WARNING!] SDL_TTF INITIALIZATION FAILED!\n"
                  << "     [SDL]: " << SDL_GetError() << '\n';
    }

    return true;
}

void Shutdown() {
    SDL_DestroyWindow(screen);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::clog << "Engine shutdown sucessfully!\n";
}
}  // namespace PurpleHole