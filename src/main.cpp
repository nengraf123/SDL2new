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
#include <fstream>
#include <filesystem>
#include <string>
#include "tinyfiledialogs.h"

namespace fs = std::filesystem;

// Функция для рендеринга текста с обрезкой и сглаживанием
SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int maxWidth = -1) {
    std::string displayText = text;
    if (maxWidth > 0) {
        if (TTF_SizeText(font, text.c_str(), nullptr, nullptr) > maxWidth) {
            displayText = text;
            while (TTF_SizeText(font, (displayText + "...").c_str(), nullptr, nullptr) > maxWidth && !displayText.empty()) {
                displayText.pop_back();
            }
            displayText += "...";
        }
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, displayText.c_str(), color);
    if (!textSurface) {
        std::cerr << "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }
    return textTexture;
}

// Форматирование времени в MM:SS
std::string formatTime(double seconds) {
    int totalSeconds = static_cast<int>(seconds);
    int minutes = totalSeconds / 60;
    int secs = totalSeconds % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}

int main(int argc, char* argv[]) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
    TTF_Font* trackFont = TTF_OpenFont("arial.ttf", 40);
    if (!font || !trackFont) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Привет, SDL2!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 750,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("ZnakMuziki.png");
    if (!surface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* btnTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!btnTexture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

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
        std::cerr << "Failed to load bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

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

    // Определение кнопок
    SDL_Rect knopka1 {0, 0, 200, 75}; // Выбор папки
    SDL_Rect knopka2 {0, 75, 200, 75}; // Выход
    SDL_Rect knopka11 {340, 550, 120, 75}; // Пауза

    // Ползунок перемотки
    SDL_Rect sliderTrack {300, 500, 200, 10};
    SDL_Rect sliderHandle {300, 495, 10, 20};
    bool isDraggingSlider = false;

    // Ползунок прокрутки музыки
    SDL_Rect musicScrollTrack {790, 50, 10, 385};
    SDL_Rect musicScrollHandle {790, 50, 10, 20};
    bool isDraggingMusicScroll = false;
    int musicScrollOffset = 0;
    const int maxVisibleSquares = 7;

    // Квадраты для музыкальных файлов
    std::vector<SDL_Rect> musicSquares;
    for (size_t i = 0; i < musicFiles.size() && i < maxVisibleSquares; ++i) {
        musicSquares.push_back({650, static_cast<int>(50 + i * 55), 140, 50});
    }

    // Текстуры для названий файлов
    std::vector<SDL_Texture*> musicFileTextures;
    SDL_Color textColor = {255, 255, 255, 255};
    for (const auto& file : musicFiles) {
        std::string filename = fs::path(file).filename().string();
        SDL_Texture* textTexture = createTextTexture(renderer, font, filename, textColor, 130);
        musicFileTextures.push_back(textTexture);
    }

    // Текст для трека
    std::string currentTrack = fs::path(musicPath).filename().string();
    SDL_Texture* trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
    int textOffset = 0;
    Uint32 lastTextUpdate = SDL_GetTicks();
    bool needsScrolling = currentTrack.length() > 15;

    // Текст для времени трека
    SDL_Texture* currentTimeText = nullptr;
    SDL_Texture* totalTimeText = nullptr;
    SDL_Texture* hoverTimeText = nullptr;
    double musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
    totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
    currentTimeText = createTextTexture(renderer, font, "00:00", textColor);

    // Квадрат для обложки
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

    SDL_Rect KvadratNaCursore = {0, 0, 2, 2};
    int scene = 0;
    bool musicStarted = false;
    bool running = true;

    SDL_Event event;
    while (running) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        KvadratNaCursore.x = mx - KvadratNaCursore.w / 2;
        KvadratNaCursore.y = my - KvadratNaCursore.h / 2;

        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_ESCAPE]) {
            running = false;
        }

        bool MouseOnKnopka1 = SDL_HasIntersection(&KvadratNaCursore, &knopka1);
        bool MouseOnKnopka2 = SDL_HasIntersection(&KvadratNaCursore, &knopka2);
        bool MouseOnKnopka11 = SDL_HasIntersection(&KvadratNaCursore, &knopka11);
        bool MouseOnSlider = SDL_HasIntersection(&KvadratNaCursore, &sliderHandle);
        bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
        bool MouseOnMusicScroll = SDL_HasIntersection(&KvadratNaCursore, &musicScrollHandle);
        bool MouseOnCover = SDL_HasIntersection(&KvadratNaCursore, &coverRect);

        std::vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
        for (size_t i = 0; i < musicSquares.size(); ++i) {
            MouseOnMusicSquare[i] = SDL_HasIntersection(&KvadratNaCursore, &musicSquares[i]);
        }

        if (bgm && musicStarted && !isDraggingSlider) {
            double musicDuration = Mix_MusicDuration(bgm);
            double currentPosition = Mix_GetMusicPosition(bgm);
            if (musicDuration > 0) {
                float progress = static_cast<float>(currentPosition) / musicDuration;
                sliderHandle.x = sliderTrack.x + static_cast<int>(progress * (sliderTrack.w - sliderHandle.w));
            }
            if (currentTimeText) SDL_DestroyTexture(currentTimeText);
            currentTimeText = createTextTexture(renderer, font, formatTime(currentPosition), textColor);
        }

        if (MouseOnSliderTrack && bgm) {
            if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
            double musicDuration = Mix_MusicDuration(bgm);
            if (musicDuration > 0) {
                float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                double hoverPosition = progress * musicDuration;
                hoverTimeText = createTextTexture(renderer, font, formatTime(hoverPosition), textColor);
            }
        } else {
            if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
            hoverTimeText = nullptr;
        }

        if (!isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
            float progress = static_cast<float>(musicScrollOffset) / (musicFiles.size() - maxVisibleSquares);
            musicScrollHandle.y = musicScrollTrack.y + static_cast<int>(progress * (musicScrollTrack.h - musicScrollHandle.h));
        }

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

        SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255);
        SDL_RenderClear(renderer);

        if (scene == 0) {
            // Отрисовка квадрата для обложки
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &coverRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &coverRect);
            if (coverTexture) {
                SDL_RenderCopy(renderer, coverTexture, nullptr, &coverRect);
            }

            // Отрисовка кнопок
            SDL_SetRenderDrawColor(renderer, MouseOnKnopka1 ? 170 : 255, MouseOnKnopka1 ? 170 : 0, MouseOnKnopka1 ? 255 : 100, 255);
            SDL_RenderFillRect(renderer, &knopka1);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &knopka1);
            SDL_RenderCopy(renderer, btnTexture, nullptr, &knopka1);

            SDL_SetRenderDrawColor(renderer, MouseOnKnopka2 ? 170 : 255, MouseOnKnopka2 ? 170 : 0, MouseOnKnopka2 ? 255 : 100, 255);
            SDL_RenderFillRect(renderer, &knopka2);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &knopka2);

            SDL_SetRenderDrawColor(renderer, MouseOnKnopka11 ? 170 : 255, MouseOnKnopka11 ? 170 : 0, MouseOnKnopka11 ? 255 : 100, 255);
            SDL_RenderFillRect(renderer, &knopka11);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &knopka11);

            // Отрисовка текста трека
            if (trackText) {
                int textW, textH;
                SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {300 - textOffset, 350, std::min(textW, 300), textH};
                SDL_Rect clipRect = {300, 350, 300, textH};
                SDL_RenderSetClipRect(renderer, &clipRect);
                SDL_RenderCopy(renderer, trackText, nullptr, &textRect);
                SDL_RenderSetClipRect(renderer, nullptr);
            }

            // Отрисовка ползунка перемотки
            int handlePos = sliderHandle.x - sliderTrack.x;
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Тёмная часть слева
            SDL_Rect darkPart = {sliderTrack.x, sliderTrack.y, handlePos, sliderTrack.h};
            SDL_RenderFillRect(renderer, &darkPart);
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Светлая часть справа
            SDL_Rect lightPart = {sliderTrack.x + handlePos, sliderTrack.y, sliderTrack.w - handlePos, sliderTrack.h};
            SDL_RenderFillRect(renderer, &lightPart);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Белый ползунок
            SDL_RenderFillRect(renderer, &sliderHandle);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Чёрный контур
            SDL_RenderDrawRect(renderer, &sliderHandle);

            // Отрисовка времени трека
            if (currentTimeText) {
                int textW, textH;
                SDL_QueryTexture(currentTimeText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {sliderTrack.x - textW - 5, sliderTrack.y - textH / 2, textW, textH};
                SDL_RenderCopy(renderer, currentTimeText, nullptr, &textRect);
            }
            if (totalTimeText) {
                int textW, textH;
                SDL_QueryTexture(totalTimeText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {sliderTrack.x + sliderTrack.w + 5, sliderTrack.y - textH / 2, textW, textH};
                SDL_RenderCopy(renderer, totalTimeText, nullptr, &textRect);
            }

            // Отрисовка времени при наведении
            if (hoverTimeText) {
                int textW, textH;
                SDL_QueryTexture(hoverTimeText, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {mx - textW / 2, my - textH - 5, textW, textH};
                SDL_RenderCopy(renderer, hoverTimeText, nullptr, &textRect);
            }

            // Отрисовка ползунка прокрутки
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &musicScrollTrack);
            SDL_SetRenderDrawColor(renderer, MouseOnMusicScroll ? 200 : 100, 100, 255, 255);
            SDL_RenderFillRect(renderer, &musicScrollHandle);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &musicScrollHandle);

            // Отрисовка квадратов для музыкальных файлов
            for (size_t i = 0; i < musicSquares.size(); ++i) {
                SDL_SetRenderDrawColor(renderer, MouseOnMusicSquare[i] ? 170 : 255, MouseOnMusicSquare[i] ? 170 : 0, MouseOnMusicSquare[i] ? 255 : 100, 255);
                SDL_RenderFillRect(renderer, &musicSquares[i]);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &musicSquares[i]);
                if (i + musicScrollOffset < musicFileTextures.size() && musicFileTextures[i + musicScrollOffset]) {
                    int textW, textH;
                    SDL_QueryTexture(musicFileTextures[i + musicScrollOffset], nullptr, nullptr, &textW, &textH);
                    SDL_Rect textRect = {musicSquares[i].x + 5, musicSquares[i].y + (musicSquares[i].h - textH) / 2, textW, textH};
                    SDL_Rect clipRect = {musicSquares[i].x + 5, musicSquares[i].y, 130, musicSquares[i].h};
                    SDL_RenderSetClipRect(renderer, &clipRect);
                    SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &textRect);
                    SDL_RenderSetClipRect(renderer, nullptr);
                }
            }
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_1 && bgm && !musicStarted) {
                    if (Mix_PlayMusic(bgm, -1) == -1) {
                        std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
                    } else {
                        musicStarted = true;
                    }
                }
                else if (event.key.keysym.sym == SDLK_SPACE) {
                    if (Mix_PausedMusic()) {
                        Mix_ResumeMusic();
                    } else {
                        Mix_PauseMusic();
                    }
                }
                else if (event.key.keysym.sym == SDLK_UP && !musicFiles.empty()) {
                    if (currentTrackIndex > 0) {
                        currentTrackIndex--;
                    } else {
                        currentTrackIndex = musicFiles.size() - 1;
                    }
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
                        std::cerr << "Failed to load new bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    } else {
                        if (Mix_PlayMusic(bgm, -1) == -1) {
                            std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
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
                    } else {
                        coverTexture = nullptr;
                    }
                    std::ofstream outFile("music_path.txt");
                    if (outFile.is_open()) {
                        outFile << musicPath << "\n" << folderPath;
                        outFile.close();
                    }
                }
                else if (event.key.keysym.sym == SDLK_DOWN && !musicFiles.empty()) {
                    if (currentTrackIndex < musicFiles.size() - 1) {
                        currentTrackIndex++;
                    } else {
                        currentTrackIndex = 0;
                    }
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
                        std::cerr << "Failed to load new bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    } else {
                        if (Mix_PlayMusic(bgm, -1) == -1) {
                            std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
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
                    } else {
                        coverTexture = nullptr;
                    }
                    std::ofstream outFile("music_path.txt");
                    if (outFile.is_open()) {
                        outFile << musicPath << "\n" << folderPath;
                        outFile.close();
                    }
                }
                else if (event.key.keysym.sym == SDLK_LEFT && bgm && musicStarted) {
                    double currentPosition = Mix_GetMusicPosition(bgm);
                    double newPosition = std::max(0.0, currentPosition - 5.0);
                    Mix_SetMusicPosition(newPosition);
                }
                else if (event.key.keysym.sym == SDLK_RIGHT && bgm && musicStarted) {
                    double currentPosition = Mix_GetMusicPosition(bgm);
                    double musicDuration = Mix_MusicDuration(bgm);
                    double newPosition = std::min(musicDuration, currentPosition + 5.0);
                    Mix_SetMusicPosition(newPosition);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (scene == 0 && MouseOnKnopka1) {
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
                            } else {
                                coverTexture = nullptr;
                            }
                        }
                        std::ofstream outFile("music_path.txt");
                        if (outFile.is_open()) {
                            outFile << musicPath << "\n" << folderPath;
                            outFile.close();
                        }
                    }
                }
                else if (scene == 0 && MouseOnKnopka2) {
                    running = false;
                }
                else if (scene == 0 && MouseOnKnopka11) {
                    if (Mix_PausedMusic()) {
                        Mix_ResumeMusic();
                    } else {
                        Mix_PauseMusic();
                    }
                }
                else if (scene == 0 && MouseOnSlider) {
                    isDraggingSlider = true;
                }
                else if (scene == 0 && MouseOnMusicScroll) {
                    isDraggingMusicScroll = true;
                }
                else if (scene == 0 && MouseOnSliderTrack && bgm) {
                    double musicDuration = Mix_MusicDuration(bgm);
                    if (musicDuration > 0) {
                        float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                        double newPosition = progress * musicDuration;
                        Mix_SetMusicPosition(newPosition);
                    }
                }
                else if (scene == 0 && MouseOnCover) {
                    const char* selectedImage = tinyfd_openFileDialog("Выберите обложку", "", 0, nullptr, nullptr, 0);
                    if (selectedImage) {
                        SDL_Surface* newCoverSurface = IMG_Load(selectedImage);
                        if (newCoverSurface) {
                            if (coverTexture) SDL_DestroyTexture(coverTexture);
                            coverTexture = SDL_CreateTextureFromSurface(renderer, newCoverSurface);
                            SDL_FreeSurface(newCoverSurface);
                            coverPath = "cover_" + fs::path(musicPath).stem().string() + ".png";
                            IMG_SavePNG(newCoverSurface, coverPath.c_str());
                        }
                    }
                }
                else if (scene == 0) {
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
                                std::cerr << "Failed to load new bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;
                            } else {
                                if (Mix_PlayMusic(bgm, -1) == -1) {
                                    std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
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
                            } else {
                                coverTexture = nullptr;
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
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                if (isDraggingSlider) {
                    isDraggingSlider = false;
                    if (bgm && musicStarted) {
                        double musicDuration = Mix_MusicDuration(bgm);
                        if (musicDuration > 0) {
                            float progress = static_cast<float>(sliderHandle.x - sliderTrack.x) / (sliderTrack.w - sliderHandle.w);
                            double newPosition = progress * musicDuration;
                            Mix_SetMusicPosition(newPosition);
                        }
                    }
                }
                else if (isDraggingMusicScroll) {
                    isDraggingMusicScroll = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION) {
                if (isDraggingSlider) {
                    int newX = mx - sliderHandle.w / 2;
                    if (newX < sliderTrack.x) newX = sliderTrack.x;
                    if (newX > sliderTrack.x + sliderTrack.w - sliderHandle.w) newX = sliderTrack.x + sliderTrack.w - sliderHandle.w;
                    sliderHandle.x = newX;
                }
                else if (isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
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

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (bgm) Mix_FreeMusic(bgm);
    if (trackText) SDL_DestroyTexture(trackText);
    if (currentTimeText) SDL_DestroyTexture(currentTimeText);
    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
    if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
    if (coverTexture) SDL_DestroyTexture(coverTexture);
    for (auto& texture : musicFileTextures) {
        if (texture) SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(btnTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(trackFont);
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
