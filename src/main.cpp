#include "common/common.h"
#include "musicPlayer/musicPlayer.h"
#include "towerDefens/towerDefens.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cerr << "Ошибка инициализации SDL: " << SDL_GetError() << endl;
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        cerr << "Ошибка инициализации SDL_image: " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() < 0) {
        cerr << "Ошибка инициализации SDL_ttf: " << TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Ошибка инициализации SDL_mixer: " << Mix_GetError() << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    cerr << "Текущая рабочая директория: " << filesystem::current_path() << endl;

    SDL_Window* window = SDL_CreateWindow("SDL2new", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Ошибка создания окна: " << SDL_GetError() << endl;
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Ошибка создания рендера: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("font/arial.ttf", 24);
    if (!font) {
        cerr << "Ошибка загрузки шрифта: " << TTF_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* trackFont = TTF_OpenFont("font/arial.ttf", 36);
    if (!trackFont) {
        cerr << "Ошибка загрузки шрифта для трека: " << TTF_GetError() << endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    string musicPath = "music/muzika.mp3";
    string folderPath;
    ifstream inFile("save/music_path.txt");
    if (inFile.is_open()) {
        getline(inFile, musicPath);
        getline(inFile, folderPath);
        inFile.close();
    }

    MusicPlayer musicPlayer;
    musicPlayer.init(musicPath, folderPath);

    TowerDefens towerDefens;
    towerDefens.init();

    int scene = 0;
    bool running = true;
    SDL_Event event;
    int mx = 0, my = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEMOTION) {
                mx = event.motion.x;
                my = event.motion.y;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
            if (scene == 0) {
                musicPlayer.handleEvents(event, renderer, font, trackFont, mx, my, running);
            } else if (scene == 1) {
                towerDefens.handleEvents(event, mx, my, scene);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (scene == 0) {
            musicPlayer.update(renderer, font);
            musicPlayer.render(renderer, font, mx, my);
        } else if (scene == 1) {
            towerDefens.update(renderer, font);
            towerDefens.render(renderer, font, mx, my);
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_CloseFont(trackFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
