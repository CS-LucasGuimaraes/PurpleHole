#include "classes/pausemenu.hpp"

namespace PurpleHole {

PauseMenu::PauseMenu(SDL_Renderer* renderer)
    : renderer(renderer), selectedIndex(0) {
    TTF_Init();
    font = TTF_OpenFont((ASSETS_PATH + "fonts/Kenney Blocks.ttf").c_str(), 24);
    options = {"Sound: ON", "Controls", "Main Menu", "Quit", "Back"};
}

PauseMenu::~PauseMenu() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void PauseMenu::render() {
    SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);  // Dark background
    SDL_RenderClear(renderer);

    SDL_Color color;
    SDL_FRect textFRect;

    for (size_t i = 0; i < options.size(); ++i) {
        color = (i == selectedIndex) ? SDL_Color{255, 215, 0, 255} : SDL_Color{255, 255, 255, 255};  // Gold if selected

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, options[i].c_str(), options[i].length(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        textFRect = {
            static_cast<float>((kScreenSize.x - textSurface->w) / 2),
            static_cast<float>(200 + static_cast<int>(i) * 60),
            static_cast<float>(textSurface->w),
            static_cast<float>(textSurface->h)
        };

        SDL_RenderTexture(renderer, textTexture, nullptr, &textFRect);

        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    SDL_RenderPresent(renderer);
}

int PauseMenu::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return 3;  // Quit
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_UP:
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                    break;
                case SDLK_DOWN:
                    selectedIndex = (selectedIndex + 1) % options.size();
                    break;
                case SDLK_RETURN:
                    if (selectedIndex == 0) {
                        options[0] = (options[0] == "Sound: ON") ? "Sound: OFF" : "Sound: ON";
                    } else {
                        return selectedIndex;
                    }
                    break;
            }
        }
    }
    return -1;  // No action taken
}

int PauseMenu::show() {
    while (true) {
        int result = handleInput();
        render();
        if (result != -1) return result;
        SDL_Delay(100);
    }
}

}  // namespace PurpleHole
