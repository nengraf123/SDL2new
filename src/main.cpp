//#include <SDL2/SDL.h>
//#include <SDL2/SDL_keycode.h>
//#include <SDL2/SDL_scancode.h>
//#include <SDL2/SDL_surface.h>
//#include <iostream>
//#include <vector>
//#include <functional>
//#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_image.h>

//#include "tinyfiledialogs.h"


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
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//        return 1;
//    }
//    // Частота 44.1 кГц, формат по умолчанию, 2 канала (стерео), буфер 2048 байт
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//        return 1;
//    }

//    // Инициализируем SDL2 (видео+аудио)
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }

//    // Инициализируем SDL_image с поддержкой PNG
//    int imgFlags = IMG_INIT_PNG;
//    if (!(IMG_Init(imgFlags) & imgFlags)) {
//        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
//        return 1;
//    }

//    Mix_Music* bgm = Mix_LoadMUS("muzika.mp3");
//    if (!bgm) {
//        printf("Failed to load bgm! SDL_mixer Error: %s\n", Mix_GetError());
//        return 1;
//    }

//    // 4.1. Загружаем PNG в SDL_Surface
//    SDL_Surface* surface = IMG_Load("ZnakMuziki.png");
//    if (!surface) {
//        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
//        // не забывай вызывать IMG_Quit и SDL_Quit перед return
//        return 1;
//    }

//    // 4.2. Преобразуем SDL_Surface в SDL_Texture
//    SDL_Texture* btnTexture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);  // больше не нужен
//    if (!btnTexture) {
//        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }




    

//    // Проигрывать bgm в бесконечном цикле: -1 = бесконечность
//    bool musicStarted = false;    // будет сигналом, что музыка уже запущена
//    // if(music==true){if(Mix_PlayMusic(bgm, -1) == -1) {printf("Mix_PlayMusic: %s\n", Mix_GetError());}}

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
//    int scene =0;

//    SDL_Event event;
//    bool running = true;
//    while (running) {

//        /* Mожно отрисовать курсорный прямоугольник для отладки */
//        SDL_SetRenderDrawColor(renderer, 255,255,0,128);
//        SDL_RenderFillRect(renderer, &KvadratNaCursore);
        
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
//        if (keyState[SDL_SCANCODE_ESCAPE]){running = false;}
//        if (keyState[SDL_SCANCODE_SPACE]){}

        
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
//        if (scene == 0)
//        {
//            /* Рисуем кнопку 1: цвет зависит от наведения */
//            if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255);}else {SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255);}
//            SDL_RenderFillRect(renderer, &knopka1);
//            /* Черная обводка вокруг кнопки */
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderDrawRect(renderer, &knopka1);
//            /* Ставим текстуру на кнопку */
//            SDL_RenderCopy(renderer, btnTexture, nullptr, &knopka1);


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

//        while (SDL_PollEvent(&event)) {if (event.type == SDL_QUIT) {running = false;}

//            /* Наши бинды кнопочек на клавиатуре */
//            if (event.type == SDL_KEYDOWN) // нужна для клавиатуры
//            {
//                /* При нажатии 1 цифры начинает играть музыка */
//                if (event.key.keysym.sym == SDLK_1) {if(!musicStarted){if(Mix_PlayMusic(bgm, -1) == -1) {std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;}
//                    else {musicStarted = true;}}}
//                // для паузы/продолжения можно, например, Space:
//                if (event.key.keysym.sym == SDLK_SPACE) {if (Mix_PausedMusic()) Mix_ResumeMusic();else Mix_PauseMusic();}

//            }  
//            /* Бинды кнопочек для мышки */
//            if (scene==0 && MouseOnKnopka1 && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {scene =1;}
//            if (scene==0 && MouseOnKnopka10 && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {scene =0;}


//        }



//        SDL_RenderPresent(renderer);SDL_Delay(16); /* ~60 FPS */}
//    //Ероры
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return 0;
//}





// #include <SDL2/SDL.h>
// #include <SDL2/SDL_keycode.h>
// #include <SDL2/SDL_scancode.h>
// #include <SDL2/SDL_surface.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <iostream>
// #include <vector>
// #include <functional>
// #include <fstream>
// #include <filesystem>
// #include <string>
// #include <algorithm>
// #include "tinyfiledialogs.h"

// namespace fs = std::filesystem;

// // Определение цветов
// SDL_Color bgColor = {28, 28, 28, 255};        // #1C1C1C
// SDL_Color buttonColor = {51, 51, 51, 255};    // #333333
// SDL_Color buttonHoverColor = {85, 85, 85, 255}; // #555555
// SDL_Color textColor = {255, 255, 255, 255};   // #FFFFFF
// SDL_Color shadowColor = {0, 0, 0, 128};       // Полупрозрачная тень
// SDL_Color sliderTrackColor = {68, 68, 68, 255}; // #444444
// SDL_Color sliderActiveColor = {102, 102, 102, 255}; // #666666
// SDL_Color sliderHandleColor = {255, 255, 255, 255}; // #FFFFFF
// SDL_Color borderColor = {0, 0, 0, 255};       // #000000
// SDL_Color pathColor = {100, 100, 100, 255};   // Серый для пути
// SDL_Color enemyColor = {255, 0, 0, 255};      // Красный для врагов
// SDL_Color towerColor = {0, 255, 0, 255};      // Зеленый для башен
// SDL_Color projectileColor = {255, 255, 0, 255}; // Желтый для снарядов
// SDL_Color validPlacementColor = {0, 255, 0, 128}; // Зеленый для допустимого размещения
// SDL_Color invalidPlacementColor = {255, 0, 0, 128}; // Красный для недопустимого размещения

// // Функция для рендеринга текста
// SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int maxWidth = -1) {
//     std::string displayText = text;
//     if (maxWidth > 0) {
//         int w;
//         TTF_SizeUTF8(font, text.c_str(), &w, nullptr);
//         if (w > maxWidth) {
//             displayText = text;
//             while (TTF_SizeUTF8(font, (displayText + "...").c_str(), &w, nullptr), w > maxWidth && !displayText.empty()) {
//                 displayText.pop_back();
//             }
//             displayText += "...";
//         }
//     }
//     SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, displayText.c_str(), color);
//     if (!textSurface) {
//         std::cerr << "TTF_RenderUTF8_Blended Error: " << TTF_GetError() << std::endl;
//         return nullptr;
//     }
//     SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//     SDL_FreeSurface(textSurface);
//     if (!textTexture) {
//         std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//     }
//     return textTexture;
// }

// // Форматирование времени
// std::string formatTime(double seconds) {
//     int totalSeconds = static_cast<int>(seconds);
//     int minutes = totalSeconds / 60;
//     int secs = totalSeconds % 60;
//     char buffer[6];
//     snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
//     return std::string(buffer);
// }

// // Структура для врагов
// struct Enemy {
//     float x, y;
//     float speed;
//     int health;
//     int pathIndex;
//     bool active;
//     int type; // Тип врага (0-9)
// };

// // Структура для башен
// struct Tower {
//     int x, y;
//     int range;
//     int damage;
//     float fireRate;
//     float lastShot;
//     bool active;
//     int type; // Тип башни (0-9)
// };

// // Структура для снарядов
// struct Projectile {
//     float x, y;
//     float speed;
//     int damage;
//     Enemy* target; // Указатель на целевого врага
//     bool active;
// };

// // 10 типов врагов
// const int ENEMY_TYPES = 10;
// float enemySpeeds[ENEMY_TYPES] = {2.0f, 1.5f, 0.8f, 3.0f, 1.0f, 2.5f, 0.5f, 1.8f, 2.2f, 1.2f};
// int enemyHealths[ENEMY_TYPES] = {2, 5, 10, 1, 7, 3, 15, 4, 6, 8};

// // 10 типов башен
// const int TOWER_TYPES = 10;
// int towerRanges[TOWER_TYPES] = {100, 120, 80, 150, 90, 110, 130, 100, 140, 95};
// int towerDamages[TOWER_TYPES] = {1, 2, 1, 3, 1, 2, 4, 1, 3, 2};
// float towerFireRates[TOWER_TYPES] = {1.0f, 0.5f, 2.0f, 0.8f, 1.5f, 1.2f, 0.6f, 2.5f, 0.9f, 1.8f};
// std::string towerNames[TOWER_TYPES] = {"Basic", "Cannon", "Laser", "Slow", "Sniper", "Multi", "Bomb", "Freeze", "Poison", "Tesla"};

// // Проверка, находится ли точка (px, py) в радиусе действия башни
// bool inRange(Tower& tower, float px, float py) {
//     float dx = tower.x + 25 - px; // Центр башни (размер башни 50x50)
//     float dy = tower.y + 25 - py;
//     return sqrt(dx * dx + dy * dy) <= tower.range;
// }

// // Проверка пересечения с другими башнями
// bool isValidPlacement(int x, int y, const std::vector<Tower>& towers, int towerSize = 50) {
//     SDL_Rect newTower = {x, y, towerSize, towerSize};
//     for (const auto& tower : towers) {
//         if (tower.active) {
//             SDL_Rect existingTower = {tower.x, tower.y, towerSize, towerSize};
//             if (SDL_HasIntersection(&newTower, &existingTower)) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// // Функция для рендеринга круга (для снарядов)
// void renderCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
//     for (int x = -radius; x <= radius; x++) {
//         for (int y = -radius; y <= radius; y++) {
//             if (x * x + y * y <= radius * radius) {
//                 SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
//             }
//         }
//     }
// }

// int main(int argc, char* argv[]) {
//     SDL_SetMainReady();
//     setlocale(LC_ALL, "ru_RU.UTF-8");
//     SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

//     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
//         std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
//         return 1;
//     }
//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//         std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }
//     int imgFlags = IMG_INIT_PNG;
//     if (!(IMG_Init(imgFlags) & imgFlags)) {
//         std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }
//     if (TTF_Init() == -1) {
//         std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
//     TTF_Font* trackFont = TTF_OpenFont("arial.ttf", 40);
//     TTF_Font* titleFont = TTF_OpenFont("arial.ttf", 48);
//     if (!font || !trackFont || !titleFont) {
//         std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
//         TTF_Quit();
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Window* window = SDL_CreateWindow("Музыкальный плеер", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 750, SDL_WINDOW_SHOWN);
//     if (!window) {
//         std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
//         TTF_CloseFont(font);
//         TTF_CloseFont(trackFont);
//         TTF_CloseFont(titleFont);
//         TTF_Quit();
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (!renderer) {
//         std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
//         SDL_DestroyWindow(window);
//         TTF_CloseFont(font);
//         TTF_CloseFont(trackFont);
//         TTF_CloseFont(titleFont);
//         TTF_Quit();
//         IMG_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     std::vector<SDL_Point> enemyPath = {{50, 50}, {700, 50}, {700, 300}, {50, 300}, {50, 550}, {700, 550}};
//     std::vector<Enemy> enemies;
//     std::vector<Projectile> projectiles; // Вектор для хранения снарядов
//     Uint32 lastEnemySpawn = SDL_GetTicks();
//     const Uint32 enemySpawnInterval = 2000;
//     std::vector<Tower> towers;
//     int playerHealth = 10;
//     int playerMoney = 100;
//     const int towerCost = 50;
//     SDL_Texture* healthText = nullptr;
//     SDL_Texture* moneyText = nullptr;
//     SDL_Rect backButton {650, 650, 120, 75};

//     // Карточки башен
//     std::vector<SDL_Rect> towerCards(TOWER_TYPES);
//     for (int i = 0; i < TOWER_TYPES; ++i) {
//         towerCards[i] = {10 + i * 75, 650, 70, 90};
//     }

//     int selectedTowerType = -1; // Выбранный тип башни
//     SDL_Rect previewTower = {0, 0, 50, 50}; // Предпросмотр башни
//     bool isPlacingTower = false; // Флаг для этапа размещения

//     std::string musicPath = "muzika.mp3";
//     std::string folderPath;
//     std::ifstream musicPathFile("music_path.txt");
//     if (musicPathFile.is_open()) {
//         std::getline(musicPathFile, musicPath);
//         std::getline(musicPathFile, folderPath);
//         musicPathFile.close();
//     }

//     Mix_Music* bgm = Mix_LoadMUS(musicPath.c_str());
//     if (!bgm) {
//         std::cerr << "Failed to load bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
//     }

//     std::vector<std::string> musicFiles;
//     size_t currentTrackIndex = 0;
//     if (!folderPath.empty() && fs::exists(folderPath)) {
//         for (const auto& entry : fs::directory_iterator(folderPath)) {
//             if (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav") {
//                 musicFiles.push_back(entry.path().string());
//                 if (entry.path().string() == musicPath) {
//                     currentTrackIndex = musicFiles.size() - 1;
//                 }
//             }
//         }
//     }

//     SDL_Rect menuButton1 {300, 300, 200, 75};
//     SDL_Rect menuButton2 {300, 400, 200, 75};
//     SDL_Rect menuButton3 {300, 500, 200, 75};
//     SDL_Rect menuButton4 {300, 600, 200, 75};
//     SDL_Rect knopka1 {0, 0, 200, 75};
//     SDL_Rect knopka2 {0, 75, 200, 75};
//     SDL_Rect knopka11 {340, 550, 120, 75};
//     SDL_Rect sliderTrack {300, 500, 200, 10};
//     SDL_Rect sliderHandle {300, 495, 10, 20};
//     bool isDraggingSlider = false;
//     SDL_Rect musicScrollTrack {790, 50, 10, 385};
//     SDL_Rect musicScrollHandle {790, 50, 10, 20};
//     bool isDraggingMusicScroll = false;
//     int musicScrollOffset = 0;
//     const int maxVisibleSquares = 7;
//     std::vector<SDL_Rect> musicSquares;
//     for (size_t i = 0; i < musicFiles.size() && i < maxVisibleSquares; ++i) {
//         musicSquares.push_back({650, static_cast<int>(50 + i * 55), 140, 50});
//     }
//     std::vector<SDL_Texture*> musicFileTextures;
//     for (const auto& file : musicFiles) {
//         std::string filename = fs::path(file).filename().string();
//         SDL_Texture* textTexture = createTextTexture(renderer, font, filename, textColor, 130);
//         musicFileTextures.push_back(textTexture);
//     }
//     std::string currentTrack = fs::path(musicPath).filename().string();
//     SDL_Texture* trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
//     int textOffset = 0;
//     Uint32 lastTextUpdate = SDL_GetTicks();
//     bool needsScrolling = currentTrack.length() > 15;
//     SDL_Texture* currentTimeText = nullptr;
//     SDL_Texture* totalTimeText = nullptr;
//     SDL_Texture* hoverTimeText = nullptr;
//     double musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
//     totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
//     currentTimeText = createTextTexture(renderer, font, "00:00", textColor);
//     SDL_Rect coverRect {300, 100, 200, 200};
//     SDL_Texture* coverTexture = nullptr;
//     std::string coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
//     if (fs::exists(coverPath)) {
//         SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
//         if (coverSurface) {
//             coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
//             SDL_FreeSurface(coverSurface);
//         }
//     }

//     int scene = -1;
//     bool musicStarted = false;
//     bool running = true;
//     SDL_Event event;
//     SDL_Rect KvadratNaCursore = {0, 0, 2, 2};

//     while (running) {
//         int mx, my;
//         SDL_GetMouseState(&mx, &my);
//         KvadratNaCursore.x = mx - KvadratNaCursore.w / 2;
//         KvadratNaCursore.y = my - KvadratNaCursore.h / 2;

//         const Uint8* keyState = SDL_GetKeyboardState(NULL);
//         if (keyState[SDL_SCANCODE_ESCAPE]) {
//             if (scene == -1) {
//                 running = false;
//             } else {
//                 scene = -1;
//                 enemies.clear();
//                 towers.clear();
//                 projectiles.clear(); // Очистка снарядов
//                 playerHealth = 10;
//                 playerMoney = 100;
//                 selectedTowerType = -1;
//                 isPlacingTower = false;
//             }
//         }

//         bool MouseOnKnopka1 = SDL_HasIntersection(&KvadratNaCursore, &knopka1);
//         bool MouseOnKnopka2 = SDL_HasIntersection(&KvadratNaCursore, &knopka2);
//         bool MouseOnKnopka11 = SDL_HasIntersection(&KvadratNaCursore, &knopka11);
//         bool MouseOnSlider = SDL_HasIntersection(&KvadratNaCursore, &sliderHandle);
//         bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
//         bool MouseOnMusicScroll = SDL_HasIntersection(&KvadratNaCursore, &musicScrollHandle);
//         bool MouseOnCover = SDL_HasIntersection(&KvadratNaCursore, &coverRect);
//         bool MouseOnMenuButton1 = SDL_HasIntersection(&KvadratNaCursore, &menuButton1);
//         bool MouseOnMenuButton2 = SDL_HasIntersection(&KvadratNaCursore, &menuButton2);
//         bool MouseOnMenuButton3 = SDL_HasIntersection(&KvadratNaCursore, &menuButton3);
//         bool MouseOnMenuButton4 = SDL_HasIntersection(&KvadratNaCursore, &menuButton4);
//         bool MouseOnBackButton = SDL_HasIntersection(&KvadratNaCursore, &backButton);
//         std::vector<bool> MouseOnTowerCard(TOWER_TYPES, false);
//         for (int i = 0; i < TOWER_TYPES; ++i) {
//             MouseOnTowerCard[i] = SDL_HasIntersection(&KvadratNaCursore, &towerCards[i]);
//         }
//         std::vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
//         for (size_t i = 0; i < musicSquares.size(); ++i) {
//             MouseOnMusicSquare[i] = SDL_HasIntersection(&KvadratNaCursore, &musicSquares[i]);
//         }

//         if (scene == 1) {
//             Uint32 currentTime = SDL_GetTicks();
//             if (currentTime - lastEnemySpawn >= enemySpawnInterval && playerHealth > 0) {
//                 int enemyType = rand() % ENEMY_TYPES;
//                 Enemy enemy = {50.0f, 50.0f, enemySpeeds[enemyType], enemyHealths[enemyType], 0, true, enemyType};
//                 enemies.push_back(enemy);
//                 lastEnemySpawn = currentTime;
//             }

//             for (auto& enemy : enemies) {
//                 if (!enemy.active) continue;
//                 if (enemy.pathIndex >= enemyPath.size() - 1) {
//                     enemy.active = false;
//                     playerHealth--;
//                     if (playerHealth <= 0) {
//                         scene = -1;
//                         enemies.clear();
//                         towers.clear();
//                         projectiles.clear(); // Очистка снарядов
//                         playerHealth = 10;
//                         playerMoney = 100;
//                         selectedTowerType = -1;
//                         isPlacingTower = false;
//                     }
//                     continue;
//                 }
//                 SDL_Point target = enemyPath[enemy.pathIndex + 1];
//                 float dx = target.x - enemy.x;
//                 float dy = target.y - enemy.y;
//                 float distance = sqrt(dx * dx + dy * dy);
//                 if (distance < enemy.speed) {
//                     enemy.pathIndex++;
//                 } else {
//                     enemy.x += (dx / distance) * enemy.speed;
//                     enemy.y += (dy / distance) * enemy.speed;
//                 }
//             }

//             // Обновление башен: создание снарядов вместо прямого урона
//             for (auto& tower : towers) {
//                 if (!tower.active) continue;
//                 if (currentTime - tower.lastShot >= 1000.0f / tower.fireRate) {
//                     for (auto& enemy : enemies) {
//                         if (!enemy.active) continue;
//                         if (inRange(tower, enemy.x, enemy.y)) {
//                             // Создание снаряда
//                             Projectile proj;
//                             proj.x = tower.x + 25; // Центр башни
//                             proj.y = tower.y + 25;
//                             proj.speed = 5.0f; // Скорость снаряда
//                             proj.damage = towerDamages[tower.type];
//                             proj.target = &enemy;
//                             proj.active = true;
//                             projectiles.push_back(proj);
//                             tower.lastShot = currentTime;
//                             break;
//                         }
//                     }
//                 }
//             }

//             // Обновление снарядов
//             for (auto& proj : projectiles) {
//                 if (!proj.active || !proj.target->active) {
//                     proj.active = false;
//                     continue;
//                 }
//                 // Движение снаряда к цели
//                 float dx = proj.target->x - proj.x;
//                 float dy = proj.target->y - proj.y;
//                 float distance = sqrt(dx * dx + dy * dy);
//                 if (distance < proj.speed) {
//                     // Попадание
//                     proj.target->health -= proj.damage;
//                     proj.active = false;
//                     if (proj.target->health <= 0) {
//                         proj.target->active = false;
//                         playerMoney += 10;
//                     }
//                 } else {
//                     proj.x += (dx / distance) * proj.speed;
//                     proj.y += (dy / distance) * proj.speed;
//                 }
//             }

//             // Удаление неактивных снарядов
//             projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
//                 [](const Projectile& p) { return !p.active; }), projectiles.end());

//             if (healthText) SDL_DestroyTexture(healthText);
//             if (moneyText) SDL_DestroyTexture(moneyText);
//             healthText = createTextTexture(renderer, font, "Здоровье: " + std::to_string(playerHealth), textColor);
//             moneyText = createTextTexture(renderer, font, "Монеты: " + std::to_string(playerMoney), textColor);

//             // Обновление предпросмотра башни
//             if (isPlacingTower && selectedTowerType >= 0) {
//                 previewTower.x = mx - 25;
//                 previewTower.y = my - 25;
//                 bool valid = isValidPlacement(previewTower.x, previewTower.y, towers) && playerMoney >= towerCost;
//                 SDL_SetRenderDrawColor(renderer, valid ? validPlacementColor.r : invalidPlacementColor.r, valid ? validPlacementColor.g : invalidPlacementColor.g, valid ? validPlacementColor.b : validPlacementColor.b, valid ? validPlacementColor.a : invalidPlacementColor.a);
//                 SDL_RenderFillRect(renderer, &previewTower);
//             }
//         }

//         if (bgm && musicStarted && !isDraggingSlider) {
//             double musicDuration = Mix_MusicDuration(bgm);
//             double currentPosition = Mix_GetMusicPosition(bgm);
//             if (musicDuration > 0) {
//                 float progress = static_cast<float>(currentPosition) / musicDuration;
//                 sliderHandle.x = sliderTrack.x + static_cast<int>(progress * (sliderTrack.w - sliderHandle.w));
//             }
//             if (currentTimeText) SDL_DestroyTexture(currentTimeText);
//             currentTimeText = createTextTexture(renderer, font, formatTime(currentPosition), textColor);
//         }

//         if (MouseOnSliderTrack && bgm) {
//             if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
//             double musicDuration = Mix_MusicDuration(bgm);
//             if (musicDuration > 0) {
//                 float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
//                 double hoverPosition = progress * musicDuration;
//                 hoverTimeText = createTextTexture(renderer, font, formatTime(hoverPosition), textColor);
//             }
//         } else {
//             if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
//             hoverTimeText = nullptr;
//         }

//         if (!isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
//             float progress = static_cast<float>(musicScrollOffset) / (musicFiles.size() - maxVisibleSquares);
//             musicScrollHandle.y = musicScrollTrack.y + static_cast<int>(progress * (musicScrollTrack.h - musicScrollHandle.h));
//         }

//         if (needsScrolling) {
//             Uint32 currentTime = SDL_GetTicks();
//             if (currentTime - lastTextUpdate >= 50) {
//                 textOffset++;
//                 int textW, textH;
//                 SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
//                 if (textOffset >= textW - 300) {
//                     textOffset = 0;
//                 }
//                 lastTextUpdate = currentTime;
//             }
//         } else {
//             textOffset = 0;
//         }

//         SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
//         SDL_RenderClear(renderer);

//         if (scene == -1) {
//             SDL_Texture* titleText = createTextTexture(renderer, titleFont, "Музыкальный плеер", textColor);
//             if (titleText) {
//                 int tw, th;
//                 SDL_QueryTexture(titleText, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {400 - tw / 2, 150 - th / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 3, tr.y + 3, tw, th};
//                 SDL_SetTextureColorMod(titleText, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(titleText, shadowColor.a);
//                 SDL_RenderCopy(renderer, titleText, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(titleText, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(titleText, 255);
//                 SDL_RenderCopy(renderer, titleText, nullptr, &tr);
//                 SDL_DestroyTexture(titleText);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnMenuButton1 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton1 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton1 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &menuButton1);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &menuButton1);
//             SDL_Texture* btn1Text = createTextTexture(renderer, font, "Начать", textColor, 180);
//             if (btn1Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn1Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {menuButton1.x + (menuButton1.w - tw) / 2, menuButton1.y + (menuButton1.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn1Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn1Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn1Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn1Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn1Text, 255);
//                 SDL_RenderCopy(renderer, btn1Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn1Text);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnMenuButton2 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton2 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton2 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &menuButton2);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &menuButton2);
//             SDL_Texture* btn2Text = createTextTexture(renderer, font, "Настройки", textColor, 180);
//             if (btn2Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn2Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {menuButton2.x + (menuButton2.w - tw) / 2, menuButton2.y + (menuButton2.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn2Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn2Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn2Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn2Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn2Text, 255);
//                 SDL_RenderCopy(renderer, btn2Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn2Text);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnMenuButton3 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton3 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton3 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &menuButton3);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &menuButton3);
//             SDL_Texture* btn3Text = createTextTexture(renderer, font, "Выход", textColor, 180);
//             if (btn3Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn3Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {menuButton3.x + (menuButton3.w - tw) / 2, menuButton3.y + (menuButton3.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn3Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn3Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn3Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn3Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn3Text, 255);
//                 SDL_RenderCopy(renderer, btn3Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn3Text);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnMenuButton4 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton4 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton4 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &menuButton4);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &menuButton4);
//             SDL_Texture* btn4Text = createTextTexture(renderer, font, "TowerDefens", textColor, 180);
//             if (btn4Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn4Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {menuButton4.x + (menuButton4.w - tw) / 2, menuButton4.y + (menuButton4.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn4Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn4Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn4Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn4Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn4Text, 255);
//                 SDL_RenderCopy(renderer, btn4Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn4Text);
//             }
//         }
//         else if (scene == 0) {
//             SDL_Rect shadowRect = {coverRect.x + 5, coverRect.y + 5, coverRect.w, coverRect.h};
//             SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
//             SDL_RenderFillRect(renderer, &shadowRect);
//             SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
//             SDL_RenderFillRect(renderer, &coverRect);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &coverRect);
//             if (coverTexture) {
//                 SDL_RenderCopy(renderer, coverTexture, nullptr, &coverRect);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnKnopka1 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka1 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka1 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &knopka1);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &knopka1);
//             SDL_Texture* btn1Text = createTextTexture(renderer, font, "Выбрать папку", textColor, 180);
//             if (btn1Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn1Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {knopka1.x + (knopka1.w - tw) / 2, knopka1.y + (knopka1.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn1Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn1Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn1Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn1Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn1Text, 255);
//                 SDL_RenderCopy(renderer, btn1Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn1Text);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnKnopka2 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka2 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka2 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &knopka2);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &knopka2);
//             SDL_Texture* btn2Text = createTextTexture(renderer, font, "Выход", textColor, 180);
//             if (btn2Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn2Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {knopka2.x + (knopka2.w - tw) / 2, knopka2.y + (knopka2.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn2Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn2Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn2Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn2Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn2Text, 255);
//                 SDL_RenderCopy(renderer, btn2Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn2Text);
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnKnopka11 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka11 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka11 ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &knopka11);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &knopka11);
//             SDL_Texture* btn11Text = createTextTexture(renderer, font, Mix_PausedMusic() ? "Играть" : "Пауза", textColor, 100);
//             if (btn11Text) {
//                 int tw, th;
//                 SDL_QueryTexture(btn11Text, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {knopka11.x + (knopka11.w - tw) / 2, knopka11.y + (knopka11.h - th) / 2, tw, th};
//                 SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
//                 SDL_SetTextureColorMod(btn11Text, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(btn11Text, shadowColor.a);
//                 SDL_RenderCopy(renderer, btn11Text, nullptr, &shadowTr);
//                 SDL_SetTextureColorMod(btn11Text, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(btn11Text, 255);
//                 SDL_RenderCopy(renderer, btn11Text, nullptr, &tr);
//                 SDL_DestroyTexture(btn11Text);
//             }
//             if (trackText) {
//                 int textW, textH;
//                 SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
//                 SDL_Rect textRect = {300 - textOffset, 350, std::min(textW, 300), textH};
//                 SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textRect.w, textRect.h};
//                 SDL_Rect clipRect = {300, 350, 300, textH};
//                 SDL_RenderSetClipRect(renderer, &clipRect);
//                 SDL_SetTextureColorMod(trackText, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(trackText, shadowColor.a);
//                 SDL_RenderCopy(renderer, trackText, nullptr, &shadowRect);
//                 SDL_SetTextureColorMod(trackText, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(trackText, 255);
//                 SDL_RenderCopy(renderer, trackText, nullptr, &textRect);
//                 SDL_RenderSetClipRect(renderer, nullptr);
//             }
//             SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
//             SDL_RenderFillRect(renderer, &sliderTrack);
//             int handlePos = sliderHandle.x - sliderTrack.x;
//             SDL_Rect activePart = {sliderTrack.x, sliderTrack.y, handlePos + sliderHandle.w / 2, sliderTrack.h};
//             SDL_SetRenderDrawColor(renderer, sliderActiveColor.r, sliderActiveColor.g, sliderActiveColor.b, sliderActiveColor.a);
//             SDL_RenderFillRect(renderer, &activePart);
//             SDL_SetRenderDrawColor(renderer, sliderHandleColor.r, sliderHandleColor.g, sliderHandleColor.b, sliderHandleColor.a);
//             SDL_RenderFillRect(renderer, &sliderHandle);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &sliderHandle);
//             if (currentTimeText) {
//                 int textW, textH;
//                 SDL_QueryTexture(currentTimeText, nullptr, nullptr, &textW, &textH);
//                 SDL_Rect textRect = {sliderTrack.x - textW - 5, sliderTrack.y - textH / 2, textW, textH};
//                 SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
//                 SDL_SetTextureColorMod(currentTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(currentTimeText, shadowColor.a);
//                 SDL_RenderCopy(renderer, currentTimeText, nullptr, &shadowRect);
//                 SDL_SetTextureColorMod(currentTimeText, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(currentTimeText, 255);
//                 SDL_RenderCopy(renderer, currentTimeText, nullptr, &textRect);
//             }
//             if (totalTimeText) {
//                 int textW, textH;
//                 SDL_QueryTexture(totalTimeText, nullptr, nullptr, &textW, &textH);
//                 SDL_Rect textRect = {sliderTrack.x + sliderTrack.w + 5, sliderTrack.y - textH / 2, textW, textH};
//                 SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
//                 SDL_SetTextureColorMod(totalTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(totalTimeText, shadowColor.a);
//                 SDL_RenderCopy(renderer, totalTimeText, nullptr, &shadowRect);
//                 SDL_SetTextureColorMod(totalTimeText, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(totalTimeText, 255);
//                 SDL_RenderCopy(renderer, totalTimeText, nullptr, &textRect);
//             }
//             if (hoverTimeText) {
//                 int textW, textH;
//                 SDL_QueryTexture(hoverTimeText, nullptr, nullptr, &textW, &textH);
//                 SDL_Rect textRect = {mx - textW / 2, my - textH - 5, textW, textH};
//                 SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
//                 SDL_SetTextureColorMod(hoverTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
//                 SDL_SetTextureAlphaMod(hoverTimeText, shadowColor.a);
//                 SDL_RenderCopy(renderer, hoverTimeText, nullptr, &shadowRect);
//                 SDL_SetTextureColorMod(hoverTimeText, textColor.r, textColor.g, textColor.b);
//                 SDL_SetTextureAlphaMod(hoverTimeText, 255);
//                 SDL_RenderCopy(renderer, hoverTimeText, nullptr, &textRect);
//             }
//             SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
//             SDL_RenderFillRect(renderer, &musicScrollTrack);
//             SDL_SetRenderDrawColor(renderer, MouseOnMusicScroll ? sliderActiveColor.r : sliderHandleColor.r, MouseOnMusicScroll ? sliderActiveColor.g : sliderHandleColor.g, MouseOnMusicScroll ? sliderActiveColor.b : sliderHandleColor.b, 255);
//             SDL_RenderFillRect(renderer, &musicScrollHandle);
//             SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//             SDL_RenderDrawRect(renderer, &musicScrollHandle);
//             for (size_t i = 0; i < musicSquares.size(); ++i) {
//                 SDL_SetRenderDrawColor(renderer, MouseOnMusicSquare[i] ? buttonHoverColor.r : buttonColor.r, MouseOnMusicSquare[i] ? buttonHoverColor.g : buttonColor.g, MouseOnMusicSquare[i] ? buttonHoverColor.b : buttonHoverColor.b, 255);
//                 SDL_RenderFillRect(renderer, &musicSquares[i]);
//                 SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//                 SDL_RenderDrawRect(renderer, &musicSquares[i]);
//                 if (i + musicScrollOffset < musicFileTextures.size() && musicFileTextures[i + musicScrollOffset]) {
//                     int textW, textH;
//                     SDL_QueryTexture(musicFileTextures[i + musicScrollOffset], nullptr, nullptr, &textW, &textH);
//                     SDL_Rect textRect = {musicSquares[i].x + 5, musicSquares[i].y + (musicSquares[i].h - textH) / 2, textW, textH};
//                     SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
//                     SDL_Rect clipRect = {musicSquares[i].x + 5, musicSquares[i].y, 130, musicSquares[i].h};
//                     SDL_RenderSetClipRect(renderer, &clipRect);
//                     SDL_SetTextureColorMod(musicFileTextures[i + musicScrollOffset], shadowColor.r, shadowColor.g, shadowColor.b);
//                     SDL_SetTextureAlphaMod(musicFileTextures[i + musicScrollOffset], shadowColor.a);
//                     SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &shadowRect);
//                     SDL_SetTextureColorMod(musicFileTextures[i + musicScrollOffset], textColor.r, textColor.g, textColor.b);
//                     SDL_SetTextureAlphaMod(musicFileTextures[i + musicScrollOffset], 255);
//                     SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &textRect);
//                     SDL_RenderSetClipRect(renderer, nullptr);
//                 }
//             }
//         }
//         else if (scene == 1) {
//             SDL_SetRenderDrawColor(renderer, pathColor.r, pathColor.g, pathColor.b, pathColor.a);
//             for (size_t i = 0; i < enemyPath.size() - 1; ++i) {
//                 SDL_RenderDrawLine(renderer, enemyPath[i].x, enemyPath[i].y, enemyPath[i + 1].x, enemyPath[i + 1].y);
//             }
//             for (const auto& enemy : enemies) {
//                 if (!enemy.active) continue;
//                 SDL_Rect enemyRect = {static_cast<int>(enemy.x - 10), static_cast<int>(enemy.y - 10), 20, 20};
//                 SDL_SetRenderDrawColor(renderer, enemyColor.r, enemyColor.g, enemyColor.b, enemyColor.a);
//                 SDL_RenderFillRect(renderer, &enemyRect);
//             }
//             for (const auto& tower : towers) {
//                 if (!tower.active) continue;
//                 SDL_Rect towerRect = {tower.x, tower.y, 50, 50};
//                 SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 255);
//                 SDL_RenderFillRect(renderer, &towerRect);
//                 SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 50);
//                 for (int i = 0; i < 360; i++) {
//                     float rad = i * M_PI / 180.0f;
//                     int x1 = tower.x + 25 + cos(rad) * towerRanges[tower.type];
//                     int y1 = tower.y + 25 + sin(rad) * towerRanges[tower.type];
//                     int x2 = tower.x + 25 + cos((i + 1) * M_PI / 180.0f) * towerRanges[tower.type];
//                     int y2 = tower.y + 25 + sin((i + 1) * M_PI / 180.0f) * towerRanges[tower.type];
//                     SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
//                 }
//             }
//             // Рендеринг снарядов
//             SDL_SetRenderDrawColor(renderer, projectileColor.r, projectileColor.g, projectileColor.b, projectileColor.a);
//             for (const auto& proj : projectiles) {
//                 if (!proj.active) continue;
//                 renderCircle(renderer, static_cast<int>(proj.x), static_cast<int>(proj.y), 3);
//             }
//             if (healthText) {
//                 int textW, textH;
//                 SDL_QueryTexture(healthText, nullptr, nullptr, &textW, &textH);
//                 SDL_Rect textRect = {10, 10, textW, textH};
//                 SDL_RenderCopy(renderer, healthText, nullptr, &textRect);
//             }
//             if (moneyText) {
//                 int textW, textH;
//                 SDL_QueryTexture(moneyText, nullptr, nullptr, &textW, &textH);
//                 SDL_Rect textRect = {10, 40, textW, textH};
//                 SDL_RenderCopy(renderer, moneyText, nullptr, &textRect);
//             }
//             for (int i = 0; i < TOWER_TYPES; ++i) {
//                 SDL_SetRenderDrawColor(renderer, MouseOnTowerCard[i] ? buttonHoverColor.r : buttonColor.r, MouseOnTowerCard[i] ? buttonHoverColor.g : buttonColor.g, MouseOnTowerCard[i] ? buttonHoverColor.b : buttonHoverColor.b, 255);
//                 SDL_RenderFillRect(renderer, &towerCards[i]);
//                 SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
//                 SDL_RenderDrawRect(renderer, &towerCards[i]);
//                 SDL_Texture* cardText = createTextTexture(renderer, font, towerNames[i] + "\n" + std::to_string(towerCost), textColor, 60);
//                 if (cardText) {
//                     int tw, th;
//                     SDL_QueryTexture(cardText, nullptr, nullptr, &tw, &th);
//                     SDL_Rect tr = {towerCards[i].x + (towerCards[i].w - tw) / 2, towerCards[i].y + (towerCards[i].h - th) / 2, tw, th};
//                     SDL_RenderCopy(renderer, cardText, nullptr, &tr);
//                     SDL_DestroyTexture(cardText);
//                 }
//             }
//             SDL_SetRenderDrawColor(renderer, MouseOnBackButton ? buttonHoverColor.r : buttonColor.r, MouseOnBackButton ? buttonHoverColor.g : buttonColor.g, MouseOnBackButton ? buttonHoverColor.b : buttonHoverColor.b, 255);
//             SDL_RenderFillRect(renderer, &backButton);
//             SDL_Texture* backText = createTextTexture(renderer, font, "Назад", textColor, 100);
//             if (backText) {
//                 int tw, th;
//                 SDL_QueryTexture(backText, nullptr, nullptr, &tw, &th);
//                 SDL_Rect tr = {backButton.x + (backButton.w - tw) / 2, backButton.y + (backButton.h - th) / 2, tw, th};
//                 SDL_RenderCopy(renderer, backText, nullptr, &tr);
//                 SDL_DestroyTexture(backText);
//             }
//             // Рендеринг предпросмотра башни должен быть последним, чтобы перекрывать другие элементы
//             if (isPlacingTower && selectedTowerType >= 0) {
//                 previewTower.x = mx - 25;
//                 previewTower.y = my - 25;
//                 bool valid = isValidPlacement(previewTower.x, previewTower.y, towers) && playerMoney >= towerCost;
//                 SDL_SetRenderDrawColor(renderer, valid ? validPlacementColor.r : invalidPlacementColor.r, valid ? validPlacementColor.g : invalidPlacementColor.g, valid ? validPlacementColor.b : validPlacementColor.b, valid ? validPlacementColor.a : invalidPlacementColor.a);
//                 SDL_RenderFillRect(renderer, &previewTower);
//                 // Добавить отображение радиуса действия
//                 SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 50);
//                 for (int i = 0; i < 360; i++) {
//                     float rad = i * M_PI / 180.0f;
//                     int x1 = previewTower.x + 25 + cos(rad) * towerRanges[selectedTowerType];
//                     int y1 = previewTower.y + 25 + sin(rad) * towerRanges[selectedTowerType];
//                     int x2 = previewTower.x + 25 + cos((i + 1) * M_PI / 180.0f) * towerRanges[selectedTowerType];
//                     int y2 = previewTower.y + 25 + sin((i + 1) * M_PI / 180.0f) * towerRanges[selectedTowerType];
//                     SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
//                 }
//             }
//         }

//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//             else if (event.type == SDL_KEYDOWN) {
//                 if (scene == 0) {
//                     if (event.key.keysym.sym == SDLK_1 && bgm && !musicStarted) {
//                         if (Mix_PlayMusic(bgm, -1) == -1) {
//                             std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
//                         } else {
//                             musicStarted = true;
//                         }
//                     }
//                     else if (event.key.keysym.sym == SDLK_SPACE) {
//                         if (Mix_PausedMusic()) {
//                             Mix_ResumeMusic();
//                         } else {
//                             Mix_PauseMusic();
//                         }
//                     }
//                     else if (event.key.keysym.sym == SDLK_UP && !musicFiles.empty()) {
//                         if (currentTrackIndex > 0) {
//                             currentTrackIndex--;
//                         } else {
//                             currentTrackIndex = musicFiles.size() - 1;
//                         }
//                         musicPath = musicFiles[currentTrackIndex];
//                         if (musicStarted) {
//                             Mix_HaltMusic();
//                             musicStarted = false;
//                         }
//                         if (bgm) {
//                             Mix_FreeMusic(bgm);
//                         }
//                         bgm = Mix_LoadMUS(musicPath.c_str());
//                         if (!bgm) {
//                             std::cerr << "Failed to load new bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
//                         } else {
//                             if (Mix_PlayMusic(bgm, -1) == -1) {
//                                 std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
//                             } else {
//                                 musicStarted = true;
//                             }
//                         }
//                         if (trackText) SDL_DestroyTexture(trackText);
//                         currentTrack = fs::path(musicPath).filename().string();
//                         trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
//                         needsScrolling = currentTrack.length() > 15;
//                         textOffset = 0;
//                         if (totalTimeText) SDL_DestroyTexture(totalTimeText);
//                         musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
//                         totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
//                         if (coverTexture) SDL_DestroyTexture(coverTexture);
//                         coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
//                         if (fs::exists(coverPath)) {
//                             SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
//                             if (coverSurface) {
//                                 coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
//                                 SDL_FreeSurface(coverSurface);
//                             }
//                         }
//                         std::ofstream outFile("music_path.txt");
//                         if (outFile.is_open()) {
//                             outFile << musicPath << "\n" << folderPath;
//                             outFile.close();
//                         }
//                     }
//                     else if (event.key.keysym.sym == SDLK_DOWN && !musicFiles.empty()) {
//                         if (currentTrackIndex < musicFiles.size() - 1) {
//                             currentTrackIndex++;
//                         } else {
//                             currentTrackIndex = 0;
//                         }
//                         musicPath = musicFiles[currentTrackIndex];
//                         if (musicStarted) {
//                             Mix_HaltMusic();
//                             musicStarted = false;
//                         }
//                         if (bgm) {
//                             Mix_FreeMusic(bgm);
//                         }
//                         bgm = Mix_LoadMUS(musicPath.c_str());
//                         if (!bgm) {
//                             std::cerr << "Failed to load new bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
//                         } else {
//                             if (Mix_PlayMusic(bgm, -1) == -1) {
//                                 std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
//                             } else {
//                                 musicStarted = true;
//                             }
//                         }
//                         if (trackText) SDL_DestroyTexture(trackText);
//                         currentTrack = fs::path(musicPath).filename().string();
//                         trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
//                         needsScrolling = currentTrack.length() > 15;
//                         textOffset = 0;
//                         if (totalTimeText) SDL_DestroyTexture(totalTimeText);
//                         musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
//                         totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
//                         if (coverTexture) SDL_DestroyTexture(coverTexture);
//                         coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
//                         if (fs::exists(coverPath)) {
//                             SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
//                             if (coverSurface) {
//                                 coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
//                                 SDL_FreeSurface(coverSurface);
//                             }
//                         }
//                         std::ofstream outFile("music_path.txt");
//                         if (outFile.is_open()) {
//                             outFile << musicPath << "\n" << folderPath;
//                             outFile.close();
//                         }
//                     }
//                     else if (event.key.keysym.sym == SDLK_LEFT && bgm && musicStarted) {
//                         double currentPosition = Mix_GetMusicPosition(bgm);
//                         double newPosition = std::max(0.0, currentPosition - 5.0);
//                         Mix_SetMusicPosition(newPosition);
//                     }
//                     else if (event.key.keysym.sym == SDLK_RIGHT && bgm && musicStarted) {
//                         double currentPosition = Mix_GetMusicPosition(bgm);
//                         double musicDuration = Mix_MusicDuration(bgm);
//                         double newPosition = std::min(musicDuration, currentPosition + 5.0);
//                         Mix_SetMusicPosition(newPosition);
//                     }
//                 }
//             }
//             else if (event.type == SDL_MOUSEBUTTONDOWN) {
//                 if (scene == -1) {
//                     if (event.button.button == SDL_BUTTON_LEFT) {
//                         if (MouseOnMenuButton1) {
//                             scene = 0;
//                         }
//                         else if (MouseOnMenuButton2) {
//                             std::cout << "Открыты настройки (функционал не реализован)" << std::endl;
//                         }
//                         else if (MouseOnMenuButton3) {
//                             running = false;
//                         }
//                         else if (MouseOnMenuButton4) {
//                             scene = 1;
//                             enemies.clear();
//                             towers.clear();
//                             projectiles.clear(); // Очистка снарядов
//                             playerHealth = 10;
//                             playerMoney = 100;
//                             selectedTowerType = -1;
//                             isPlacingTower = false;
//                         }
//                     }
//                 }
//                 else if (scene == 0) {
//                     if (event.button.button == SDL_BUTTON_LEFT) {
//                         if (MouseOnKnopka1) {
//                             const char* selectedFolder = tinyfd_selectFolderDialog("Выберите папку с музыкой", "");
//                             if (selectedFolder) {
//                                 folderPath = selectedFolder;
//                                 musicFiles.clear();
//                                 musicSquares.clear();
//                                 for (auto& texture : musicFileTextures) {
//                                     if (texture) SDL_DestroyTexture(texture);
//                                 }
//                                 musicFileTextures.clear();
//                                 currentTrackIndex = 0;
//                                 for (const auto& entry : fs::directory_iterator(folderPath)) {
//                                     if (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav") {
//                                         musicFiles.push_back(entry.path().string());
//                                         std::string filename = fs::path(entry.path()).filename().string();
//                                         SDL_Texture* textTexture = createTextTexture(renderer, font, filename, textColor, 130);
//                                         musicFileTextures.push_back(textTexture);
//                                     }
//                                 }
//                                 musicScrollOffset = 0;
//                                 musicSquares.clear();
//                                 for (size_t i = 0; i < musicFiles.size() && i < maxVisibleSquares; ++i) {
//                                     musicSquares.push_back({650, static_cast<int>(50 + i * 55), 140, 50});
//                                 }
//                                 if (!musicFiles.empty()) {
//                                     musicPath = musicFiles[0];
//                                     if (musicStarted) {
//                                         Mix_HaltMusic();
//                                         musicStarted = false;
//                                     }
//                                     if (bgm) {
//                                         Mix_FreeMusic(bgm);
//                                     }
//                                     bgm = Mix_LoadMUS(musicPath.c_str());
//                                     if (trackText) SDL_DestroyTexture(trackText);
//                                     currentTrack = fs::path(musicPath).filename().string();
//                                     trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
//                                     needsScrolling = currentTrack.length() > 15;
//                                     textOffset = 0;
//                                     if (totalTimeText) SDL_DestroyTexture(totalTimeText);
//                                     musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
//                                     totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
//                                     if (coverTexture) SDL_DestroyTexture(coverTexture);
//                                     coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
//                                     if (fs::exists(coverPath)) {
//                                         SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
//                                         if (coverSurface) {
//                                             coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
//                                             SDL_FreeSurface(coverSurface);
//                                         }
//                                     }
//                                 }
//                                 std::ofstream outFile("music_path.txt");
//                                 if (outFile.is_open()) {
//                                     outFile << musicPath << "\n" << folderPath;
//                                     outFile.close();
//                                 }
//                             }
//                         }
//                         else if (MouseOnKnopka2) {
//                             running = false;
//                         }
//                         else if (MouseOnKnopka11) {
//                             if (Mix_PausedMusic()) {
//                                 Mix_ResumeMusic();
//                             } else {
//                                 Mix_PauseMusic();
//                             }
//                         }
//                         else if (MouseOnSlider) {
//                             isDraggingSlider = true;
//                         }
//                         else if (MouseOnMusicScroll) {
//                             isDraggingMusicScroll = true;
//                         }
//                         else if (MouseOnSliderTrack && bgm) {
//                             double musicDuration = Mix_MusicDuration(bgm);
//                             if (musicDuration > 0) {
//                                 float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
//                                 double newPosition = progress * musicDuration;
//                                 Mix_SetMusicPosition(newPosition);
//                             }
//                         }
//                         else if (MouseOnCover) {
//                             const char* selectedImage = tinyfd_openFileDialog("Выберите обложку", "", 0, nullptr, nullptr, 0);
//                             if (selectedImage) {
//                                 SDL_Surface* newCoverSurface = IMG_Load(selectedImage);
//                                 if (newCoverSurface) {
//                                     if (coverTexture) SDL_DestroyTexture(coverTexture);
//                                     coverTexture = SDL_CreateTextureFromSurface(renderer, newCoverSurface);
//                                     coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
//                                     IMG_SavePNG(newCoverSurface, coverPath.c_str());
//                                     SDL_FreeSurface(newCoverSurface);
//                                 }
//                             }
//                         }
//                         else {
//                             for (size_t i = 0; i < musicSquares.size(); ++i) {
//                                 if (MouseOnMusicSquare[i] && i + musicScrollOffset < musicFiles.size()) {
//                                     currentTrackIndex = i + musicScrollOffset;
//                                     musicPath = musicFiles[currentTrackIndex];
//                                     if (musicStarted) {
//                                         Mix_HaltMusic();
//                                         musicStarted = false;
//                                     }
//                                     if (bgm) {
//                                         Mix_FreeMusic(bgm);
//                                     }
//                                     bgm = Mix_LoadMUS(musicPath.c_str());
//                                     if (!bgm) {
//                                         std::cerr << "Failed to load new bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
//                                     } else {
//                                         if (Mix_PlayMusic(bgm, -1) == -1) {
//                                             std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
//                                         } else {
//                                             musicStarted = true;
//                                         }
//                                     }
//                                     if (trackText) SDL_DestroyTexture(trackText);
//                                     currentTrack = fs::path(musicPath).filename().string();
//                                     trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
//                                     needsScrolling = currentTrack.length() > 15;
//                                     textOffset = 0;
//                                     if (totalTimeText) SDL_DestroyTexture(totalTimeText);
//                                     musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
//                                     totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
//                                     if (coverTexture) SDL_DestroyTexture(coverTexture);
//                                     coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
//                                     if (fs::exists(coverPath)) {
//                                         SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
//                                         if (coverSurface) {
//                                             coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
//                                             SDL_FreeSurface(coverSurface);
//                                         }
//                                     }
//                                     std::ofstream outFile("music_path.txt");
//                                     if (outFile.is_open()) {
//                                         outFile << musicPath << "\n" << folderPath;
//                                         outFile.close();
//                                     }
//                                     break;
//                                 }
//                             }
//                         }
//                     }
//                 }
//                 else if (scene == 1) {
//                     if (event.button.button == SDL_BUTTON_LEFT) {
//                         if (MouseOnBackButton) {
//                             scene = -1;
//                             enemies.clear();
//                             towers.clear();
//                             projectiles.clear(); // Очистка снарядов
//                             playerHealth = 10;
//                             playerMoney = 100;
//                             selectedTowerType = -1;
//                             isPlacingTower = false;
//                         }
//                         else if (isPlacingTower && selectedTowerType >= 0) {
//                             // Второй клик: размещение башни
//                             int towerX = mx - 25;
//                             int towerY = my - 25;
//                             if (isValidPlacement(towerX, towerY, towers) && playerMoney >= towerCost) {
//                                 Tower tower = {towerX, towerY, towerRanges[selectedTowerType], towerDamages[selectedTowerType], towerFireRates[selectedTowerType], 0.0f, true, selectedTowerType};
//                                 towers.push_back(tower);
//                                 playerMoney -= towerCost;
//                                 selectedTowerType = -1;
//                                 isPlacingTower = false;
//                             }
//                         }
//                         else {
//                             // Первый клик: выбор башни
//                             for (int i = 0; i < TOWER_TYPES; ++i) {
//                                 if (MouseOnTowerCard[i] && playerMoney >= towerCost) {
//                                     selectedTowerType = i;
//                                     isPlacingTower = true;
//                                     break;
//                                 }
//                             }
//                         }
//                     }
//                     else if (event.button.button == SDL_BUTTON_RIGHT && isPlacingTower) {
//                         // Отмена выбора башни
//                         selectedTowerType = -1;
//                         isPlacingTower = false;
//                     }
//                 }
//             }
//             else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
//                 if (scene == 0) {
//                     if (isDraggingSlider) {
//                         isDraggingSlider = false;
//                         if (bgm && musicStarted) {
//                             double musicDuration = Mix_MusicDuration(bgm);
//                             if (musicDuration > 0) {
//                                 float progress = static_cast<float>(sliderHandle.x - sliderTrack.x) / (sliderTrack.w - sliderHandle.w);
//                                 double newPosition = progress * musicDuration;
//                                 Mix_SetMusicPosition(newPosition);
//                             }
//                         }
//                     }
//                     else if (isDraggingMusicScroll) {
//                         isDraggingMusicScroll = false;
//                     }
//                 }
//             }
//             else if (event.type == SDL_MOUSEMOTION) {
//                 if (scene == 0) {
//                     if (isDraggingSlider) {
//                         int newX = mx - sliderHandle.w / 2;
//                         if (newX < sliderTrack.x) newX = sliderTrack.x;
//                         if (newX > sliderTrack.x + sliderTrack.w - sliderHandle.w) newX = sliderTrack.x + sliderTrack.w - sliderHandle.w;
//                         sliderHandle.x = newX;
//                     }
//                     else if (isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
//                         int newY = my - musicScrollHandle.h / 2;
//                         if (newY < musicScrollTrack.y) newY = musicScrollTrack.y;
//                         if (newY > musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h) newY = musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h;
//                         musicScrollHandle.y = newY;
//                         float progress = static_cast<float>(musicScrollHandle.y - musicScrollTrack.y) / (musicScrollTrack.h - musicScrollHandle.h);
//                         musicScrollOffset = static_cast<int>(progress * (musicFiles.size() - maxVisibleSquares));
//                         musicSquares.clear();
//                         for (size_t i = musicScrollOffset; i < musicFiles.size() && i < musicScrollOffset + maxVisibleSquares; ++i) {
//                             musicSquares.push_back({650, static_cast<int>(50 + (i - musicScrollOffset) * 55), 140, 50});
//                         }
//                     }
//                 }
//             }
//         }

//         SDL_RenderPresent(renderer);
//         SDL_Delay(16);
//     }

//     if (bgm) Mix_FreeMusic(bgm);
//     if (trackText) SDL_DestroyTexture(trackText);
//     if (currentTimeText) SDL_DestroyTexture(currentTimeText);
//     if (totalTimeText) SDL_DestroyTexture(totalTimeText);
//     if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
//     if (coverTexture) SDL_DestroyTexture(coverTexture);
//     if (healthText) SDL_DestroyTexture(healthText);
//     if (moneyText) SDL_DestroyTexture(moneyText);
//     for (auto& texture : musicFileTextures) {
//         if (texture) SDL_DestroyTexture(texture);
//     }
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     TTF_CloseFont(font);
//     TTF_CloseFont(trackFont);
//     TTF_CloseFont(titleFont);
//     TTF_Quit();
//     Mix_CloseAudio();
//     IMG_Quit();
//     SDL_Quit();
//     return 0;
// }





#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <functional>
#include <filesystem>
#include <string>
#include <algorithm>
#include <fstream>
#include "tinyfiledialogs.h"

namespace fs = std::filesystem;

// Определяем цвета для интерфейса и игры
SDL_Color bgColor = {123, 123, 123, 255}; // Фон по твоему стилю (серый)
SDL_Color buttonColor = {255, 0, 100, 255}; // Твой цвет кнопок
SDL_Color buttonHoverColor = {170, 170, 255, 255}; // Твой цвет при наведении
SDL_Color textColor = {255, 255, 255, 255}; // Белый для текста
SDL_Color shadowColor = {0, 0, 0, 128}; // Полупрозрачная тень
SDL_Color sliderTrackColor = {68, 68, 68, 255}; // Трек слайдера
SDL_Color sliderActiveColor = {102, 102, 102, 255}; // Активный трек
SDL_Color sliderHandleColor = {255, 255, 255, 255}; // Ручка слайдера
SDL_Color borderColor = {0, 0, 0, 255}; // Черная обводка
SDL_Color pathColor = {100, 100, 100, 255}; // Путь для врагов
SDL_Color enemyColor = {255, 0, 0, 255}; // Красный для врагов
SDL_Color towerColor = {0, 255, 0, 255}; // Зеленый для башен
SDL_Color projectileColor = {255, 255, 0, 255}; // Желтый для снарядов
SDL_Color validPlacementColor = {0, 255, 0, 128}; // Зеленый для размещения
SDL_Color invalidPlacementColor = {255, 0, 0, 128}; // Красный для недопустимого

// Функция для рендеринга текста (используем SDL_ttf)
SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int maxWidth = -1) {
    std::string displayText = text;
    if (maxWidth > 0) {
        int w;
        TTF_SizeUTF8(font, text.c_str(), &w, nullptr);
        if (w > maxWidth) {
            displayText = text;
            while (TTF_SizeUTF8(font, (displayText + "...").c_str(), &w, nullptr), w > maxWidth && !displayText.empty()) {
                displayText.pop_back();
            }
            displayText += "...";
        }
    }
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, displayText.c_str(), color);
    if (!textSurface) {
        std::cerr << "TTF_RenderUTF8_Blended Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }
    return textTexture;
}

// Форматирование времени для слайдера
std::string formatTime(double seconds) {
    int totalSeconds = static_cast<int>(seconds);
    int minutes = totalSeconds / 60;
    int secs = totalSeconds % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}

// Структуры для Tower Defense
struct Enemy {
    float x, y;
    float speed;
    int health;
    int pathIndex;
    bool active;
    int type;
};

struct Tower {
    int x, y;
    int range;
    int damage;
    float fireRate;
    float lastShot;
    bool active;
    int type;
};

struct Projectile {
    float x, y;
    float speed;
    int damage;
    Enemy* target;
    bool active;
};

// Определяем типы врагов и башен
const int ENEMY_TYPES = 10;
float enemySpeeds[ENEMY_TYPES] = {2.0f, 1.5f, 0.8f, 3.0f, 1.0f, 2.5f, 0.5f, 1.8f, 2.2f, 1.2f};
int enemyHealths[ENEMY_TYPES] = {2, 5, 10, 1, 7, 3, 15, 4, 6, 8};

const int TOWER_TYPES = 10;
int towerRanges[TOWER_TYPES] = {100, 120, 80, 150, 90, 110, 130, 100, 140, 95};
int towerDamages[TOWER_TYPES] = {1, 2, 1, 3, 1, 2, 4, 1, 3, 2};
float towerFireRates[TOWER_TYPES] = {1.0f, 0.5f, 2.0f, 0.8f, 1.5f, 1.2f, 0.6f, 2.5f, 0.9f, 1.8f};
std::string towerNames[TOWER_TYPES] = {"Basic", "Cannon", "Laser", "Slow", "Sniper", "Multi", "Bomb", "Freeze", "Poison", "Tesla"};

// Проверка, в радиусе ли враг
bool inRange(Tower& tower, float px, float py) {
    float dx = tower.x + 25 - px;
    float dy = tower.y + 25 - py;
    return sqrt(dx * dx + dy * dy) <= tower.range;
}

// Проверка, можно ли поставить башню
bool isValidPlacement(int x, int y, const std::vector<Tower>& towers, int towerSize = 50) {
    SDL_Rect newTower = {x, y, towerSize, towerSize};
    for (const auto& tower : towers) {
        if (tower.active) {
            SDL_Rect existingTower = {tower.x, tower.y, towerSize, towerSize};
            if (SDL_HasIntersection(&newTower, &existingTower)) {
                return false;
            }
        }
    }
    return true;
}

// Рендеринг круга для снарядов
void renderCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Устанавливаем локализацию для русских символов
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Инициализация SDL (видео + аудио)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Инициализация SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer не инициализирован! Ошибка: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Инициализация SDL_image для PNG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Инициализация SDL_ttf для текста
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Загружаем шрифты (используем Arial, как в примере)
    TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
    TTF_Font* trackFont = TTF_OpenFont("arial.ttf", 40);
    TTF_Font* titleFont = TTF_OpenFont("arial.ttf", 48);
    if (!font || !trackFont || !titleFont) {
        std::cerr << "Ошибка загрузки шрифта: " << TTF_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Создаем окно
    SDL_Window* window = SDL_CreateWindow(
        "Музыкальный плеер с Tower Defense",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 750,
        SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_CloseFont(titleFont);
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Создаем рендерер
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_CloseFont(titleFont);
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Загружаем музыку
    std::string musicPath = "muzika.mp3";
    std::string folderPath;
    std::ifstream musicPathFile("music_path.txt");
    if (musicPathFile.is_open()) {
        std::getline(musicPathFile, musicPath);
        std::getline(musicPathFile, folderPath);
        musicPathFile.close();
    }

    Mix_Music* bgm = Mix_LoadMUS(musicPath.c_str());
    if (!bgm) {
        std::cerr << "Ошибка загрузки музыки: " << Mix_GetError() << std::endl;
    }

    // Загружаем список треков из папки
    std::vector<std::string> musicFiles;
    size_t currentTrackIndex = 0;
    if (!folderPath.empty() && fs::exists(folderPath)) {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav") {
                musicFiles.push_back(entry.path().string());
                if (entry.path().string() == musicPath) {
                    currentTrackIndex = musicFiles.size() - 1;
                }
            }
        }
    }

    // Загружаем текстуру для кнопки (твоя ZnakMuziki.png)
    SDL_Surface* surface = IMG_Load("ZnakMuziki.png");
    if (!surface) {
        std::cerr << "Ошибка загрузки ZnakMuziki.png: " << IMG_GetError() << std::endl;
        Mix_FreeMusic(bgm);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_CloseFont(titleFont);
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* btnTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!btnTexture) {
        std::cerr << "Ошибка создания текстуры: " << SDL_GetError() << std::endl;
        Mix_FreeMusic(bgm);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_CloseFont(titleFont);
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Твои кнопки
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

    // Кнопки меню
    SDL_Rect menuButton1 {300, 300, 200, 75};
    SDL_Rect menuButton2 {300, 400, 200, 75};
    SDL_Rect menuButton3 {300, 500, 200, 75};
    SDL_Rect menuButton4 {300, 600, 200, 75};

    // Слайдер и элементы плеера
    SDL_Rect knopka11 {340, 550, 120, 75};
    SDL_Rect sliderTrack {300, 500, 200, 10};
    SDL_Rect sliderHandle {300, 495, 10, 20};
    bool isDraggingSlider = false;
    SDL_Rect musicScrollTrack {790, 50, 10, 385};
    SDL_Rect musicScrollHandle {790, 50, 10, 20};
    bool isDraggingMusicScroll = false;
    int musicScrollOffset = 0;
    const int maxVisibleSquares = 7;
    std::vector<SDL_Rect> musicSquares;
    for (size_t i = 0; i < musicFiles.size() && i < maxVisibleSquares; ++i) {
        musicSquares.push_back({650, static_cast<int>(50 + i * 55), 140, 50});
    }
    std::vector<SDL_Texture*> musicFileTextures;
    for (const auto& file : musicFiles) {
        std::string filename = fs::path(file).filename().string();
        SDL_Texture* textTexture = createTextTexture(renderer, font, filename, textColor, 130);
        musicFileTextures.push_back(textTexture);
    }

    // Текущий трек и его текст
    std::string currentTrack = fs::path(musicPath).filename().string();
    SDL_Texture* trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
    int textOffset = 0;
    Uint32 lastTextUpdate = SDL_GetTicks();
    bool needsScrolling = currentTrack.length() > 15;

    // Текущее и общее время трека
    SDL_Texture* currentTimeText = nullptr;
    SDL_Texture* totalTimeText = nullptr;
    SDL_Texture* hoverTimeText = nullptr;
    double musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
    totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
    currentTimeText = createTextTexture(renderer, font, "00:00", textColor);

    // Обложка альбома
    SDL_Rect coverRect {300, 100, 200, 200};
    SDL_Texture* coverTexture = nullptr;
    std::string coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
    if (fs::exists(coverPath)) {
        SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
        if (coverSurface) {
            coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
            SDL_FreeSurface(coverSurface);
        }
    }

    // Путь врагов для Tower Defense
    std::vector<SDL_Point> enemyPath = {{50, 50}, {700, 50}, {700, 300}, {50, 300}, {50, 550}, {700, 550}};
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    Uint32 lastEnemySpawn = SDL_GetTicks();
    const Uint32 enemySpawnInterval = 2000;
    std::vector<Tower> towers;
    int playerHealth = 10;
    int playerMoney = 100;
    const int towerCost = 50;
    SDL_Texture* healthText = nullptr;
    SDL_Texture* moneyText = nullptr;
    SDL_Rect backButton {650, 650, 120, 75};

    // Карточки башен
    std::vector<SDL_Rect> towerCards(TOWER_TYPES);
    for (int i = 0; i < TOWER_TYPES; ++i) {
        towerCards[i] = {10 + i * 75, 650, 70, 90};
    }

    int selectedTowerType = -1;
    SDL_Rect previewTower = {0, 0, 50, 50};
    bool isPlacingTower = false;

    // Курсорный прямоугольник
    SDL_Rect KvadratNaCursore = {0, 0, 2, 2};

    // Переменные состояния
    int scene = -1; // -1: меню, 0: плеер, 1: Tower Defense
    bool musicStarted = false;
    bool running = true;
    SDL_Event event;

    while (running) {
        // Обновляем позицию курсора
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        KvadratNaCursore.x = mx - KvadratNaCursore.w / 2;
        KvadratNaCursore.y = my - KvadratNaCursore.h / 2;

        // Проверяем клавиатуру
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_ESCAPE]) {
            if (scene == -1) {
                running = false; // Выход из программы
            } else {
                scene = -1; // Возврат в меню
                enemies.clear();
                towers.clear();
                projectiles.clear();
                playerHealth = 10;
                playerMoney = 100;
                selectedTowerType = -1;
                isPlacingTower = false;
            }
        }

        // Проверяем наведение на кнопки
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
        bool MouseOnKnopka11 = SDL_HasIntersection(&KvadratNaCursore, &knopka11);
        bool MouseOnSlider = SDL_HasIntersection(&KvadratNaCursore, &sliderHandle);
        bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
        bool MouseOnMusicScroll = SDL_HasIntersection(&KvadratNaCursore, &musicScrollHandle);
        bool MouseOnCover = SDL_HasIntersection(&KvadratNaCursore, &coverRect);
        bool MouseOnMenuButton1 = SDL_HasIntersection(&KvadratNaCursore, &menuButton1);
        bool MouseOnMenuButton2 = SDL_HasIntersection(&KvadratNaCursore, &menuButton2);
        bool MouseOnMenuButton3 = SDL_HasIntersection(&KvadratNaCursore, &menuButton3);
        bool MouseOnMenuButton4 = SDL_HasIntersection(&KvadratNaCursore, &menuButton4);
        bool MouseOnBackButton = SDL_HasIntersection(&KvadratNaCursore, &backButton);
        std::vector<bool> MouseOnTowerCard(TOWER_TYPES, false);
        for (int i = 0; i < TOWER_TYPES; ++i) {
            MouseOnTowerCard[i] = SDL_HasIntersection(&KvadratNaCursore, &towerCards[i]);
        }
        std::vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
        for (size_t i = 0; i < musicSquares.size(); ++i) {
            MouseOnMusicSquare[i] = SDL_HasIntersection(&KvadratNaCursore, &musicSquares[i]);
        }

        // Логика Tower Defense
        if (scene == 1) {
            Uint32 currentTime = SDL_GetTicks();
            // Спавн врагов
            if (currentTime - lastEnemySpawn >= enemySpawnInterval && playerHealth > 0) {
                int enemyType = rand() % ENEMY_TYPES;
                Enemy enemy = {50.0f, 50.0f, enemySpeeds[enemyType], enemyHealths[enemyType], 0, true, enemyType};
                enemies.push_back(enemy);
                lastEnemySpawn = currentTime;
            }

            // Движение врагов
            for (auto& enemy : enemies) {
                if (!enemy.active) continue;
                if (enemy.pathIndex >= enemyPath.size() - 1) {
                    enemy.active = false;
                    playerHealth--;
                    if (playerHealth <= 0) {
                        scene = -1;
                        enemies.clear();
                        towers.clear();
                        projectiles.clear();
                        playerHealth = 10;
                        playerMoney = 100;
                        selectedTowerType = -1;
                        isPlacingTower = false;
                    }
                    continue;
                }
                SDL_Point target = enemyPath[enemy.pathIndex + 1];
                float dx = target.x - enemy.x;
                float dy = target.y - enemy.y;
                float distance = sqrt(dx * dx + dy * dy);
                if (distance < enemy.speed) {
                    enemy.pathIndex++;
                } else {
                    enemy.x += (dx / distance) * enemy.speed;
                    enemy.y += (dy / distance) * enemy.speed;
                }
            }

            // Стрельба башен
            for (auto& tower : towers) {
                if (!tower.active) continue;
                if (currentTime - tower.lastShot >= 1000.0f / tower.fireRate) {
                    for (auto& enemy : enemies) {
                        if (!enemy.active) continue;
                        if (inRange(tower, enemy.x, enemy.y)) {
                            Projectile proj;
                            proj.x = tower.x + 25;
                            proj.y = tower.y + 25;
                            proj.speed = 5.0f;
                            proj.damage = towerDamages[tower.type];
                            proj.target = &enemy;
                            proj.active = true;
                            projectiles.push_back(proj);
                            tower.lastShot = currentTime;
                            break;
                        }
                    }
                }
            }

            // Движение снарядов
            for (auto& proj : projectiles) {
                if (!proj.active || !proj.target->active) {
                    proj.active = false;
                    continue;
                }
                float dx = proj.target->x - proj.x;
                float dy = proj.target->y - proj.y;
                float distance = sqrt(dx * dx + dy * dy);
                if (distance < proj.speed) {
                    proj.target->health -= proj.damage;
                    proj.active = false;
                    if (proj.target->health <= 0) {
                        proj.target->active = false;
                        playerMoney += 10;
                    }
                } else {
                    proj.x += (dx / distance) * proj.speed;
                    proj.y += (dy / distance) * proj.speed;
                }
            }

            // Удаляем неактивные снаряды
            projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                [](const Projectile& p) { return !p.active; }), projectiles.end());

            // Обновляем текст здоровья и денег
            if (healthText) SDL_DestroyTexture(healthText);
            if (moneyText) SDL_DestroyTexture(moneyText);
            healthText = createTextTexture(renderer, font, "Здоровье: " + std::to_string(playerHealth), textColor);
            moneyText = createTextTexture(renderer, font, "Монеты: " + std::to_string(playerMoney), textColor);

            // Предпросмотр башни
            if (isPlacingTower && selectedTowerType >= 0) {
                previewTower.x = mx - 25;
                previewTower.y = my - 25;
                bool valid = isValidPlacement(previewTower.x, previewTower.y, towers) && playerMoney >= towerCost;
                SDL_SetRenderDrawColor(renderer, valid ? validPlacementColor.r : invalidPlacementColor.r,
                    valid ? validPlacementColor.g : invalidPlacementColor.g,
                    valid ? validPlacementColor.b : invalidPlacementColor.b,
                    valid ? validPlacementColor.a : invalidPlacementColor.a);
                SDL_RenderFillRect(renderer, &previewTower);
            }
        }

        // Обновляем слайдер музыки
        if (bgm && musicStarted && !isDraggingSlider) {
            double currentPosition = Mix_GetMusicPosition(bgm);
            if (musicDuration > 0) {
                float progress = static_cast<float>(currentPosition) / musicDuration;
                sliderHandle.x = sliderTrack.x + static_cast<int>(progress * (sliderTrack.w - sliderHandle.w));
            }
            if (currentTimeText) SDL_DestroyTexture(currentTimeText);
            currentTimeText = createTextTexture(renderer, font, formatTime(currentPosition), textColor);
        }

        // Время при наведении на слайдер
        if (MouseOnSliderTrack && bgm) {
            if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
            if (musicDuration > 0) {
                float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                double hoverPosition = progress * musicDuration;
                hoverTimeText = createTextTexture(renderer, font, formatTime(hoverPosition), textColor);
            }
        } else {
            if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
            hoverTimeText = nullptr;
        }

        // Обновляем скролл треков
        if (!isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
            float progress = static_cast<float>(musicScrollOffset) / (musicFiles.size() - maxVisibleSquares);
            musicScrollHandle.y = musicScrollTrack.y + static_cast<int>(progress * (musicScrollTrack.h - musicScrollHandle.h));
        }

        // Анимация текста трека
        if (needsScrolling) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastTextUpdate >= 50) {
                textOffset++;
                int textW, textH;
                SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
                if (textOffset >= textW - 300) {
                    textOffset = 0;
                }
                lastTextUpdate = currentTime;
            }
        } else {
            textOffset = 0;
        }

        // Отрисовка
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);

        if (scene == -1) {
            // Главное меню
            SDL_Texture* titleText = createTextTexture(renderer, titleFont, "Музыкальный плеер", textColor);
            if (titleText) {
                int tw, th;
                SDL_QueryTexture(titleText, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {400 - tw / 2, 150 - th / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 3, tr.y + 3, tw, th};
                SDL_SetTextureColorMod(titleText, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(titleText, shadowColor.a);
                SDL_RenderCopy(renderer, titleText, nullptr, &shadowTr);
                SDL_SetTextureColorMod(titleText, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(titleText, 255);
                SDL_RenderCopy(renderer, titleText, nullptr, &tr);
                SDL_DestroyTexture(titleText);
            }

            // Кнопки меню
            SDL_SetRenderDrawColor(renderer, MouseOnMenuButton1 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton1 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton1 ? buttonHoverColor.b : buttonHoverColor.b, 255);
            SDL_RenderFillRect(renderer, &menuButton1);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &menuButton1);
            SDL_Texture* btn1Text = createTextTexture(renderer, font, "Начать", textColor, 180);
            if (btn1Text) {
                int tw, th;
                SDL_QueryTexture(btn1Text, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {menuButton1.x + (menuButton1.w - tw) / 2, menuButton1.y + (menuButton1.h - th) / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
                SDL_SetTextureColorMod(btn1Text, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(btn1Text, shadowColor.a);
                SDL_RenderCopy(renderer, btn1Text, nullptr, &shadowTr);
                SDL_SetTextureColorMod(btn1Text, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(btn1Text, 255);
                SDL_RenderCopy(renderer, btn1Text, nullptr, &tr);
                SDL_DestroyTexture(btn1Text);
            }

            SDL_SetRenderDrawColor(renderer, MouseOnMenuButton2 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton2 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton2 ? buttonHoverColor.b : buttonHoverColor.b, 255);
            SDL_RenderFillRect(renderer, &menuButton2);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &menuButton2);
            SDL_Texture* btn2Text = createTextTexture(renderer, font, "Настройки", textColor, 180);
            if (btn2Text) {
                int tw, th;
                SDL_QueryTexture(btn2Text, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {menuButton2.x + (menuButton2.w - tw) / 2, menuButton2.y + (menuButton2.h - th) / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
                SDL_SetTextureColorMod(btn2Text, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(btn2Text, shadowColor.a);
                SDL_RenderCopy(renderer, btn2Text, nullptr, &shadowTr);
                SDL_SetTextureColorMod(btn2Text, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(btn2Text, 255);
                SDL_RenderCopy(renderer, btn2Text, nullptr, &tr);
                SDL_DestroyTexture(btn2Text);
            }

            SDL_SetRenderDrawColor(renderer, MouseOnMenuButton3 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton3 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton3 ? buttonHoverColor.b : buttonHoverColor.b, 255);
            SDL_RenderFillRect(renderer, &menuButton3);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &menuButton3);
            SDL_Texture* btn3Text = createTextTexture(renderer, font, "Выход", textColor, 180);
            if (btn3Text) {
                int tw, th;
                SDL_QueryTexture(btn3Text, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {menuButton3.x + (menuButton3.w - tw) / 2, menuButton3.y + (menuButton3.h - th) / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
                SDL_SetTextureColorMod(btn3Text, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(btn3Text, shadowColor.a);
                SDL_RenderCopy(renderer, btn3Text, nullptr, &shadowTr);
                SDL_SetTextureColorMod(btn3Text, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(btn3Text, 255);
                SDL_RenderCopy(renderer, btn3Text, nullptr, &tr);
                SDL_DestroyTexture(btn3Text);
            }

            SDL_SetRenderDrawColor(renderer, MouseOnMenuButton4 ? buttonHoverColor.r : buttonColor.r, MouseOnMenuButton4 ? buttonHoverColor.g : buttonColor.g, MouseOnMenuButton4 ? buttonHoverColor.b : buttonHoverColor.b, 255);
            SDL_RenderFillRect(renderer, &menuButton4);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &menuButton4);
            SDL_Texture* btn4Text = createTextTexture(renderer, font, "Tower Defense", textColor, 180);
            if (btn4Text) {
                int tw, th;
                SDL_QueryTexture(btn4Text, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {menuButton4.x + (menuButton4.w - tw) / 2, menuButton4.y + (menuButton4.h - th) / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
                SDL_SetTextureColorMod(btn4Text, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(btn4Text, shadowColor.a);
                SDL_RenderCopy(renderer, btn4Text, nullptr, &shadowTr);
                SDL_SetTextureColorMod(btn4Text, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(btn4Text, 255);
                SDL_RenderCopy(renderer, btn4Text, nullptr, &tr);
                SDL_DestroyTexture(btn4Text);
            }
        } else if (scene == 0) {
            // Сцена плеера
            SDL_Rect shadowRect = {coverRect.x + 5, coverRect.y + 5, coverRect.w, coverRect.h};
            SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
            SDL_RenderFillRect(renderer, &shadowRect);
            SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
            SDL_RenderFillRect(renderer, &coverRect);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &coverRect);
            if (coverTexture) {
                SDL_RenderCopy(renderer, coverTexture, nullptr, &coverRect);
            }

            // Твои кнопки (с текстурой на knopka1)
            if (MouseOnKnopka1) {SDL_SetRenderDrawColor(renderer, buttonHoverColor.r, buttonHoverColor.g, buttonHoverColor.b, 255);} else {SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, 255);}
            SDL_RenderFillRect(renderer, &knopka1);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &knopka1);
            SDL_RenderCopy(renderer, btnTexture, nullptr, &knopka1);

            if (MouseOnKnopka2) {SDL_SetRenderDrawColor(renderer, buttonHoverColor.r, buttonHoverColor.g, buttonHoverColor.b, 255);} else {SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, 255);}
            SDL_RenderFillRect(renderer, &knopka2);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &knopka2);
            SDL_Texture* btn2Text = createTextTexture(renderer, font, "Выход", textColor, 180);
            if (btn2Text) {
                int tw, th;
                SDL_QueryTexture(btn2Text, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {knopka2.x + (knopka2.w - tw) / 2, knopka2.y + (knopka2.h - th) / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
                SDL_SetTextureColorMod(btn2Text, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(btn2Text, shadowColor.a);
                SDL_RenderCopy(renderer, btn2Text, nullptr, &shadowTr);
                SDL_SetTextureColorMod(btn2Text, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(btn2Text, 255);
                SDL_RenderCopy(renderer, btn2Text, nullptr, &tr);
                SDL_DestroyTexture(btn2Text);
            }

            // Остальные кнопки (3-10) пока без функционала
            for (int i = 2; i < 10; ++i) {
                SDL_Rect& btn = (i == 2 ? knopka3 : i == 3 ? knopka4 : i == 4 ? knopka5 : i == 5 ? knopka6 : i == 6 ? knopka7 : i == 7 ? knopka8 : i == 8 ? knopka9 : knopka10);
                bool mouseOn = (i == 2 ? MouseOnKnopka3 : i == 3 ? MouseOnKnopka4 : i == 4 ? MouseOnKnopka5 : i == 5 ? MouseOnKnopka6 : i == 6 ? MouseOnKnopka7 : i == 7 ? MouseOnKnopka8 : i == 8 ? MouseOnKnopka9 : MouseOnKnopka10);
                if (mouseOn) {SDL_SetRenderDrawColor(renderer, buttonHoverColor.r, buttonHoverColor.g, buttonHoverColor.b, 255);} else {SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, 255);}
                SDL_RenderFillRect(renderer, &btn);
                SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
                SDL_RenderDrawRect(renderer, &btn);
            }

            // Кнопка паузы/воспроизведения
            SDL_SetRenderDrawColor(renderer, MouseOnKnopka11 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka11 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka11 ? buttonHoverColor.b : buttonHoverColor.b, 255);
            SDL_RenderFillRect(renderer, &knopka11);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &knopka11);
            SDL_Texture* btn11Text = createTextTexture(renderer, font, Mix_PausedMusic() ? "Играть" : "Пауза", textColor, 100);
            if (btn11Text) {
                int tw, th;
                SDL_QueryTexture(btn11Text, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {knopka11.x + (knopka11.w - tw) / 2, knopka11.y + (knopka11.h - th) / 2, tw, th};
                SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
                SDL_SetTextureColorMod(btn11Text, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(btn11Text, shadowColor.a);
                SDL_RenderCopy(renderer, btn11Text, nullptr, &shadowTr);
                SDL_SetTextureColorMod(btn11Text, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(btn11Text, 255);
                SDL_RenderCopy(renderer, btn11Text, nullptr, &tr);
                SDL_DestroyTexture(btn11Text);
            }

            // Название трека
            if (trackText) {
                int textW, textH;
                SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {300 - textOffset, 350, std::min(textW, 300), textH};
                SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textRect.w, textRect.h};
                SDL_Rect clipRect = {300, 350, 300, textH};
                SDL_RenderSetClipRect(renderer, &clipRect);
                SDL_SetTextureColorMod(trackText, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(trackText, shadowColor.a);
                SDL_RenderCopy(renderer, trackText, nullptr, &shadowRect);
                SDL_SetTextureColorMod(trackText, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(trackText, 255);
                SDL_RenderCopy(renderer, trackText, nullptr, &textRect);
                SDL_RenderSetClipRect(renderer, nullptr);
            }

            // Слайдер
            SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
            SDL_RenderFillRect(renderer, &sliderTrack);
            int handlePos = sliderHandle.x - sliderTrack.x;
            SDL_Rect activePart = {sliderTrack.x, sliderTrack.y, handlePos + sliderHandle.w / 2, sliderTrack.h};
            SDL_SetRenderDrawColor(renderer, sliderActiveColor.r, sliderActiveColor.g, sliderActiveColor.b, sliderActiveColor.a);
            SDL_RenderFillRect(renderer, &activePart);
            SDL_SetRenderDrawColor(renderer, sliderHandleColor.r, sliderHandleColor.g, sliderHandleColor.b, sliderHandleColor.a);
            SDL_RenderFillRect(renderer, &sliderHandle);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &sliderHandle);

            // Время трека
            if (currentTimeText) {
                int textW, textH;
                SDL_QueryTexture(currentTimeText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {sliderTrack.x - textW - 5, sliderTrack.y - textH / 2, textW, textH};
                SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
                SDL_SetTextureColorMod(currentTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(currentTimeText, shadowColor.a);
                SDL_RenderCopy(renderer, currentTimeText, nullptr, &shadowRect);
                SDL_SetTextureColorMod(currentTimeText, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(currentTimeText, 255);
                SDL_RenderCopy(renderer, currentTimeText, nullptr, &textRect);
            }
            if (totalTimeText) {
                int textW, textH;
                SDL_QueryTexture(totalTimeText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {sliderTrack.x + sliderTrack.w + 5, sliderTrack.y - textH / 2, textW, textH};
                SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
                SDL_SetTextureColorMod(totalTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(totalTimeText, shadowColor.a);
                SDL_RenderCopy(renderer, totalTimeText, nullptr, &shadowRect);
                SDL_SetTextureColorMod(totalTimeText, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(totalTimeText, 255);
                SDL_RenderCopy(renderer, totalTimeText, nullptr, &textRect);
            }
            if (hoverTimeText) {
                int textW, textH;
                SDL_QueryTexture(hoverTimeText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {mx - textW / 2, my - textH - 5, textW, textH};
                SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
                SDL_SetTextureColorMod(hoverTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
                SDL_SetTextureAlphaMod(hoverTimeText, shadowColor.a);
                SDL_RenderCopy(renderer, hoverTimeText, nullptr, &shadowRect);
                SDL_SetTextureColorMod(hoverTimeText, textColor.r, textColor.g, textColor.b);
                SDL_SetTextureAlphaMod(hoverTimeText, 255);
                SDL_RenderCopy(renderer, hoverTimeText, nullptr, &textRect);
            }

            // Список треков
            SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
            SDL_RenderFillRect(renderer, &musicScrollTrack);
            SDL_SetRenderDrawColor(renderer, MouseOnMusicScroll ? sliderActiveColor.r : sliderHandleColor.r, MouseOnMusicScroll ? sliderActiveColor.g : sliderHandleColor.g, MouseOnMusicScroll ? sliderActiveColor.b : sliderHandleColor.b, 255);
            SDL_RenderFillRect(renderer, &musicScrollHandle);
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &musicScrollHandle);
            for (size_t i = 0; i < musicSquares.size(); ++i) {
                SDL_SetRenderDrawColor(renderer, MouseOnMusicSquare[i] ? buttonHoverColor.r : buttonColor.r, MouseOnMusicSquare[i] ? buttonHoverColor.g : buttonColor.g, MouseOnMusicSquare[i] ? buttonHoverColor.b : buttonHoverColor.b, 255);
                SDL_RenderFillRect(renderer, &musicSquares[i]);
                SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
                SDL_RenderDrawRect(renderer, &musicSquares[i]);
                if (i + musicScrollOffset < musicFileTextures.size() && musicFileTextures[i + musicScrollOffset]) {
                    int textW, textH;
                    SDL_QueryTexture(musicFileTextures[i + musicScrollOffset], nullptr, nullptr, &textW, &textH);
                    SDL_Rect textRect = {musicSquares[i].x + 5, musicSquares[i].y + (musicSquares[i].h - textH) / 2, textW, textH};
                    SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
                    SDL_Rect clipRect = {musicSquares[i].x + 5, musicSquares[i].y, 130, musicSquares[i].h};
                    SDL_RenderSetClipRect(renderer, &clipRect);
                    SDL_SetTextureColorMod(musicFileTextures[i + musicScrollOffset], shadowColor.r, shadowColor.g, shadowColor.b);
                    SDL_SetTextureAlphaMod(musicFileTextures[i + musicScrollOffset], shadowColor.a);
                    SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &shadowRect);
                    SDL_SetTextureColorMod(musicFileTextures[i + musicScrollOffset], textColor.r, textColor.g, textColor.b);
                    SDL_SetTextureAlphaMod(musicFileTextures[i + musicScrollOffset], 255);
                    SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &textRect);
                    SDL_RenderSetClipRect(renderer, nullptr);
                }
            }
        } else if (scene == 1) {
            // Сцена Tower Defense
            SDL_SetRenderDrawColor(renderer, pathColor.r, pathColor.g, pathColor.b, pathColor.a);
            for (size_t i = 0; i < enemyPath.size() - 1; ++i) {
                SDL_RenderDrawLine(renderer, enemyPath[i].x, enemyPath[i].y, enemyPath[i + 1].x, enemyPath[i + 1].y);
            }
            for (const auto& enemy : enemies) {
                if (!enemy.active) continue;
                SDL_Rect enemyRect = {static_cast<int>(enemy.x - 10), static_cast<int>(enemy.y - 10), 20, 20};
                SDL_SetRenderDrawColor(renderer, enemyColor.r, enemyColor.g, enemyColor.b, enemyColor.a);
                SDL_RenderFillRect(renderer, &enemyRect);
            }
            for (const auto& tower : towers) {
                if (!tower.active) continue;
                SDL_Rect towerRect = {tower.x, tower.y, 50, 50};
                SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 255);
                SDL_RenderFillRect(renderer, &towerRect);
                SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 50);
                for (int i = 0; i < 360; i++) {
                    float rad = i * M_PI / 180.0f;
                    int x1 = tower.x + 25 + cos(rad) * towerRanges[tower.type];
                    int y1 = tower.y + 25 + sin(rad) * towerRanges[tower.type];
                    int x2 = tower.x + 25 + cos((i + 1) * M_PI / 180.0f) * towerRanges[tower.type];
                    int y2 = tower.y + 25 + sin((i + 1) * M_PI / 180.0f) * towerRanges[tower.type];
                    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                }
            }
            SDL_SetRenderDrawColor(renderer, projectileColor.r, projectileColor.g, projectileColor.b, projectileColor.a);
            for (const auto& proj : projectiles) {
                if (!proj.active) continue;
                renderCircle(renderer, static_cast<int>(proj.x), static_cast<int>(proj.y), 3);
            }
            if (healthText) {
                int textW, textH;
                SDL_QueryTexture(healthText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {10, 10, textW, textH};
                SDL_RenderCopy(renderer, healthText, nullptr, &textRect);
            }
            if (moneyText) {
                int textW, textH;
                SDL_QueryTexture(moneyText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {10, 40, textW, textH};
                SDL_RenderCopy(renderer, moneyText, nullptr, &textRect);
            }
            for (int i = 0; i < TOWER_TYPES; ++i) {
                SDL_SetRenderDrawColor(renderer, MouseOnTowerCard[i] ? buttonHoverColor.r : buttonColor.r, MouseOnTowerCard[i] ? buttonHoverColor.g : buttonColor.g, MouseOnTowerCard[i] ? buttonHoverColor.b : buttonHoverColor.b, 255);
                SDL_RenderFillRect(renderer, &towerCards[i]);
                SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
                SDL_RenderDrawRect(renderer, &towerCards[i]);
                SDL_Texture* cardText = createTextTexture(renderer, font, towerNames[i] + "\n" + std::to_string(towerCost), textColor, 60);
                if (cardText) {
                    int tw, th;
                    SDL_QueryTexture(cardText, nullptr, nullptr, &tw, &th);
                    SDL_Rect tr = {towerCards[i].x + (towerCards[i].w - tw) / 2, towerCards[i].y + (towerCards[i].h - th) / 2, tw, th};
                    SDL_RenderCopy(renderer, cardText, nullptr, &tr);
                    SDL_DestroyTexture(cardText);
                }
            }
            SDL_SetRenderDrawColor(renderer, MouseOnBackButton ? buttonHoverColor.r : buttonColor.r, MouseOnBackButton ? buttonHoverColor.g : buttonColor.g, MouseOnBackButton ? buttonHoverColor.b : buttonHoverColor.b, 255);
            SDL_RenderFillRect(renderer, &backButton);
            SDL_Texture* backText = createTextTexture(renderer, font, "Назад", textColor, 100);
            if (backText) {
                int tw, th;
                SDL_QueryTexture(backText, nullptr, nullptr, &tw, &th);
                SDL_Rect tr = {backButton.x + (backButton.w - tw) / 2, backButton.y + (backButton.h - th) / 2, tw, th};
                SDL_RenderCopy(renderer, backText, nullptr, &tr);
                SDL_DestroyTexture(backText);
            }
            if (isPlacingTower && selectedTowerType >= 0) {
                previewTower.x = mx - 25;
                previewTower.y = my - 25;
                bool valid = isValidPlacement(previewTower.x, previewTower.y, towers) && playerMoney >= towerCost;
                SDL_SetRenderDrawColor(renderer, valid ? validPlacementColor.r : invalidPlacementColor.r, valid ? validPlacementColor.g : invalidPlacementColor.g, valid ? validPlacementColor.b : invalidPlacementColor.b, valid ? validPlacementColor.a : invalidPlacementColor.a);
                SDL_RenderFillRect(renderer, &previewTower);
                SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 50);
                for (int i = 0; i < 360; i++) {
                    float rad = i * M_PI / 180.0f;
                    int x1 = previewTower.x + 25 + cos(rad) * towerRanges[selectedTowerType];
                    int y1 = previewTower.y + 25 + sin(rad) * towerRanges[selectedTowerType];
                    int x2 = previewTower.x + 25 + cos((i + 1) * M_PI / 180.0f) * towerRanges[selectedTowerType];
                    int y2 = previewTower.y + 25 + sin((i + 1) * M_PI / 180.0f) * towerRanges[selectedTowerType];
                    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                }
            }
        }

        // Отрисовываем курсор
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Белый курсор
        SDL_RenderFillRect(renderer, &KvadratNaCursore);

        // Завершаем рендеринг кадра
        SDL_RenderPresent(renderer);

        // Обрабатываем события
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (scene == 0) {
                    // Управление музыкой
                    if (event.key.keysym.sym == SDLK_1 && bgm && !musicStarted) {
                        if (Mix_PlayMusic(bgm, -1) == -1) {
                            std::cerr << "Ошибка Mix_PlayMusic: " << Mix_GetError() << std::endl;
                        } else {
                            musicStarted = true;
                        }
                    } else if (event.key.keysym.sym == SDLK_SPACE) {
                        if (Mix_PausedMusic()) {
                            Mix_ResumeMusic();
                        } else {
                            Mix_PauseMusic();
                        }
                    } else if (event.key.keysym.sym == SDLK_UP && !musicFiles.empty()) {
                        // Предыдущий трек
                        currentTrackIndex = (currentTrackIndex > 0) ? currentTrackIndex - 1 : musicFiles.size() - 1;
                        musicPath = musicFiles[currentTrackIndex];
                        if (musicStarted) {
                            Mix_HaltMusic();
                            musicStarted = false;
                        }
                        if (bgm) {
                            Mix_FreeMusic(bgm);
                        }
                        bgm = Mix_LoadMUS(musicPath.c_str());
                        if (!bgm) {
                            std::cerr << "Ошибка загрузки трека: " << Mix_GetError() << std::endl;
                        } else {
                            if (Mix_PlayMusic(bgm, -1) == -1) {
                                std::cerr << "Ошибка Mix_PlayMusic: " << Mix_GetError() << std::endl;
                            } else {
                                musicStarted = true;
                            }
                        }
                        if (trackText) SDL_DestroyTexture(trackText);
                        currentTrack = fs::path(musicPath).filename().string();
                        trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
                        needsScrolling = currentTrack.length() > 15;
                        textOffset = 0;
                        if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                        musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
                        totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                        if (coverTexture) SDL_DestroyTexture(coverTexture);
                        coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
                        if (fs::exists(coverPath)) {
                            SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                            if (coverSurface) {
                                coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                                SDL_FreeSurface(coverSurface);
                            }
                        }
                        std::ofstream outFile("music_path.txt");
                        if (outFile.is_open()) {
                            outFile << musicPath << "\n" << folderPath;
                            outFile.close();
                        }
                    } else if (event.key.keysym.sym == SDLK_DOWN && !musicFiles.empty()) {
                        // Следующий трек
                        currentTrackIndex = (currentTrackIndex < musicFiles.size() - 1) ? currentTrackIndex + 1 : 0;
                        musicPath = musicFiles[currentTrackIndex];
                        if (musicStarted) {
                            Mix_HaltMusic();
                            musicStarted = false;
                        }
                        if (bgm) {
                            Mix_FreeMusic(bgm);
                        }
                        bgm = Mix_LoadMUS(musicPath.c_str());
                        if (!bgm) {
                            std::cerr << "Ошибка загрузки трека: " << Mix_GetError() << std::endl;
                        } else {
                            if (Mix_PlayMusic(bgm, -1) == -1) {
                                std::cerr << "Ошибка Mix_PlayMusic: " << Mix_GetError() << std::endl;
                            } else {
                                musicStarted = true;
                            }
                        }
                        if (trackText) SDL_DestroyTexture(trackText);
                        currentTrack = fs::path(musicPath).filename().string();
                        trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
                        needsScrolling = currentTrack.length() > 15;
                        textOffset = 0;
                        if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                        musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
                        totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                        if (coverTexture) SDL_DestroyTexture(coverTexture);
                        coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
                        if (fs::exists(coverPath)) {
                            SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                            if (coverSurface) {
                                coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                                SDL_FreeSurface(coverSurface);
                            }
                        }
                        std::ofstream outFile("music_path.txt");
                        if (outFile.is_open()) {
                            outFile << musicPath << "\n" << folderPath;
                            outFile.close();
                        }
                    } else if (event.key.keysym.sym == SDLK_LEFT && bgm && musicStarted) {
                        // Перемотка назад
                        double currentPosition = Mix_GetMusicPosition(bgm);
                        double newPosition = std::max(0.0, currentPosition - 5.0);
                        Mix_SetMusicPosition(newPosition);
                    } else if (event.key.keysym.sym == SDLK_RIGHT && bgm && musicStarted) {
                        // Перемотка вперед
                        double currentPosition = Mix_GetMusicPosition(bgm);
                        double newPosition = std::min(musicDuration, currentPosition + 5.0);
                        Mix_SetMusicPosition(newPosition);
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (scene == -1) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (MouseOnMenuButton1) {
                            scene = 0; // Переход к плееру
                        } else if (MouseOnMenuButton2) {
                            std::cout << "Настройки (не реализованы)" << std::endl;
                        } else if (MouseOnMenuButton3) {
                            running = false; // Выход
                        } else if (MouseOnMenuButton4) {
                            scene = 1; // Переход к Tower Defense
                            enemies.clear();
                            towers.clear();
                            projectiles.clear();
                            playerHealth = 10;
                            playerMoney = 100;
                            selectedTowerType = -1;
                            isPlacingTower = false;
                        }
                    }
                } else if (scene == 0) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (MouseOnKnopka1) {
                            // Выбор папки с музыкой
                            const char* selectedFolder = tinyfd_selectFolderDialog("Выберите папку с музыкой", "");
                            if (selectedFolder) {
                                folderPath = selectedFolder;
                                musicFiles.clear();
                                musicSquares.clear();
                                for (auto& texture : musicFileTextures) {
                                    if (texture) SDL_DestroyTexture(texture);
                                }
                                musicFileTextures.clear();
                                currentTrackIndex = 0;
                                for (const auto& entry : fs::directory_iterator(folderPath)) {
                                    if (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav") {
                                        musicFiles.push_back(entry.path().string());
                                        std::string filename = fs::path(entry.path()).filename().string();
                                        SDL_Texture* textTexture = createTextTexture(renderer, font, filename, textColor, 130);
                                        musicFileTextures.push_back(textTexture);
                                    }
                                }
                                musicScrollOffset = 0;
                                musicSquares.clear();
                                for (size_t i = 0; i < musicFiles.size() && i < maxVisibleSquares; ++i) {
                                    musicSquares.push_back({650, static_cast<int>(50 + i * 55), 140, 50});
                                }
                                if (!musicFiles.empty()) {
                                    musicPath = musicFiles[0];
                                    if (musicStarted) {
                                        Mix_HaltMusic();
                                        musicStarted = false;
                                    }
                                    if (bgm) {
                                        Mix_FreeMusic(bgm);
                                    }
                                    bgm = Mix_LoadMUS(musicPath.c_str());
                                    if (trackText) SDL_DestroyTexture(trackText);
                                    currentTrack = fs::path(musicPath).filename().string();
                                    trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
                                    needsScrolling = currentTrack.length() > 15;
                                    textOffset = 0;
                                    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                                    musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
                                    totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                                    if (coverTexture) SDL_DestroyTexture(coverTexture);
                                    coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
                                    if (fs::exists(coverPath)) {
                                        SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                                        if (coverSurface) {
                                            coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                                            SDL_FreeSurface(coverSurface);
                                        }
                                    }
                                }
                                std::ofstream outFile("music_path.txt");
                                if (outFile.is_open()) {
                                    outFile << musicPath << "\n" << folderPath;
                                    outFile.close();
                                }
                            }
                        } else if (MouseOnKnopka2) {
                            running = false; // Выход
                        } else if (MouseOnKnopka11) {
                            // Пауза/воспроизведение
                            if (Mix_PausedMusic()) {
                                Mix_ResumeMusic();
                            } else {
                                Mix_PauseMusic();
                            }
                        } else if (MouseOnSlider) {
                            isDraggingSlider = true;
                        } else if (MouseOnMusicScroll) {
                            isDraggingMusicScroll = true;
                        } else if (MouseOnSliderTrack && bgm) {
                            // Перемотка по клику на трек
                            if (musicDuration > 0) {
                                float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                                double newPosition = progress * musicDuration;
                                Mix_SetMusicPosition(newPosition);
                            }
                        } else if (MouseOnCover) {
                            // Выбор обложки
                            const char* selectedImage = tinyfd_openFileDialog("Выберите обложку", "", 0, nullptr, nullptr, 0);
                            if (selectedImage) {
                                SDL_Surface* newCoverSurface = IMG_Load(selectedImage);
                                if (newCoverSurface) {
                                    if (coverTexture) SDL_DestroyTexture(coverTexture);
                                    coverTexture = SDL_CreateTextureFromSurface(renderer, newCoverSurface);
                                    coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
                                    IMG_SavePNG(newCoverSurface, coverPath.c_str());
                                    SDL_FreeSurface(newCoverSurface);
                                }
                            }
                        } else {
                            // Выбор трека из списка
                            for (size_t i = 0; i < musicSquares.size(); ++i) {
                                if (MouseOnMusicSquare[i] && i + musicScrollOffset < musicFiles.size()) {
                                    currentTrackIndex = i + musicScrollOffset;
                                    musicPath = musicFiles[currentTrackIndex];
                                    if (musicStarted) {
                                        Mix_HaltMusic();
                                        musicStarted = false;
                                    }
                                    if (bgm) {
                                        Mix_FreeMusic(bgm);
                                    }
                                    bgm = Mix_LoadMUS(musicPath.c_str());
                                    if (!bgm) {
                                        std::cerr << "Ошибка загрузки трека: " << Mix_GetError() << std::endl;
                                    } else {
                                        if (Mix_PlayMusic(bgm, -1) == -1) {
                                            std::cerr << "Ошибка Mix_PlayMusic: " << Mix_GetError() << std::endl;
                                        } else {
                                            musicStarted = true;
                                        }
                                    }
                                    if (trackText) SDL_DestroyTexture(trackText);
                                    currentTrack = fs::path(musicPath).filename().string();
                                    trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
                                    needsScrolling = currentTrack.length() > 15;
                                    textOffset = 0;
                                    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                                    musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
                                    totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                                    if (coverTexture) SDL_DestroyTexture(coverTexture);
                                    coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
                                    if (fs::exists(coverPath)) {
                                        SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                                        if (coverSurface) {
                                            coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                                            SDL_FreeSurface(coverSurface);
                                        }
                                    }
                                    std::ofstream outFile("music_path.txt");
                                    if (outFile.is_open()) {
                                        outFile << musicPath << "\n" << folderPath;
                                        outFile.close();
                                    }
                                    break;
                                }
                            }
                        }
                    }
                } else if (scene == 1) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (MouseOnBackButton) {
                            scene = -1; // Возврат в меню
                            enemies.clear();
                            towers.clear();
                            projectiles.clear();
                            playerHealth = 10;
                            playerMoney = 100;
                            selectedTowerType = -1;
                            isPlacingTower = false;
                        } else if (isPlacingTower && selectedTowerType >= 0) {
                            // Размещение башни
                            int towerX = mx - 25;
                            int towerY = my - 25;
                            if (isValidPlacement(towerX, towerY, towers) && playerMoney >= towerCost) {
                                Tower tower = {towerX, towerY, towerRanges[selectedTowerType], towerDamages[selectedTowerType], towerFireRates[selectedTowerType], 0.0f, true, selectedTowerType};
                                towers.push_back(tower);
                                playerMoney -= towerCost;
                                selectedTowerType = -1;
                                isPlacingTower = false;
                            }
                        } else {
                            // Выбор башни
                            for (int i = 0; i < TOWER_TYPES; ++i) {
                                if (MouseOnTowerCard[i] && playerMoney >= towerCost) {
                                    selectedTowerType = i;
                                    isPlacingTower = true;
                                    break;
                                }
                            }
                        }
                    } else if (event.button.button == SDL_BUTTON_RIGHT && isPlacingTower) {
                        // Отмена размещения
                        selectedTowerType = -1;
                        isPlacingTower = false;
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                if (scene == 0) {
                    if (isDraggingSlider) {
                        isDraggingSlider = false;
                        if (bgm && musicStarted) {
                            if (musicDuration > 0) {
                                float progress = static_cast<float>(sliderHandle.x - sliderTrack.x) / (sliderTrack.w - sliderHandle.w);
                                double newPosition = progress * musicDuration;
                                Mix_SetMusicPosition(newPosition);
                            }
                        }
                    } else if (isDraggingMusicScroll) {
                        isDraggingMusicScroll = false;
                    }
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                if (scene == 0) {
                    if (isDraggingSlider) {
                        // Перетаскивание слайдера
                        int newX = mx - sliderHandle.w / 2;
                        if (newX < sliderTrack.x) newX = sliderTrack.x;
                        if (newX > sliderTrack.x + sliderTrack.w - sliderHandle.w) newX = sliderTrack.x + sliderTrack.w - sliderHandle.w;
                        sliderHandle.x = newX;
                    } else if (isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
                        // Перетаскивание скролла треков
                        int newY = my - musicScrollHandle.h / 2;
                        if (newY < musicScrollTrack.y) newY = musicScrollTrack.y;
                        if (newY > musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h) newY = musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h;
                        musicScrollHandle.y = newY;
                        float progress = static_cast<float>(musicScrollHandle.y - musicScrollTrack.y) / (musicScrollTrack.h - musicScrollHandle.h);
                        musicScrollOffset = static_cast<int>(progress * (musicFiles.size() - maxVisibleSquares));
                        musicSquares.clear();
                        for (size_t i = musicScrollOffset; i < musicFiles.size() && i < musicScrollOffset + maxVisibleSquares; ++i) {
                            musicSquares.push_back({650, static_cast<int>(50 + (i - musicScrollOffset) * 55), 140, 50});
                        }
                    }
                }
            }
        }
    }

    // Очистка ресурсов
    if (bgm) Mix_FreeMusic(bgm);
    for (auto& texture : musicFileTextures) {
        if (texture) SDL_DestroyTexture(texture);
    }
    if (trackText) SDL_DestroyTexture(trackText);
    if (currentTimeText) SDL_DestroyTexture(currentTimeText);
    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
    if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
    if (coverTexture) SDL_DestroyTexture(coverTexture);
    if (btnTexture) SDL_DestroyTexture(btnTexture);
    if (healthText) SDL_DestroyTexture(healthText);
    if (moneyText) SDL_DestroyTexture(moneyText);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(trackFont);
    TTF_CloseFont(titleFont);
    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
