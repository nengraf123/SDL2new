// #include <iostream>
// #include <stdio.h>
// #include <SDL2/SDL.h>

// int main(int argc, char* argv[]) {

//     #include "h/error1.h"

//     // Создание окна
//     SDL_Window* window = SDL_CreateWindow(
//         "SDL2 Пример",                  // Заголовок окна
//         SDL_WINDOWPOS_CENTERED,         // Позиция X
//         SDL_WINDOWPOS_CENTERED,         // Позиция Y
//         800,                            // Ширина
//         600,                            // Высота
//         SDL_WINDOW_SHOWN                // Флаги
//     );

//     #include "h/error2.h"

//     // Основной цикл
//     bool running = true;
//     SDL_Event event;
//     while (running) {

//         // Очистка экрана (черный цвет)
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);SDL_RenderClear(renderer);


//         // Обработка событий
//     while (SDL_PollEvent(&event)) {
//         if (event.type == SDL_QUIT) {running = false;}

//         /* Если нажата клавиша на клавиатуре то */
//         if (event.type == SDL_KEYDOWN) {
//         if (event.key.keysym.sym == SDLK_ESCAPE) {running = false;}
//         else if (event.key.keysym.sym == SDLK_w) {std::cout << "W pressed" << std::endl;}
//         else if (event.key.keysym.sym == SDLK_s) {std::cout << "S pressed" << std::endl;}

//         }



//     }
//     // Обновление экрана
//     SDL_RenderPresent(renderer);
//     }

//     // Очистка ресурсов
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// } 



//////////////////////////////////////////////////Музыкальный плеер
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <filesystem> // C++17
// #include <algorithm>  
// #include <iomanip>    
// #include <sstream>    
// #include <cmath> // For round

// // --- Конфигурация ---
// const int SCREEN_WIDTH = 800;
// const int SCREEN_HEIGHT = 180; 
// const char* FONT_PATH = "/usr/share/fonts/TTF/DejaVuSans.ttf"; 
// const int FONT_SIZE_TITLE = 24;
// const int FONT_SIZE_INFO = 18;
// const std::string MUSIC_DIR = "music"; 

// // --- Цвета (Темная тема) ---
// const SDL_Color COLOR_BACKGROUND = {0x1E, 0x1E, 0x1E, 0xFF}; 
// const SDL_Color COLOR_BUTTON = {0x3A, 0x3A, 0x3A, 0xFF};     
// const SDL_Color COLOR_BUTTON_HOVER = {0x5A, 0x5A, 0x5A, 0xFF}; 
// const SDL_Color COLOR_SYMBOL = {0xE0, 0xE0, 0xE0, 0xFF};      
// const SDL_Color COLOR_TEXT = {0xF0, 0xF0, 0xF0, 0xFF};        
// const SDL_Color COLOR_PROGRESS_BG = {0x44, 0x44, 0x44, 0xFF}; 
// const SDL_Color COLOR_PROGRESS_FG = {0x00, 0x7A, 0xCC, 0xFF}; 

// // --- Глобальные переменные (для простоты) ---
// SDL_Window* gWindow = nullptr;
// SDL_Renderer* gRenderer = nullptr;
// TTF_Font* gFontTitle = nullptr;
// TTF_Font* gFontInfo = nullptr;
// Mix_Music* gMusic = nullptr;

// std::vector<std::string> playlist;
// int currentTrackIndex = -1;
// bool isPlaying = false;
// bool isPaused = false; 
// double musicDuration = 0.0; 
// int volume = MIX_MAX_VOLUME / 2; 

// // --- Кнопки ---
// enum ButtonType { BTN_PREV, BTN_PLAY_PAUSE, BTN_STOP, BTN_NEXT, BTN_VOL_DOWN, BTN_VOL_UP };
// struct Button {
//     SDL_Rect rect;
//     ButtonType type;
//     bool hovered = false;
// };
// std::vector<Button> buttons;
// SDL_Rect progressBarRect; 


// // Отрисовка текста
// void renderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color) {
//     if (!font || text.empty()) return; 
//     SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
//     if (!textSurface) {
//         std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
//         return;
//     }
//     SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//     if (!textTexture) {
//         std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
//         SDL_FreeSurface(textSurface);
//         return;
//     }
//     SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
//     SDL_RenderCopy(gRenderer, textTexture, nullptr, &dstRect);
//     SDL_FreeSurface(textSurface);
//     SDL_DestroyTexture(textTexture);
// }

// // Отрисовка треугольника (для кнопок Play, Next, Prev)
// void drawTriangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color) {
//     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
//     int min_y = std::min({y1, y2, y3});
//     int max_y = std::max({y1, y2, y3});

//     for (int y_scan = min_y; y_scan <= max_y; ++y_scan) { // Renamed y to y_scan to avoid conflict
//         std::vector<int> intersections;
//         // Edge 1-2
//         if (((y_scan >= y1 && y_scan <= y2) || (y_scan >= y2 && y_scan <= y1))) {
//             if (y2 - y1 == 0) { 
//                  if (y_scan == y1) {intersections.push_back(x1); intersections.push_back(x2);}
//             } else {
//                 intersections.push_back(x1 + (x2 - x1) * (y_scan - y1) / (y2 - y1));
//             }
//         }
//         // Edge 2-3
//         if (((y_scan >= y2 && y_scan <= y3) || (y_scan >= y3 && y_scan <= y2))) {
//              if (y3 - y2 == 0) {
//                  if (y_scan == y2) {intersections.push_back(x2); intersections.push_back(x3);}
//             } else {
//                 intersections.push_back(x2 + (x3 - x2) * (y_scan - y2) / (y3 - y2));
//             }
//         }
//         // Edge 3-1
//         if (((y_scan >= y3 && y_scan <= y1) || (y_scan >= y1 && y_scan <= y3))) {
//             if (y1 - y3 == 0) {
//                 if (y_scan == y3) {intersections.push_back(x3); intersections.push_back(x1);}
//             } else {
//                 intersections.push_back(x3 + (x1 - x3) * (y_scan - y3) / (y1 - y3));
//             }
//         }
        
//         if (intersections.size() >= 2) {
//             std::sort(intersections.begin(), intersections.end());
//             intersections.erase(std::unique(intersections.begin(), intersections.end()), intersections.end());
//             if (intersections.size() >=2)
//                 SDL_RenderDrawLine(renderer, intersections[0], y_scan, intersections.back(), y_scan);
//         }
//     }
// }


// bool init() {
//     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//         std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//         return false;
//     }
//     gWindow = SDL_CreateWindow("SDL Music Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//     if (!gWindow) {
//         std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//         return false;
//     }
//     gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (!gRenderer) {
//         std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//         return false;
//     }
//     if (TTF_Init() == -1) {
//         std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
//         return false;
//     }
//     gFontTitle = TTF_OpenFont(FONT_PATH, FONT_SIZE_TITLE);
//     gFontInfo = TTF_OpenFont(FONT_PATH, FONT_SIZE_INFO);
//     if (!gFontTitle || !gFontInfo) {
//         std::cerr << "Failed to load primary font: " << FONT_PATH << "! TTF_Error: " << TTF_GetError() << std::endl;
//         TTF_CloseFont(gFontTitle); 
//         TTF_CloseFont(gFontInfo);  
//         gFontTitle = TTF_OpenFont("sans.ttf", FONT_SIZE_TITLE); 
//         gFontInfo = TTF_OpenFont("sans.ttf", FONT_SIZE_INFO);
//         if(!gFontTitle || !gFontInfo){
//              std::cerr << "Failed to load fallback font 'sans.ttf'! TTF_Error: " << TTF_GetError() << std::endl;
//              return false;
//         }
//          std::cout << "Loaded fallback font 'sans.ttf'." << std::endl;
//     }
//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//         std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
//         return false;
//     }
//     Mix_VolumeMusic(volume);
//     return true;
// }

// void loadPlaylist() {
//     playlist.clear();
//     try {
//         if (!std::filesystem::exists(MUSIC_DIR) || !std::filesystem::is_directory(MUSIC_DIR)) {
//              std::cout << "Music directory '" << MUSIC_DIR << "' not found or is not a directory." << std::endl;
//              // No critical error, playlist will just be empty
//              return;
//         }
//         for (const auto& entry : std::filesystem::directory_iterator(MUSIC_DIR)) {
//             if (entry.is_regular_file()) {
//                 std::string ext = entry.path().extension().string();
//                 std::transform(ext.begin(), ext.end(), ext.begin(), 
//                     [](unsigned char c){ return std::tolower(c); });
//                 if (ext == ".mp3" || ext == ".ogg" || ext == ".wav" || ext == ".flac") {
//                     playlist.push_back(entry.path().string());
//                 }
//             }
//         }
//         std::sort(playlist.begin(), playlist.end()); 
//     } catch (const std::filesystem::filesystem_error& e) {
//         std::cerr << "Error accessing music directory '" << MUSIC_DIR << "': " << e.what() << std::endl;
//     }
// }

// void loadAndPlayTrack(int trackIndex) {
//     if (trackIndex < 0 || trackIndex >= static_cast<int>(playlist.size())) {
//          std::cerr << "Invalid track index: " << trackIndex << " Playlist size: " << playlist.size() << std::endl;
//          currentTrackIndex = -1; // Reset if invalid
//          musicDuration = 0.0;
//          isPlaying = false;
//          isPaused = false;
//          if (gMusic) { Mix_HaltMusic(); Mix_FreeMusic(gMusic); gMusic = nullptr; }
//         return;
//     }

//     if (gMusic) {
//         Mix_HaltMusic(); 
//         Mix_FreeMusic(gMusic);
//         gMusic = nullptr;
//     }
//     gMusic = Mix_LoadMUS(playlist[trackIndex].c_str());
//     if (!gMusic) {
//         std::cerr << "Failed to load music: " << playlist[trackIndex] << " - " << Mix_GetError() << std::endl;
//         // Не меняем currentTrackIndex здесь, чтобы дать возможность выбрать другой трек
//         // Но сбрасываем флаги воспроизведения
//         isPlaying = false;
//         isPaused = false;
//         musicDuration = 0.0;
//         // Удалим битый файл из плейлиста, чтобы не спотыкаться о него снова (опционально, но может быть полезно)
//         // playlist.erase(playlist.begin() + trackIndex);
//         // if (currentTrackIndex >= trackIndex && currentTrackIndex > 0) currentTrackIndex--; // adjust index if needed
//         // else if (playlist.empty()) currentTrackIndex = -1;
//         return;
//     }

//     musicDuration = Mix_MusicDuration(gMusic); 
    
//     if (Mix_PlayMusic(gMusic, 1) == -1) { 
//         std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
//         isPlaying = false;
//         isPaused = false;
//     } else {
//         currentTrackIndex = trackIndex; // Устанавливаем только при успешном запуске
//         isPlaying = true;
//         isPaused = false;
//         if (musicDuration <= 0.001) { 
//             SDL_Delay(50); 
//             musicDuration = Mix_MusicDuration(gMusic);
//         }
//         std::cout << "Playing: " << playlist[trackIndex] << " (Duration: " << std::fixed << std::setprecision(2) << musicDuration << "s)" << std::endl;
//     }
// }

// std::string formatTime(double seconds) {
//     if (seconds < 0 || std::isnan(seconds)) seconds = 0; // Handle NaN
//     int total_seconds = static_cast<int>(round(seconds));
//     int min = total_seconds / 60;
//     int sec = total_seconds % 60;
//     std::ostringstream oss;
//     oss << std::setw(2) << std::setfill('0') << min << ":" << std::setw(2) << std::setfill('0') << sec;
//     return oss.str();
// }

// void drawButtons() {
//     for (auto& btn : buttons) { 
//         SDL_Color currentButtonColor = btn.hovered ? COLOR_BUTTON_HOVER : COLOR_BUTTON;
//         SDL_SetRenderDrawColor(gRenderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, currentButtonColor.a);
//         SDL_RenderFillRect(gRenderer, &btn.rect);

//         int cx = btn.rect.x + btn.rect.w / 2;
//         int cy = btn.rect.y + btn.rect.h / 2;
//         int s = std::min(btn.rect.w, btn.rect.h) / 3; 

//         switch (btn.type) {
//             case BTN_PREV:
//                 drawTriangle(gRenderer, cx + s/2, cy - s, cx + s/2, cy + s, cx - s/2, cy, COLOR_SYMBOL); 
//                 SDL_SetRenderDrawColor(gRenderer, COLOR_SYMBOL.r, COLOR_SYMBOL.g, COLOR_SYMBOL.b, COLOR_SYMBOL.a);
//                 { SDL_Rect bar = {cx - s - 1, cy - s, 2, s * 2}; SDL_RenderFillRect(gRenderer, &bar); } 
//                 break;
//             case BTN_PLAY_PAUSE:
//                 if (isPlaying && !isPaused) { 
//                     SDL_Rect p1 = {cx - s/2 - 1, cy - s, s/2, s * 2};
//                     SDL_Rect p2 = {cx + 1, cy - s, s/2, s * 2};
//                     SDL_SetRenderDrawColor(gRenderer, COLOR_SYMBOL.r, COLOR_SYMBOL.g, COLOR_SYMBOL.b, COLOR_SYMBOL.a);
//                     SDL_RenderFillRect(gRenderer, &p1);
//                     SDL_RenderFillRect(gRenderer, &p2);
//                 } else { 
//                     drawTriangle(gRenderer, cx - s/2, cy - s, cx + s, cy, cx - s/2, cy + s, COLOR_SYMBOL); 
//                 }
//                 break;
//             case BTN_STOP: { 
//                 SDL_Rect stopSq = {cx - s, cy - s, s * 2, s * 2}; 
//                  if (s < 3) stopSq = {cx-2, cy-2, 4, 4}; 
//                 SDL_SetRenderDrawColor(gRenderer, COLOR_SYMBOL.r, COLOR_SYMBOL.g, COLOR_SYMBOL.b, COLOR_SYMBOL.a);
//                 SDL_RenderFillRect(gRenderer, &stopSq);
//                 break;
//             }
//             case BTN_NEXT:
//                 drawTriangle(gRenderer, cx - s/2, cy - s, cx + s, cy, cx - s/2, cy + s, COLOR_SYMBOL); 
//                 SDL_SetRenderDrawColor(gRenderer, COLOR_SYMBOL.r, COLOR_SYMBOL.g, COLOR_SYMBOL.b, COLOR_SYMBOL.a);
//                 { SDL_Rect bar = {cx + s + 1, cy - s, 2, s * 2}; SDL_RenderFillRect(gRenderer, &bar); } 
//                 break;
//             case BTN_VOL_DOWN: {
//                 const char* symbol = "-";
//                 int text_w = 0, text_h = 0;
//                 if (gFontInfo && TTF_SizeUTF8(gFontInfo, symbol, &text_w, &text_h) == 0) {
//                     renderText(symbol, cx - text_w / 2, cy - text_h / 2, gFontInfo, COLOR_SYMBOL);
//                 } else {
//                     renderText(symbol, cx - FONT_SIZE_INFO / 4, cy - FONT_SIZE_INFO / 2, gFontInfo, COLOR_SYMBOL); 
//                 }
//                 break;
//             }
//             case BTN_VOL_UP: {
//                 const char* symbol = "+";
//                 int text_w = 0, text_h = 0;
//                 if (gFontInfo && TTF_SizeUTF8(gFontInfo, symbol, &text_w, &text_h) == 0) {
//                     renderText(symbol, cx - text_w / 2, cy - text_h / 2, gFontInfo, COLOR_SYMBOL);
//                 } else {
//                     renderText(symbol, cx - FONT_SIZE_INFO / 4, cy - FONT_SIZE_INFO / 2, gFontInfo, COLOR_SYMBOL); 
//                 }
//                 break;
//             }
//         }
//     }
// }

// void setupButtons() {
//     buttons.clear();
//     int btn_w = 50; 
//     int btn_h = 40; 
//     int btn_spacing = 10;
//     int total_main_btn_width = 4 * btn_w + 3 * btn_spacing;
//     int volume_btn_w = 35; 
//     int total_width_all = total_main_btn_width + 2 * volume_btn_w + 2 * btn_spacing + 20; 

//     int start_x_main = (SCREEN_WIDTH - total_width_all) / 2;
//     int y_pos = SCREEN_HEIGHT - btn_h - 15 - 35; 

//     buttons.push_back({{start_x_main, y_pos, btn_w, btn_h}, BTN_PREV});
//     buttons.push_back({{start_x_main + btn_w + btn_spacing, y_pos, btn_w, btn_h}, BTN_PLAY_PAUSE});
//     buttons.push_back({{start_x_main + 2*(btn_w + btn_spacing), y_pos, btn_w, btn_h}, BTN_STOP});
//     buttons.push_back({{start_x_main + 3*(btn_w + btn_spacing), y_pos, btn_w, btn_h}, BTN_NEXT});

//     int vol_start_x = start_x_main + total_main_btn_width + btn_spacing + 20; 
//     buttons.push_back({{vol_start_x, y_pos + (btn_h - volume_btn_w)/2, volume_btn_w, volume_btn_w}, BTN_VOL_DOWN});
//     buttons.push_back({{vol_start_x + volume_btn_w + btn_spacing, y_pos+ (btn_h - volume_btn_w)/2, volume_btn_w, volume_btn_w}, BTN_VOL_UP});
// }

// void drawProgressBar() {
//     int bar_height = 12;
//     int bar_margin_x = 20;
//     int bar_y_pos = SCREEN_HEIGHT - 40; 

//     progressBarRect = {bar_margin_x, bar_y_pos, SCREEN_WIDTH - 2 * bar_margin_x - 100, bar_height}; 

//     SDL_SetRenderDrawColor(gRenderer, COLOR_PROGRESS_BG.r, COLOR_PROGRESS_BG.g, COLOR_PROGRESS_BG.b, COLOR_PROGRESS_BG.a);
//     SDL_RenderFillRect(gRenderer, &progressBarRect);

//     double currentTime = 0.0;
//     if (gMusic) { // Проверяем, существует ли gMusic
//         if (Mix_PlayingMusic() || Mix_PausedMusic()) {
//              currentTime = Mix_GetMusicPosition(gMusic);
//         } else if (!isPlaying && !isPaused && currentTrackIndex != -1) { 
//             currentTime = 0.0; 
//         }
//     }


//     if (musicDuration > 0.001) { 
//         double progress = (currentTime / musicDuration);
//         if (progress > 1.0) progress = 1.0;
//         if (progress < 0.0) progress = 0.0;

//         SDL_Rect fgRect = {progressBarRect.x, progressBarRect.y, (int)(progressBarRect.w * progress), progressBarRect.h};
//         SDL_SetRenderDrawColor(gRenderer, COLOR_PROGRESS_FG.r, COLOR_PROGRESS_FG.g, COLOR_PROGRESS_FG.b, COLOR_PROGRESS_FG.a);
//         SDL_RenderFillRect(gRenderer, &fgRect);
//     }
    
//     std::string timeStr = formatTime(currentTime) + " / " + formatTime(musicDuration > 0.001 ? musicDuration : 0.0);
//     renderText(timeStr, progressBarRect.x + progressBarRect.w + 10, progressBarRect.y - FONT_SIZE_INFO/4 + 2, gFontInfo, COLOR_TEXT);
// }

// void handleButtonClick(ButtonType type) {
//     switch (type) {
//         case BTN_PREV:
//             if (!playlist.empty()) {
//                 int prevIndex = currentTrackIndex;
//                 if (currentTrackIndex == -1 || playlist.empty()) { // Если ничего не играло или плейлист пуст, но был передан файл
//                      if(!playlist.empty()) prevIndex = playlist.size() -1;
//                      else return; // Нечего играть
//                 }
//                 else if (currentTrackIndex == 0) prevIndex = playlist.size() - 1; // зациклить с конца
//                 else prevIndex = currentTrackIndex - 1;
//                 loadAndPlayTrack(prevIndex);
//             }
//             break;
//         case BTN_PLAY_PAUSE:
//             if (!gMusic && !playlist.empty()) { 
//                  loadAndPlayTrack(currentTrackIndex != -1 ? currentTrackIndex : 0); 
//             } else if (gMusic) {
//                 if (Mix_PlayingMusic()) { 
//                     if (Mix_PausedMusic()) {
//                         Mix_ResumeMusic();
//                     } else {
//                         Mix_PauseMusic();
//                     }
//                 } else { 
//                     if(currentTrackIndex != -1) loadAndPlayTrack(currentTrackIndex); 
//                     else if (!playlist.empty()) loadAndPlayTrack(0);
//                 }
//             }
//             // Обновляем isPlaying/isPaused в конце цикла, а не здесь
//             break;
//         case BTN_STOP:
//             if (gMusic) {
//                 Mix_HaltMusic();
//                 // isPlaying и isPaused будут обновлены в главном цикле
//             }
//             break;
//         case BTN_NEXT:
//              if (!playlist.empty()) {
//                 int nextIndex = 0; 
//                 if (currentTrackIndex != -1) {
//                     nextIndex = (currentTrackIndex + 1) % playlist.size();
//                 }
//                 loadAndPlayTrack(nextIndex);
//             }
//             break;
//         case BTN_VOL_DOWN:
//             volume = Mix_VolumeMusic(Mix_VolumeMusic(-1) - MIX_MAX_VOLUME / 16); 
//             if (volume < 0) volume = Mix_VolumeMusic(0); // Установка и получение
//             break;
//         case BTN_VOL_UP:
//             volume = Mix_VolumeMusic(Mix_VolumeMusic(-1) + MIX_MAX_VOLUME / 16);
//             if (volume > MIX_MAX_VOLUME) volume = Mix_VolumeMusic(MIX_MAX_VOLUME);
//             break;
//     }
// }

// void musicFinishedCallback() {
//     // isPlaying проверяется в главном цикле
//     if (Mix_PlayingMusic() == 0 && Mix_PausedMusic() == 0 && currentTrackIndex != -1 && gMusic) { // Проверка что не остановлено и не на паузе
//         if (!playlist.empty()) {
//             std::cout << "Music finished callback - auto next track." << std::endl;
//             int nextIndex = (currentTrackIndex + 1) % playlist.size();
//             loadAndPlayTrack(nextIndex);
//         } else {
//              std::cout << "Music finished callback - playlist empty." << std::endl;
//         }
//     }
// }

// void close() {
//     if (gMusic) Mix_FreeMusic(gMusic);
//     Mix_HookMusicFinished(nullptr); 
//     Mix_CloseAudio();
//     Mix_Quit();

//     if (gFontTitle) TTF_CloseFont(gFontTitle);
//     if (gFontInfo) TTF_CloseFont(gFontInfo);
//     TTF_Quit();

//     if (gRenderer) SDL_DestroyRenderer(gRenderer);
//     if (gWindow) SDL_DestroyWindow(gWindow);
//     SDL_Quit();
// }

// // Переименовал main аргумент для ясности (argc, argv)
// int main(int argc, char* argv[]) { // Было (int argc, char* args[])
//     if (!init()) {
//         std::cerr << "Failed to initialize!" << std::endl;
//         close(); 
//         return 1;
//     }

//     std::string initialFileToPlay = "";
//     bool playInitialFile = false;

//     // --- ОБРАБОТКА АРГУМЕНТА КОМАНДНОЙ СТРОКИ ---
//     if (argc > 1) {
//         std::string filePathArg = argv[1]; // Используем argv
//         try { // Добавим try-catch для std::filesystem
//             if (std::filesystem::exists(filePathArg) && std::filesystem::is_regular_file(filePathArg)) {
//                 std::string ext = std::filesystem::path(filePathArg).extension().string();
//                 std::transform(ext.begin(), ext.end(), ext.begin(), 
//                     [](unsigned char c){ return std::tolower(c); });
//                 if (ext == ".mp3" || ext == ".ogg" || ext == ".wav" || ext == ".flac") {
//                     initialFileToPlay = filePathArg;
//                     playInitialFile = true; // Устанавливаем флаг, что нужно играть этот файл
//                     std::cout << "Will attempt to play from argument: " << initialFileToPlay << std::endl;
//                 } else {
//                     std::cerr << "Unsupported file type from argument: " << filePathArg << std::endl;
//                 }
//             } else {
//                 std::cerr << "File from argument not found or not a regular file: " << filePathArg << std::endl;
//             }
//         } catch (const std::filesystem::filesystem_error& fs_err) {
//             std::cerr << "Filesystem error checking argument: " << fs_err.what() << std::endl;
//         }
//     }
//     // --- КОНЕЦ ОБРАБОТКИ АРГУМЕНТА ---


//     loadPlaylist(); // Загружаем основной плейлист из папки 'music'

//     if (playInitialFile) {
//         // Поищем, есть ли этот файл уже в основном плейлисте (например, если он лежит в ./music)
//         auto it = std::find(playlist.begin(), playlist.end(), initialFileToPlay);
//         if (it != playlist.end()) {
//             // Файл уже в плейлисте, просто установим currentTrackIndex
//             currentTrackIndex = std::distance(playlist.begin(), it);
//         } else {
//             // Файла нет в основном плейлисте, добавляем его в начало
//             playlist.insert(playlist.begin(), initialFileToPlay);
//             currentTrackIndex = 0; // Теперь этот файл - первый в плейлисте
//         }
//         // Загружаем и играем этот трек
//         if(currentTrackIndex != -1 && currentTrackIndex < static_cast<int>(playlist.size())) {
//              std::cout << "Loading and playing track from argument: " << playlist[currentTrackIndex] << std::endl;
//              loadAndPlayTrack(currentTrackIndex);
//         } else {
//             std::cerr << "Failed to set up track from argument for playing." << std::endl;
//             playInitialFile = false; // Сбрасываем флаг, если что-то пошло не так
//             currentTrackIndex = -1;
//         }
//     }

//     if (!playInitialFile && currentTrackIndex == -1) { // Если не было файла из аргумента (или он не загрузился) И НИЧЕГО ЕЩЕ НЕ ВЫБРАНО
//         if (!playlist.empty()) {
//             // Загружаем метаданные первого трека из папки 'music' без воспроизведения (как раньше)
//             if (gMusic) { Mix_HaltMusic(); Mix_FreeMusic(gMusic); gMusic = nullptr; }
//             gMusic = Mix_LoadMUS(playlist[0].c_str()); 
//             if (gMusic) {
//                 musicDuration = Mix_MusicDuration(gMusic);
//                 if (musicDuration <= 0.001 && Mix_PlayMusic(gMusic, 0) == 0) { // Пробный плей для получения длительности VBR
//                     Mix_HaltMusic();
//                     musicDuration = Mix_MusicDuration(gMusic);
//                 }
//                 currentTrackIndex = 0; 
//                  std::cout << "Preloaded metadata for: " << playlist[0] << std::endl;
//             } else {
//                  std::cerr << "Failed to preload metadata for first track in playlist: " << playlist[0] << " - " << Mix_GetError() << std::endl;
//                  musicDuration = 0.0;
//             }
//         } else {
//             std::cout << "Playlist is empty and no file provided via argument." << std::endl;
//              musicDuration = 0.0;
//         }
//     }


//     setupButtons();
//     Mix_HookMusicFinished(musicFinishedCallback); 

//     bool quit = false;
//     SDL_Event e;

//     while (!quit) {
//         while (SDL_PollEvent(&e) != 0) {
//             if (e.type == SDL_QUIT) {
//                 quit = true;
//             } else if (e.type == SDL_MOUSEMOTION) {
//                 int x, y;
//                 SDL_GetMouseState(&x, &y);
//                 for (auto& btn : buttons) {
//                     btn.hovered = (x >= btn.rect.x && x <= btn.rect.x + btn.rect.w &&
//                                    y >= btn.rect.y && y <= btn.rect.y + btn.rect.h);
//                 }
//             } else if (e.type == SDL_MOUSEBUTTONDOWN) {
//                 if (e.button.button == SDL_BUTTON_LEFT) {
//                     int x, y;
//                     SDL_GetMouseState(&x, &y);
//                     for (const auto& btn : buttons) { 
//                         if (btn.hovered) {
//                             handleButtonClick(btn.type);
//                             break; 
//                         }
//                     }
//                     if (x >= progressBarRect.x && x <= progressBarRect.x + progressBarRect.w &&
//                         y >= progressBarRect.y && y <= progressBarRect.y + progressBarRect.h) {
//                         if (gMusic && musicDuration > 0.001) {
//                             double seekRatio = (double)(x - progressBarRect.x) / progressBarRect.w;
//                             double seekPos = seekRatio * musicDuration;
                            
//                             int was_playing = Mix_PlayingMusic() && !Mix_PausedMusic(); // Был ли трек активен
//                             int was_paused = Mix_PausedMusic();

//                             if(Mix_SetMusicPosition(seekPos) == -1) {
//                                 std::cerr << "SDL_mixer Error (Mix_SetMusicPosition): " << Mix_GetError() << std::endl;
//                             } else {
//                                 if (was_playing) { // Если трек играл, убедимся, что он продолжает играть
//                                      // SDL_Mixer для некоторых форматов (mp3) может остановить воспроизведение после seek.
//                                      // Если он не играет, но должен - запустим снова.
//                                      if (!Mix_PlayingMusic()) {
//                                         Mix_PlayMusic(gMusic, 1); // Воспроизвести один раз
//                                      }
//                                 } else if (was_paused) {
//                                     // Если был на паузе, он останется на паузе на новой позиции, это ок.
//                                     // SDL_mixer обычно сохраняет состояние паузы при перемотке.
//                                 }
//                                 // Обновляем флаги, так как состояние могло измениться
//                                 isPlaying = Mix_PlayingMusic() && !Mix_PausedMusic();
//                                 isPaused = Mix_PausedMusic();
//                             }
//                         }
//                     }
//                 }
//             } else if (e.type == SDL_KEYDOWN) {
//                 switch(e.key.keysym.sym) {
//                     case SDLK_SPACE: handleButtonClick(BTN_PLAY_PAUSE); break;
//                     case SDLK_s: case SDLK_STOP: handleButtonClick(BTN_STOP); break; 
//                     case SDLK_LEFT: 
//                         if(e.key.keysym.mod & KMOD_CTRL) handleButtonClick(BTN_VOL_DOWN);
//                         else handleButtonClick(BTN_PREV); 
//                         break;
//                     case SDLK_RIGHT: 
//                         if(e.key.keysym.mod & KMOD_CTRL) handleButtonClick(BTN_VOL_UP);
//                         else handleButtonClick(BTN_NEXT); 
//                         break;
//                     case SDLK_MINUS: case SDLK_DOWN: handleButtonClick(BTN_VOL_DOWN); break; 
//                     case SDLK_PLUS: case SDLK_EQUALS: case SDLK_UP: handleButtonClick(BTN_VOL_UP); break;  
//                     case SDLK_q: quit = true; break;
//                 }
//             }
//         }
        
//         if (gMusic) {
//             isPlaying = Mix_PlayingMusic() && !Mix_PausedMusic();
//             isPaused = Mix_PausedMusic();

//             // Проверка на завершение трека вручную, если Mix_HookMusicFinished по какой-то причине не сработал
//             // Это дополнительная страховка, но Mix_HookMusicFinished должен быть основным механизмом.
//             if (!isPlaying && !isPaused && Mix_PlayingMusic() == 0 && currentTrackIndex != -1 && Mix_MusicDuration(gMusic) > 0 && Mix_GetMusicPosition(gMusic) >= Mix_MusicDuration(gMusic) - 0.1 ) {
//                 // Условие: не играет, не на паузе, музыкальный объект есть, трек выбран, длительность есть, позиция в конце.
//                 // Не вызываем musicFinishedCallback напрямую, чтобы избежать двойного вызова, если хук сработает.
//                 // Хук надежнее. Но isPlaying обновится и это должно корректно отразиться.
//             }

//         } else { // Если gMusic == nullptr (например, после неудачной загрузки)
//             isPlaying = false;
//             isPaused = false;
//             musicDuration = 0.0; // Также сбросить длительность
//         }


//         SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
//         SDL_RenderClear(gRenderer);

//         if (currentTrackIndex != -1 && currentTrackIndex < static_cast<int>(playlist.size())) {
//             std::filesystem::path p(playlist[currentTrackIndex]);
//             renderText(p.filename().string(), 20, 15, gFontTitle, COLOR_TEXT);
//         } else if (!playlist.empty()){ // Если currentTrackIndex = -1, но плейлист есть
//              renderText("Select a track or press play", 20, 15, gFontTitle, COLOR_TEXT);
//         }
//          else { // Плейлист пуст
//             renderText("No music. Put files in 'music' or open a file.", 20, 15, gFontTitle, COLOR_TEXT);
//         }
        
//         volume = Mix_VolumeMusic(-1); // Получить актуальную громкость
//         std::string volText = "Vol: " + std::to_string((int)round(volume * 100.0 / MIX_MAX_VOLUME)) + "%";
//         renderText(volText, SCREEN_WIDTH - 120, 15, gFontInfo, COLOR_TEXT);


//         drawProgressBar();
//         drawButtons();

//         SDL_RenderPresent(gRenderer);
//         SDL_Delay(16); 
//     }

//     close();
//     return 0;
// }









