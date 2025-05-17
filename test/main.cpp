#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    #include "h/error1.h"

    // Создание окна
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Пример",                  // Заголовок окна
        SDL_WINDOWPOS_CENTERED,         // Позиция X
        SDL_WINDOWPOS_CENTERED,         // Позиция Y
        800,                            // Ширина
        600,                            // Высота
        SDL_WINDOW_SHOWN                // Флаги
    );

    #include "h/error2.h"

    // Основной цикл
    bool running = true;
    SDL_Event event;
    while (running) {

        // Очистка экрана (черный цвет)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderClear(renderer);


        // Обработка событий
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {running = false;}



    }
    // Обновление экрана
    SDL_RenderPresent(renderer);
    }

    // Очистка ресурсов
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
