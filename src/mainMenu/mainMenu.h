#ifndef MAINMENU_H
#define MAINMENU_H
#include "../common/common.h"
#include <vector>

class MainMenu {
public:
    MainMenu();
    ~MainMenu();
    void init(SDL_Renderer* renderer, TTF_Font* font);
    void handleEvents(SDL_Event& event, int& scene, bool& running, int mx, int my);
    void render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my);

private:
    SDL_Rect playerButton;
    SDL_Rect gameButton;
    SDL_Rect settingsButton;
    SDL_Rect exitButton;
    SDL_Texture* titleTexture;
    bool isMouseOnButton(int mx, int my, const SDL_Rect& button);
};

#endif
