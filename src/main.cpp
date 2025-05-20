#include <SDL2/SDL_rect.h>
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


    SDL_Rect knopka1 = { 0, 0, 0, 0,};
    SDL_Rect knopka2 = { 0, 0, 0, 0,};
    SDL_Rect knopka3 = { 0, 0, 0, 0,};
    SDL_Rect knopka4 = { 0, 0, 0, 0,};
    SDL_Rect knopka5 = { 0, 0, 0, 0,};
    SDL_Rect knopka6 = { 0, 0, 0, 0,};
    SDL_Rect knopka7 = { 0, 0, 0, 0,};
    SDL_Rect knopka8 = { 0, 0, 0, 0,};
    SDL_Rect knopka9 = { 0, 0, 0, 0,};
    SDL_Rect knopka10 = { 0, 0, 0, 0,};
    SDL_Rect knopka11 = { 0, 0, 0, 0,};
    SDL_Rect knopka12 = { 0, 0, 0, 0,};
    SDL_Rect knopka13 = { 0, 0, 0, 0,};
    SDL_Rect knopka14 = { 0, 0, 0, 0,};
    SDL_Rect knopka15 = { 0, 0, 0, 0,};


    SDL_Rect square_rect = { 750, 0, 50, 50 };
    bool is_square_present = true;   // Флаг: должен ли квадрат быть нарисован
    bool is_square_hovered = false;  // Флаг: находится ли мышь над квадратом

    SDL_Color color_default = { 0, 0, 255, 255 }; // Синий (R, G, B, A)
    SDL_Color color_hovered = { 255, 255, 0, 255 }; // Желтый



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
