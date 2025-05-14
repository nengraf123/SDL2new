#include <SDL2/SDL.h>
#include <iostream>



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Привет, SDL2!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800,
        800,
        SDL_WINDOW_SHOWN);

    // Проверки усякие
    // Ошибка создания окна:
    if (!window) {
        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Ошибка создания рендера
    if (!renderer) {
        std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    /* Наши кнопки */
    SDL_Rect knopka1 {0, 0, 200, 75};
    SDL_Rect knopka2 {0, 75, 200, 75};
    SDL_Rect knopka3 {0, 150, 200, 75};
    SDL_Rect knopka4 {0, 225, 200, 75};
    SDL_Rect knopka5 {0, 300, 200, 75};
    SDL_Rect knopka6 {0, 375, 200, 75};


    /* Невидимый прямоугольник-курсора */
    SDL_Rect KvadratNaCursore = {0, 0, 2, 2};

    while (running) {
        while (SDL_PollEvent(&event)) {if (event.type == SDL_QUIT) {running = false;}}

        
        // Обновляем позицию «курсорного» прямоугольника
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        KvadratNaCursore.x = mx - KvadratNaCursore.w / 2;
        KvadratNaCursore.y = my - KvadratNaCursore.h / 2;
        /* Хуйня для Клавиатуры */
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        /* Фон */
        SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255); SDL_RenderClear(renderer);
        /* Выход на Esc */
        if (keyState[SDL_SCANCODE_ESCAPE]) running = false;


        /* Проверяем пересечение */
        bool MouseOnKnopka1 = SDL_HasIntersection(&KvadratNaCursore, &knopka1);


        /* Рисуем кнопку 1: цвет зависит от наведения */
        if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
        SDL_RenderFillRect(renderer, &knopka1);
        /* Черная обводка вокруг кнопки */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


        /* Рисуем кнопку 2: цвет зависит от наведения */
        if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
        SDL_RenderFillRect(renderer, &knopka1);
        /* Черная обводка вокруг кнопки */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


        /* Рисуем кнопку 3: цвет зависит от наведения */
        if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
        SDL_RenderFillRect(renderer, &knopka1);
        /* Черная обводка вокруг кнопки */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


        /* Рисуем кнопку 4: цвет зависит от наведения */
        if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
        SDL_RenderFillRect(renderer, &knopka1);
        /* Черная обводка вокруг кнопки */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


        /* Рисуем кнопку 5: цвет зависит от наведения */
        if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
        SDL_RenderFillRect(renderer, &knopka1);
        /* Черная обводка вокруг кнопки */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


        /* Рисуем кнопку 6: цвет зависит от наведения */
        if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
        SDL_RenderFillRect(renderer, &knopka1);
        /* Черная обводка вокруг кнопки */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);






        /* Mожно отрисовать курсорный прямоугольник для отладки */
        SDL_SetRenderDrawColor(renderer, 255,255,0,128);
        SDL_RenderFillRect(renderer, &KvadratNaCursore);

        SDL_RenderPresent(renderer);SDL_Delay(16); /* 60 FPS */}
    //Ероры
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// #include <SDL2/SDL.h>
// #include <iostream>

// int main(int argc, char* argv[]) {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("Simple Button",
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

//     // Кнопка
//     SDL_Rect knopka1 = {300, 250, 200, 100};
//     // Невидимый прямоугольник-курсора (например, 10×10)
//     SDL_Rect KvadratNaCursore = {0, 0, 2, 2};

//     bool running = true;
//     SDL_Event e;

//     while (running) {
//         // Обновляем позицию «курсорного» прямоугольника
//         int mx, my;
//         SDL_GetMouseState(&mx, &my);
//         KvadratNaCursore.x = mx - KvadratNaCursore.w / 2;
//         KvadratNaCursore.y = my - KvadratNaCursore.h / 2;

//         // Проверяем пересечение
//         bool hovering = SDL_HasIntersection(&KvadratNaCursore, &knopka1);

//         while (SDL_PollEvent(&e)) {
//             if (e.type == SDL_QUIT) {
//                 running = false;
//             }
//             else if (e.type == SDL_MOUSEBUTTONUP &&
//                      e.button.button == SDL_BUTTON_LEFT &&
//                      hovering)
//             {
//                 std::cout << "Button clicked via cursorRect!\n";
//             }
//         }

//         // Рендер фон
//         SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
//         SDL_RenderClear(renderer);

//         // Рисуем кнопку: цвет зависит от hovering
//         if (hovering) SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);
//         else          SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
//         SDL_RenderFillRect(renderer, &knopka1);
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderDrawRect(renderer, &knopka1);

//         // (Опционально) можно отрисовать курсорный прямоугольник для отладки
//         SDL_SetRenderDrawColor(renderer, 255,255,0,128);
//         SDL_RenderFillRect(renderer, &KvadratNaCursore);

//         SDL_RenderPresent(renderer);
//         SDL_Delay(16);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }

