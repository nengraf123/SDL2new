#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <vector>
#include <functional>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "tinyfiledialogs.h"


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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    // Частота 44.1 кГц, формат по умолчанию, 2 канала (стерео), буфер 2048 байт
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    // Инициализируем SDL2 (видео+аудио)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Инициализируем SDL_image с поддержкой PNG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    Mix_Music* bgm = Mix_LoadMUS("muzika.mp3");
    if (!bgm) {
        printf("Failed to load bgm! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    // 4.1. Загружаем PNG в SDL_Surface
    SDL_Surface* surface = IMG_Load("ZnakMuziki.png");
    if (!surface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        // не забывай вызывать IMG_Quit и SDL_Quit перед return
        return 1;
    }

    // 4.2. Преобразуем SDL_Surface в SDL_Texture
    SDL_Texture* btnTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // больше не нужен
    if (!btnTexture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }




    

    // Проигрывать bgm в бесконечном цикле: -1 = бесконечность
    bool musicStarted = false;    // будет сигналом, что музыка уже запущена
    // if(music==true){if(Mix_PlayMusic(bgm, -1) == -1) {printf("Mix_PlayMusic: %s\n", Mix_GetError());}}

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
    int scene =0;

    SDL_Event event;
    bool running = true;
    while (running) {

        /* Mожно отрисовать курсорный прямоугольник для отладки */
        SDL_SetRenderDrawColor(renderer, 255,255,0,128);
        SDL_RenderFillRect(renderer, &KvadratNaCursore);
        
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
        if (keyState[SDL_SCANCODE_ESCAPE]){running = false;}
        if (keyState[SDL_SCANCODE_SPACE]){}

        
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
        if (scene == 0)
        {
            /* Рисуем кнопку 1: цвет зависит от наведения */
            if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
            SDL_RenderFillRect(renderer, &knopka1);
            /* Черная обводка вокруг кнопки */
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);
            /* Ставим текстуру на кнопку */
            SDL_RenderCopy(renderer, btnTexture, nullptr, &knopka1);


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

        while (SDL_PollEvent(&event)) {if (event.type == SDL_QUIT) {running = false;}

            /* Наши бинды кнопочек на клавиатуре */
            if (event.type == SDL_KEYDOWN) // нужна для клавиатуры
            {
                /* При нажатии 1 цифры начинает играть музыка */
                if (event.key.keysym.sym == SDLK_1) {if(!musicStarted){if(Mix_PlayMusic(bgm, -1) == -1) {std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;}
                    else {musicStarted = true;}}}
                // для паузы/продолжения можно, например, Space:
                if (event.key.keysym.sym == SDLK_SPACE) {if (Mix_PausedMusic()) Mix_ResumeMusic();else Mix_PauseMusic();}

            }  
            /* Бинды кнопочек для мышки */
            if (scene==0 && MouseOnKnopka1 && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {scene =1;}
            if (scene==0 && MouseOnKnopka10 && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {scene =0;}

            // По нажатию клавиши (скажем, 'O') открываем диалог:
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o) {
                // Фильтр по аудио-файлам
                const char *filters[] = { "*.mp3", "*.wav", "*.ogg" };
                const char *file = tinyfd_openFileDialog(
                    "Выберите аудиофайл", // заголовок
                    NULL,                 // начальная папка (NULL = текущая)
                    3,                    // число фильтров
                    filters,              // список фильтров
                    NULL,                 // description (можно NULL)
                    0                     // разрешить множественный выбор? 0 = нет
                );
                if (file) {
                    // Загружаем новую музыку
                    Mix_FreeMusic(bgm);
                    bgm = Mix_LoadMUS(file);
                    if (!bgm) {
                        std::cerr << "Ошибка загрузки: " << Mix_GetError() << std::endl;
                    }
                }
            }

        }



        SDL_RenderPresent(renderer);SDL_Delay(16); /* ~60 FPS */}
    //Ероры
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

