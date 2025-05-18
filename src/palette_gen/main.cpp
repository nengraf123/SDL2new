#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>     // Для генерации случайных чисел
#include <iomanip>    // Для std::setw, std::setfill
#include <sstream>    // Для форматирования HEX

// --- Конфигурация ---
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const char* FONT_PATH = "/usr/share/fonts/TTF/DejaVuSansMono.ttf"; // Моноширинный шрифт для HEX
const int FONT_SIZE_HEX = 18;
const int NUM_PALETTE_COLORS = 4; // Количество цветов в палитре

// --- Цвета ---
const SDL_Color COLOR_BACKGROUND = {0x1E, 0x1E, 0x1E, 0xFF}; // Темно-серый
const SDL_Color COLOR_TEXT_LIGHT = {0xF0, 0xF0, 0xF0, 0xFF}; // Светлый текст
const SDL_Color COLOR_TEXT_DARK = {0x10, 0x10, 0x10, 0xFF};  // Темный текст (для светлых плашек)

// --- Глобальные переменные ---
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFontHex = nullptr;

std::vector<SDL_Color> gCurrentPalette;

// --- Вспомогательные функции ---

// Генерация случайного числа в диапазоне [min, max]
int randomNumber(int min, int max) {
    static std::mt19937 rng(std::random_device{}()); // Инициализируем один раз
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Конвертация SDL_Color в HEX-строку (#RRGGBB)
std::string colorToHex(SDL_Color color) {
    std::stringstream ss;
    ss << "#";
    ss << std::setfill('0') << std::setw(2) << std::hex << (int)color.r;
    ss << std::setfill('0') << std::setw(2) << std::hex << (int)color.g;
    ss << std::setfill('0') << std::setw(2) << std::hex << (int)color.b;
    return ss.str();
}

// Определение контрастного цвета для текста (очень упрощенно)
SDL_Color getContrastingTextColor(SDL_Color bgColor) {
    // Простое правило: если яркость фона > 128, текст темный, иначе светлый
    // Более точный расчет: (0.299*R + 0.587*G + 0.114*B)
    float luminance = 0.299f * bgColor.r + 0.587f * bgColor.g + 0.114f * bgColor.b;
    if (luminance > 128) {
        return COLOR_TEXT_DARK;
    } else {
        return COLOR_TEXT_LIGHT;
    }
}

void renderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, bool centered_x = false, int parent_w = 0) {
    if (!font || text.empty()) return;
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!textSurface) {
        // std::cerr << "TTF_RenderUTF8_Blended Error: " << TTF_GetError() << std::endl; // Может спамить
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (!textTexture) {
        // std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
     if (centered_x && parent_w > 0) {
        dstRect.x = x + (parent_w - dstRect.w) / 2;
    }

    SDL_RenderCopy(gRenderer, textTexture, nullptr, &dstRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


// Генерация новой палитры
void generatePalette() {
    gCurrentPalette.clear();

    // 1. Базовый цвет (полностью случайный)
    SDL_Color baseColor = {
        (Uint8)randomNumber(0, 255),
        (Uint8)randomNumber(0, 255),
        (Uint8)randomNumber(0, 255),
        255
    };
    gCurrentPalette.push_back(baseColor);

    // 2. Генерация остальных цветов (простые вариации от базового)
    // Для более сложных правил (аналогичные, комплементарные, триада) нужна работа с HSV/HSL
    for (int i = 1; i < NUM_PALETTE_COLORS; ++i) {
        SDL_Color nextColor;
        // Простая вариация: изменяем каждый компонент случайно, но не слишком сильно
        nextColor.r = std::max(0, std::min(255, (int)baseColor.r + randomNumber(-60, 60)));
        nextColor.g = std::max(0, std::min(255, (int)baseColor.g + randomNumber(-60, 60)));
        nextColor.b = std::max(0, std::min(255, (int)baseColor.b + randomNumber(-60, 60)));
        nextColor.a = 255;

        // Чтобы избежать слишком похожих цветов, можно добавить проверку на минимальное различие
        // или использовать более продвинутые алгоритмы генерации.
        // Для простоты пока так.

        gCurrentPalette.push_back(nextColor);
    }

    std::cout << "New Palette Generated:" << std::endl;
    for(const auto& color : gCurrentPalette) {
        std::cout << colorToHex(color) << std::endl;
    }
     std::cout << "---" << std::endl;
}


bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Для улучшения качества масштабирования (хотя здесь не масштабируем текстуры изображений)
    // но это хорошая практика для SDL2 рендеринга в целом.
    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    gWindow = SDL_CreateWindow("Palette Generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    gFontHex = TTF_OpenFont(FONT_PATH, FONT_SIZE_HEX);
    if (!gFontHex) {
        std::cerr << "Failed to load font: " << FONT_PATH << "! TTF_Error: " << TTF_GetError() << std::endl;
        // Попробуем резервный
        gFontHex = TTF_OpenFont("monospace", FONT_SIZE_HEX); // Или "Liberation Mono", "DejaVuSansMono" - общие имена
        if (!gFontHex) {
             std::cerr << "Failed to load fallback monospace font! TTF_Error: " << TTF_GetError() << std::endl;
            return false;
        }
    }
    
    generatePalette(); // Сгенерировать первую палитру при запуске
    return true;
}

void close() {
    if (gFontHex) TTF_CloseFont(gFontHex);
    TTF_Quit();
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Initialization failed." << std::endl;
        close();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    int colorBoxWidth = SCREEN_WIDTH / NUM_PALETTE_COLORS;
    int colorBoxHeight = SCREEN_HEIGHT - (FONT_SIZE_HEX + 20); // Оставляем место для текста HEX

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        generatePalette();
                        break;
                    case SDLK_c: // Просто выведем в консоль (буфер обмена сложнее)
                        if(!gCurrentPalette.empty()){
                            std::cout << "Palette HEX codes copied to console:" << std::endl;
                            for(const auto& color : gCurrentPalette) {
                                std::cout << colorToHex(color) << std::endl;
                            }
                            std::cout << "---" << std::endl;
                            // Можно добавить маленькое сообщение на экране "Copied!"
                        }
                        break;
                }
            }
        }

        // Очистка экрана
        SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
        SDL_RenderClear(gRenderer);

        // Отрисовка палитры
        for (int i = 0; i < static_cast<int>(gCurrentPalette.size()); ++i) {
            SDL_Color color = gCurrentPalette[i];
            SDL_Rect colorRect = { i * colorBoxWidth, 0, colorBoxWidth, colorBoxHeight };
            
            SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(gRenderer, &colorRect);

            // Отрисовка HEX-кода
            std::string hexCode = colorToHex(color);
            SDL_Color textColor = getContrastingTextColor(color);
            renderText(hexCode, colorRect.x, colorRect.y + colorRect.h + 5, gFontHex, textColor, true, colorBoxWidth);
        }

        renderText("Space - New Palette | C - Print HEX | Q - Quit", 10, SCREEN_HEIGHT - FONT_SIZE_HEX - 5, gFontHex, COLOR_TEXT_LIGHT);


        // Обновление экрана
        SDL_RenderPresent(gRenderer);
        SDL_Delay(16); // ~60 FPS, но здесь не так критично
    }

    close();
    return 0;
}
