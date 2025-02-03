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

#ifndef CPPGAMEDEV_CORE_GAME_HPP_
#define CPPGAMEDEV_CORE_GAME_HPP_

#include "classes/entities.hpp"
#include "classes/tilemap.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/imageHandle.hpp"

namespace PurpleHole {

class Game {
   public:
    Game();
    ~Game();

    /**
     * Processes user input events in the game loop.
     *
     * \returns (bool):
     * true if the game should continue running.
     * false if the game should exit.
     */
    bool handleEvents();

    /**
     * Updates the game state and logic.
     *
     * \returns (void): This function does not return a value.
     */
    void update();

    /**
     * Renders the game state to the screen.
     *
     * \returns (void): This function does not return a value.
     */
    void render();

    /**
     * Checks if the game is currently running.
     * \returns (bool):
     *  true if the game is running.
     *  false if the game has quit.
     */
    bool running() { return this->isRunning; }

   private:
    bool isRunning = true;
    Player* player;
    Tilemap** tilemap;
    Tilemap* past;
    Tilemap* present;
    Tilemap* future;
    std::pair<int, int> movement = {0, 0};
};
}  // namespace PurpleHole

#endif  // CPPGAMEDEV_CORE_GAME_HPP_