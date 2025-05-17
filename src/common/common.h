#ifndef COMMON_H
#define COMMON_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

const SDL_Color textColor = {200, 200, 200, 255}; // Светло-серый текст
const SDL_Color shadowColor = {50, 50, 50, 100}; // Тёмная тень
const SDL_Color buttonColor = {40, 40, 60, 255}; // Тёмно-синий для кнопок
const SDL_Color buttonHoverColor = {60, 60, 90, 255}; // Светлее при наведении
const SDL_Color borderColor = {100, 100, 100, 255}; // Серый для границ
const SDL_Color backgroundColor = {30, 30, 30, 255}; // Тёмно-серый фон

SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int maxWidth = 0);
std::string formatTime(double seconds);
#endif
