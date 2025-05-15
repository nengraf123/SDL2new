//#include <SDL2/SDL.h>
//#include <iostream>



//int main(int argc, char* argv[]) {
//    // Проверки усякие
//    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
//        return 1;
//    }

//    SDL_Window* window = SDL_CreateWindow(
//        "Привет, SDL2!",
//        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//        800,
//        750,
//        SDL_WINDOW_SHOWN);

//    // Проверки усякие
//    // Ошибка создания окна:
//    if (!window) {
//        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    // Ошибка создания рендера
//    if (!renderer) {
//        std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }


//    /* Наши кнопки */
//    SDL_Rect knopka1 {0, 0, 200, 75};
//    SDL_Rect knopka2 {0, 75, 200, 75};
//    SDL_Rect knopka3 {0, 150, 200, 75};
//    SDL_Rect knopka4 {0, 225, 200, 75};
//    SDL_Rect knopka5 {0, 300, 200, 75};
//    SDL_Rect knopka6 {0, 375, 200, 75};
//    SDL_Rect knopka7 {0, 450, 200, 75};
//    SDL_Rect knopka8 {0, 525, 200, 75};
//    SDL_Rect knopka9 {0, 600, 200, 75};
//    SDL_Rect knopka10 {0, 675, 200, 75};

//    /* Невидимый прямоугольник-курсора */
//    SDL_Rect KvadratNaCursore = {0, 0, 2, 2};

//    /* Переменная сцены */
//    int scene =1;

//    SDL_Event event;
//    bool running = true;
//    while (running) {
//        while (SDL_PollEvent(&event)) {if (event.type == SDL_QUIT) {running = false;}}

        
//        // Обновляем позицию «курсорного» прямоугольника
//        int mx, my;
//        SDL_GetMouseState(&mx, &my);
//        KvadratNaCursore.x = mx - KvadratNaCursore.w / 2;
//        KvadratNaCursore.y = my - KvadratNaCursore.h / 2;

//        /* Хуйня для Клавиатуры */
//        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//        /* Фон */
//        SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255); SDL_RenderClear(renderer);
//        /* Выход на Esc */
//        if (keyState[SDL_SCANCODE_ESCAPE]) running = false;

        
//        /* Проверяем пересечение */
//        bool MouseOnKnopka1 = SDL_HasIntersection(&KvadratNaCursore, &knopka1);
//        bool MouseOnKnopka2 = SDL_HasIntersection(&KvadratNaCursore, &knopka2);
//        bool MouseOnKnopka3 = SDL_HasIntersection(&KvadratNaCursore, &knopka3);
//        bool MouseOnKnopka4 = SDL_HasIntersection(&KvadratNaCursore, &knopka4);
//        bool MouseOnKnopka5 = SDL_HasIntersection(&KvadratNaCursore, &knopka5);
//        bool MouseOnKnopka6 = SDL_HasIntersection(&KvadratNaCursore, &knopka6);
//        bool MouseOnKnopka7 = SDL_HasIntersection(&KvadratNaCursore, &knopka7);
//        bool MouseOnKnopka8 = SDL_HasIntersection(&KvadratNaCursore, &knopka8);
//        bool MouseOnKnopka9 = SDL_HasIntersection(&KvadratNaCursore, &knopka9);
//        bool MouseOnKnopka10 = SDL_HasIntersection(&KvadratNaCursore, &knopka10);


//        /* Механика кнопочек */
//        if (scene == 1)
//        {
//            /* Рисуем кнопку 1: цвет зависит от наведения */
//            if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka1);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


//            /* Рисуем кнопку 2: цвет зависит от наведения */
//            if (MouseOnKnopka2) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka2);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka2);


//            /* Рисуем кнопку 3: цвет зависит от наведения */
//            if (MouseOnKnopka3) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka3);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka3);


//            /* Рисуем кнопку 4: цвет зависит от наведения */
//            if (MouseOnKnopka4) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka4);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka4);


//            /* Рисуем кнопку 5: цвет зависит от наведения */
//            if (MouseOnKnopka5) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka5);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka5);
//        }
//        if (scene == 2)
//        {
//            /* Рисуем кнопку 6: цвет зависит от наведения */
//            if (MouseOnKnopka6) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka6);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka6);


//            /* Рисуем кнопку 7: цвет зависит от наведения */
//            if (MouseOnKnopka7) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka7);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka7);


//            /* Рисуем кнопку 8: цвет зависит от наведения */
//            if (MouseOnKnopka8) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka8);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka8);


//            /* Рисуем кнопку 9: цвет зависит от наведения */
//            if (MouseOnKnopka9) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka9);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka9);


//            /* Рисуем кнопку 10: цвет зависит от наведения */
//            if (MouseOnKnopka10) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka10);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka10);
//        }

//        /* Проверка нажатия на кнопочки (пока что хуево работает слишком много кликов */
//        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && MouseOnKnopka1) {scene =2;}
//        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && MouseOnKnopka2) {scene =1;}


//        /* Mожно отрисовать курсорный прямоугольник для отладки */
//        SDL_SetRenderDrawColor(renderer, 255,255,0,128);
//        SDL_RenderFillRect(renderer, &KvadratNaCursore);

//        SDL_RenderPresent(renderer);SDL_Delay(16); /* 60 FPS */}
//    //Ероры
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return 0;
//}

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
        800, 750, SDL_WINDOW_SHOWN);
    if (!window) { std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl; SDL_Quit(); return 1; }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) { std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl; SDL_DestroyWindow(window); SDL_Quit(); return 1; }

    bool running = true;
    SDL_Event event;

    // Состояние сцены: 0 — меню с кнопками, 1 — другая сцена
    int scene = 0;

    // Кнопки (рисуются только в scene == 0)
    SDL_Rect buttons[10];
    for (int i = 0; i < 10; ++i) {
        buttons[i] = { 0, i * 75, 200, 75 };
    }

    // Невидимый курсорный прямоугольник
    SDL_Rect cursorRect = { 0, 0, 2, 2 };

    while (running) {
        // Обработка событий
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x, my = event.button.y;
                cursorRect.x = mx - cursorRect.w / 2;
                cursorRect.y = my - cursorRect.h / 2;
                if (scene == 0) {
                    // Проверяем клик по любой кнопке
                    for (int i = 0; i < 10; ++i) {
                        if (SDL_HasIntersection(&cursorRect, &buttons[i])) {
                            // Например: при клике на первую кнопку переходим на сцену 1
                            if (i == 0) {
                                scene = 1;
                                std::cout << "Перешли на сцену 1\n";
                            }
                            // можно обрабатывать другие кнопки: else if (i == 1) { ... }
                        }
                    }
                }
            }
        }

        // Выходим по Esc
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_ESCAPE]) running = false;

        // Отрисовка
        SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255);
        SDL_RenderClear(renderer);

        if (scene == 0) {
            // Меню: рисуем все кнопки
            int mx, my;
            Uint32 mb = SDL_GetMouseState(&mx, &my);
            cursorRect.x = mx - cursorRect.w / 2;
            cursorRect.y = my - cursorRect.h / 2;

            for (int i = 0; i < 10; ++i) {
                bool hover = SDL_HasIntersection(&cursorRect, &buttons[i]);
                if (hover) SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);
                else      SDL_SetRenderDrawColor(renderer, 255,   0, 100, 255);
                SDL_RenderFillRect(renderer, &buttons[i]);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &buttons[i]);
            }
        }
        else if (scene == 1) {
            // Сцена 1: рисуем что-то другое
            SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
            SDL_Rect rect = { 200, 200, 400, 300 };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


