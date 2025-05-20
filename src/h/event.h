











    if (event.type == SDL_QUIT) {running = false;}

        /* Если нажата клавиша на клавиатуре то */
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {running = false;}
            else if (event.key.keysym.sym == SDLK_w) {std::cout << "W pressed" << std::endl;}
            else if (event.key.keysym.sym == SDLK_s) {std::cout << "S pressed" << std::endl;}

        }
        /* Если нажата кнопка мыши */
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {printf("Нажата одиночная ЛЕВАЯ кнопка мыши\n");}
            if (event.button.button == SDL_BUTTON_RIGHT) {printf("Нажата одиночная ПРАВАЯ кнопка мыши\n");}
            if (event.button.button == SDL_BUTTON_MIDDLE) {printf("Нажата одиночная СРЕДНЯЯ (колесико) кнопка мыши\n");}


        }






