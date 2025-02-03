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

#include "classes/animation.hpp"

namespace PurpleHole {

void Animation::update() {
    if (this->is_looping) {
        this->frame =
            (this->frame + 1) % (this->img_duration * this->images.size());
    } else {
        this->frame =
            std::min(int(this->frame + 1),
                     int(this->img_duration * this->images.size() - 1));
        if (this->frame >= int(this->img_duration * this->images.size() - 1)) {
            this->done = true;
        }
    }
}

SDL_Texture * Animation::img() {
    return this->images[size_t(this->frame / this->img_duration)];
}

std::vector<SDL_Texture *>* Animation::img_list() { return &this->images; }
}  // namespace PurpleHole