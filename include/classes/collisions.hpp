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

#ifndef CPPGAMEDEV_CLASSES_COLLISIONS_HPP_
#define CPPGAMEDEV_CLASSES_COLLISIONS_HPP_

#include "core/engine.hpp"
#include "classes/tilemap.hpp"

namespace PurpleHole {
class PhysicsEntities;

class Collisions {
   public:
    Collisions(PhysicsEntities * entity, Tilemap*** tilemap): tilemap(tilemap), entity(entity) {};


    void physics_tiles_collisions_X(float frame_movement);
    void physics_tiles_collisions_Y(float frame_movement);
    
    void crates_tiles_collisions_X(float frame_movement);
    void crates_tiles_collisions_Y(float frame_movement);
    
            
   private:
    Tilemap *** tilemap;
    PhysicsEntities* entity;

};
}  // namespace PurpleHole

#endif  // CPPGAMEDEV_CLASSES_COLLISIONS_HPP_
