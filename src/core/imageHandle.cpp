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

#include "core/imageHandle.hpp"

namespace PurpleHole {

std::string BASE_PATH = "../../assets/images/";

SDL_Texture * load_image(const char* path) {
    return IMG_LoadTexture(PurpleHole::renderer, path);
}

const std::vector<SDL_Texture *> load_images(const char* path) {
    std::vector<SDL_Texture *> images;
    for (auto const& file :
         std::filesystem::directory_iterator((BASE_PATH + path).c_str())) {
        images.push_back(load_image((BASE_PATH + std::string(path) + "/" +
                                     file.path().filename().string())
                                        .c_str()));
        std::clog << "    " << std::string(path) << "/"
                  << file.path().filename().string() << " loaded.\n";
    }

    return images;
}
}  // namespace PurpleHole