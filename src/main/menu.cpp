#include "main/menu.hpp"
#include <iostream>

// Inclui SDL_image se estiver em vendor
#include <SDL3_image/SDL_image.h>

namespace PurpleHole {

Menu::Menu(SDL_Renderer* renderer)
    : renderer(renderer), selectedIndex(0)
{
    // Inicializa TTF
    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialize TTF: " << SDL_GetError() << std::endl;
    }

    // Carrega a fonte
    font = TTF_OpenFont("../../assets/fonts/Kenney Blocks.ttf", 32);
    if (!font) {
        std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    }

    // Opções do menu
    options = {"Start Game", "Editor", "Settings", "Credits", "Exit"};
}

Menu::~Menu()
{
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

/**
 * Renderiza texto na posição (x, y).
 * Sua versão do TTF exige (font, text, length, SDL_Color).
 */
void Menu::renderText(std::string_view text, int x, int y, bool selected)
{
    SDL_Color color = selected ? SDL_Color{255, 255, 0, 255}
                               : SDL_Color{255, 255, 255, 255};

    // Converter string_view -> string, para pegar .size() e .c_str()
    std::string str = std::string(text);

    // TTF_RenderText_Solid( TTF_Font*, const char*, size_t length, SDL_Color )
    SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), str.size(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText_Solid failed: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect dst = {
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(surface->w),
        static_cast<float>(surface->h)
    };

    SDL_RenderTexture(renderer, texture, nullptr, &dst);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * Renderiza todo o menu.
 */
void Menu::render()
{
    // Fundo bege
    SDL_SetRenderDrawColor(renderer, 222, 203, 169, 255);
    SDL_RenderClear(renderer);

    const int startX = 100;
    const int startY = 200;
    const int spacing = 50;

    for (size_t i = 0; i < options.size(); ++i) {
        int posY = startY + static_cast<int>(i) * spacing;
        renderText(options[i], startX, posY, (i == static_cast<size_t>(selectedIndex)));
    }

    // Carregar e desenhar a imagem
    SDL_Surface* imageSurface = IMG_Load("../../assets/images/menu_image.png");
    if (imageSurface) {
        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

        float imageX = 1280.0f - (imageSurface->w * 0.5f) - 50.0f;
        float imageY = (720.0f - (imageSurface->h * 0.5f)) * 0.5f;

        SDL_FRect dst = {
            imageX,
            imageY,
            imageSurface->w * 0.5f,
            imageSurface->h * 0.5f
        };

        SDL_RenderTexture(renderer, imageTexture, nullptr, &dst);

        SDL_DestroySurface(imageSurface);
        SDL_DestroyTexture(imageTexture);
    } else {
        std::cerr << "Failed to load menu image: " << SDL_GetError() << std::endl;
    }

    SDL_RenderPresent(renderer);
}

/**
 * Lida com eventos de teclado na sua versão do SDL3.
 * O struct SDL_KeyboardEvent possui 'scancode' ao invés de 'keysym' ou 'keysym_scancode'.
 */
void Menu::handleInput(bool& running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
            selectedIndex = static_cast<int>(options.size()) - 1; // \"Exit\"
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.scancode) { // <= USAMOS 'scancode'
                case SDL_SCANCODE_UP:
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                    break;
                case SDL_SCANCODE_DOWN:
                    selectedIndex = (selectedIndex + 1) % options.size();
                    break;
                case SDL_SCANCODE_RETURN:
                case SDL_SCANCODE_KP_ENTER:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }
}

/**
 * Loop principal do menu
 */
int Menu::show()
{
    bool running = true;
    while (running) {
        handleInput(running);
        render();
        SDL_Delay(16); // ~60 FPS
    }
    // Retorna o índice + 1
    return selectedIndex + 1;
}

} // namespace PurpleHole
