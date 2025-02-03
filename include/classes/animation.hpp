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

#ifndef CPPGAMEDEV_CORE_ANIMATION_HPP_
#define CPPGAMEDEV_CORE_ANIMATION_HPP_

#include "core/engine.hpp"

namespace PurpleHole {

class Animation {
   public:
    Animation(const std::vector<SDL_Texture *> imgs, int img_dur = 5,
              bool loop = true) {
        this->images = imgs;
        this->img_duration = img_dur;
        this->is_looping = loop;
        this->done = false;
        this->frame = 0;
    }
    ~Animation() {
        std::clog << "Animation class successfully destroyed!\n";
        ;
    }

    /**
     * Updates the animation frame.
     *
     * \returns (void): This function does not return a value.
     *
     */
    void update();

    /**
     * Get the image that represents the current frame.
     *
     * \returns (SDL_Texture * *):
     * The image that represents the frame.
     *
     */
    SDL_Texture * img();

    std::vector<SDL_Texture *>* img_list();

   private:
    std::vector<SDL_Texture *> images;
    int img_duration;
    bool is_looping;
    bool done;
    int frame;
};
}  // namespace PurpleHole

#endif  // CPPGAMEDEV_CORE_ANIMATION_HPP_