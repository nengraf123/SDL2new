#include <iostream>
#include <stdio.h>
#include <cmath> 
#include <SDL2/SDL.h>


// Функция для проверки, находится ли точка (x, y) внутри прямоугольника (rect)
// Это моя нахуй реализация В SDL есть готовая SDL_PointInRect, но эта понятнее.
bool IsPointInRect(int x, int y, const SDL_Rect* rect) {
    if (rect == nullptr) return false; // Проверка на нулевой указатель в C++ стиле
    return (x >= rect->x && x < rect->x + rect->w &&
            y >= rect->y && y < rect->y + rect->h);
}



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


    SDL_Rect square_rect = { 100, 100, 100, 100 }; // x, y, ширина, высота
    bool is_square_present = true;   // Флаг: должен ли квадрат быть нарисован
    bool is_square_hovered = false;  // Флаг: находится ли мышь над квадратом

    SDL_Color color_default = { 0, 0, 255, 255 }; // Синий (R, G, B, A)
    SDL_Color color_hovered = { 255, 255, 0, 255 }; // Желтый
    SDL_Color color_background = { 0, 0, 0, 255 }; // Черный фон



    // Основной цикл
    bool running = true;
    SDL_Event event;
    while (running) {

        // Очистка экрана (черный цвет)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderClear(renderer);




        // Отрисовка квадрата, если он существует
        if (is_square_present) {
            // Выбираем цвет в зависимости от состояния наведения
            if (is_square_hovered) {SDL_SetRenderDrawColor(renderer, color_hovered.r, color_hovered.g, color_hovered.b, color_hovered.a);}
            else {SDL_SetRenderDrawColor(renderer, color_default.r, color_default.g, color_default.b, color_default.a);}

            // Рисуем заполненный прямоугольник (наш квадрат)
            SDL_RenderFillRect(renderer, &square_rect);
        }



        // Обработка событий
    while (SDL_PollEvent(&event)) {
        #include "h/event.h"
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
