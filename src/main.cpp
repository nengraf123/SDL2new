#include <SDL2/SDL.h>
#include <iostream>
 #include <vector>
 #include <functional>


 // Структура «кнопка» с колбэком
 struct Button {
     SDL_Rect rect;
     std::function<void()> onClick;
 };

 // Функция проверки клика по набору кнопок
 void handleClicks(int mx, int my, const std::vector<Button>& buttons) {
     for (auto& btn : buttons) {
         if (mx >= btn.rect.x && mx <= btn.rect.x + btn.rect.w &&
             my >= btn.rect.y && my <= btn.rect.y + btn.rect.h) {
             btn.onClick();
         }
     }
 }


int main(int argc, char* argv[]) {
    // Проверки усякие
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Привет, SDL2!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800,
        750,
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


    /* Наши кнопки */
    SDL_Rect knopka1 {0, 0, 200, 75};
    SDL_Rect knopka2 {0, 75, 200, 75};
    SDL_Rect knopka3 {0, 150, 200, 75};
    SDL_Rect knopka4 {0, 225, 200, 75};
    SDL_Rect knopka5 {0, 300, 200, 75};
    SDL_Rect knopka6 {0, 375, 200, 75};
    SDL_Rect knopka7 {0, 450, 200, 75};
    SDL_Rect knopka8 {0, 525, 200, 75};
    SDL_Rect knopka9 {0, 600, 200, 75};
    SDL_Rect knopka10 {0, 675, 200, 75};

    /* Невидимый прямоугольник-курсора */
    SDL_Rect KvadratNaCursore = {0, 0, 2, 2};

    /* Переменная сцены */
    int scene =1;

    SDL_Event event;
    bool running = true;
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
        bool MouseOnKnopka2 = SDL_HasIntersection(&KvadratNaCursore, &knopka2);
        bool MouseOnKnopka3 = SDL_HasIntersection(&KvadratNaCursore, &knopka3);
        bool MouseOnKnopka4 = SDL_HasIntersection(&KvadratNaCursore, &knopka4);
        bool MouseOnKnopka5 = SDL_HasIntersection(&KvadratNaCursore, &knopka5);
        bool MouseOnKnopka6 = SDL_HasIntersection(&KvadratNaCursore, &knopka6);
        bool MouseOnKnopka7 = SDL_HasIntersection(&KvadratNaCursore, &knopka7);
        bool MouseOnKnopka8 = SDL_HasIntersection(&KvadratNaCursore, &knopka8);
        bool MouseOnKnopka9 = SDL_HasIntersection(&KvadratNaCursore, &knopka9);
        bool MouseOnKnopka10 = SDL_HasIntersection(&KvadratNaCursore, &knopka10);


        /* Механика кнопочек */
        if (scene == 1)
        {
            /* Рисуем кнопку 1: цвет зависит от наведения */
            if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka1);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);


            /* Рисуем кнопку 2: цвет зависит от наведения */
            if (MouseOnKnopka2) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka2);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka2);


            /* Рисуем кнопку 3: цвет зависит от наведения */
            if (MouseOnKnopka3) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka3);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka3);


            /* Рисуем кнопку 4: цвет зависит от наведения */
            if (MouseOnKnopka4) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka4);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka4);


            /* Рисуем кнопку 5: цвет зависит от наведения */
            if (MouseOnKnopka5) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka5);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka5);
        }
        if (scene == 2)
        {
            /* Рисуем кнопку 6: цвет зависит от наведения */
            if (MouseOnKnopka6) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka6);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka6);


            /* Рисуем кнопку 7: цвет зависит от наведения */
            if (MouseOnKnopka7) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka7);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka7);


            /* Рисуем кнопку 8: цвет зависит от наведения */
            if (MouseOnKnopka8) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka8);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka8);


            /* Рисуем кнопку 9: цвет зависит от наведения */
            if (MouseOnKnopka9) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka9);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka9);


            /* Рисуем кнопку 10: цвет зависит от наведения */
            if (MouseOnKnopka10) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka10);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka10);
        }

        /* Проверка нажатия на кнопочки (пока что хуево работает слишком много кликов */
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && MouseOnKnopka1) {scene =2;}
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && MouseOnKnopka2) {scene =1;}


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
// #include <vector>
// #include <functional>

// // Структура «кнопка» с колбэком
// struct Button {
//     SDL_Rect rect;
//     std::function<void()> onClick;
// };

// // Функция проверки клика по набору кнопок
// void handleClicks(int mx, int my, const std::vector<Button>& buttons) {
//     for (auto& btn : buttons) {
//         if (mx >= btn.rect.x && mx <= btn.rect.x + btn.rect.w &&
//             my >= btn.rect.y && my <= btn.rect.y + btn.rect.h) {
//             btn.onClick();
//         }
//     }
// }

// int main(int argc, char* argv[]) {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("Простой пример",
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 750, 0);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

//     bool running = true;
//     SDL_Event event;

//     int scene = 0;

//     // Создаём набор кнопок для сцены 0
//     std::vector<Button> menuButtons;
//     for (int i = 0; i < 10; ++i) {
//         menuButtons.push_back({
//             SDL_Rect{0, i * 75, 200, 75},
//             // колбэк для каждой кнопки
//             [i, &scene](){
//                 std::cout << "Нажата кнопка " << i+1 << " на сцене 0\n";
//                 if (i == 0) scene = 1;  // например, первая переводит на сцену 1
//             }
//         });
//     }

//     // Набор кнопок для сцены 1
//     std::vector<Button> scene1Buttons = {
//         {{300,300,200,100}, [&scene](){
//             std::cout << "Back from scene 1\n";
//             scene = 0;
//         }}
//     };

//     while (running) {
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) running = false;

//             // Обработка клика ВСЕГДА в одном месте
//             if (event.type == SDL_MOUSEBUTTONUP &&
//                 event.button.button == SDL_BUTTON_LEFT) {
//                 int mx = event.button.x;
//                 int my = event.button.y;
//                 if (scene == 0) {
//                     handleClicks(mx, my, menuButtons);
//                 } else if (scene == 1) {
//                     handleClicks(mx, my, scene1Buttons);
//                 }
//                 // ... можно добавить ещё else if для других сцен
//             }
//         }

//         // Рисуем
//         SDL_SetRenderDrawColor(renderer, 123,123,123,255);
//         SDL_RenderClear(renderer);

//         if (scene == 0) {
//             // отрисовка кнопок меню
//             for (auto& btn : menuButtons) {
//                 SDL_SetRenderDrawColor(renderer, 200,0,100,255);
//                 SDL_RenderFillRect(renderer, &btn.rect);
//                 SDL_SetRenderDrawColor(renderer, 0,0,0,255);
//                 SDL_RenderDrawRect(renderer, &btn.rect);
//             }
//         } else if (scene == 1) {
//             // отрисовка кнопки «Назад»
//             for (auto& btn : scene1Buttons) {
//                 SDL_SetRenderDrawColor(renderer, 100,200,100,255);
//                 SDL_RenderFillRect(renderer, &btn.rect);
//                 SDL_SetRenderDrawColor(renderer, 0,0,0,255);
//                 SDL_RenderDrawRect(renderer, &btn.rect);
//             }
//         }

//         SDL_RenderPresent(renderer);
//         SDL_Delay(16);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }

