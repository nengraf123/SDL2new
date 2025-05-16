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

// Структура для хранения информации о треке
struct Track {
    std::string title;
    std::string url;
    SDL_Texture* coverTexture = nullptr;
    Mix_Music* music = nullptr;
};

bool isYouTubeURL(const std::string& url) {
    return url.find("youtube.com") != std::string::npos || url.find("youtu.be") != std::string::npos;
}

void fetchYouTubeInfo(const std::string& url, Track& track) {
    std::string command = "yt-dlp --get-title --get-thumbnail \"" + url + "\"";
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe) {
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), pipe)) {
            track.title = buffer;
            track.title.erase(track.title.find_last_not_of("\n") + 1);
        }
        if (fgets(buffer, sizeof(buffer), pipe)) {
            std::string thumbnailUrl = buffer;
            thumbnailUrl.erase(thumbnailUrl.find_last_not_of("\n") + 1);
            std::string tempPath = "temp_cover.png";
            std::string downloadCmd = "curl -o " + tempPath + " \"" + thumbnailUrl + "\"";
            system(downloadCmd.c_str());
            SDL_Surface* coverSurface = IMG_Load(tempPath.c_str());
            if (coverSurface) {
                track.coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                SDL_FreeSurface(coverSurface);
            }
            fs::remove(tempPath);
        }
        pclose(pipe);
    }
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
        "YouTube Music Player",
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

    // Поисковая строка
    SDL_Rect searchRect {10, 10, 780, 40};
    std::string searchText = "";
    bool isTyping = false;

    // Кнопка сохранения
    SDL_Rect saveButton {10, 60, 100, 40};

    // Треки из YouTube
    std::vector<Track> youtubeTracks;
    size_t currentTrackIndex = 0;

    // Ползунок перемотки
    SDL_Rect sliderTrack {300, 500, 200, 10};
    SDL_Rect sliderHandle {300, 495, 10, 20};
    bool isDraggingSlider = false;

    // Ползунок прокрутки треков
    SDL_Rect musicScrollTrack {790, 110, 10, 385};
    SDL_Rect musicScrollHandle {790, 110, 10, 20};
    bool isDraggingMusicScroll = false;
    int musicScrollOffset = 0;
    const int maxVisibleSquares = 7;

    // Квадраты для треков
    std::vector<SDL_Rect> musicSquares;
    for (size_t i = 0; i < youtubeTracks.size() && i < maxVisibleSquares; ++i) {
        musicSquares.push_back({150, static_cast<int>(110 + i * 55), 640, 50});
    }

    // Текст для текущего трека
    SDL_Texture* trackText = nullptr;
    int textOffset = 0;
    Uint32 lastTextUpdate = SDL_GetTicks();
    bool needsScrolling = false;

    // Текст для времени трека
    SDL_Texture* currentTimeText = nullptr;
    SDL_Texture* totalTimeText = nullptr;
    SDL_Texture* hoverTimeText = nullptr;
    double musicDuration = 0.0;

    // Квадрат для обложки
    SDL_Rect coverRect {300, 100, 200, 200};
    SDL_Texture* coverTexture = nullptr;

    SDL_Rect KvadratNaCursore = {0, 0, 2, 2};
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

        bool MouseOnSearch = SDL_HasIntersection(&KvadratNaCursore, &searchRect);
        bool MouseOnSaveButton = SDL_HasIntersection(&KvadratNaCursore, &saveButton);
        bool MouseOnSlider = SDL_HasIntersection(&KvadratNaCursore, &sliderHandle);
        bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
        bool MouseOnMusicScroll = SDL_HasIntersection(&KvadratNaCursore, &musicScrollHandle);

        std::vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
        for (size_t i = 0; i < musicSquares.size(); ++i) {
            MouseOnMusicSquare[i] = SDL_HasIntersection(&KvadratNaCursore, &musicSquares[i]);
        }

        if (youtubeTracks.size() > currentTrackIndex && youtubeTracks[currentTrackIndex].music && musicStarted && !isDraggingSlider) {
            double currentPosition = Mix_GetMusicPosition(youtubeTracks[currentTrackIndex].music);
            if (musicDuration > 0) {
                float progress = static_cast<float>(currentPosition) / musicDuration;
                sliderHandle.x = sliderTrack.x + static_cast<int>(progress * (sliderTrack.w - sliderHandle.w));
            }
            if (currentTimeText) SDL_DestroyTexture(currentTimeText);
            currentTimeText = createTextTexture(renderer, font, formatTime(currentPosition), textColor);
        }

        if (MouseOnSliderTrack && youtubeTracks.size() > currentTrackIndex && youtubeTracks[currentTrackIndex].music) {
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

        if (!isDraggingMusicScroll && youtubeTracks.size() > maxVisibleSquares) {
            float progress = static_cast<float>(musicScrollOffset) / (youtubeTracks.size() - maxVisibleSquares);
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

        // Отрисовка поисковой строки
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &searchRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &searchRect);
        SDL_Texture* searchTextTexture = createTextTexture(renderer, font, searchText, textColor);
        if (searchTextTexture) {
            int textW, textH;
            SDL_QueryTexture(searchTextTexture, nullptr, nullptr, &textW, &textH);
            SDL_Rect textRect = {searchRect.x + 5, searchRect.y + (searchRect.h - textH) / 2, textW, textH};
            SDL_RenderCopy(renderer, searchTextTexture, nullptr, &textRect);
            SDL_DestroyTexture(searchTextTexture);
        }

        // Отрисовка кнопки сохранения
        SDL_SetRenderDrawColor(renderer, MouseOnSaveButton ? 170 : 255, MouseOnSaveButton ? 170 : 0, MouseOnSaveButton ? 255 : 100, 255);
        SDL_RenderFillRect(renderer, &saveButton);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &saveButton);
        SDL_Texture* saveText = createTextTexture(renderer, font, "Save", textColor);
        if (saveText) {
            int textW, textH;
            SDL_QueryTexture(saveText, nullptr, nullptr, &textW, &textH);
            SDL_Rect textRect = {saveButton.x + (saveButton.w - textW) / 2, saveButton.y + (saveButton.h - textH) / 2, textW, textH};
            SDL_RenderCopy(renderer, saveText, nullptr, &textRect);
            SDL_DestroyTexture(saveText);
        }

        // Отрисовка обложки
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &coverRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &coverRect);
        if (youtubeTracks.size() > currentTrackIndex && youtubeTracks[currentTrackIndex].coverTexture) {
            SDL_RenderCopy(renderer, youtubeTracks[currentTrackIndex].coverTexture, nullptr, &coverRect);
        }

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
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect darkPart = {sliderTrack.x, sliderTrack.y, handlePos, sliderTrack.h};
        SDL_RenderFillRect(renderer, &darkPart);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_Rect lightPart = {sliderTrack.x + handlePos, sliderTrack.y, sliderTrack.w - handlePos, sliderTrack.h};
        SDL_RenderFillRect(renderer, &lightPart);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &sliderHandle);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

        // Отрисовка квадратов для треков
        for (size_t i = 0; i < musicSquares.size(); ++i) {
            SDL_SetRenderDrawColor(renderer, MouseOnMusicSquare[i] ? 170 : 255, MouseOnMusicSquare[i] ? 170 : 0, MouseOnMusicSquare[i] ? 255 : 100, 255);
            SDL_RenderFillRect(renderer, &musicSquares[i]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &musicSquares[i]);
            if (i + musicScrollOffset < youtubeTracks.size()) {
                SDL_Texture* titleTexture = createTextTexture(renderer, font, youtubeTracks[i + musicScrollOffset].title, textColor, 600);
                if (titleTexture) {
                    int textW, textH;
                    SDL_QueryTexture(titleTexture, nullptr, nullptr, &textW, &textH);
                    SDL_Rect textRect = {musicSquares[i].x + 5, musicSquares[i].y + (musicSquares[i].h - textH) / 2, textW, textH};
                    SDL_RenderCopy(renderer, titleTexture, nullptr, &textRect);
                    SDL_DestroyTexture(titleTexture);
                }
            }
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN && isTyping) {
                    if (isYouTubeURL(searchText)) {
                        youtubeTracks.clear();
                        musicSquares.clear();
                        if (searchText.find("playlist") != std::string::npos) {
                            std::string command = "yt-dlp --get-id --skip-download --flat-playlist \"" + searchText + "\"";
                            FILE* pipe = popen(command.c_str(), "r");
                            if (pipe) {
                                char buffer[256];
                                while (fgets(buffer, sizeof(buffer), pipe)) {
                                    std::string videoId = buffer;
                                    videoId.erase(videoId.find_last_not_of("\n") + 1);
                                    Track track;
                                    track.url = "https://www.youtube.com/watch?v=" + videoId;
                                    fetchYouTubeInfo(track.url, track);
                                    youtubeTracks.push_back(track);
                                }
                                pclose(pipe);
                            }
                        } else {
                            Track track;
                            track.url = searchText;
                            fetchYouTubeInfo(track.url, track);
                            youtubeTracks.push_back(track);
                        }
                        musicScrollOffset = 0;
                        for (size_t i = 0; i < youtubeTracks.size() && i < maxVisibleSquares; ++i) {
                            musicSquares.push_back({150, static_cast<int>(110 + i * 55), 640, 50});
                        }
                        if (!youtubeTracks.empty()) {
                            currentTrackIndex = 0;
                            if (trackText) SDL_DestroyTexture(trackText);
                            trackText = createTextTexture(renderer, trackFont, youtubeTracks[0].title.length() > 15 ? youtubeTracks[0].title.substr(0, 15) + "..." : youtubeTracks[0].title, textColor);
                            needsScrolling = youtubeTracks[0].title.length() > 15;
                            textOffset = 0;
                            if (coverTexture) SDL_DestroyTexture(coverTexture);
                            coverTexture = youtubeTracks[0].coverTexture;
                            if (youtubeTracks[0].music) Mix_FreeMusic(youtubeTracks[0].music);
                            std::string tempPath = "temp_audio.mp3";
                            std::string downloadCmd = "yt-dlp -x --audio-format mp3 -o " + tempPath + " \"" + youtubeTracks[0].url + "\"";
                            system(downloadCmd.c_str());
                            youtubeTracks[0].music = Mix_LoadMUS(tempPath.c_str());
                            musicDuration = youtubeTracks[0].music ? Mix_MusicDuration(youtubeTracks[0].music) : 0.0;
                            if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                            totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                            fs::remove(tempPath);
                        }
                    }
                    isTyping = false;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE && isTyping) {
                    if (!searchText.empty()) searchText.pop_back();
                } else if (isTyping && event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
                    searchText += static_cast<char>(event.key.keysym.sym - SDLK_a + 'a');
                }
                if (event.key.keysym.sym == SDLK_SPACE && isTyping) {
                    searchText += " ";
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (MouseOnSearch) {
                    isTyping = true;
                } else if (MouseOnSaveButton && youtubeTracks.size() > currentTrackIndex) {
                    const char* savePath = tinyfd_selectFolderDialog("Выберите папку для сохранения", "");
                    if (savePath) {
                        std::string downloadCmd = "yt-dlp -x --audio-format mp3 -o \"" + std::string(savePath) + "/%(title)s.%(ext)s\" \"" + youtubeTracks[currentTrackIndex].url + "\"";
                        system(downloadCmd.c_str());
                    }
                } else if (MouseOnSlider) {
                    isDraggingSlider = true;
                } else if (MouseOnMusicScroll) {
                    isDraggingMusicScroll = true;
                } else if (MouseOnSliderTrack && youtubeTracks.size() > currentTrackIndex && youtubeTracks[currentTrackIndex].music) {
                    if (musicDuration > 0) {
                        float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                        double newPosition = progress * musicDuration;
                        Mix_SetMusicPosition(newPosition);
                    }
                } else {
                    for (size_t i = 0; i < musicSquares.size(); ++i) {
                        if (MouseOnMusicSquare[i] && i + musicScrollOffset < youtubeTracks.size()) {
                            currentTrackIndex = i + musicScrollOffset;
                            if (musicStarted) Mix_HaltMusic();
                            if (youtubeTracks[currentTrackIndex].music) Mix_FreeMusic(youtubeTracks[currentTrackIndex].music);
                            std::string tempPath = "temp_audio.mp3";
                            std::string downloadCmd = "yt-dlp -x --audio-format mp3 -o " + tempPath + " \"" + youtubeTracks[currentTrackIndex].url + "\"";
                            system(downloadCmd.c_str());
                            youtubeTracks[currentTrackIndex].music = Mix_LoadMUS(tempPath.c_str());
                            musicDuration = youtubeTracks[currentTrackIndex].music ? Mix_MusicDuration(youtubeTracks[currentTrackIndex].music) : 0.0;
                            if (trackText) SDL_DestroyTexture(trackText);
                            trackText = createTextTexture(renderer, trackFont, youtubeTracks[currentTrackIndex].title.length() > 15 ? youtubeTracks[currentTrackIndex].title.substr(0, 15) + "..." : youtubeTracks[currentTrackIndex].title, textColor);
                            needsScrolling = youtubeTracks[currentTrackIndex].title.length() > 15;
                            textOffset = 0;
                            if (coverTexture) SDL_DestroyTexture(coverTexture);
                            coverTexture = youtubeTracks[currentTrackIndex].coverTexture;
                            if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                            totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                            fs::remove(tempPath);
                            if (youtubeTracks[currentTrackIndex].music && !musicStarted) {
                                if (Mix_PlayMusic(youtubeTracks[currentTrackIndex].music, -1) == -1) {
                                    std::cerr << "Mix_PlayMusic error: " << Mix_GetError() << std::endl;
                                } else {
                                    musicStarted = true;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                if (isDraggingSlider) {
                    isDraggingSlider = false;
                    if (youtubeTracks.size() > currentTrackIndex && youtubeTracks[currentTrackIndex].music && musicStarted) {
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
            else if (event.type == SDL_MOUSEMOTION) {
                if (isDraggingSlider) {
                    int newX = mx - sliderHandle.w / 2;
                    if (newX < sliderTrack.x) newX = sliderTrack.x;
                    if (newX > sliderTrack.x + sliderTrack.w - sliderHandle.w) newX = sliderTrack.x + sliderTrack.w - sliderHandle.w;
                    sliderHandle.x = newX;
                }
                else if (isDraggingMusicScroll && youtubeTracks.size() > maxVisibleSquares) {
                    int newY = my - musicScrollHandle.h / 2;
                    if (newY < musicScrollTrack.y) newY = musicScrollTrack.y;
                    if (newY > musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h) newY = musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h;
                    musicScrollHandle.y = newY;
                    float progress = static_cast<float>(musicScrollHandle.y - musicScrollTrack.y) / (musicScrollTrack.h - musicScrollHandle.h);
                    musicScrollOffset = static_cast<int>(progress * (youtubeTracks.size() - maxVisibleSquares));
                    musicSquares.clear();
                    for (size_t i = musicScrollOffset; i < youtubeTracks.size() && i < musicScrollOffset + maxVisibleSquares; ++i) {
                        musicSquares.push_back({150, static_cast<int>(110 + (i - musicScrollOffset) * 55), 640, 50});
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                if (youtubeTracks.size() > currentTrackIndex && youtubeTracks[currentTrackIndex].music) {
                    if (Mix_PausedMusic()) {
                        Mix_ResumeMusic();
                    } else {
                        Mix_PauseMusic();
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (auto& track : youtubeTracks) {
        if (track.coverTexture) SDL_DestroyTexture(track.coverTexture);
        if (track.music) Mix_FreeMusic(track.music);
    }
    if (trackText) SDL_DestroyTexture(trackText);
    if (currentTimeText) SDL_DestroyTexture(currentTimeText);
    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
    if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
    if (coverTexture) SDL_DestroyTexture(coverTexture);
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
