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

#ifndef CPPGAMEDEV_CORE_IMAGEHANDLE_HPP_
#define CPPGAMEDEV_CORE_IMAGEHANDLE_HPP_

#include "core/engine.hpp"

namespace PurpleHole {

extern std::string BASE_PATH;

/**
 * Create a texture from an image file using the class surface as base.
 *
 * \param path a path on the filesystem to load an image from.
 * \returns the created texture or NULL on failure; call SDL_GetError() for more
 * information.
 */
SDL_Texture * load_image(const char* path);

/**
 * Create a list of textures from a folder path.
 *
 * \param path a path on the filesystem to the folder you want to load the
 * images from. \returns a vector with the created textures or NULL on failure;
 */
const std::vector<SDL_Texture *> load_images(const char* path);

}  // namespace PurpleHole

#endif // CPPGAMEDEV_CORE_IMAGEHANDLE_HPP_