#include <SDL2/SDL.h>
#include <iostream>

class Game {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running = true;

public:
    Game() {
        // Инициализация SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
            running = false;
            return;
        }

        // Создание окна
        window = SDL_CreateWindow(
            "SDL2 C++ Пример",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN
        );

        if (!window) {
            std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
            running = false;
            return;
        }

        // Создание рендера
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
            running = false;
            return;
        }
    }

    ~Game() {
        // Очистка ресурсов
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void run() {
        if (!running) return;

        SDL_Event event;
        while (running) {
            // Обработка событий
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

            // Очистка экрана (черный цвет)
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Здесь можно добавить отрисовку

            // Обновление экрана
            SDL_RenderPresent(renderer);
        }
    }
};

int main(int argc, char* argv[]) {
    Game game;
    game.run();
    return 0;
}
