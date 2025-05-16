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
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <regex>

namespace fs = std::filesystem;
using json = nlohmann::json;

// Коллбэк для обработки ответа от curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

// Функция для фильтрации текста
std::string filterText(const std::string& text) {
    std::string filtered;
    for (char c : text) {
        if (c >= 32 && c <= 126) {
            filtered += c;
        }
    }
    return filtered.empty() ? " " : filtered;
}

// Функция для рендеринга текста
SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int maxWidth = -1) {
    std::string filteredText = filterText(text);
    if (filteredText.empty()) return nullptr;
    std::string displayText = filteredText;
    if (maxWidth > 0) {
        int textWidth;
        if (TTF_SizeText(font, filteredText.c_str(), &textWidth, nullptr) > maxWidth) {
            displayText = filteredText.substr(0, filteredText.find_last_of(' ', maxWidth / 10)) + "...";
        }
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, displayText.c_str(), color);
    if (!textSurface) return nullptr;
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return textTexture;
}

// Форматирование времени
std::string formatTime(double seconds) {
    int totalSeconds = static_cast<int>(seconds);
    int minutes = totalSeconds / 60;
    int secs = totalSeconds % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}

// Структура трека
struct Track {
    std::string title;
    std::string url;
    Mix_Music* music = nullptr;
    double duration = 0.0;
};

// Функция для поиска треков через парсинг vk.com/audio
std::vector<Track> fetchVKTracks(const std::string& query) {
    std::vector<Track> tracks;
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string access_token = "ваш_токен"; // Замените на ваш токен
        std::string url = "https://vk.com/audio?act=audio_search&q=" + curl_easy_escape(curl, query.c_str(), 0) + "&access_token=" + access_token;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); // Разрешить cookies
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Следовать редиректам

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::regex audioPattern(R"("url":"([^"]+\.mp3)")");
            std::regex titlePattern(R"("artist":"([^"]+)","title":"([^"]+)")");
            auto audioWords = std::sregex_iterator(readBuffer.begin(), readBuffer.end(), audioPattern);
            auto titleWords = std::sregex_iterator(readBuffer.begin(), readBuffer.end(), titlePattern);

            auto audioIt = audioWords.begin();
            auto titleIt = titleWords.begin();
            while (audioIt != audioWords.end() && titleIt != titleWords.end()) {
                Track track;
                track.url = audioIt->str(1);
                std::string artist = titleIt->str(1);
                std::string title = titleIt->str(2);
                track.title = artist + " - " + title;
                tracks.push_back(track);
                ++audioIt;
                ++titleIt;
                if (tracks.size() >= 10) break; // Ограничим до 10 треков
            }
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return tracks;
}

// Функция для скачивания трека
std::string downloadTrack(const std::string& url, const std::string& title) {
    std::string filename = title + ".mp3";
    std::string command = "curl -o \"" + filename + "\" \"" + url + "\"";
    system(command.c_str());
    if (fs::exists(filename)) return filename;
    return "";
}

int main(int argc, char* argv[]) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "IMG Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF Error: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
    TTF_Font* trackFont = TTF_OpenFont("arial.ttf", 40);
    if (!font || !trackFont) {
        std::cerr << "Font Error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("VK Music Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 750, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_CloseFont(trackFont);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    // Поисковая строка и кнопка "Найти"
    SDL_Rect searchRect {10, 10, 650, 40};
    SDL_Rect findButtonRect {670, 10, 120, 40};
    std::string searchText = "";
    bool isTyping = false;
    bool isSearching = false;
    Uint32 searchStartTime = 0;

    // Индикатор загрузки
    SDL_Rect loadingRect {10, 700, 40, 40};
    int loadingAngle = 0;

    // Треки
    std::vector<Track> tracks;
    size_t currentTrackIndex = 0;

    // Ползунок перемотки
    SDL_Rect sliderTrack {300, 500, 200, 10};
    SDL_Rect sliderHandle {300, 495, 10, 20};
    bool isDraggingSlider = false;

    // Ползунок прокрутки
    SDL_Rect musicScrollTrack {790, 110, 10, 385};
    SDL_Rect musicScrollHandle {790, 110, 10, 20};
    bool isDraggingMusicScroll = false;
    int musicScrollOffset = 0;
    const int maxVisibleSquares = 7;

    // Квадраты для треков
    std::vector<SDL_Rect> musicSquares;

    // Текст трека
    SDL_Texture* trackText = nullptr;
    int textOffset = 0;
    Uint32 lastTextUpdate = SDL_GetTicks();
    bool needsScrolling = false;

    // Время трека
    SDL_Texture* currentTimeText = nullptr;
    SDL_Texture* totalTimeText = nullptr;
    SDL_Texture* hoverTimeText = nullptr;
    double musicDuration = 0.0;

    SDL_Rect cursorRect = {0, 0, 2, 2};
    bool musicStarted = false;
    bool running = true;

    SDL_StartTextInput();

    SDL_Event event;
    while (running) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        cursorRect.x = mx - cursorRect.w / 2;
        cursorRect.y = my - cursorRect.h / 2;

        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_ESCAPE]) running = false;

        bool MouseOnSearch = SDL_HasIntersection(&cursorRect, &searchRect);
        bool MouseOnFindButton = SDL_HasIntersection(&cursorRect, &findButtonRect);
        bool MouseOnSlider = SDL_HasIntersection(&cursorRect, &sliderHandle);
        bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
        bool MouseOnMusicScroll = SDL_HasIntersection(&cursorRect, &musicScrollHandle);

        std::vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
        for (size_t i = 0; i < musicSquares.size(); ++i) {
            MouseOnMusicSquare[i] = SDL_HasIntersection(&cursorRect, &musicSquares[i]);
        }

        if (isSearching) {
            loadingAngle += 10;
            if (loadingAngle >= 360) loadingAngle = 0;
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - searchStartTime > 2000) { // Имитация 2 секунд загрузки
                isSearching = false;
            }
        }

        if (tracks.size() > currentTrackIndex && tracks[currentTrackIndex].music && musicStarted && !isDraggingSlider) {
            double currentPosition = Mix_GetMusicPosition(tracks[currentTrackIndex].music);
            if (musicDuration > 0) {
                float progress = currentPosition / musicDuration;
                sliderHandle.x = sliderTrack.x + static_cast<int>(progress * (sliderTrack.w - sliderHandle.w));
            }
            if (currentTimeText) SDL_DestroyTexture(currentTimeText);
            currentTimeText = createTextTexture(renderer, font, formatTime(currentPosition), textColor);
        }

        if (MouseOnSliderTrack && tracks.size() > currentTrackIndex && tracks[currentTrackIndex].music) {
            if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
            if (musicDuration > 0) {
                float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                double hoverPosition = progress * musicDuration;
                hoverTimeText = createTextTexture(renderer, font, formatTime(hoverPosition), textColor);
            }
        } else if (hoverTimeText) {
            SDL_DestroyTexture(hoverTimeText);
            hoverTimeText = nullptr;
        }

        if (!isDraggingMusicScroll && tracks.size() > maxVisibleSquares) {
            float progress = static_cast<float>(musicScrollOffset) / (tracks.size() - maxVisibleSquares);
            musicScrollHandle.y = musicScrollTrack.y + static_cast<int>(progress * (musicScrollTrack.h - musicScrollHandle.h));
        }

        if (needsScrolling) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastTextUpdate >= 50) {
                textOffset++;
                int textW, textH;
                SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
                if (textOffset >= textW - 300) textOffset = 0;
                lastTextUpdate = currentTime;
            }
        } else {
            textOffset = 0;
        }

        SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255);
        SDL_RenderClear(renderer);

        // Поисковая строка
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &searchRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &searchRect);
        if (!searchText.empty()) {
            SDL_Texture* searchTextTexture = createTextTexture(renderer, font, searchText, textColor);
            if (searchTextTexture) {
                int textW, textH;
                SDL_QueryTexture(searchTextTexture, nullptr, nullptr, &textW, &textH);
                SDL_Rect textRect = {searchRect.x + 5, searchRect.y + (searchRect.h - textH) / 2, textW, textH};
                SDL_RenderCopy(renderer, searchTextTexture, nullptr, &textRect);
                SDL_DestroyTexture(searchTextTexture);
            }
        }

        // Кнопка "Найти"
        SDL_SetRenderDrawColor(renderer, MouseOnFindButton ? 170 : 255, MouseOnFindButton ? 170 : 0, MouseOnFindButton ? 255 : 100, 255);
        SDL_RenderFillRect(renderer, &findButtonRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &findButtonRect);
        SDL_Texture* findText = createTextTexture(renderer, font, "Find", textColor);
        if (findText) {
            int textW, textH;
            SDL_QueryTexture(findText, nullptr, nullptr, &textW, &textH);
            SDL_Rect textRect = {findButtonRect.x + (findButtonRect.w - textW) / 2, findButtonRect.y + (findButtonRect.h - textH) / 2, textW, textH};
            SDL_RenderCopy(renderer, findText, nullptr, &textRect);
            SDL_DestroyTexture(findText);
        }

        // Индикатор загрузки
        if (isSearching) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            int centerX = loadingRect.x + loadingRect.w / 2;
            int centerY = loadingRect.y + loadingRect.h / 2;
            int radius = loadingRect.w / 2;
            for (int i = 0; i < 360; i += 45) {
                int alpha = (loadingAngle + i) % 360;
                int x = centerX + radius * cos(alpha * M_PI / 180.0);
                int y = centerY + radius * sin(alpha * M_PI / 180.0);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 - (i / 2));
                SDL_Rect dot = {x - 5, y - 5, 10, 10};
                SDL_RenderFillRect(renderer, &dot);
            }
        }

        // Обложка
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_Rect coverRect {300, 100, 200, 200};
        SDL_RenderFillRect(renderer, &coverRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &coverRect);

        // Текст трека
        if (trackText) {
            int textW, textH;
            SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
            SDL_Rect textRect = {300 - textOffset, 350, std::min(textW, 300), textH};
            SDL_Rect clipRect = {300, 350, 300, textH};
            SDL_RenderSetClipRect(renderer, &clipRect);
            SDL_RenderCopy(renderer, trackText, nullptr, &textRect);
            SDL_RenderSetClipRect(renderer, nullptr);
        }

        // Ползунок перемотки
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

        // Время
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

        if (hoverTimeText) {
            int textW, textH;
            SDL_QueryTexture(hoverTimeText, nullptr, nullptr, &textW, &textH);
            SDL_Rect textRect = {mx - textW / 2, my - textH - 5, textW, textH};
            SDL_RenderCopy(renderer, hoverTimeText, nullptr, &textRect);
        }

        // Ползунок прокрутки
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &musicScrollTrack);
        SDL_SetRenderDrawColor(renderer, MouseOnMusicScroll ? 200 : 100, 100, 255, 255);
        SDL_RenderFillRect(renderer, &musicScrollHandle);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &musicScrollHandle);

        // Квадраты треков
        for (size_t i = 0; i < musicSquares.size(); ++i) {
            SDL_SetRenderDrawColor(renderer, MouseOnMusicSquare[i] ? 170 : 255, MouseOnMusicSquare[i] ? 170 : 0, MouseOnMusicSquare[i] ? 255 : 100, 255);
            SDL_RenderFillRect(renderer, &musicSquares[i]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &musicSquares[i]);
            if (i + musicScrollOffset < tracks.size()) {
                SDL_Texture* titleTexture = createTextTexture(renderer, font, tracks[i + musicScrollOffset].title, textColor, 600);
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
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN && isTyping) {
                    isSearching = true;
                    searchStartTime = SDL_GetTicks();
                    tracks.clear();
                    musicSquares.clear();
                    tracks = fetchVKTracks(searchText);
                    musicScrollOffset = 0;
                    for (size_t i = 0; i < tracks.size() && i < maxVisibleSquares; ++i) {
                        musicSquares.push_back({150, static_cast<int>(110 + i * 55), 640, 50});
                    }
                    if (!tracks.empty()) {
                        currentTrackIndex = 0;
                        if (trackText) SDL_DestroyTexture(trackText);
                        trackText = createTextTexture(renderer, trackFont, tracks[0].title.length() > 15 ? tracks[0].title.substr(0, 15) + "..." : tracks[0].title, textColor);
                        needsScrolling = tracks[0].title.length() > 15;
                        textOffset = 0;
                        if (tracks[0].music) Mix_FreeMusic(tracks[0].music);
                        std::string tempPath = downloadTrack(tracks[0].url, tracks[0].title);
                        if (!tempPath.empty()) {
                            tracks[0].music = Mix_LoadMUS(tempPath.c_str());
                            musicDuration = tracks[0].duration > 0 ? tracks[0].duration : Mix_MusicDuration(tracks[0].music);
                            if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                            totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                        }
                    }
                    isTyping = false;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE && isTyping) {
                    if (!searchText.empty()) searchText.pop_back();
                } else if (event.key.keysym.sym == SDLK_SPACE && isTyping) {
                    searchText += " ";
                } else if (event.key.keysym.sym == SDLK_v && keyState[SDL_SCANCODE_LCTRL] && isTyping) {
                    char* clipboardText = SDL_GetClipboardText();
                    if (clipboardText) {
                        searchText += filterText(clipboardText);
                        SDL_free(clipboardText);
                    }
                }
            } else if (event.type == SDL_TEXTINPUT && isTyping) {
                searchText += filterText(event.text.text);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (MouseOnSearch) isTyping = true;
                else if (MouseOnFindButton) {
                    isSearching = true;
                    searchStartTime = SDL_GetTicks();
                    tracks.clear();
                    musicSquares.clear();
                    tracks = fetchVKTracks(searchText);
                    musicScrollOffset = 0;
                    for (size_t i = 0; i < tracks.size() && i < maxVisibleSquares; ++i) {
                        musicSquares.push_back({150, static_cast<int>(110 + i * 55), 640, 50});
                    }
                    if (!tracks.empty()) {
                        currentTrackIndex = 0;
                        if (trackText) SDL_DestroyTexture(trackText);
                        trackText = createTextTexture(renderer, trackFont, tracks[0].title.length() > 15 ? tracks[0].title.substr(0, 15) + "..." : tracks[0].title, textColor);
                        needsScrolling = tracks[0].title.length() > 15;
                        textOffset = 0;
                        if (tracks[0].music) Mix_FreeMusic(tracks[0].music);
                        std::string tempPath = downloadTrack(tracks[0].url, tracks[0].title);
                        if (!tempPath.empty()) {
                            tracks[0].music = Mix_LoadMUS(tempPath.c_str());
                            musicDuration = tracks[0].duration > 0 ? tracks[0].duration : Mix_MusicDuration(tracks[0].music);
                            if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                            totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                        }
                    }
                } else if (MouseOnSlider) isDraggingSlider = true;
                else if (MouseOnMusicScroll) isDraggingMusicScroll = true;
                else if (MouseOnSliderTrack && tracks.size() > currentTrackIndex && tracks[currentTrackIndex].music) {
                    if (musicDuration > 0) {
                        float progress = (mx - sliderTrack.x) / static_cast<float>(sliderTrack.w);
                        Mix_SetMusicPosition(progress * musicDuration);
                    }
                } else {
                    for (size_t i = 0; i < musicSquares.size(); ++i) {
                        if (MouseOnMusicSquare[i] && i + musicScrollOffset < tracks.size()) {
                            currentTrackIndex = i + musicScrollOffset;
                            if (musicStarted) Mix_HaltMusic();
                            if (tracks[currentTrackIndex].music) Mix_FreeMusic(tracks[currentTrackIndex].music);
                            std::string tempPath = downloadTrack(tracks[currentTrackIndex].url, tracks[currentTrackIndex].title);
                            if (!tempPath.empty()) {
                                tracks[currentTrackIndex].music = Mix_LoadMUS(tempPath.c_str());
                                musicDuration = tracks[currentTrackIndex].duration > 0 ? tracks[currentTrackIndex].duration : Mix_MusicDuration(tracks[currentTrackIndex].music);
                                if (trackText) SDL_DestroyTexture(trackText);
                                trackText = createTextTexture(renderer, trackFont, tracks[currentTrackIndex].title.length() > 15 ? tracks[currentTrackIndex].title.substr(0, 15) + "..." : tracks[currentTrackIndex].title, textColor);
                                needsScrolling = tracks[currentTrackIndex].title.length() > 15;
                                textOffset = 0;
                                if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                                totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                                if (!musicStarted && tracks[currentTrackIndex].music) {
                                    if (Mix_PlayMusic(tracks[currentTrackIndex].music, -1) == -1) {
                                        std::cerr << "Play Error: " << Mix_GetError() << std::endl;
                                    } else {
                                        musicStarted = true;
                                    }
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
                    if (tracks.size() > currentTrackIndex && tracks[currentTrackIndex].music && musicStarted) {
                        if (musicDuration > 0) {
                            float progress = (sliderHandle.x - sliderTrack.x) / static_cast<float>(sliderTrack.w - sliderHandle.w);
                            Mix_SetMusicPosition(progress * musicDuration);
                        }
                    }
                } else if (isDraggingMusicScroll) isDraggingMusicScroll = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                if (isDraggingSlider) {
                    int newX = mx - sliderHandle.w / 2;
                    sliderHandle.x = std::max(sliderTrack.x, std::min(newX, sliderTrack.x + sliderTrack.w - sliderHandle.w));
                } else if (isDraggingMusicScroll && tracks.size() > maxVisibleSquares) {
                    int newY = my - musicScrollHandle.h / 2;
                    musicScrollHandle.y = std::max(musicScrollTrack.y, std::min(newY, musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h));
                    float progress = (musicScrollHandle.y - musicScrollTrack.y) / static_cast<float>(musicScrollTrack.h - musicScrollHandle.h);
                    musicScrollOffset = static_cast<int>(progress * (tracks.size() - maxVisibleSquares));
                    musicSquares.clear();
                    for (size_t i = musicScrollOffset; i < tracks.size() && i < musicScrollOffset + maxVisibleSquares; ++i) {
                        musicSquares.push_back({150, static_cast<int>(110 + (i - musicScrollOffset) * 55), 640, 50});
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                if (tracks.size() > currentTrackIndex && tracks[currentTrackIndex].music) {
                    if (Mix_PausedMusic()) Mix_ResumeMusic();
                    else Mix_PauseMusic();
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (auto& track : tracks) {
        if (track.music) Mix_FreeMusic(track.music);
    }
    if (trackText) SDL_DestroyTexture(trackText);
    if (currentTimeText) SDL_DestroyTexture(currentTimeText);
    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
    if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
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
