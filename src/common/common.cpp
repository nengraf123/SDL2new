#include "common.h"
#include <iostream>

SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int maxWidth) {
    if (text.empty() || !font || !renderer) return nullptr;
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, maxWidth);
    if (!surface) {
        std::cerr << "Ошибка создания поверхности текста: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Ошибка создания текстуры текста: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

std::string formatTime(double seconds) {
    int minutes = static_cast<int>(seconds) / 60;
    int secs = static_cast<int>(seconds) % 60;
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}
