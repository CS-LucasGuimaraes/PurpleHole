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

#include "main/game.hpp"

namespace PurpleHole {

Game::Game() {
    this->past = new Tilemap("past");
    this->present = new Tilemap("present");
    this->future = new Tilemap("future");

    this->tilemap = &present;
    
    this->player = new Player({0, 0, 21, 21}, &tilemap);
}

Game::~Game() {
    delete this->player;
    std::clog << "Game class successfully destroyed!\n";
}

bool Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                this->isRunning = false;
                return false;
            
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                std::cout << "GAMEPAD ADDED" << std::endl;    
                SDL_OpenGamepad(event.gdevice.which);
            break;
              
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                if (event.gbutton.button == keybinds::keymap["jump"].controller) {
                    this->player->jump();
                }
            break;

            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == keybinds::keymap["left"].main || event.key.key == keybinds::keymap["left"].secondary) {
                    this->movement.first = 1;
                } 
                else if (event.key.key == keybinds::keymap["right"].main || event.key.key == keybinds::keymap["right"].secondary) {
                    this->movement.second = 1;
                }
                else if (event.key.key == keybinds::keymap["jump"].main || event.key.key == keybinds::keymap["jump"].secondary) {
                    this->player->jump();
                }
                else if (event.key.key == keybinds::keymap["previous"].main || event.key.key == keybinds::keymap["previous"].secondary) {
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
                else if (event.key.key == keybinds::keymap["next"].main || event.key.key == keybinds::keymap["next"].secondary) {
                     if (*this->tilemap == this->past) {
                        this->tilemap = &this->present;
                    } else
                    if (*this->tilemap == this->present) {
                        this->tilemap = &this->future;

                    } else
                    if (*this->tilemap == this->future) {
                        continue;
                    }
                }
            break;

            case SDL_EVENT_KEY_UP:
                if (event.key.key == keybinds::keymap["left"].main || event.key.key == keybinds::keymap["left"].secondary) {
                    this->movement.first = 0;
                }
                else if (event.key.key == keybinds::keymap["right"].main || event.key.key == keybinds::keymap["right"].secondary) {
                    this->movement.second = 0;
                }
            break;
        }
    }
    return true;
}

void Game::update() {
    this->player->update(this->movement.second - this->movement.first);
    this->camera_control();
}

void Game::camera_control() {
    this->offset.x += int((this->player->Rect()->x+this->player->Rect()->w - PurpleHole::kDisplaySize.x / 2 - this->offset.x) / 32);
    this->offset.y += int((this->player->Rect()->y + this->player->Rect()->h - PurpleHole::kDisplaySize.y / 2 - this->offset.y) / 32);
}

void Game::render() {
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderClear(renderer);

    this->player->render(this->offset);
    (*this->tilemap)->render(this->offset);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, display, NULL, NULL);

    SDL_RenderPresent(renderer);
}
}  // namespace PurpleHole