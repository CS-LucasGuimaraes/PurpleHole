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

#include "classes/collisions.hpp"
#include "classes/entities.hpp"
#include "main/game.hpp"

namespace PurpleHole {

// public:

Collisions::Collisions(PhysicsEntities * entity, Tilemap*** tilemap, Game* game): tilemap(tilemap), entity(entity), game(game) {
    this->platform_isInside = 0;
};

void Collisions::physics_collision_X(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Physical")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect,rs)) 
        if (rs->h > 0) {
            if (frame_movement > 0) {
                entity->collisions["right"] = true;
                entity_rect->x = rect->x - entity_rect->w;
            }
            else if (frame_movement < 0) {
                entity->collisions["left"] = true;
                entity_rect->x = rect->x + rect->w;
            }
            if (frame_movement != 0) {
                entity->pos.x = entity_rect->x;
                break;
            }
        }
    }
}

void Collisions::physics_collision_Y(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Physical")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect, rs)) 
        if (rs->w > 0) {
            if (frame_movement < 0) {
                entity->collisions["up"] = true;
                entity_rect->y = rect->y + rect->h;
            }
            else if (frame_movement > 0) {
                entity->collisions["down"] = true;
                entity_rect->y = rect->y - entity_rect->h;
            }
            if (frame_movement != 0) {
                entity->pos.y = entity_rect->y;
                break;
            }
        }
    }
}


void Collisions::crates_collision_X(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Crate")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect,rs)) 
        if (rs->h > 0) {
            if (frame_movement > 0) {
                std::string loc = std::to_string(int(rect->x/(**tilemap)->tile_size)) + ';' +
                          std::to_string(int(rect->y/(**tilemap)->tile_size));
                
                std::string newloc = std::to_string(int(rect->x/(**tilemap)->tile_size)+1) + ';' +
                          std::to_string(int(rect->y/(**tilemap)->tile_size));
                
                if ((**tilemap)->tilemap.find(newloc) != (**tilemap)->tilemap.end()) {
                    entity->collisions["right"] = true;
                    entity_rect->x = rect->x - entity_rect->w;
                }
                else {
                    auto tmp = (**tilemap)->tilemap[loc];
                    tmp.pos.x++;
                    
                    (**tilemap)->tilemap.erase(loc);
                    (**tilemap)->tilemap[newloc] = tmp;
                }
            }
            else if (frame_movement < 0) {
                std::string loc = std::to_string(int(rect->x/(**tilemap)->tile_size)) + ';' +
                          std::to_string(int(rect->y/(**tilemap)->tile_size));
                
                std::string newloc = std::to_string(int(rect->x/(**tilemap)->tile_size)-1) + ';' +
                          std::to_string(int(rect->y/(**tilemap)->tile_size));
                
                if ((**tilemap)->tilemap.find(newloc) != (**tilemap)->tilemap.end()) {
                    entity->collisions["left"] = true;
                    entity_rect->x = rect->x + rect->w;
                }
                else {
                    auto tmp = (**tilemap)->tilemap[loc];
                    tmp.pos.x--;
                    
                    (**tilemap)->tilemap.erase(loc);
                    (**tilemap)->tilemap[newloc] = tmp;
                }
            }
            if (frame_movement != 0) {
                entity->pos.x = entity_rect->x;
                break;
            }
        }
    }
}



void Collisions::crates_collision_Y(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Crate")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect, rs)) 
        if (rs->w > 0) {
            if (frame_movement < 0) {
                entity->collisions["up"] = true;
                entity_rect->y = rect->y + rect->h;
            }
            else if (frame_movement > 0) {
                entity->collisions["down"] = true;
                entity_rect->y = rect->y - entity_rect->h;
            }
            if (frame_movement != 0) {
                entity->pos.y = entity_rect->y;
                break;
            }
        }
    }
}

void Collisions::platform_collision_X(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Platform")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect,rs)) 
        if (rs->h > 0) {
            if (!platform_isInside){
                if (frame_movement > 0) {
                    entity->collisions["right"] = true;
                    entity_rect->x = rect->x - entity_rect->w;
                }
                else if (frame_movement < 0) {
                    entity->collisions["left"] = true;
                    entity_rect->x = rect->x + rect->w;
                }
                if (frame_movement != 0) {
                    entity->pos.x = entity_rect->x;
                    break;
                }
            }
        }
    }
}

void Collisions::platform_collision_Y(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Platform")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect, rs)) 
        if (rs->w > 0) {
            if (frame_movement < 0 || this->platform_isInside) {
                this->platform_isInside = 2;
                // entity->collisions["up"] = true;
                // entity_rect->y = rect->y + rect->h;
            }
            else if (frame_movement > 0) {
                entity->collisions["down"] = true;
                entity_rect->y = rect->y - entity_rect->h;
            }

            if (frame_movement != 0 || !this->platform_isInside) {
                entity->pos.y = entity_rect->y;
                break;
            }
        }
        this->platform_isInside = std::max(0, this->platform_isInside - 1);
    }
}

void Collisions::key_door_collision_X(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "KeyDoor")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect,rs)) 
        if (rs->h > 0) {
            if (entity->collectibles["key"] > 0) {
                entity->collectibles["key"]--;
                std::string loc = std::to_string(int(rect->x/(**tilemap)->tile_size)) + ';' +
                            std::to_string(int(rect->y/(**tilemap)->tile_size));
                (**tilemap)->tilemap.erase(loc);
            }
            else {
                if (frame_movement > 0) {
                    entity->collisions["right"] = true;
                    entity_rect->x = rect->x - entity_rect->w;
                }
                else if (frame_movement < 0) {
                    entity->collisions["left"] = true;
                    entity_rect->x = rect->x + rect->w;
                }
                if (frame_movement != 0) {
                    entity->pos.x = entity_rect->x;
                    break;
                }
            }
        }
    }
}

void Collisions::key_door_collision_Y(float frame_movement) {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "KeyDoor")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect, rs)) 
        if (rs->w > 0) {
            if (entity->collectibles["key"] > 0) {
                entity->collectibles["key"]--;
                std::string loc = std::to_string(int(rect->x/(**tilemap)->tile_size)) + ';' +
                            std::to_string(int(rect->y/(**tilemap)->tile_size));
                (**tilemap)->tilemap.erase(loc);
            }
            else {
                if (frame_movement < 0) {
                    entity->collisions["up"] = true;
                    entity_rect->y = rect->y + rect->h;
                }
                else if (frame_movement > 0) {
                    entity->collisions["down"] = true;
                    entity_rect->y = rect->y - entity_rect->h;
                }
                if (frame_movement != 0) {
                    entity->pos.y = entity_rect->y;
                    break;
                }
            }
        }
    }
}

void Collisions::collectibles_collision() {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Collectible")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect,rs)) 
        if (rs->h > 0) {
            std::string loc = std::to_string(int(rect->x/(**tilemap)->tile_size)) + ';' +
                        std::to_string(int(rect->y/(**tilemap)->tile_size));
            entity->collectibles[(**tilemap)->tilemap[loc].type]++;
            std::clog << "Collectible: " << (**tilemap)->tilemap[loc].type << ": " << entity->collectibles[(**tilemap)->tilemap[loc].type] << std::endl;
            (**tilemap)->tilemap.erase(loc);
        }
    }
}

void Collisions::Damage_collision() {
    SDL_FRect* entity_rect = entity->Rect();
    for (auto rect : (**tilemap)->tilerects_around(entity->pos, "Damage")) {
        SDL_FRect * rs = new SDL_FRect();
        if (SDL_GetRectIntersectionFloat(entity_rect, rect,rs)) 
        if (rs->h > 0) {
            std::string loc = std::to_string(int(rect->x/(**tilemap)->tile_size)) + ';' +
                        std::to_string(int(rect->y/(**tilemap)->tile_size));

            this->entity->life--;
            if ((**tilemap)->tilemap[loc].type == "death_point") this->entity->life = 0;

            entity->go_to_checkpoint();
            return;
        }
    }
}

}  // namespace PurpleHole