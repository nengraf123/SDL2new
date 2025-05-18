#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Helper function to render text
SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int* outW, int* outH) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) {
        printf("TTF_RenderUTF8_Blended Error: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    }
    if (outW) *outW = surface->w;
    if (outH) *outH = surface->h;
    SDL_FreeSurface(surface);
    return texture;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Discord Profile Mockup",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // --- FONT LOADING ---
    // Make sure "DejaVuSans.ttf" is in the same directory or provide a full path
    // You can download it from: https://dejavu-fonts.github.io/
    TTF_Font* fontLarge = TTF_OpenFont("DejaVuSans.ttf", 24);
    TTF_Font* fontMedium = TTF_OpenFont("DejaVuSans.ttf", 18);
    TTF_Font* fontSmall = TTF_OpenFont("DejaVuSans.ttf", 14);
    TTF_Font* fontTiny = TTF_OpenFont("DejaVuSans.ttf", 12);

    if (!fontLarge || !fontMedium || !fontSmall || !fontTiny) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // --- COLORS (approximated from screenshot) ---
    SDL_Color bgColor = {0x20, 0x22, 0x25, 0xFF}; // Very dark gray (screen background)
    SDL_Color cardBgColor = {0x2F, 0x31, 0x36, 0xFF}; // Dark gray (card background)
    SDL_Color textColorWhite = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Color textColorGray = {0xB9, 0xBB, 0xBE, 0xFF}; // Lighter gray text
    SDL_Color textColorDarkGray = {0x72, 0x76, 0x7D, 0xFF}; // Username-like gray
    SDL_Color dividerColor = {0x3A, 0x3D, 0x42, 0xFF};
    SDL_Color gameIconBlue = {0x3A, 0x70, 0xDD, 0xFF};
    SDL_Color gameIconYellow = {0xF8, 0xA5, 0x1B, 0xFF};
    SDL_Color onlineIconGreen = {0x43, 0xB5, 0x81, 0xFF};

    // Abstract art colors
    SDL_Color artPurple = {0x58, 0x65, 0xF2, 0xFF}; // Discord purple
    SDL_Color artPink = {0xEB, 0x45, 0x9E, 0xFF};
    SDL_Color artBlue = {0x34, 0x98, 0xDB, 0xFF};
    SDL_Color artLightBlue = {0x99, 0xAAb5, 0x40}; // A bit transparent for layering


    // --- UI ELEMENT POSITIONS & SIZES ---
    int cardX = 50;
    int cardY = 50;
    int cardWidth = 350;
    // Card height will be dynamic based on content or fixed
    // For this demo, let's calculate offsets from cardY
    int currentY = cardY + 20; // Start with some padding
    int padding = 10;
    int smallPadding = 5;
    int lineHeight = 20; // Approximate height for text lines

    // --- RENDER LOOP ---
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen with overall background color
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);

        // --- DRAW ABSTRACT ART (RIGHT SIDE) ---
        SDL_Rect artRect1 = {SCREEN_WIDTH - 150, 0, 150, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(renderer, artPurple.r, artPurple.g, artPurple.b, artPurple.a);
        SDL_RenderFillRect(renderer, &artRect1);

        SDL_Rect artRect2 = {SCREEN_WIDTH - 200, SCREEN_HEIGHT / 3, 200, SCREEN_HEIGHT / 3};
        SDL_SetRenderDrawColor(renderer, artPink.r, artPink.g, artPink.b, artPink.a);
        SDL_RenderFillRect(renderer, &artRect2);

        SDL_Rect artRect3 = {SCREEN_WIDTH - 100, SCREEN_HEIGHT / 2, 100, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(renderer, artBlue.r, artBlue.g, artBlue.b, artBlue.a);
        SDL_RenderFillRect(renderer, &artRect3);

        SDL_Rect artRect4 = {SCREEN_WIDTH - 220, 20, 100, 200};
        SDL_SetRenderDrawColor(renderer, artLightBlue.r, artLightBlue.g, artLightBlue.b, artLightBlue.a);
        SDL_RenderFillRect(renderer, &artRect4);


        // --- DRAW PROFILE CARD BACKGROUND ---
        // Calculate total card height dynamically or fix it
        int cardBottomY = cardY + 380; // Fixed height for now
        SDL_Rect cardRect = {cardX, cardY, cardWidth, cardBottomY - cardY};
        SDL_SetRenderDrawColor(renderer, cardBgColor.r, cardBgColor.g, cardBgColor.b, cardBgColor.a);
        SDL_RenderFillRect(renderer, &cardRect);

        // --- CONTENT ---
        currentY = cardY + 20; // Reset currentY for card content

        // 1. Lirika / lirikamerts
        int textW, textH;
        SDL_Texture* texLirika = renderText(renderer, fontLarge, "Lirika", textColorWhite, &textW, &textH);
        SDL_Rect dstLirika = {cardX + padding, currentY, textW, textH};
        SDL_RenderCopy(renderer, texLirika, NULL, &dstLirika);
        SDL_DestroyTexture(texLirika);
        currentY += textH + smallPadding;

        SDL_Texture* texUsername = renderText(renderer, fontSmall, "lirikamerts", textColorDarkGray, &textW, &textH);
        SDL_Rect dstUsername = {cardX + padding, currentY, textW, textH};
        SDL_RenderCopy(renderer, texUsername, NULL, &dstUsername);
        SDL_DestroyTexture(texUsername);
        currentY += textH + padding * 2; // More space after username

        // --- "Играет в" Section ---
        SDL_Texture* texPlayingHeader = renderText(renderer, fontSmall, "Играет в", textColorGray, &textW, &textH);
        SDL_Rect dstPlayingHeader = {cardX + padding, currentY, textW, textH};
        SDL_RenderCopy(renderer, texPlayingHeader, NULL, &dstPlayingHeader);
        SDL_DestroyTexture(texPlayingHeader);
        currentY += textH + padding;

        // Game Icon (Approximation)
        int gameIconX = cardX + padding;
        int gameIconY = currentY;
        int gameIconSize = 50;
        SDL_Rect gameIconBgRect = {gameIconX, gameIconY, gameIconSize, gameIconSize};
        SDL_SetRenderDrawColor(renderer, gameIconBlue.r, gameIconBlue.g, gameIconBlue.b, gameIconBlue.a);
        SDL_RenderFillRect(renderer, &gameIconBgRect);

        SDL_Rect gameIconFgRect = {gameIconX + gameIconSize / 4, gameIconY + gameIconSize / 4, gameIconSize / 2, gameIconSize / 2 };
        // A more complex shape for "silhouette"
        SDL_Rect silhouetteArm = { gameIconX + gameIconSize * 0.2f, gameIconY + gameIconSize * 0.3f, gameIconSize * 0.6f, gameIconSize * 0.15f };
        SDL_Rect silhouetteBody = { gameIconX + gameIconSize * 0.4f, gameIconY + gameIconSize * 0.1f, gameIconSize * 0.2f, gameIconSize * 0.8f };
        SDL_SetRenderDrawColor(renderer, gameIconYellow.r, gameIconYellow.g, gameIconYellow.b, gameIconYellow.a);
        // Instead of just a rect, let's try to make it a bit more like the person
        // SDL_RenderFillRect(renderer, &gameIconFgRect); // Simple square
        // Attempt at simple person shape:
        SDL_Rect person_head = { gameIconX + 18, gameIconY + 8, 14, 14};
        SDL_Rect person_body_main = { gameIconX + 15, gameIconY + 22, 20, 20};
        SDL_Rect person_gun_stock = { gameIconX + 5, gameIconY + 25, 15, 8};
        SDL_Rect person_gun_barrel = { gameIconX + 2, gameIconY + 27, 20, 4};
        SDL_SetRenderDrawColor(renderer, textColorWhite.r, textColorWhite.g, textColorWhite.b, textColorWhite.a); // White silhouette
        SDL_RenderFillRect(renderer, &person_body_main); // Body first
        SDL_RenderFillRect(renderer, &person_head);   // Head on top
        SDL_SetRenderDrawColor(renderer, gameIconYellow.r, gameIconYellow.g, gameIconYellow.b, gameIconYellow.a); // Gun parts in yellow (like the logo)
        SDL_RenderFillRect(renderer, &person_gun_stock);
        SDL_RenderFillRect(renderer, &person_gun_barrel);


        // Game Name and Time
        int textBlockX = gameIconX + gameIconSize + padding;
        SDL_Texture* texGameName = renderText(renderer, fontMedium, "Counter-Strike 2", textColorWhite, &textW, &textH);
        SDL_Rect dstGameName = {textBlockX, gameIconY + smallPadding, textW, textH};
        SDL_RenderCopy(renderer, texGameName, NULL, &dstGameName);
        SDL_DestroyTexture(texGameName);

        // Green "online" icon + time
        SDL_Rect onlineIconRect = {textBlockX, gameIconY + smallPadding + textH + smallPadding, 10, 10};
        SDL_SetRenderDrawColor(renderer, onlineIconGreen.r, onlineIconGreen.g, onlineIconGreen.b, onlineIconGreen.a);
        SDL_RenderFillRect(renderer, &onlineIconRect);

        SDL_Texture* texGameTime = renderText(renderer, fontTiny, "0:54", textColorGray, &textW, &textH);
        SDL_Rect dstGameTime = {textBlockX + onlineIconRect.w + smallPadding, gameIconY + smallPadding + textH + smallPadding, textW, textH};
        SDL_RenderCopy(renderer, texGameTime, NULL, &dstGameTime);
        SDL_DestroyTexture(texGameTime);

        currentY += gameIconSize + padding * 2;

        // Divider
        SDL_SetRenderDrawColor(renderer, dividerColor.r, dividerColor.g, dividerColor.b, dividerColor.a);
        SDL_RenderDrawLine(renderer, cardX + padding, currentY, cardX + cardWidth - padding, currentY);
        currentY += padding;

        // --- "В числе участников с" Section ---
        SDL_Texture* texMemberHeader = renderText(renderer, fontSmall, "В числе участников с", textColorGray, &textW, &textH);
        SDL_Rect dstMemberHeader = {cardX + padding, currentY, textW, textH};
        SDL_RenderCopy(renderer, texMemberHeader, NULL, &dstMemberHeader);
        SDL_DestroyTexture(texMemberHeader);
        currentY += textH + smallPadding;

        SDL_Texture* texMemberDate = renderText(renderer, fontMedium, "21 нояб. 2021 г.", textColorWhite, &textW, &textH);
        SDL_Rect dstMemberDate = {cardX + padding, currentY, textW, textH};
        SDL_RenderCopy(renderer, texMemberDate, NULL, &dstMemberDate);
        SDL_DestroyTexture(texMemberDate);
        currentY += textH + padding * 2;

        // Divider
        SDL_SetRenderDrawColor(renderer, dividerColor.r, dividerColor.g, dividerColor.b, dividerColor.a);
        SDL_RenderDrawLine(renderer, cardX + padding, currentY, cardX + cardWidth - padding, currentY);
        currentY += padding;

        // --- "Общие серверы" Section ---
        SDL_Texture* texServers = renderText(renderer, fontMedium, "Общие серверы — 8", textColorWhite, &textW, &textH);
        SDL_Rect dstServers = {cardX + padding, currentY + (lineHeight - textH)/2, textW, textH}; // Vertically center
        SDL_RenderCopy(renderer, texServers, NULL, &dstServers);
        SDL_DestroyTexture(texServers);

        SDL_Texture* texChevron1 = renderText(renderer, fontMedium, ">", textColorGray, &textW, &textH);
        SDL_Rect dstChevron1 = {cardX + cardWidth - padding - textW, currentY + (lineHeight - textH)/2, textW, textH};
        SDL_RenderCopy(renderer, texChevron1, NULL, &dstChevron1);
        SDL_DestroyTexture(texChevron1);
        currentY += lineHeight + padding;

        // Divider
        SDL_SetRenderDrawColor(renderer, dividerColor.r, dividerColor.g, dividerColor.b, dividerColor.a);
        SDL_RenderDrawLine(renderer, cardX + padding, currentY, cardX + cardWidth - padding, currentY);
        currentY += padding;

        // --- "Общие друзья" Section ---
        SDL_Texture* texFriends = renderText(renderer, fontMedium, "Общие друзья — 9", textColorWhite, &textW, &textH);
        SDL_Rect dstFriends = {cardX + padding, currentY + (lineHeight - textH)/2, textW, textH};
        SDL_RenderCopy(renderer, texFriends, NULL, &dstFriends);
        SDL_DestroyTexture(texFriends);

        SDL_Texture* texChevron2 = renderText(renderer, fontMedium, ">", textColorGray, &textW, &textH);
        SDL_Rect dstChevron2 = {cardX + cardWidth - padding - textW, currentY + (lineHeight - textH)/2, textW, textH};
        SDL_RenderCopy(renderer, texChevron2, NULL, &dstChevron2);
        SDL_DestroyTexture(texChevron2);
        // currentY += lineHeight + padding; // Last element, no need to advance currentY further for card height

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // --- CLEANUP ---
    TTF_CloseFont(fontLarge);
    TTF_CloseFont(fontMedium);
    TTF_CloseFont(fontSmall);
    TTF_CloseFont(fontTiny);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
