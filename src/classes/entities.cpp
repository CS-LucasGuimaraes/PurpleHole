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

#include "classes/entities.hpp"
#include "main/game.hpp"

namespace PurpleHole {

// PhysicsEntities
// public:
PhysicsEntities::PhysicsEntities(std::string e_type, SDL_FRect initial_rect, Tilemap*** tilemap, Game* game, int max_life) : type(e_type), tilemap(tilemap), ID(GenID(e_type)), game(game), max_life(max_life) {
    this->life = this->max_life;

    this->size.x = initial_rect.h;
    this->size.y = initial_rect.w;

    this->set_action("idle");

    this->collisions_control = new Collisions(this, this->tilemap, this->game);
}
PhysicsEntities::~PhysicsEntities() {
    std::clog << "PhysicsEntities class (" << this->type << ':' << this->ID
                << ") successfully destroyed!\n";
}

void PhysicsEntities::update(int movement) {
    this->reset_collisions();
    this->movement_and_collide(movement);
    this->movement_physics();
    this->facing_side(movement);
    this->animation->update();
}

void PhysicsEntities::render(fCord offset) {
    SDL_FRect* dstrect = this->Rect();
    dstrect->x -= offset.x;
    dstrect->y -= offset.y;

    if (this->flip)
        SDL_RenderTextureRotated(renderer, this->animation->img(), NULL,
                         dstrect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderTexture(renderer, this->animation->img(), NULL, dstrect);
}

SDL_FRect * PhysicsEntities::Rect() {
    return new SDL_FRect({this->pos.x, this->pos.y, (float)this->size.x, (float)this->size.y});
}

void PhysicsEntities::go_to_checkpoint() {
    this->pos.x = this->checkpoint.x;
    this->pos.y = this->checkpoint.y;
    this->collectibles = this->collectibles_checkpoint;
}

void PhysicsEntities::set_checkpoint() {
    this->checkpoint = {int(this->pos.x), int(this->pos.y)};
    this->collectibles_checkpoint = this->collectibles;
}

// protected:

void PhysicsEntities::set_action(std::string action) {
    if (action != this->action) {
        this->action = action;
        this->animation =
            assets::animations[this->type + '/' + this->action];

        for (auto img : *this->animation->img_list()) {
            SDL_SetTextureColorMod(img, this->color_mod.r, this->color_mod.g, this->color_mod.b);
        }
    }
}

void PhysicsEntities::reset_collisions() {
    this->collisions = {
        {"up", false}, {"down", false}, {"right", false}, {"left", false}};
}

void PhysicsEntities::movement_and_collide(int movement) {
    this->pos.x += movement + this->velocity.x;
    if (this->type == "Player") {
        ;
    }
    collisions_control->physics_collision_X(movement+this->velocity.x);
    collisions_control->crates_collision_X(movement+this->velocity.x);
    collisions_control->platform_collision_X(movement+this->velocity.x);
    collisions_control->key_door_collision_X(movement+this->velocity.x);
    
    

    this->pos.y += this->velocity.y;
    if (this->type == "Player") {
        ;
    }
    
    collisions_control->physics_collision_Y(this->velocity.y);
    collisions_control->crates_collision_Y(this->velocity.y);
    collisions_control->platform_collision_Y(this->velocity.y);
    collisions_control->key_door_collision_Y(this->velocity.y);

    collisions_control->collectibles_collision();
    collisions_control->Damage_collision();
}

void PhysicsEntities::movement_physics() {
    this->velocity.y = std::min(5.0, this->velocity.y + 0.1); // Gravity

    if (this->velocity.x > 0) {
        this->velocity.x = std::max(this->velocity.x - 0.1, 0.0);  // Right slowdown
    } else if (this->velocity.x < 0) {
        this->velocity.x = std::min(this->velocity.x + 0.1, 0.0);  // Left slowdown
    }

    if (this->collisions["down"] || this->collisions["up"]) {
        this->velocity.y = 0;
    }
}

void PhysicsEntities::facing_side(int movement) {
    if (movement + this->velocity.x > 0) {
        this->flip = false;
    } else if (movement + this->velocity.x < 0) {
        this->flip = true;
    }
}

// Player
// public:
Player::Player(SDL_FRect initial_rect, Tilemap *** tilemap, Game* game) : PhysicsEntities("player", initial_rect, tilemap, game, 3) {
    this->max_jumps = 2;
    this->cur_jumps = 0;
    this->air_time = 0;
    this->in_air = 0;
}

void Player::update(int movement) {
    PhysicsEntities::update(movement);
    
    this->jump_control();
    
    if (this->life <= 0) {
        this->life = this->max_life;
        this->pos = {float((**tilemap)->spawn.x), float((**tilemap)->spawn.y)};
        this->velocity = {0.0, 0.0};

        this->game->restartLevel();
    }
}

void Player::jump() {
    if (this->in_air && (this->collisions["left"] || this->collisions["right"])) {
        this->wall_jump();
        // play sound
    }
    else if (this->cur_jumps > 0 && (this->cur_jumps != this->max_jumps || this->air_time < 10)) {
        this->velocity.y = -3.1;
        this->cur_jumps -= 1;
        this->in_air = true;
        
        // play sound
    }
}

// protected:
void Player::jump_control() {
    this->air_time += 1;

    if (this->air_time > 10) this->in_air = true;

    if (this->collisions["down"]) {
        this->cur_jumps = this->max_jumps;
        this->air_time = 0;
        this->in_air = false;
    }
}

void Player::wall_jump() {
    if (this->collisions["left"]) {
        this->velocity.x = +2.75;
    }
    else if (this->collisions["right"]) {
        this->velocity.x = -2.75;
    }

    this->velocity.y = -2;
    this->cur_jumps = std::max(0, this->cur_jumps-1);
}

}  // namespace PurpleHole