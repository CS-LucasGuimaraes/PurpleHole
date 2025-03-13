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

#ifndef PURPLEHOLE_CLASSES_ENTITIES_HPP_
#define PURPLEHOLE_CLASSES_ENTITIES_HPP_

#include "core/engine.hpp"
#include "core/assets.hpp"
#include "classes/animation.hpp"
#include "classes/tilemap.hpp"
#include "classes/collisions.hpp"

namespace PurpleHole {

class Game;

class PhysicsEntities {
   friend class Collisions;

   public:
    PhysicsEntities(std::string e_type, SDL_FRect initial_rect, Tilemap *** tilemap, Game* game, int max_life = 1);
    ~PhysicsEntities();

    /**
     * Updates the physics entity's internal state.
     *
     * This function updates all the physics entity's state and logic.
     *
     * @returns (void): This function does not return a value.
     */
    void update(int movement = 0);
    
    /**
     *  Render the entity's animation onto the PurpleHole::renderer surface.
     *
     * \returns (void): This function does not return a value.
     */
    void render(fCord offset);
    
    SDL_FRect * Rect();
    PurpleHole::fCord pos;
    iCord checkpoint;
    
    protected:
    std::string type;
    std::string ID;
    std::string action = "";
    PurpleHole::iCord size;
    PurpleHole::fCord velocity = {0.0, 0.0};
    PurpleHole::RGB color_mod = {255, 255, 255};
    Animation *animation;
    std::map<std::string, bool> collisions;
    bool flip = false;
    Tilemap *** tilemap;
    Game * game;
    Collisions * collisions_control;
    int max_life;
    int life;
    
    /**
     * Sets the action of the physics entity.
     *
     * This function updates the action of the physics entity and assigns the
     * corresponding animation.
     *
     * @param action (std::string): The new action to be set for the physics
     * entity.
     *
     * @returns (void): This function does not return a value.
     */
    void set_action(std::string action);

    void reset_collisions();
    void movement_and_collide(int movement);
    void movement_physics();
    void facing_side(int movement);
};

class Player : public PhysicsEntities {
    public:
    Player(SDL_FRect initial_rect, Tilemap*** tilemap, Game* game);

    void jump();
    void update(int movement = 0);
    
    protected:
    int max_jumps;
    int cur_jumps;
    int air_time;
    bool in_air;
    
    void jump_control();
    void wall_jump();

};


}  // namespace PurpleHole

#endif  // PURPLEHOLE_CLASSES_ENTITIES_HPP_