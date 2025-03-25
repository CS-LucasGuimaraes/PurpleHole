#ifndef PURPLEHOLE_CORE_MENU_HPP_
#define PURPLEHOLE_CORE_MENU_HPP_

#include "core/engine.hpp"
#include <string_view>

namespace PurpleHole {

    class Menu {
    public:
        explicit Menu(SDL_Renderer* renderer);
        ~Menu();

        // Retorna a escolha do usuário: 1=Start, 2=Editor, 3=Settings, 4=Credits, 5=Exit
        int show();

    private:
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::vector<std::string> options;
        int selectedIndex;

        void render();
        void handleInput(bool& running);

        // Renderiza texto em (x, y). 'selected' = se texto está selecionado
        void renderText(std::string_view text, int x, int y, bool selected);
    };

} // namespace PurpleHole

#endif // PURPLEHOLE_CORE_MENU_HPP_
