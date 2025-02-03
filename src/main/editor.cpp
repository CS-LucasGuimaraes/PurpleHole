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

#include "main/editor.hpp"

namespace PurpleHole {

Editor::Editor() {
    this->past = new Tilemap("past");
    this->present = new Tilemap("present");
    this->future = new Tilemap("future");
    
    this->tilemap = &present;
}

Editor::~Editor() {
    delete this->past;
    delete this->present;
    delete this->future;
    std::clog << "Editor class successfully destroyed!\n";
}

bool Editor::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                this->isRunning = false;
                return false;

            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_A:
                        this->movementX.first = 1;
                        break;

                    case SDLK_D:
                        this->movementX.second = 1;
                        break;

                    case SDLK_W:
                        this->movementY.first = 1;
                        break;

                    case SDLK_S:
                        this->movementY.second = 1;
                        break;
                    case SDLK_E:
                         if (*this->tilemap == this->past) {
                            this->tilemap = &this->present;
                        } else
                        if (*this->tilemap == this->present) {
                            this->tilemap = &this->future;

                        } else
                        if (*this->tilemap == this->future) {
                            continue;
                        }
                        break;
                    case SDLK_Q:
                         if (*this->tilemap == this->past) {
                            continue;
                        } else
                        if (*this->tilemap == this->present) {
                            this->tilemap = &this->past;

                        } else
                        if (*this->tilemap == this->future) {
                            this->tilemap = &this->present;
                        }
                        break;
                }
                break;

            case SDL_EVENT_KEY_UP:
                switch (event.key.key) {
                    case SDLK_A:
                        this->movementX.first = 0;
                        break;

                    case SDLK_D:
                        this->movementX.second = 0;
                        break;

                    case SDLK_W:
                        this->movementY.first = 0;
                        break;

                    case SDLK_S:
                        this->movementY.second = 0;
                        break;
                }
                break;

            case SDL_EVENT_MOUSE_MOTION:
                SDL_GetMouseState(&this->mpos.x, &this->mpos.y);

                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        this->clicking = true;
                        break;

                    case SDL_BUTTON_RIGHT:
                        this->right_clicking = true;
                        break;

                    case SDL_BUTTON_MIDDLE:

                        break;
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        this->clicking = false;
                        break;

                    case SDL_BUTTON_RIGHT:
                        this->right_clicking = false;
                        break;

                    case SDL_BUTTON_MIDDLE:

                        break;
                }
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                if (event.wheel.y > 0) { // UP
                    tile_group = (tile_group + 1) % tile_list.size();
                }
                else if (event.wheel.y < 0) { // DOWN
                    tile_group = (tile_group - 1 + tile_list.size()) % tile_list.size();
                }
        }
    }
    return true;
}

void Editor::update() {
    this->cameraControl();

    if (this->ongrid) {
        iCord tilepos = this->getTilePos();
        std::string tile_loc =
            std::to_string(tilepos.x) + ";" + std::to_string(tilepos.y);

        if (this->clicking) {
            (*this->tilemap)->tilemap[tile_loc] = {
                this->tile_list[this->tile_group].first, this->tile_variant,
                tilepos, this->tile_list[this->tile_group].second};
                std::cout << int(this->tile_group) << std::endl;
        }

        if (this->right_clicking) {
            if ((*this->tilemap)->tilemap.count(tile_loc) != 0) {
                (*this->tilemap)->tilemap.erase(tile_loc);
            }
        }
    }

    else {
    }
}

void Editor::render() {
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderClear(renderer);

    (*this->tilemap)->render(this->scroll);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, display, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void Editor::cameraControl() {
    this->scroll.x +=
        (this->movementX.second - this->movementX.first) * this->scrollCord;
    this->scroll.y +=
        (this->movementY.second - this->movementY.first) * this->scrollCord;
}

iCord Editor::getTilePos() {
    return {(int)std::floor(((this->mpos.x / kRenderScale) +
                             this->scroll.x) /
                            (*this->tilemap)->tile_size),
            (int)std::floor(((this->mpos.y / kRenderScale) +
                             this->scroll.y) /
                            (*this->tilemap)->tile_size)};
}
}  // namespace PurpleHole