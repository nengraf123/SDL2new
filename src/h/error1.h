    // для компиляции на wayland
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland");

    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }

