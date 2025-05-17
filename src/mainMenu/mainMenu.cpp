#include "mainMenu.h"
#include <iostream>

MainMenu::MainMenu() : playerButton({300, 300, 200, 60}), gameButton({300, 380, 200, 60}),
    settingsButton({300, 460, 200, 60}), exitButton({300, 540, 200, 60}), titleTexture(nullptr) {}

MainMenu::~MainMenu() {
    if (titleTexture) SDL_DestroyTexture(titleTexture);
}

void MainMenu::init(SDL_Renderer* renderer, TTF_Font* font) {
    titleTexture = createTextTexture(renderer, font, "Главное меню", textColor, 400);
    if (!titleTexture) {
        std::cerr << "Ошибка создания текстуры заголовка" << std::endl;
    }
}

void MainMenu::handleEvents(SDL_Event& event, int& scene, bool& running, int mx, int my) {
    bool mouseOnPlayer = isMouseOnButton(mx, my, playerButton);
    bool mouseOnGame = isMouseOnButton(mx, my, gameButton);
    bool mouseOnSettings = isMouseOnButton(mx, my, settingsButton);
    bool mouseOnExit = isMouseOnButton(mx, my, exitButton);

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (mouseOnPlayer) {
            scene = 0; // Плеер
        } else if (mouseOnGame) {
            scene = 1; // Tower Defense
        } else if (mouseOnSettings) {
            scene = 2; // Настройки
        } else if (mouseOnExit) {
            running = false; // Выход
        }
    }
}

void MainMenu::render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my) {
    bool mouseOnPlayer = isMouseOnButton(mx, my, playerButton);
    bool mouseOnGame = isMouseOnButton(mx, my, gameButton);
    bool mouseOnSettings = isMouseOnButton(mx, my, settingsButton);
    bool mouseOnExit = isMouseOnButton(mx, my, exitButton);

    // Рендеринг кнопок
    SDL_SetRenderDrawColor(renderer, mouseOnPlayer ? buttonHoverColor.r : buttonColor.r,
        mouseOnPlayer ? buttonHoverColor.g : buttonColor.g,
        mouseOnPlayer ? buttonHoverColor.b : buttonColor.b, 255);
    SDL_Rect scaledPlayerButton = {playerButton.x - (mouseOnPlayer ? 5 : 0), playerButton.y - (mouseOnPlayer ? 5 : 0),
        playerButton.w + (mouseOnPlayer ? 10 : 0), playerButton.h + (mouseOnPlayer ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledPlayerButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledPlayerButton);

    SDL_SetRenderDrawColor(renderer, mouseOnGame ? buttonHoverColor.r : buttonColor.r,
        mouseOnGame ? buttonHoverColor.g : buttonColor.g,
        mouseOnGame ? buttonHoverColor.b : buttonColor.b, 255);
    SDL_Rect scaledGameButton = {gameButton.x - (mouseOnGame ? 5 : 0), gameButton.y - (mouseOnGame ? 5 : 0),
        gameButton.w + (mouseOnGame ? 10 : 0), gameButton.h + (mouseOnGame ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledGameButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledGameButton);

    SDL_SetRenderDrawColor(renderer, mouseOnSettings ? buttonHoverColor.r : buttonColor.r,
        mouseOnSettings ? buttonHoverColor.g : buttonColor.g,
        mouseOnSettings ? buttonHoverColor.b : buttonColor.b, 255);
    SDL_Rect scaledSettingsButton = {settingsButton.x - (mouseOnSettings ? 5 : 0), settingsButton.y - (mouseOnSettings ? 5 : 0),
        settingsButton.w + (mouseOnSettings ? 10 : 0), settingsButton.h + (mouseOnSettings ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledSettingsButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledSettingsButton);

    SDL_SetRenderDrawColor(renderer, mouseOnExit ? buttonHoverColor.r : buttonColor.r,
        mouseOnExit ? buttonHoverColor.g : buttonColor.g,
        mouseOnExit ? buttonHoverColor.b : buttonColor.b, 255);
    SDL_Rect scaledExitButton = {exitButton.x - (mouseOnExit ? 5 : 0), exitButton.y - (mouseOnExit ? 5 : 0),
        exitButton.w + (mouseOnExit ? 10 : 0), exitButton.h + (mouseOnExit ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledExitButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledExitButton);

    // Рендеринг текста кнопок
    SDL_Texture* playerText = createTextTexture(renderer, font, "Музыкальный плеер", textColor, 180);
    if (playerText) {
        int tw, th;
        SDL_QueryTexture(playerText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledPlayerButton.x + (scaledPlayerButton.w - tw) / 2, scaledPlayerButton.y + (scaledPlayerButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(playerText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(playerText, shadowColor.a);
        SDL_RenderCopy(renderer, playerText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(playerText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(playerText, 255);
        SDL_RenderCopy(renderer, playerText, nullptr, &tr);
        SDL_DestroyTexture(playerText);
    }

    SDL_Texture* gameText = createTextTexture(renderer, font, "Tower Defense", textColor, 180);
    if (gameText) {
        int tw, th;
        SDL_QueryTexture(gameText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledGameButton.x + (scaledGameButton.w - tw) / 2, scaledGameButton.y + (scaledGameButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(gameText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(gameText, shadowColor.a);
        SDL_RenderCopy(renderer, gameText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(gameText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(gameText, 255);
        SDL_RenderCopy(renderer, gameText, nullptr, &tr);
        SDL_DestroyTexture(gameText);
    }

    SDL_Texture* settingsText = createTextTexture(renderer, font, "Настройки", textColor, 180);
    if (settingsText) {
        int tw, th;
        SDL_QueryTexture(settingsText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledSettingsButton.x + (scaledSettingsButton.w - tw) / 2, scaledSettingsButton.y + (scaledSettingsButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(settingsText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(settingsText, shadowColor.a);
        SDL_RenderCopy(renderer, settingsText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(settingsText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(settingsText, 255);
        SDL_RenderCopy(renderer, settingsText, nullptr, &tr);
        SDL_DestroyTexture(settingsText);
    }

    SDL_Texture* exitText = createTextTexture(renderer, font, "Выход", textColor, 180);
    if (exitText) {
        int tw, th;
        SDL_QueryTexture(exitText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledExitButton.x + (scaledExitButton.w - tw) / 2, scaledExitButton.y + (scaledExitButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(exitText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(exitText, shadowColor.a);
        SDL_RenderCopy(renderer, exitText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(exitText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(exitText, 255);
        SDL_RenderCopy(renderer, exitText, nullptr, &tr);
        SDL_DestroyTexture(exitText);
    }

    // Рендеринг заголовка
    if (titleTexture) {
        int tw, th;
        SDL_QueryTexture(titleTexture, nullptr, nullptr, &tw, &th);
        SDL_Rect titleRect = {400 - tw / 2, 100, tw, th};
        SDL_Rect shadowRect = {titleRect.x + 3, titleRect.y + 3, tw, th};
        SDL_SetTextureColorMod(titleTexture, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(titleTexture, shadowColor.a);
        SDL_RenderCopy(renderer, titleTexture, nullptr, &shadowRect);
        SDL_SetTextureColorMod(titleTexture, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(titleTexture, 255);
        SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    }
}

bool MainMenu::isMouseOnButton(int mx, int my, const SDL_Rect& button) {
    SDL_Rect cursor = {mx, my, 2, 2};
    return SDL_HasIntersection(&cursor, &button);
}
