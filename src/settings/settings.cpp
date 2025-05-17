#include "settings.h"
#include <iostream>

Settings::Settings() : volumeSliderTrack({300, 350, 200, 10}), volumeSliderHandle({300, 345, 10, 20}),
    backButton({650, 650, 120, 60}), isDraggingSlider(false),
    sliderTrackColor({100, 100, 100, 255}), sliderHandleColor({150, 150, 150, 255}),
    sliderActiveColor({80, 80, 120, 255}) {}

Settings::~Settings() {}

void Settings::init(SDL_Renderer* renderer, TTF_Font* font) {
    int volume = Mix_VolumeMusic(-1);
    float progress = static_cast<float>(volume) / MIX_MAX_VOLUME;
    volumeSliderHandle.x = volumeSliderTrack.x + static_cast<int>(progress * (volumeSliderTrack.w - volumeSliderHandle.w));
}

void Settings::handleEvents(SDL_Event& event, int& scene, int mx, int my) {
    bool mouseOnSlider = isMouseOnButton(mx, my, volumeSliderHandle);
    bool mouseOnBack = isMouseOnButton(mx, my, backButton);

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (mouseOnSlider) {
            isDraggingSlider = true;
        } else if (mouseOnBack) {
            scene = -1; // Вернуться в главное меню
        }
    } else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        isDraggingSlider = false;
    } else if (event.type == SDL_MOUSEMOTION && isDraggingSlider) {
        int newX = mx - volumeSliderHandle.w / 2;
        if (newX < volumeSliderTrack.x) newX = volumeSliderTrack.x;
        if (newX > volumeSliderTrack.x + volumeSliderTrack.w - volumeSliderHandle.w) newX = volumeSliderTrack.x + volumeSliderTrack.w - volumeSliderHandle.w;
        volumeSliderHandle.x = newX;
        float progress = static_cast<float>(volumeSliderHandle.x - volumeSliderTrack.x) / (volumeSliderTrack.w - volumeSliderHandle.w);
        int volume = static_cast<int>(progress * MIX_MAX_VOLUME);
        Mix_VolumeMusic(volume);
    }
}

void Settings::render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my) {
    bool mouseOnBack = isMouseOnButton(mx, my, backButton);

    // Рендеринг ползунка громкости
    SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
    SDL_RenderFillRect(renderer, &volumeSliderTrack);
    int handlePos = volumeSliderHandle.x - volumeSliderTrack.x;
    SDL_Rect activePart = {volumeSliderTrack.x, volumeSliderTrack.y, handlePos + volumeSliderHandle.w / 2, volumeSliderTrack.h};
    SDL_SetRenderDrawColor(renderer, sliderActiveColor.r, sliderActiveColor.g, sliderActiveColor.b, sliderActiveColor.a);
    SDL_RenderFillRect(renderer, &activePart);
    SDL_SetRenderDrawColor(renderer, sliderHandleColor.r, sliderHandleColor.g, sliderHandleColor.b, sliderHandleColor.a);
    SDL_RenderFillRect(renderer, &volumeSliderHandle);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &volumeSliderHandle);

    // Рендеринг текста громкости
    SDL_Texture* volumeText = createTextTexture(renderer, font, "Громкость", textColor, 180);
    if (volumeText) {
        int tw, th;
        SDL_QueryTexture(volumeText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {volumeSliderTrack.x + (volumeSliderTrack.w - tw) / 2, volumeSliderTrack.y - th - 10, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(volumeText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(volumeText, shadowColor.a);
        SDL_RenderCopy(renderer, volumeText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(volumeText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(volumeText, 255);
        SDL_RenderCopy(renderer, volumeText, nullptr, &tr);
        SDL_DestroyTexture(volumeText);
    }

    // Рендеринг кнопки "Назад"
    SDL_SetRenderDrawColor(renderer, mouseOnBack ? buttonHoverColor.r : buttonColor.r,
        mouseOnBack ? buttonHoverColor.g : buttonColor.g,
        mouseOnBack ? buttonHoverColor.b : buttonColor.b, 255);
    SDL_Rect scaledBackButton = {backButton.x - (mouseOnBack ? 5 : 0), backButton.y - (mouseOnBack ? 5 : 0),
        backButton.w + (mouseOnBack ? 10 : 0), backButton.h + (mouseOnBack ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledBackButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledBackButton);

    SDL_Texture* backText = createTextTexture(renderer, font, "Назад", textColor, 100);
    if (backText) {
        int tw, th;
        SDL_QueryTexture(backText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledBackButton.x + (scaledBackButton.w - tw) / 2, scaledBackButton.y + (scaledBackButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(backText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(backText, shadowColor.a);
        SDL_RenderCopy(renderer, backText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(backText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(backText, 255);
        SDL_RenderCopy(renderer, backText, nullptr, &tr);
        SDL_DestroyTexture(backText);
    }
}

bool Settings::isMouseOnButton(int mx, int my, const SDL_Rect& button) {
    SDL_Rect cursor = {mx, my, 2, 2};
    return SDL_HasIntersection(&cursor, &button);
}
