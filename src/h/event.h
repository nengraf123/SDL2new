











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


            if (event.type == SDL_MOUSEMOTION) {
                if (is_square_present) {
                    // event.motion.x, event.motion.y - текущие координаты мыши
                    if (IsPointInRect(event.motion.x, event.motion.y, &square_rect)) {
                        // Мышь находится над квадратом
                        if (!is_square_hovered) { // Если только что навели
                            std::cout << "Навели мышь на квадрат" << std::endl;
                            is_square_hovered = true;
                        }
                    } else {
                        // Мышь не над квадратом
                         if (is_square_hovered) { // Если только что увели
                            std::cout << "Увели мышь с квадрата" << std::endl;
                            is_square_hovered = false;
                        }
                    }
                } else {
                     // Если квадрата нет, сбросим флаг наведения на всякий случай
                    is_square_hovered = false; // Можно и не делать, если отрисовка зависит от is_square_present
                }

            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                    // Проверяем, было ли нажатие внутри квадрата, если он существует
                    if (is_square_present) {
                         // event.button.x, event.button.y - координаты нажатия мыши
                         if (IsPointInRect(event.button.x, event.button.y, &square_rect)) {
                            // Нажатие левой кнопки внутри квадрата!
                            std::cout << "Квадрат нажат, он исчезает!" << std::endl;
                            is_square_present = false; // Квадрат больше не будет рисоваться
                            is_square_hovered = false; // Сбросить флаг наведения
                        }
                    }
                
            }




