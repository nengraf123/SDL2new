// #include <iostream>
// #include <stdio.h>
// #include <SDL2/SDL.h>
#include <cmath>

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
///g++ main.cpp -o music_player $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_mixer -lstdc++fs -std=c++17
///
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




/////////////////////////////////////////////////////////// просмотр изображений 
///g++ main.cpp -o image_viewer $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf -lstdc++fs -std=c++17
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <exception>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <filesystem> // C++17
// #include <algorithm>  // std::sort, std::find, std::min, std::max
// #include <cmath>      // std::round, M_PI (для окружности), std::abs, std::isnan
// #include <iomanip>    // Для отладки может пригодиться
// #include <sstream>    // Для конкатенации строк с fs_err.what()

// // --- Конфигурация ---
// const int DEFAULT_SCREEN_WIDTH = 1024;
// const int DEFAULT_SCREEN_HEIGHT = 768;
// const char* FONT_PATH = "/usr/share/fonts/TTF/DejaVuSans.ttf"; 
// const int FONT_SIZE_INFO = 18;
// const int FONT_SIZE_BUTTON = 16; 

// // --- Цвета (Темная тема) ---
// const SDL_Color COLOR_BACKGROUND = {0x1E, 0x1E, 0x1E, 0xFF}; 
// const SDL_Color COLOR_TEXT = {0xF0, 0xF0, 0xF0, 0xFF};
// const SDL_Color COLOR_BUTTON_BG = {0x3A, 0x3A, 0x3A, 0xFF};
// const SDL_Color COLOR_BUTTON_HOVER_BG = {0x5A, 0x5A, 0x5A, 0xFF};
// const SDL_Color COLOR_BUTTON_SYMBOL = {0xE0, 0xE0, 0xE0, 0xFF};
// const SDL_Color COLOR_INFO_PANEL_BG = {0x2A, 0x2A, 0x2A, 0xD0}; 

// // --- Глобальные переменные ---
// SDL_Window* gWindow = nullptr;
// SDL_Renderer* gRenderer = nullptr;
// TTF_Font* gFontInfo = nullptr;
// TTF_Font* gFontButton = nullptr; 
// SDL_Texture* gImageTexture = nullptr;

// int gImageWidth = 0;
// int gImageHeight = 0;
// std::string gCurrentImagePath = "";
// std::vector<std::string> gImagePlaylist;
// int gCurrentImageIndex = -1;

// float gZoomFactor = 1.0f;
// SDL_FPoint gViewOffset = {0.0f, 0.0f}; 
// SDL_Point gPanStartMouse = {0,0};      
// SDL_FPoint gPanStartOffset = {0.0f,0.0f}; 
// bool gIsPanning = false;
// bool gFitToWindow = true; 

// int gWindowWidth = DEFAULT_SCREEN_WIDTH;
// int gWindowHeight = DEFAULT_SCREEN_HEIGHT;

// enum class ButtonAction { NONE, PREV_IMG, NEXT_IMG, ZOOM_IN, ZOOM_OUT, TOGGLE_FIT, RESET_VIEW, OPEN_FILE };
// struct UIButton {
//     SDL_Rect rect;
//     ButtonAction action;
//     std::string tooltip; 
//     bool hovered = false;
//     void (*drawSymbol)(SDL_Renderer* renderer, const SDL_Rect& r, const SDL_Color& c, bool is_hovered); 
// };
// std::vector<UIButton> gButtons;

// // --- Вспомогательные функции ---
// void renderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, bool centered_x = false, int parent_w = 0) {
//     if (!font || text.empty()) return;
//     SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
//     if (!textSurface) {
//         return;
//     }
//     SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//     if (!textTexture) {
//         SDL_FreeSurface(textSurface);
//         return;
//     }
//     SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
//     if (centered_x && parent_w > 0) {
//         dstRect.x = x + (parent_w - dstRect.w) / 2;
//     }
//     SDL_RenderCopy(gRenderer, textTexture, nullptr, &dstRect);
//     SDL_FreeSurface(textSurface);
//     SDL_DestroyTexture(textTexture);
// }

// void drawTriangleSymbol(SDL_Renderer* renderer, const SDL_Rect& btnRect, SDL_Color color, bool point_right) {
//     int s = std::min(btnRect.w, btnRect.h) / 4; 
//     int cx = btnRect.x + btnRect.w / 2;
//     int cy = btnRect.y + btnRect.h / 2;
    
//     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//     for (int y_scan = cy - s; y_scan <= cy + s; ++y_scan) {
//         int x_start, x_end;
//         float progress = (float)(y_scan - (cy - s)) / (2.0f * s); 
//         if (progress < 0.0f) progress = 0.0f;
//         if (progress > 1.0f) progress = 1.0f;

//         if (point_right) {
//             x_start = cx - s;
//             x_end = cx - s + static_cast<int>(2 * s * (0.5f - std::abs(0.5f - progress)));
//         } else {
//              x_start = cx + s - static_cast<int>(2 * s * (0.5f - std::abs(0.5f - progress)));
//              x_end = cx + s;
//         }
//          if (x_start <= x_end) SDL_RenderDrawLine(renderer, x_start, y_scan, x_end, y_scan);
//     }
// }

// void drawPrevSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){ drawTriangleSymbol(r, rect, c, false); }
// void drawNextSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){ drawTriangleSymbol(r, rect, c, true); }
// void drawZoomInSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){ 
//     int s = std::min(rect.w, rect.h) / 5; int cx = rect.x+rect.w/2; int cy = rect.y+rect.h/2;
//     SDL_SetRenderDrawColor(r, c.r,c.g,c.b,c.a);
//     SDL_RenderDrawLine(r, cx-s,cy, cx+s,cy); SDL_RenderDrawLine(r, cx,cy-s, cx,cy+s); 
// }
// void drawZoomOutSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){
//     int s = std::min(rect.w, rect.h) / 5; int cx = rect.x+rect.w/2; int cy = rect.y+rect.h/2;
//     SDL_SetRenderDrawColor(r, c.r,c.g,c.b,c.a);
//     SDL_RenderDrawLine(r, cx-s,cy, cx+s,cy); 
// }
// void drawFitSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h) { 
//     int s_outer = std::min(rect.w, rect.h) / 4; 
//     int s_inner = s_outer / 2; 
//     int cx = rect.x + rect.w / 2;
//     int cy = rect.y + rect.h / 2;
//     SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
//     SDL_RenderDrawLine(r, cx - s_outer, cy - s_outer, cx - s_inner, cy - s_inner);
//     SDL_RenderDrawLine(r, cx - s_inner, cy - s_inner, cx - s_inner, cy - s_inner + s_inner / 2);
//     SDL_RenderDrawLine(r, cx - s_inner, cy - s_inner, cx - s_inner + s_inner / 2, cy - s_inner);
//     SDL_RenderDrawLine(r, cx + s_outer, cy + s_outer, cx + s_inner, cy + s_inner);
//     SDL_RenderDrawLine(r, cx + s_inner, cy + s_inner, cx + s_inner, cy + s_inner - s_inner / 2);
//     SDL_RenderDrawLine(r, cx + s_inner, cy + s_inner, cx + s_inner - s_inner / 2, cy + s_inner);
// }
// void drawResetSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h) { 
//     int radius = std::min(rect.w, rect.h) / 4;
//     int cx = rect.x + rect.w / 2;
//     int cy = rect.y + rect.h / 2;
//     SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
//     for (int i = 0; i < 360; i += 5) { 
//         float angle = i * M_PI / 180.0f;
//         float next_angle = (i+5) * M_PI / 180.0f;
//          SDL_RenderDrawLine(r, cx + static_cast<int>(radius * cos(angle)), 
//                                cy + static_cast<int>(radius * sin(angle)),
//                                cx + static_cast<int>(radius * cos(next_angle)), 
//                                cy + static_cast<int>(radius * sin(next_angle)));
//     }
//     SDL_RenderDrawLine(r, cx - radius/2, cy - radius/2, cx + radius/2, cy + radius/2);
//     SDL_RenderDrawLine(r, cx + radius/2, cy - radius/2, cx - radius/2, cy + radius/2);
// }

// void setupUIButtons() {
//     gButtons.clear();
//     int btn_size = 36;
//     int btn_spacing = 8;
//     int current_x = btn_spacing; 
//     int y_pos = gWindowHeight - btn_size - btn_spacing; 

//     gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::PREV_IMG, "Previous (Left Arrow)", false, drawPrevSymbol});
//     current_x += btn_size + btn_spacing;
//     gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::NEXT_IMG, "Next (Right Arrow)", false, drawNextSymbol});
//     current_x += btn_size + btn_spacing + btn_spacing*2; 
    
//     gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::ZOOM_OUT, "Zoom Out (-)", false, drawZoomOutSymbol});
//     current_x += btn_size + btn_spacing;
//     gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::ZOOM_IN, "Zoom In (+)", false, drawZoomInSymbol});
//     current_x += btn_size + btn_spacing + btn_spacing*2; 

//     gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::TOGGLE_FIT, "Toggle Fit/Actual (0)", false, drawFitSymbol});
//     current_x += btn_size + btn_spacing;
//     gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::RESET_VIEW, "Reset View (R)", false, drawResetSymbol});
// }

// void drawUI() {
//     SDL_Rect infoPanelRect; 
//     infoPanelRect.x = 0;
//     infoPanelRect.w = gWindowWidth;
//     infoPanelRect.h = FONT_SIZE_INFO + 12; 
//     if (!gButtons.empty()){
//         infoPanelRect.y = gButtons[0].rect.y - infoPanelRect.h - 5; 
//     } else {
//         infoPanelRect.y = gWindowHeight - infoPanelRect.h - 5; 
//     }

//     if (gImageTexture || !gCurrentImagePath.empty()) { 
//         SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); 
//         SDL_SetRenderDrawColor(gRenderer, COLOR_INFO_PANEL_BG.r, COLOR_INFO_PANEL_BG.g, COLOR_INFO_PANEL_BG.b, COLOR_INFO_PANEL_BG.a);
//         SDL_RenderFillRect(gRenderer, &infoPanelRect);
        
//         std::string filename_str = "Error"; 
//         if (!gCurrentImagePath.empty()) {
//             if (gCurrentImagePath.rfind("Error: ", 0) != 0) { 
//                try { 
//                    filename_str = std::filesystem::path(gCurrentImagePath).filename().string(); 
//                } catch (const std::filesystem::filesystem_error& ) { 
//                    filename_str = "Invalid Path"; 
//                } catch (...) {
//                    filename_str = "Unknown Path Error";
//                }
//             } else {
//                 filename_str = gCurrentImagePath; 
//             }
//         } else if (gImageTexture) { 
//             filename_str = "[Image loaded, no path]";
//         }


//         std::string infoText = filename_str;
//         if(gImageWidth > 0 && gImageHeight > 0) infoText += " (" + std::to_string(gImageWidth) + "x" + std::to_string(gImageHeight) + ")";
//         infoText += " Z: " + std::to_string((int)std::round(gZoomFactor*100)) + "%";
        
//         if(gCurrentImageIndex != -1 && !gImagePlaylist.empty()) {
//             infoText += " [" + std::to_string(gCurrentImageIndex + 1) + "/" + std::to_string(gImagePlaylist.size()) + "]";
//         }
//         infoText += gFitToWindow ? " (Fit)" : " (Actual)";
//         renderText(infoText, 10, infoPanelRect.y + (infoPanelRect.h - FONT_SIZE_INFO)/2, gFontInfo, COLOR_TEXT);
//     }
    
//     for (const auto& btn : gButtons) {
//         SDL_Color bgColor = btn.hovered ? COLOR_BUTTON_HOVER_BG : COLOR_BUTTON_BG;
//         SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
//         SDL_RenderFillRect(gRenderer, &btn.rect);
//         if (btn.drawSymbol) {
//             btn.drawSymbol(gRenderer, btn.rect, COLOR_BUTTON_SYMBOL, btn.hovered);
//         }
//         if(btn.hovered && !btn.tooltip.empty()){
//             int text_w = 0, text_h = 0; 
//             if (gFontInfo) { 
//                 TTF_SizeUTF8(gFontInfo, btn.tooltip.c_str(), &text_w, &text_h);
//             }
            
//             int tip_x = btn.rect.x + (btn.rect.w - text_w)/2;
//             tip_x = std::max(5, std::min(tip_x, gWindowWidth - text_w - 5)); 
//             int tip_y = btn.rect.y - text_h - 5;
//             if(tip_y < 5) tip_y = btn.rect.y + btn.rect.h + 5; 

//             renderText(btn.tooltip, tip_x, tip_y, gFontInfo, COLOR_TEXT);
//         }
//     }
// }

// bool init() {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//         return false;
//     }
//     // ***************** ИСПРАВЛЕНИЕ ДЛЯ ПИКСЕЛИЗАЦИИ *****************
//     if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE) { // "1" for linear filtering
//         std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
//     }
//     // ****************************************************************

//     gWindow = SDL_CreateWindow("SDL Image Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
//                                DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
//     if (!gWindow) {
//         std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//         return false;
//     }
//     SDL_GetWindowSize(gWindow, &gWindowWidth, &gWindowHeight);

//     gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (!gRenderer) {
//         std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//         return false;
//     }
//     SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

//     int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF; 
//     if (!(IMG_Init(imgFlags) & imgFlags)) {
//         std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
//         return false;
//     }

//     if (TTF_Init() == -1) {
//         std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
//         return false;
//     }
//     gFontInfo = TTF_OpenFont(FONT_PATH, FONT_SIZE_INFO);
//     gFontButton = TTF_OpenFont(FONT_PATH, FONT_SIZE_BUTTON); 
//     if (!gFontInfo || !gFontButton) {
//         std::cerr << "Failed to load font: " << FONT_PATH << "! TTF_Error: " << TTF_GetError() << std::endl;
//         TTF_CloseFont(gFontInfo); TTF_CloseFont(gFontButton);
//         gFontInfo = TTF_OpenFont("sans.ttf", FONT_SIZE_INFO);
//         gFontButton = TTF_OpenFont("sans.ttf", FONT_SIZE_BUTTON);
//         if (!gFontInfo || !gFontButton) {
//              std::cerr << "Failed to load fallback font 'sans.ttf'! TTF_Error: " << TTF_GetError() << std::endl;
//             return false;
//         }
//     }
//     setupUIButtons(); 
//     return true;
// }

// void calculateInitialZoomAndOffset() {
//     if (!gImageTexture || gImageWidth == 0 || gImageHeight == 0) return;

//     if (gFitToWindow) {
//         float scaleX = (float)gWindowWidth / gImageWidth;
//         float scaleY = (float)gWindowHeight / gImageHeight;
//         gZoomFactor = std::min(1.0f, std::min(scaleX, scaleY)); 
//     } else {
//         gZoomFactor = 1.0f; 
//     }
//     gViewOffset.x = (gWindowWidth - (gImageWidth * gZoomFactor)) / 2.0f;
//     gViewOffset.y = (gWindowHeight - (gImageHeight * gZoomFactor)) / 2.0f;
// }

// void resetView(bool keep_fit_mode = false) { 
//     if(!keep_fit_mode) gFitToWindow = true; 
//     calculateInitialZoomAndOffset();
// }

// bool loadImage(const std::string& path) {
//     if (gImageTexture) {
//         SDL_DestroyTexture(gImageTexture);
//         gImageTexture = nullptr;
//     }
//     gImageWidth = 0;
//     gImageHeight = 0;
    
//     if (path.empty()){
//         gCurrentImagePath = ""; 
//         return false; 
//     }
    
//     SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
//     if (!newTexture) {
//         std::string errorMsg = IMG_GetError();
//         std::cerr << "Unable to load image " << path << "! SDL_image Error: " << errorMsg << std::endl;
//         try {
//              gCurrentImagePath = std::string("Error: ") + std::filesystem::path(path).filename().string() + " (" + errorMsg + ")"; 
//         } catch (const std::filesystem::filesystem_error& fs_err){ 
//              gCurrentImagePath = std::string("Error loading (invalid path: ") + fs_err.what() + ")"; 
//         } catch (...){ 
//             gCurrentImagePath = "Error loading (unknown path error)";
//         }
//         return false;
//     }

//     gImageTexture = newTexture;
//     SDL_QueryTexture(gImageTexture, nullptr, nullptr, &gImageWidth, &gImageHeight);
//     gCurrentImagePath = path; 
    
//     resetView(true); 

//     std::cout << "Loaded: " << path << " (" << gImageWidth << "x" << gImageHeight << ")" << std::endl;
//     return true;
// }

// void loadImagePlaylist(const std::string& currentFilePathOrDir) {
//     gImagePlaylist.clear();
    
//     std::filesystem::path basePath;
//     std::string targetFileToFind;

//     try {
//         if (!currentFilePathOrDir.empty() && std::filesystem::exists(currentFilePathOrDir)) {
//             if (std::filesystem::is_regular_file(currentFilePathOrDir)) {
//                 basePath = std::filesystem::path(currentFilePathOrDir).parent_path();
//                 targetFileToFind = currentFilePathOrDir;
//             } else if (std::filesystem::is_directory(currentFilePathOrDir)) {
//                 basePath = currentFilePathOrDir;
//             } else { 
//                 basePath = std::filesystem::current_path();
//             }
//         } else { 
//             basePath = std::filesystem::current_path();
//         }

//         if (!std::filesystem::exists(basePath) || !std::filesystem::is_directory(basePath)) {
//              std::cerr << "Playlist base path is not a valid directory: " << basePath.string() << std::endl;
//              if(!targetFileToFind.empty() && std::filesystem::exists(targetFileToFind) && std::filesystem::is_regular_file(targetFileToFind)){
//                 gImagePlaylist.push_back(targetFileToFind);
//              }
//             return;
//         }

//         for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
//             if (entry.is_regular_file()) {
//                 std::string ext = entry.path().extension().string();
//                 std::transform(ext.begin(), ext.end(), ext.begin(),
//                                [](unsigned char c){ return std::tolower(c); });
//                 if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp" ||
//                     ext == ".gif" || ext == ".tga" || ext == ".webp" || ext == ".tif" || ext == ".tiff") {
//                     gImagePlaylist.push_back(entry.path().string());
//                 }
//             }
//         }
//         if (!gImagePlaylist.empty()) std::sort(gImagePlaylist.begin(), gImagePlaylist.end());
        
//         gCurrentImageIndex = -1; 
//         if(!targetFileToFind.empty()){ 
//             auto it = std::find(gImagePlaylist.begin(), gImagePlaylist.end(), targetFileToFind);
//             if (it != gImagePlaylist.end()) { 
//                 gCurrentImageIndex = std::distance(gImagePlaylist.begin(), it);
//             } else { 
//                  if(std::filesystem::exists(targetFileToFind) && std::filesystem::is_regular_file(targetFileToFind)){
//                      bool found_after_add = false;
//                      for(size_t i = 0; i < gImagePlaylist.size(); ++i) { 
//                         try { 
//                             if(std::filesystem::equivalent(gImagePlaylist[i], targetFileToFind)) {
//                                 gCurrentImageIndex = i;
//                                 found_after_add = true;
//                                 break;
//                             }
//                         } catch (const std::filesystem::filesystem_error&) { /* Пропускаем */ }
//                      }
//                      if(!found_after_add) {
//                         gImagePlaylist.insert(gImagePlaylist.begin(), targetFileToFind); 
//                         std::sort(gImagePlaylist.begin(), gImagePlaylist.end()); 
//                         it = std::find(gImagePlaylist.begin(), gImagePlaylist.end(), targetFileToFind);
//                         if(it != gImagePlaylist.end()) gCurrentImageIndex = std::distance(gImagePlaylist.begin(), it);
//                      }
//                  } else if (!gImagePlaylist.empty()) { 
//                     gCurrentImageIndex = 0;
//                  }
//             }
//         } else if (!gImagePlaylist.empty()) { 
//             gCurrentImageIndex = 0; 
//         }

//     } catch (const std::filesystem::filesystem_error& e) {
//         std::cerr << "Error scanning directory " << basePath.string() << ": " << e.what() << std::endl;
//          if(!targetFileToFind.empty() && std::filesystem::exists(targetFileToFind) && std::filesystem::is_regular_file(targetFileToFind) && gImagePlaylist.empty()){
//             gImagePlaylist.push_back(targetFileToFind);
//             gCurrentImageIndex = 0; 
//         } else if (gImagePlaylist.empty()) {
//             gCurrentImageIndex = -1; 
//         }
//     }
// }

// void navigateImage(int direction) { 
//     if (gImagePlaylist.empty() || (direction == 0 && gCurrentImageIndex == -1) ) return;
//     if (gImagePlaylist.size() == 1 && gCurrentImageIndex != -1) return; 

//     int oldIndex = gCurrentImageIndex; 
//     std::string oldPath = (oldIndex != -1 && oldIndex < static_cast<int>(gImagePlaylist.size())) ? gImagePlaylist[oldIndex] : "";


//     if (gCurrentImageIndex == -1) { 
//         gCurrentImageIndex = (direction > 0) ? 0 : (gImagePlaylist.empty() ? -1 : static_cast<int>(gImagePlaylist.size()) - 1);
//     } else {
//         gCurrentImageIndex += direction;
//     }

//     if (gCurrentImageIndex < 0) {
//         gCurrentImageIndex = gImagePlaylist.size() - 1;
//     } else if (gCurrentImageIndex >= static_cast<int>(gImagePlaylist.size())) {
//         gCurrentImageIndex = 0;
//     }

//     if(gCurrentImageIndex >=0 && gCurrentImageIndex < static_cast<int>(gImagePlaylist.size())) {
//       if (!loadImage(gImagePlaylist[gCurrentImageIndex])) {
//           if (oldIndex != -1 && !oldPath.empty()) { 
//             gCurrentImageIndex = oldIndex;
//             if(gCurrentImagePath != oldPath || !gImageTexture) {
//                 loadImage(oldPath); 
//             }
//           } else { 
//               gCurrentImageIndex = -1; 
//               gCurrentImagePath = "Error: Could not navigate."; 
//           }
//       }
//     } else {
//         gCurrentImageIndex = -1; 
//         gCurrentImagePath = "Error: Navigation failed.";
//     }
// }

// void applyZoom(float factorChange, int mouseX = -1, int mouseY = -1) {
//     if (!gImageTexture || gImageWidth == 0 || gImageHeight == 0) return;

//     float oldZoom = gZoomFactor;
//     gZoomFactor *= factorChange;

//     gZoomFactor = std::max(0.05f, gZoomFactor); 
//     gZoomFactor = std::min(20.0f, gZoomFactor); 

//     if (std::abs(factorChange - 1.0f) > 0.001f) gFitToWindow = false; 

//     SDL_FPoint zoomCenter;
//     if (mouseX != -1 && mouseY != -1) {
//         zoomCenter = {(float)mouseX, (float)mouseY};
//     } else {
//         zoomCenter = {(float)gWindowWidth / 2.0f, (float)gWindowHeight / 2.0f};
//     }

//     float imageX_at_zoom_center = (zoomCenter.x - gViewOffset.x) / oldZoom;
//     float imageY_at_zoom_center = (zoomCenter.y - gViewOffset.y) / oldZoom;

//     gViewOffset.x = zoomCenter.x - (imageX_at_zoom_center * gZoomFactor);
//     gViewOffset.y = zoomCenter.y - (imageY_at_zoom_center * gZoomFactor);

//     float zoomedWidth = gImageWidth * gZoomFactor;
//     float zoomedHeight = gImageHeight * gZoomFactor;

//     if (zoomedWidth < gWindowWidth) {
//         gViewOffset.x = (gWindowWidth - zoomedWidth) / 2.0f;
//     } else {
//         gViewOffset.x = std::min(0.0f, gViewOffset.x);
//         gViewOffset.x = std::max((float)gWindowWidth - zoomedWidth, gViewOffset.x);
//     }

//     if (zoomedHeight < gWindowHeight) {
//         gViewOffset.y = (gWindowHeight - zoomedHeight) / 2.0f;
//     } else {
//         gViewOffset.y = std::min(0.0f, gViewOffset.y);
//         gViewOffset.y = std::max((float)gWindowHeight - zoomedHeight, gViewOffset.y);
//     }
// }

// void toggleFitToWindow() {
//     gFitToWindow = !gFitToWindow;
//     calculateInitialZoomAndOffset(); 
// }

// void close() {
//     if (gImageTexture) SDL_DestroyTexture(gImageTexture);
//     if (gFontInfo) TTF_CloseFont(gFontInfo);
//     if (gFontButton) TTF_CloseFont(gFontButton);
//     TTF_Quit();
//     IMG_Quit();
//     if (gRenderer) SDL_DestroyRenderer(gRenderer);
//     if (gWindow) SDL_DestroyWindow(gWindow);
//     SDL_Quit();
// }

// void handleButtonAction(ButtonAction action) {
//     switch (action) {
//         case ButtonAction::PREV_IMG:    navigateImage(-1); break;
//         case ButtonAction::NEXT_IMG:    navigateImage(1); break;
//         case ButtonAction::ZOOM_IN:     applyZoom(1.2f); break;
//         case ButtonAction::ZOOM_OUT:    applyZoom(1.0f/1.2f); break;
//         case ButtonAction::TOGGLE_FIT:  toggleFitToWindow(); break;
//         case ButtonAction::RESET_VIEW:  resetView(); break;
//         case ButtonAction::OPEN_FILE:   std::cout << "Open File clicked (not implemented)\n"; break;
//         default: break;
//     }
// }


// int main(int argc, char* argv[]) {
//     if (!init()) { 
//         std::cerr << "Failed to initialize!" << std::endl;
//         close();
//         return 1;
//     }

//     std::string fileToOpenArg = ""; 
//     if (argc > 1) {
//         fileToOpenArg = argv[1];
//     }
    
//     bool initialLoadSuccess = false;
//     if (!fileToOpenArg.empty()) {
//         if (loadImage(fileToOpenArg)) { 
//             initialLoadSuccess = true;
//         } else {
//              try { 
//                  gCurrentImagePath = std::string("Error loading argument: ") + std::filesystem::path(fileToOpenArg).filename().string();
//              } catch (const std::exception& e) { 
//                  gCurrentImagePath = std::string("Error with argument path: ") + e.what();
//              }
//         }
//     }
    
//     loadImagePlaylist(initialLoadSuccess ? gCurrentImagePath : (fileToOpenArg.empty() ? std::filesystem::current_path().string() : fileToOpenArg));
    
//     if (!gImageTexture && !gImagePlaylist.empty()) {
//          if (gCurrentImageIndex != -1 && gCurrentImageIndex < static_cast<int>(gImagePlaylist.size())) {
//             // Ничего не делаем, ошибка уже должна быть в gCurrentImagePath
//          } else if (loadImage(gImagePlaylist[0])) { 
//             gCurrentImageIndex = 0;
//          }
//     }
    
//     bool quit = false;
//     SDL_Event e;

//     Uint32 lastClickTime = 0;
//     ButtonAction lastClickedAction = ButtonAction::NONE;

//     while (!quit) {
//         while (SDL_PollEvent(&e) != 0) {
//             if (e.type == SDL_QUIT) {
//                 quit = true;
//             } else if (e.type == SDL_WINDOWEVENT) {
//                 if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//                     SDL_GetWindowSize(gWindow, &gWindowWidth, &gWindowHeight);
//                     setupUIButtons(); 
//                     if (gImageTexture && gFitToWindow) { 
//                         calculateInitialZoomAndOffset();
//                     } else if (gImageTexture) { 
//                          applyZoom(1.0f); 
//                     }
//                 }
//             } else if (e.type == SDL_KEYDOWN) {
//                 switch (e.key.keysym.sym) {
//                     case SDLK_q: quit = true; break;
//                     case SDLK_LEFT:  handleButtonAction(ButtonAction::PREV_IMG); break;
//                     case SDLK_RIGHT: handleButtonAction(ButtonAction::NEXT_IMG); break;
//                     case SDLK_EQUALS: case SDLK_PLUS: case SDLK_KP_PLUS: handleButtonAction(ButtonAction::ZOOM_IN); break;
//                     case SDLK_MINUS: case SDLK_KP_MINUS: handleButtonAction(ButtonAction::ZOOM_OUT); break;
//                     case SDLK_0: case SDLK_KP_0: handleButtonAction(ButtonAction::TOGGLE_FIT); break;
//                     case SDLK_r: handleButtonAction(ButtonAction::RESET_VIEW); break;
//                     case SDLK_f: 
//                         {
//                             Uint32 fsFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
//                             bool isFs = (SDL_GetWindowFlags(gWindow) & fsFlag) != 0; 
//                             SDL_SetWindowFullscreen(gWindow, isFs ? 0 : fsFlag);
//                             SDL_GetWindowSize(gWindow, &gWindowWidth, &gWindowHeight); 
//                             setupUIButtons(); 
//                              if (gImageTexture && gFitToWindow) calculateInitialZoomAndOffset();
//                              else if (gImageTexture) applyZoom(1.0f); 
//                         }
//                         break;
//                 }
//             } else if (e.type == SDL_MOUSEWHEEL) {
//                 int mouseX, mouseY;
//                 SDL_GetMouseState(&mouseX, &mouseY);
//                 if (e.wheel.y > 0) applyZoom(1.2f, mouseX, mouseY);
//                 else if (e.wheel.y < 0) applyZoom(1.0f / 1.2f, mouseX, mouseY);
//             } else if (e.type == SDL_MOUSEBUTTONDOWN) {
//                  if (e.button.button == SDL_BUTTON_LEFT) {
//                     SDL_Point mousePoint = {e.button.x, e.button.y}; 
//                     bool button_clicked = false;
//                     for (const auto& btn : gButtons) {
//                         if (SDL_PointInRect(&mousePoint, &btn.rect)) { 
//                             handleButtonAction(btn.action);
//                             button_clicked = true;
//                             if(btn.action == ButtonAction::ZOOM_IN || btn.action == ButtonAction::ZOOM_OUT) {
//                                 lastClickTime = SDL_GetTicks();
//                                 lastClickedAction = btn.action;
//                             }
//                             break;
//                         }
//                     }
//                     if(!button_clicked && gImageTexture){
//                         gIsPanning = true;
//                         gPanStartMouse = {e.button.x, e.button.y};
//                         gPanStartOffset = gViewOffset;
//                     }
//                 }
//             } else if (e.type == SDL_MOUSEBUTTONUP) {
//                 if (e.button.button == SDL_BUTTON_LEFT) {
//                     gIsPanning = false;
//                     lastClickedAction = ButtonAction::NONE; 
//                 }
//             } else if (e.type == SDL_MOUSEMOTION) {
//                 SDL_Point motionMousePoint = {e.motion.x, e.motion.y}; 
//                 for (auto& btn : gButtons) { 
//                     btn.hovered = SDL_PointInRect(&motionMousePoint, &btn.rect); 
//                 }
//                 if (gIsPanning && gImageTexture) {
//                     gViewOffset.x = gPanStartOffset.x + (e.motion.x - gPanStartMouse.x);
//                     gViewOffset.y = gPanStartOffset.y + (e.motion.y - gPanStartMouse.y);
                    
//                     float zoomedWidth = gImageWidth * gZoomFactor;
//                     float zoomedHeight = gImageHeight * gZoomFactor;
//                     if (zoomedWidth < gWindowWidth) gViewOffset.x = (gWindowWidth - zoomedWidth) / 2.0f;
//                     else { gViewOffset.x = std::min(0.0f, std::max((float)gWindowWidth - zoomedWidth, gViewOffset.x));}
//                     if (zoomedHeight < gWindowHeight) gViewOffset.y = (gWindowHeight - zoomedHeight) / 2.0f;
//                     else {gViewOffset.y = std::min(0.0f, std::max((float)gWindowHeight - zoomedHeight, gViewOffset.y));}
//                 }
//             }
//         }

//         if (lastClickedAction == ButtonAction::ZOOM_IN || lastClickedAction == ButtonAction::ZOOM_OUT) {
//             if (SDL_GetTicks() - lastClickTime > 200) { 
//                  int mx, my; SDL_GetMouseState(&mx, &my);
//                  SDL_Point currentMousePos = {mx,my}; 
//                  bool still_on_button = false;
//                  for(const auto& btn : gButtons) {
//                      if (btn.action == lastClickedAction && SDL_PointInRect(&currentMousePos, &btn.rect)) { 
//                          still_on_button = true; break;
//                      }
//                  }
//                  if(still_on_button) handleButtonAction(lastClickedAction);
//                  else lastClickedAction = ButtonAction::NONE; 
//                  lastClickTime = SDL_GetTicks() - 150; 
//             }
//         }

//         SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
//         SDL_RenderClear(gRenderer);

//         if (gImageTexture) {
//             SDL_FRect dstRect; 
//             dstRect.w = gImageWidth * gZoomFactor;
//             dstRect.h = gImageHeight * gZoomFactor;
//             dstRect.x = gViewOffset.x;
//             dstRect.y = gViewOffset.y;
//             SDL_RenderCopyF(gRenderer, gImageTexture, nullptr, &dstRect);
//         } else {
//              std::string msgToShow = gCurrentImagePath.empty() ? "No image. Open an image or use arrows." : gCurrentImagePath;
//              renderText(msgToShow , 20 , gWindowHeight / 2 - FONT_SIZE_INFO, gFontInfo, COLOR_TEXT, true, gWindowWidth - 40);
//         }
        
//         drawUI(); 

//         SDL_RenderPresent(gRenderer);
//         SDL_Delay(16); 
//     }

//     close();
//     return 0;
// }





#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>     // Для генерации случайных чисел
#include <iomanip>    // Для std::setw, std::setfill
#include <sstream>    // Для форматирования HEX

// --- Конфигурация ---
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const char* FONT_PATH = "/usr/share/fonts/TTF/DejaVuSansMono.ttf"; // Моноширинный шрифт для HEX
const int FONT_SIZE_HEX = 18;
const int NUM_PALETTE_COLORS = 4; // Количество цветов в палитре

// --- Цвета ---
const SDL_Color COLOR_BACKGROUND = {0x1E, 0x1E, 0x1E, 0xFF}; // Темно-серый
const SDL_Color COLOR_TEXT_LIGHT = {0xF0, 0xF0, 0xF0, 0xFF}; // Светлый текст
const SDL_Color COLOR_TEXT_DARK = {0x10, 0x10, 0x10, 0xFF};  // Темный текст (для светлых плашек)

// --- Глобальные переменные ---
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFontHex = nullptr;

std::vector<SDL_Color> gCurrentPalette;

// --- Вспомогательные функции ---

// Генерация случайного числа в диапазоне [min, max]
int randomNumber(int min, int max) {
    static std::mt19937 rng(std::random_device{}()); // Инициализируем один раз
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Конвертация SDL_Color в HEX-строку (#RRGGBB)
std::string colorToHex(SDL_Color color) {
    std::stringstream ss;
    ss << "#";
    ss << std::setfill('0') << std::setw(2) << std::hex << (int)color.r;
    ss << std::setfill('0') << std::setw(2) << std::hex << (int)color.g;
    ss << std::setfill('0') << std::setw(2) << std::hex << (int)color.b;
    return ss.str();
}

// Определение контрастного цвета для текста (очень упрощенно)
SDL_Color getContrastingTextColor(SDL_Color bgColor) {
    // Простое правило: если яркость фона > 128, текст темный, иначе светлый
    // Более точный расчет: (0.299*R + 0.587*G + 0.114*B)
    float luminance = 0.299f * bgColor.r + 0.587f * bgColor.g + 0.114f * bgColor.b;
    if (luminance > 128) {
        return COLOR_TEXT_DARK;
    } else {
        return COLOR_TEXT_LIGHT;
    }
}

void renderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, bool centered_x = false, int parent_w = 0) {
    if (!font || text.empty()) return;
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!textSurface) {
        // std::cerr << "TTF_RenderUTF8_Blended Error: " << TTF_GetError() << std::endl; // Может спамить
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (!textTexture) {
        // std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
     if (centered_x && parent_w > 0) {
        dstRect.x = x + (parent_w - dstRect.w) / 2;
    }

    SDL_RenderCopy(gRenderer, textTexture, nullptr, &dstRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


// Генерация новой палитры
void generatePalette() {
    gCurrentPalette.clear();

    // 1. Базовый цвет (полностью случайный)
    SDL_Color baseColor = {
        (Uint8)randomNumber(0, 255),
        (Uint8)randomNumber(0, 255),
        (Uint8)randomNumber(0, 255),
        255
    };
    gCurrentPalette.push_back(baseColor);

    // 2. Генерация остальных цветов (простые вариации от базового)
    // Для более сложных правил (аналогичные, комплементарные, триада) нужна работа с HSV/HSL
    for (int i = 1; i < NUM_PALETTE_COLORS; ++i) {
        SDL_Color nextColor;
        // Простая вариация: изменяем каждый компонент случайно, но не слишком сильно
        nextColor.r = std::max(0, std::min(255, (int)baseColor.r + randomNumber(-60, 60)));
        nextColor.g = std::max(0, std::min(255, (int)baseColor.g + randomNumber(-60, 60)));
        nextColor.b = std::max(0, std::min(255, (int)baseColor.b + randomNumber(-60, 60)));
        nextColor.a = 255;

        // Чтобы избежать слишком похожих цветов, можно добавить проверку на минимальное различие
        // или использовать более продвинутые алгоритмы генерации.
        // Для простоты пока так.

        gCurrentPalette.push_back(nextColor);
    }

    std::cout << "New Palette Generated:" << std::endl;
    for(const auto& color : gCurrentPalette) {
        std::cout << colorToHex(color) << std::endl;
    }
     std::cout << "---" << std::endl;
}


bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Для улучшения качества масштабирования (хотя здесь не масштабируем текстуры изображений)
    // но это хорошая практика для SDL2 рендеринга в целом.
    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    gWindow = SDL_CreateWindow("Palette Generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    gFontHex = TTF_OpenFont(FONT_PATH, FONT_SIZE_HEX);
    if (!gFontHex) {
        std::cerr << "Failed to load font: " << FONT_PATH << "! TTF_Error: " << TTF_GetError() << std::endl;
        // Попробуем резервный
        gFontHex = TTF_OpenFont("monospace", FONT_SIZE_HEX); // Или "Liberation Mono", "DejaVuSansMono" - общие имена
        if (!gFontHex) {
             std::cerr << "Failed to load fallback monospace font! TTF_Error: " << TTF_GetError() << std::endl;
            return false;
        }
    }
    
    generatePalette(); // Сгенерировать первую палитру при запуске
    return true;
}

void close() {
    if (gFontHex) TTF_CloseFont(gFontHex);
    TTF_Quit();
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Initialization failed." << std::endl;
        close();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    int colorBoxWidth = SCREEN_WIDTH / NUM_PALETTE_COLORS;
    int colorBoxHeight = SCREEN_HEIGHT - (FONT_SIZE_HEX + 20); // Оставляем место для текста HEX

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        generatePalette();
                        break;
                    case SDLK_c: // Просто выведем в консоль (буфер обмена сложнее)
                        if(!gCurrentPalette.empty()){
                            std::cout << "Palette HEX codes copied to console:" << std::endl;
                            for(const auto& color : gCurrentPalette) {
                                std::cout << colorToHex(color) << std::endl;
                            }
                            std::cout << "---" << std::endl;
                            // Можно добавить маленькое сообщение на экране "Copied!"
                        }
                        break;
                }
            }
        }

        // Очистка экрана
        SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
        SDL_RenderClear(gRenderer);

        // Отрисовка палитры
        for (int i = 0; i < static_cast<int>(gCurrentPalette.size()); ++i) {
            SDL_Color color = gCurrentPalette[i];
            SDL_Rect colorRect = { i * colorBoxWidth, 0, colorBoxWidth, colorBoxHeight };
            
            SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(gRenderer, &colorRect);

            // Отрисовка HEX-кода
            std::string hexCode = colorToHex(color);
            SDL_Color textColor = getContrastingTextColor(color);
            renderText(hexCode, colorRect.x, colorRect.y + colorRect.h + 5, gFontHex, textColor, true, colorBoxWidth);
        }

        renderText("Space - New Palette | C - Print HEX | Q - Quit", 10, SCREEN_HEIGHT - FONT_SIZE_HEX - 5, gFontHex, COLOR_TEXT_LIGHT);


        // Обновление экрана
        SDL_RenderPresent(gRenderer);
        SDL_Delay(16); // ~60 FPS, но здесь не так критично
    }

    close();
    return 0;
}
//1430
