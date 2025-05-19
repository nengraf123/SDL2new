#include <iostream>
#include <stdio.h>
#include <cmath> 
#include <SDL2/SDL.h>


// Функция для проверки, находится ли точка (x, y) внутри прямоугольника (rect)
// Это наша реализация. В SDL есть готовая SDL_PointInRect, но эта понятнее.
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
        if (event.type == SDL_QUIT) {running = false;}
        /* Если нажата клавиша на клавиатуре то */
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {running = false;}
            else if (event.key.keysym.sym == SDLK_w) {std::cout << "W pressed" << std::endl;}
            else if (event.key.keysym.sym == SDLK_s) {std::cout << "S pressed" << std::endl;}

        }
        /* Если нажата кнопка мыши */
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {printf("Нажата одиночная ЛЕВАЯ кнопка мыши\n");}
            if (event.button.button == SDL_BUTTON_RIGHT) {printf("Нажата одиночная ПРАВАЯ кнопка мыши\n");}
            if (event.button.button == SDL_BUTTON_MIDDLE) {printf("Нажата одиночная СРЕДНЯЯ (колесико) кнопка мыши\n");}

        }


            if (event.type == SDL_MOUSEMOTION) {
                if (is_square_present) {
                    // event.motion.x, event.motion.y - текущие координаты мыши
                    if (IsPointInRect(event.motion.x, event.motion.y, &square_rect)) {
                        // Мышь находится над квадратом
                        if (!is_square_hovered) { // Если только что навели
                            std::cout << "Навели мышь на квадрат" << std::endl;
                            is_square_hovered = true;
                        }
                    } else {
                        // Мышь не над квадратом
                         if (is_square_hovered) { // Если только что увели
                            std::cout << "Увели мышь с квадрата" << std::endl;
                            is_square_hovered = false;
                        }
                    }
                } else {
                     // Если квадрата нет, сбросим флаг наведения на всякий случай
                    is_square_hovered = false; // Можно и не делать, если отрисовка зависит от is_square_present
                }

            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                    // Проверяем, было ли нажатие внутри квадрата, если он существует
                    if (is_square_present) {
                         // event.button.x, event.button.y - координаты нажатия мыши
                         if (IsPointInRect(event.button.x, event.button.y, &square_rect)) {
                            // Нажатие левой кнопки внутри квадрата!
                            std::cout << "Квадрат нажат, он исчезает!" << std::endl;
                            is_square_present = false; // Квадрат больше не будет рисоваться
                            is_square_hovered = false; // Сбросить флаг наведения
                        }
                    }
                
            }



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
