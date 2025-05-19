#include <SDL2/SDL.h>
#include <iostream> // Для использования std::cout, std::endl

// Используем SDL_Rect и PointInRect из предыдущего примера

// Функция для проверки, находится ли точка (x, y) внутри прямоугольника (rect)
// Это наша реализация. В SDL есть готовая SDL_PointInRect, но эта понятнее.
bool IsPointInRect(int x, int y, const SDL_Rect* rect) {
    if (rect == nullptr) return false; // Проверка на нулевой указатель в C++ стиле
    return (x >= rect->x && x < rect->x + rect->w &&
            y >= rect->y && y < rect->y + rect->h);
}

int main(int argc, char* argv[]) {
    // 1. Инициализация SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Используем std::cerr для вывода ошибок
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1; // Возвращаем код ошибки
    }

    // 2. Создание окна
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Interactive Square (C++ style)", // Заголовок окна
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,                     // Ширина окна
        600,                     // Высота окна
        SDL_WINDOW_SHOWN
    );

    // Используем nullptr для проверки указателя
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit(); // Если окно не создалось, очищаем ресурсы SDL
        return 1;   // Возвращаем код ошибки
    }

    // 3. Создание рендерера (для отрисовки)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4. Определение квадрата и его состояния
    SDL_Rect square_rect = { 100, 100, 100, 100 }; // x, y, ширина, высота
    bool is_square_present = true;   // Флаг: должен ли квадрат быть нарисован
    bool is_square_hovered = false;  // Флаг: находится ли мышь над квадратом

    // Цвета для квадрата
    SDL_Color color_default = { 0, 0, 255, 255 }; // Синий (R, G, B, A)
    SDL_Color color_hovered = { 255, 255, 0, 255 }; // Желтый
    SDL_Color color_background = { 0, 0, 0, 255 }; // Черный фон

    // 5. Основной цикл программы (цикл событий и отрисовки)
    bool running = true; // Используем bool true/false для флага
    SDL_Event event;

    while (running) { // Условие остается тем же
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false; 
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false; 
                }
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
            // Можно добавить else if для других типов событий, если нужно
        }

        // --- Код отрисовки ---

        // 7. Очистка рендерера (заливка фона)
        SDL_SetRenderDrawColor(renderer, color_background.r, color_background.g, color_background.b, color_background.a);
        SDL_RenderClear(renderer);

        // 8. Отрисовка квадрата, если он существует
        if (is_square_present) {
            // Выбираем цвет в зависимости от состояния наведения
            if (is_square_hovered) {
                SDL_SetRenderDrawColor(renderer, color_hovered.r, color_hovered.g, color_hovered.b, color_hovered.a);
            } else {
                SDL_SetRenderDrawColor(renderer, color_default.r, color_default.g, color_default.b, color_default.a);
            }

            // Рисуем заполненный прямоугольник (наш квадрат)
            SDL_RenderFillRect(renderer, &square_rect);
        }

        // 9. Обновление экрана
        SDL_RenderPresent(renderer);

        // Небольшая задержка (не всегда нужна при активной отрисовке и v-sync)
        // SDL_Delay(16); // ~60 FPS
    }

    // 10. Очистка ресурсов SDL2
    SDL_DestroyRenderer(renderer); // Уничтожаем рендерер
    SDL_DestroyWindow(window);     // Уничтожаем окно
    SDL_Quit();                    // Завершаем работу SDL подсистем

    return 0;
}
