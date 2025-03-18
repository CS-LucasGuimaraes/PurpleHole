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

#include "main/editor.hpp"

namespace PurpleHole {

Editor::Editor() {
    this->past = new Tilemap("past", 0);
    this->present = new Tilemap("present", 0);
    this->future = new Tilemap("future", 0);
    
    this->tilemap = &present;
}

Editor::~Editor() {
    delete this->past;
    delete this->present;
    delete this->future;
    std::clog << "Editor class successfully destroyed!\n";
}

void Editor::restartLevel() {
    delete this->past;
    delete this->present;
    delete this->future;
    
    this->past = new Tilemap("past", this->curr_lvl);
    this->present = new Tilemap("present", this->curr_lvl);
    this->future = new Tilemap("future", this->curr_lvl);
}

bool Editor::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                this->isRunning = false;
                return false;

            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_LCTRL:
                        this->modifiers["ctrl"] = true;
                        break;
                    case SDLK_LSHIFT:
                        this->modifiers["shift"] = true;
                        break;
                    case SDLK_LALT:
                        this->modifiers["alt"] = true;
                        break;

                        
                    case SDLK_A:
                        this->movementX.first = 1;
                        break;

                    case SDLK_D:
                        this->movementX.second = 1;
                        break;

                    case SDLK_W:
                        this->movementY.first = 1;
                        break;

                    case SDLK_S:
                        this->movementY.second = 1;
                        break;
                    case SDLK_E:
                         if (*this->tilemap == this->past) {
                            this->tilemap = &this->present;
                        } else
                        if (*this->tilemap == this->present) {
                            this->tilemap = &this->future;

                        } else
                        if (*this->tilemap == this->future) {
                            continue;
                        }
                        break;
                    case SDLK_Q:
                         if (*this->tilemap == this->past) {
                            continue;
                        } else
                        if (*this->tilemap == this->present) {
                            this->tilemap = &this->past;

                        } else
                        if (*this->tilemap == this->future) {
                            this->tilemap = &this->present;
                        }
                        break;
                    case SDLK_COMMA:
                        this->curr_lvl--;
                        this->restartLevel();
                        break;
                    case SDLK_PERIOD:
                        this->curr_lvl++;
                        this->restartLevel();
                        break;
                }
                break;

            case SDL_EVENT_KEY_UP:
                switch (event.key.key) {
                case SDLK_LCTRL:
                    this->modifiers["ctrl"] = false;
                    break;
                case SDLK_LSHIFT:
                    this->modifiers["shift"] = false;
                    break;
                case SDLK_LALT:
                    this->modifiers["alt"] = false;
                    break;


                    case SDLK_A:
                        this->movementX.first = 0;
                        break;

                    case SDLK_D:
                        this->movementX.second = 0;
                        break;

                    case SDLK_W:
                        this->movementY.first = 0;
                        break;

                    case SDLK_S:
                        this->movementY.second = 0;
                        break;
                }
                break;

            case SDL_EVENT_MOUSE_MOTION:
                SDL_GetMouseState(&this->mpos.x, &this->mpos.y);

                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        this->clicking = true;
                        break;

                    case SDL_BUTTON_RIGHT:
                        this->right_clicking = true;
                        break;

                    case SDL_BUTTON_MIDDLE:

                        break;
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        this->clicking = false;
                        break;

                    case SDL_BUTTON_RIGHT:
                        this->right_clicking = false;
                        break;

                    case SDL_BUTTON_MIDDLE:{
                        iCord tilepos = this->getTilePos();
                        std::string tile_loc = std::to_string(tilepos.x) + ";" + std::to_string(tilepos.y);
            
                        auto it = (*this->tilemap)->tilemap.find(tile_loc);
                        if (it != (*this->tilemap)->tilemap.end()) {
                            const tile& clicked_tile = it->second;
            
                            auto foundTile = std::find_if(this->tile_list.begin(), this->tile_list.end(),
                                [&](const auto& pair) { return pair.first == clicked_tile.type; });
            
                            if (foundTile != this->tile_list.end()) {
                                this->tile_group = std::distance(this->tile_list.begin(), foundTile);
                                this->tile_variant = clicked_tile.variant;
                            }
                        }
                        break;
                    }
                }
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                std::string tile_category = this->tile_list[tile_group].second;
                
                if (event.wheel.y > 0) { // UP
                    if (this->modifiers["shift"]) {
                        if (tile_category.substr(0, tile_category.find('/')) != "animated")   
                        this->tile_variant = (this->tile_variant + 1) % assets::tiles[this->tile_list[this->tile_group].first].size();
                    } else {
                        tile_group = (tile_group + 1) % tile_list.size();
                        this->tile_variant = 0;
                    }
                }
                else if (event.wheel.y < 0) { // DOWN
                    if (this->modifiers["shift"]) {
                        if (tile_category.substr(0, tile_category.find('/')) != "animated")   
                            this->tile_variant = (this->tile_variant - 1) % assets::tiles[this->tile_list[this->tile_group].first].size();
                    } else {
                        tile_group = (tile_group - 1 + tile_list.size()) % tile_list.size();
                        this->tile_variant = 0;
                    }
                }
        }
    }
    return true;
}

void Editor::update() {
    this->cameraControl();

    if (this->ongrid) {
        iCord tilepos = this->getTilePos();
        std::string tile_loc =
            std::to_string(tilepos.x) + ";" + std::to_string(tilepos.y);

        std::string tile_category = this->tile_list[tile_group].second;
        std::string render = "";

        
        if (this->clicking) {
            auto f = tile_category.find('/');
            if (f != tile_category.npos) {
                render = tile_category.substr(0, f);
                tile_category = tile_category.substr(f + 1);
            }
            (*this->tilemap)->tilemap[tile_loc] = {
                this->tile_list[tile_group].first, this->tile_variant, tilepos, 
                tile_category, render};
        }

        if (this->right_clicking) {
            if ((*this->tilemap)->tilemap.count(tile_loc) != 0) {
                (*this->tilemap)->tilemap.erase(tile_loc);
            }
        }
    }

    else {
    }
}

SDL_Texture * Editor::get_curr_tile() {
    auto tile_type = this->tile_list[this->tile_group].second;
    if (tile_type.substr(0, tile_type.find('/')) == "animated") {
        return assets::animated_tiles[this->tile_list[this->tile_group].first]->img();
    }
    else {
        return assets::tiles[this->tile_list[this->tile_group].first][this->tile_variant];
    }
}

void Editor::tile_preview() {
    SDL_Texture* curr_tile_img = get_curr_tile();

    float tile_size = (*this->tilemap)->tile_size;
    iCord tile_pos = this->getTilePos();
    fCord tile_pos_f = {tile_pos.x * tile_size - this->scroll.x, tile_pos.y * tile_size - this->scroll.y};
    SDL_FRect preview_corner = {tile_size/2, tile_size/2, tile_size, tile_size};
    SDL_FRect preview_mouse = {tile_pos_f.x, tile_pos_f.y, tile_size, tile_size};

    // SDL_BlendMode prev_blendMode;
    // SDL_GetTextureBlendMode(curr_tile_img, &prev_blendMode);
    // SDL_SetTextureBlendMode(curr_tile_img, SDL_BLENDMODE_BLEND);


    // Uint8 prev_alpha;
    // SDL_GetTextureAlphaMod(curr_tile_img, &prev_alpha);
    // SDL_SetTextureAlphaMod(curr_tile_img, 95);
        
    SDL_RenderTexture(renderer, curr_tile_img, NULL, &preview_corner);
    SDL_RenderTexture(renderer, curr_tile_img, NULL, &preview_mouse);

    // SDL_SetTextureAlphaMod(curr_tile_img, prev_alpha);
    // SDL_SetTextureBlendMode(curr_tile_img, prev_blendMode);
}

void Editor::render() {
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderClear(renderer);

    (*this->tilemap)->render(this->scroll, "editor");
    this->tile_preview();

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, display, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void Editor::cameraControl() {
    this->scroll.x +=
        (this->movementX.second - this->movementX.first) * this->scrollCord;
    this->scroll.y +=
        (this->movementY.second - this->movementY.first) * this->scrollCord;
}

iCord Editor::getTilePos() {
    return {(int)std::floor(((this->mpos.x / kRenderScale) +
                             this->scroll.x) /
                            (*this->tilemap)->tile_size),
            (int)std::floor(((this->mpos.y / kRenderScale) +
                             this->scroll.y) /
                            (*this->tilemap)->tile_size)};
}
}  // namespace PurpleHole