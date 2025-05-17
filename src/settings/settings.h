#ifndef SETTINGS_H
#define SETTINGS_H
#include "../common/common.h"

class Settings {
public:
    Settings();
    ~Settings();
    void init(SDL_Renderer* renderer, TTF_Font* font);
    void handleEvents(SDL_Event& event, int& scene, int mx, int my);
    void render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my);

private:
    SDL_Rect volumeSliderTrack;
    SDL_Rect volumeSliderHandle;
    SDL_Rect backButton;
    bool isDraggingSlider;
    SDL_Color sliderTrackColor;
    SDL_Color sliderHandleColor;
    SDL_Color sliderActiveColor;
    bool isMouseOnButton(int mx, int my, const SDL_Rect& button);
};

#endif
