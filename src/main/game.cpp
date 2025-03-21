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

Game::Game() : player(new Player({0, 0, 21, 21}, &tilemap, this)), pauseMenu(new PauseMenu(renderer)), ui(new UserInterface), curr_lvl(0) {
    this->restartLevel();

    //Serve para colocar imagem de background
    // SDL_Surface* backgroundSurface = IMG_Load("../../assets/images/background.png");
    // if (!backgroundSurface) {
    //     std::cerr << "Failed to load background image: " << SDL_GetError() << std::endl;
    // } else {
    //     backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    //     SDL_DestroySurface(backgroundSurface);
    // }

    
}

Game::~Game() {
    delete this->player;
    std::clog << "Game class successfully destroyed!\n";
    delete pauseMenu;

    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
}

void Game::previous_time() {
    if (*this->tilemap == this->present) {
        this->tilemap = &this->past;

    } else
    if (*this->tilemap == this->future) {
        this->tilemap = &this->present;
    }
}

void Game::next_time() {
    if (*this->tilemap == this->past) {
        this->tilemap = &this->present;

    } else
    if (*this->tilemap == this->present) {
        this->tilemap = &this->future;
    }
}

void Game::nextLevel() {
    std::cerr << "NOT IMPLEMENTED YET!\n";
}

bool Game::handleEvents() {
    SDL_Event event;

    for (auto [_gamepad, _player] : Gamepad2Player) {
        long long x = SDL_GetGamepadAxis(_gamepad, SDL_GAMEPAD_AXIS_LEFTX);
        long long y = SDL_GetGamepadAxis(_gamepad, SDL_GAMEPAD_AXIS_LEFTY);

        if (x*x + y*y > 8000*8000) {
            if (x < -8000)
                this->movement.first = 1;
            else if (x > 8000)
                this->movement.second = 1;
            else
                this->movement.first = this->movement.second = 0;
        }
        else
            this->movement.first = this->movement.second = 0;
        }
        while (SDL_PollEvent(&event)) {

            if (isPaused) {
                int result = -1;
                while (result == -1) {
                    result = pauseMenu->handleInput();
                    pauseMenu->render();
                    SDL_Delay(100);
                }
                isPaused = false;
    
                if (result == 2) {  // Main Menu selected
                    this->isRunning = false;
                } else if (result == 3) {  // Quit selected
                    this->isRunning = false;
                    exit(0);
                }
            }
        switch (event.type) {
            case SDL_EVENT_QUIT:
                this->isRunning = false;
                return false;
            
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                std::cout << "GAMEPAD ADDED" << std::endl;
                Gamepad2Player[SDL_OpenGamepad(event.gdevice.which)] = this->player;
            break;
              
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                if (event.gbutton.button == keybinds::keymap["jump"].controller) {
                    this->player->jump();
                }
                if (event.gbutton.button == keybinds::keymap["previous"].controller) {
                    previous_time();
                    break;
                }
                if (event.gbutton.button == keybinds::keymap["next"].controller) {
                    next_time();
                    break;
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
                    previous_time();
                    break;
                }
                else if (event.key.key == keybinds::keymap["next"].main || event.key.key == keybinds::keymap["next"].secondary) {
                    next_time();
                    break;
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

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                fCord mpos;
                SDL_GetMouseState(&mpos.x, &mpos.y);

                if (event.button.button == SDL_BUTTON_MIDDLE) {  // GOD MODE
                    this->player->pos = {(mpos.x / kRenderScale) + this->offset.x, (mpos.y / kRenderScale) + this->offset.y};
                }

                else if (event.button.button == SDL_BUTTON_LEFT) {
                    if (mpos.x >= pauseButton.x && mpos.x <= pauseButton.x + pauseButton.w &&
                        mpos.y >= pauseButton.y && mpos.y <= pauseButton.y + pauseButton.h) togglePause();
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
{
    SDL_SetRenderTarget(renderer, display);
    SDL_SetRenderDrawColor(renderer, 171, 233, 251, 255);
    SDL_RenderClear(renderer);
    //Tem um jeito melhor de fazer isso?
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //Para colocar imagem de Background
    // if (backgroundTexture) {
    //     SDL_RenderTexture(renderer, backgroundTexture, NULL, NULL);
    // }

    if (!isPaused) { 
        (*this->tilemap)->render(this->offset);
        this->player->render(this->offset);
    }
}
    
{   
    SDL_SetRenderTarget(renderer, interface);
    SDL_RenderClear(renderer);

    ui->render();

    SDL_RenderTexture(renderer, PurpleHole::assets::ui_elements["pause_button"], NULL, &pauseButton);
    
}

{
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    
    SDL_RenderTexture(renderer, display, NULL, NULL);
    SDL_RenderTexture(renderer, interface, NULL, NULL);

    if (isPaused) {
        pauseMenu->render();
    }

    SDL_RenderPresent(renderer);
}
}

void Game::restartLevel() {
    this->past = new Tilemap("past", curr_lvl);
    this->present = new Tilemap("present", curr_lvl);
    this->future = new Tilemap("future", curr_lvl);
    this->tilemap = &present;
    
    this->player->pos.x = (*this->tilemap)->spawn.x;
    this->player->pos.y = (*this->tilemap)->spawn.y;
    
    this->player->checkpoint.x = (*this->tilemap)->spawn.x;
    this->player->checkpoint.y = (*this->tilemap)->spawn.y;
}

void Game::togglePause() {
    isPaused = !isPaused;
}

}  // namespace PurpleHole