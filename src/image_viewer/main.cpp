#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem> // C++17
#include <algorithm>  // std::sort, std::find, std::min, std::max
#include <cmath>      // std::round, M_PI (для окружности), std::abs, std::isnan
#include <iomanip>    // Для отладки может пригодиться
#include <sstream>    // Для конкатенации строк с fs_err.what()

// --- Конфигурация ---
const int DEFAULT_SCREEN_WIDTH = 1024;
const int DEFAULT_SCREEN_HEIGHT = 768;
const char* FONT_PATH = "/usr/share/fonts/TTF/DejaVuSans.ttf"; 
const int FONT_SIZE_INFO = 18;
const int FONT_SIZE_BUTTON = 16; 

// --- Цвета (Темная тема) ---
const SDL_Color COLOR_BACKGROUND = {0x1E, 0x1E, 0x1E, 0xFF}; 
const SDL_Color COLOR_TEXT = {0xF0, 0xF0, 0xF0, 0xFF};
const SDL_Color COLOR_BUTTON_BG = {0x3A, 0x3A, 0x3A, 0xFF};
const SDL_Color COLOR_BUTTON_HOVER_BG = {0x5A, 0x5A, 0x5A, 0xFF};
const SDL_Color COLOR_BUTTON_SYMBOL = {0xE0, 0xE0, 0xE0, 0xFF};
const SDL_Color COLOR_INFO_PANEL_BG = {0x2A, 0x2A, 0x2A, 0xD0}; 

// --- Глобальные переменные ---
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFontInfo = nullptr;
TTF_Font* gFontButton = nullptr; 
SDL_Texture* gImageTexture = nullptr;

int gImageWidth = 0;
int gImageHeight = 0;
std::string gCurrentImagePath = "";
std::vector<std::string> gImagePlaylist;
int gCurrentImageIndex = -1;

float gZoomFactor = 1.0f;
SDL_FPoint gViewOffset = {0.0f, 0.0f}; 
SDL_Point gPanStartMouse = {0,0};      
SDL_FPoint gPanStartOffset = {0.0f,0.0f}; 
bool gIsPanning = false;
bool gFitToWindow = true; 

int gWindowWidth = DEFAULT_SCREEN_WIDTH;
int gWindowHeight = DEFAULT_SCREEN_HEIGHT;

enum class ButtonAction { NONE, PREV_IMG, NEXT_IMG, ZOOM_IN, ZOOM_OUT, TOGGLE_FIT, RESET_VIEW, OPEN_FILE };
struct UIButton {
    SDL_Rect rect;
    ButtonAction action;
    std::string tooltip; 
    bool hovered = false;
    void (*drawSymbol)(SDL_Renderer* renderer, const SDL_Rect& r, const SDL_Color& c, bool is_hovered); 
};
std::vector<UIButton> gButtons;

// --- Вспомогательные функции ---
void renderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, bool centered_x = false, int parent_w = 0) {
    if (!font || text.empty()) return;
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!textSurface) {
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (!textTexture) {
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

void drawTriangleSymbol(SDL_Renderer* renderer, const SDL_Rect& btnRect, SDL_Color color, bool point_right) {
    int s = std::min(btnRect.w, btnRect.h) / 4; 
    int cx = btnRect.x + btnRect.w / 2;
    int cy = btnRect.y + btnRect.h / 2;
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int y_scan = cy - s; y_scan <= cy + s; ++y_scan) {
        int x_start, x_end;
        float progress = (float)(y_scan - (cy - s)) / (2.0f * s); 
        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;

        if (point_right) {
            x_start = cx - s;
            x_end = cx - s + static_cast<int>(2 * s * (0.5f - std::abs(0.5f - progress)));
        } else {
             x_start = cx + s - static_cast<int>(2 * s * (0.5f - std::abs(0.5f - progress)));
             x_end = cx + s;
        }
         if (x_start <= x_end) SDL_RenderDrawLine(renderer, x_start, y_scan, x_end, y_scan);
    }
}

void drawPrevSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){ drawTriangleSymbol(r, rect, c, false); }
void drawNextSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){ drawTriangleSymbol(r, rect, c, true); }
void drawZoomInSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){ 
    int s = std::min(rect.w, rect.h) / 5; int cx = rect.x+rect.w/2; int cy = rect.y+rect.h/2;
    SDL_SetRenderDrawColor(r, c.r,c.g,c.b,c.a);
    SDL_RenderDrawLine(r, cx-s,cy, cx+s,cy); SDL_RenderDrawLine(r, cx,cy-s, cx,cy+s); 
}
void drawZoomOutSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h){
    int s = std::min(rect.w, rect.h) / 5; int cx = rect.x+rect.w/2; int cy = rect.y+rect.h/2;
    SDL_SetRenderDrawColor(r, c.r,c.g,c.b,c.a);
    SDL_RenderDrawLine(r, cx-s,cy, cx+s,cy); 
}
void drawFitSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h) { 
    int s_outer = std::min(rect.w, rect.h) / 4; 
    int s_inner = s_outer / 2; 
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(r, cx - s_outer, cy - s_outer, cx - s_inner, cy - s_inner);
    SDL_RenderDrawLine(r, cx - s_inner, cy - s_inner, cx - s_inner, cy - s_inner + s_inner / 2);
    SDL_RenderDrawLine(r, cx - s_inner, cy - s_inner, cx - s_inner + s_inner / 2, cy - s_inner);
    SDL_RenderDrawLine(r, cx + s_outer, cy + s_outer, cx + s_inner, cy + s_inner);
    SDL_RenderDrawLine(r, cx + s_inner, cy + s_inner, cx + s_inner, cy + s_inner - s_inner / 2);
    SDL_RenderDrawLine(r, cx + s_inner, cy + s_inner, cx + s_inner - s_inner / 2, cy + s_inner);
}
void drawResetSymbol(SDL_Renderer* r, const SDL_Rect& rect, const SDL_Color& c, bool h) { 
    int radius = std::min(rect.w, rect.h) / 4;
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    for (int i = 0; i < 360; i += 5) { 
        float angle = i * M_PI / 180.0f;
        float next_angle = (i+5) * M_PI / 180.0f;
         SDL_RenderDrawLine(r, cx + static_cast<int>(radius * cos(angle)), 
                               cy + static_cast<int>(radius * sin(angle)),
                               cx + static_cast<int>(radius * cos(next_angle)), 
                               cy + static_cast<int>(radius * sin(next_angle)));
    }
    SDL_RenderDrawLine(r, cx - radius/2, cy - radius/2, cx + radius/2, cy + radius/2);
    SDL_RenderDrawLine(r, cx + radius/2, cy - radius/2, cx - radius/2, cy + radius/2);
}

void setupUIButtons() {
    gButtons.clear();
    int btn_size = 36;
    int btn_spacing = 8;
    int current_x = btn_spacing; 
    int y_pos = gWindowHeight - btn_size - btn_spacing; 

    gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::PREV_IMG, "Previous (Left Arrow)", false, drawPrevSymbol});
    current_x += btn_size + btn_spacing;
    gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::NEXT_IMG, "Next (Right Arrow)", false, drawNextSymbol});
    current_x += btn_size + btn_spacing + btn_spacing*2; 
    
    gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::ZOOM_OUT, "Zoom Out (-)", false, drawZoomOutSymbol});
    current_x += btn_size + btn_spacing;
    gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::ZOOM_IN, "Zoom In (+)", false, drawZoomInSymbol});
    current_x += btn_size + btn_spacing + btn_spacing*2; 

    gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::TOGGLE_FIT, "Toggle Fit/Actual (0)", false, drawFitSymbol});
    current_x += btn_size + btn_spacing;
    gButtons.push_back({{current_x, y_pos, btn_size, btn_size}, ButtonAction::RESET_VIEW, "Reset View (R)", false, drawResetSymbol});
}

void drawUI() {
    SDL_Rect infoPanelRect; 
    infoPanelRect.x = 0;
    infoPanelRect.w = gWindowWidth;
    infoPanelRect.h = FONT_SIZE_INFO + 12; 
    if (!gButtons.empty()){
        infoPanelRect.y = gButtons[0].rect.y - infoPanelRect.h - 5; 
    } else {
        infoPanelRect.y = gWindowHeight - infoPanelRect.h - 5; 
    }

    if (gImageTexture || !gCurrentImagePath.empty()) { 
        SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); 
        SDL_SetRenderDrawColor(gRenderer, COLOR_INFO_PANEL_BG.r, COLOR_INFO_PANEL_BG.g, COLOR_INFO_PANEL_BG.b, COLOR_INFO_PANEL_BG.a);
        SDL_RenderFillRect(gRenderer, &infoPanelRect);
        
        std::string filename_str = "Error"; 
        if (!gCurrentImagePath.empty()) {
            if (gCurrentImagePath.rfind("Error: ", 0) != 0) { 
               try { 
                   filename_str = std::filesystem::path(gCurrentImagePath).filename().string(); 
               } catch (const std::filesystem::filesystem_error& ) { 
                   filename_str = "Invalid Path"; 
               } catch (...) {
                   filename_str = "Unknown Path Error";
               }
            } else {
                filename_str = gCurrentImagePath; 
            }
        } else if (gImageTexture) { 
            filename_str = "[Image loaded, no path]";
        }


        std::string infoText = filename_str;
        if(gImageWidth > 0 && gImageHeight > 0) infoText += " (" + std::to_string(gImageWidth) + "x" + std::to_string(gImageHeight) + ")";
        infoText += " Z: " + std::to_string((int)std::round(gZoomFactor*100)) + "%";
        
        if(gCurrentImageIndex != -1 && !gImagePlaylist.empty()) {
            infoText += " [" + std::to_string(gCurrentImageIndex + 1) + "/" + std::to_string(gImagePlaylist.size()) + "]";
        }
        infoText += gFitToWindow ? " (Fit)" : " (Actual)";
        renderText(infoText, 10, infoPanelRect.y + (infoPanelRect.h - FONT_SIZE_INFO)/2, gFontInfo, COLOR_TEXT);
    }
    
    for (const auto& btn : gButtons) {
        SDL_Color bgColor = btn.hovered ? COLOR_BUTTON_HOVER_BG : COLOR_BUTTON_BG;
        SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(gRenderer, &btn.rect);
        if (btn.drawSymbol) {
            btn.drawSymbol(gRenderer, btn.rect, COLOR_BUTTON_SYMBOL, btn.hovered);
        }
        if(btn.hovered && !btn.tooltip.empty()){
            int text_w = 0, text_h = 0; 
            if (gFontInfo) { 
                TTF_SizeUTF8(gFontInfo, btn.tooltip.c_str(), &text_w, &text_h);
            }
            
            int tip_x = btn.rect.x + (btn.rect.w - text_w)/2;
            tip_x = std::max(5, std::min(tip_x, gWindowWidth - text_w - 5)); 
            int tip_y = btn.rect.y - text_h - 5;
            if(tip_y < 5) tip_y = btn.rect.y + btn.rect.h + 5; 

            renderText(btn.tooltip, tip_x, tip_y, gFontInfo, COLOR_TEXT);
        }
    }
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // ***************** ИСПРАВЛЕНИЕ ДЛЯ ПИКСЕЛИЗАЦИИ *****************
    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE) { // "1" for linear filtering
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }
    // ****************************************************************

    gWindow = SDL_CreateWindow("SDL Image Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                               DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!gWindow) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_GetWindowSize(gWindow, &gWindowWidth, &gWindowHeight);

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF; 
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    gFontInfo = TTF_OpenFont(FONT_PATH, FONT_SIZE_INFO);
    gFontButton = TTF_OpenFont(FONT_PATH, FONT_SIZE_BUTTON); 
    if (!gFontInfo || !gFontButton) {
        std::cerr << "Failed to load font: " << FONT_PATH << "! TTF_Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(gFontInfo); TTF_CloseFont(gFontButton);
        gFontInfo = TTF_OpenFont("sans.ttf", FONT_SIZE_INFO);
        gFontButton = TTF_OpenFont("sans.ttf", FONT_SIZE_BUTTON);
        if (!gFontInfo || !gFontButton) {
             std::cerr << "Failed to load fallback font 'sans.ttf'! TTF_Error: " << TTF_GetError() << std::endl;
            return false;
        }
    }
    setupUIButtons(); 
    return true;
}

void calculateInitialZoomAndOffset() {
    if (!gImageTexture || gImageWidth == 0 || gImageHeight == 0) return;

    if (gFitToWindow) {
        float scaleX = (float)gWindowWidth / gImageWidth;
        float scaleY = (float)gWindowHeight / gImageHeight;
        gZoomFactor = std::min(1.0f, std::min(scaleX, scaleY)); 
    } else {
        gZoomFactor = 1.0f; 
    }
    gViewOffset.x = (gWindowWidth - (gImageWidth * gZoomFactor)) / 2.0f;
    gViewOffset.y = (gWindowHeight - (gImageHeight * gZoomFactor)) / 2.0f;
}

void resetView(bool keep_fit_mode = false) { 
    if(!keep_fit_mode) gFitToWindow = true; 
    calculateInitialZoomAndOffset();
}

bool loadImage(const std::string& path) {
    if (gImageTexture) {
        SDL_DestroyTexture(gImageTexture);
        gImageTexture = nullptr;
    }
    gImageWidth = 0;
    gImageHeight = 0;
    
    if (path.empty()){
        gCurrentImagePath = ""; 
        return false; 
    }
    
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if (!newTexture) {
        std::string errorMsg = IMG_GetError();
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << errorMsg << std::endl;
        try {
             gCurrentImagePath = std::string("Error: ") + std::filesystem::path(path).filename().string() + " (" + errorMsg + ")"; 
        } catch (const std::filesystem::filesystem_error& fs_err){ 
             gCurrentImagePath = std::string("Error loading (invalid path: ") + fs_err.what() + ")"; 
        } catch (...){ 
            gCurrentImagePath = "Error loading (unknown path error)";
        }
        return false;
    }

    gImageTexture = newTexture;
    SDL_QueryTexture(gImageTexture, nullptr, nullptr, &gImageWidth, &gImageHeight);
    gCurrentImagePath = path; 
    
    resetView(true); 

    std::cout << "Loaded: " << path << " (" << gImageWidth << "x" << gImageHeight << ")" << std::endl;
    return true;
}

void loadImagePlaylist(const std::string& currentFilePathOrDir) {
    gImagePlaylist.clear();
    
    std::filesystem::path basePath;
    std::string targetFileToFind;

    try {
        if (!currentFilePathOrDir.empty() && std::filesystem::exists(currentFilePathOrDir)) {
            if (std::filesystem::is_regular_file(currentFilePathOrDir)) {
                basePath = std::filesystem::path(currentFilePathOrDir).parent_path();
                targetFileToFind = currentFilePathOrDir;
            } else if (std::filesystem::is_directory(currentFilePathOrDir)) {
                basePath = currentFilePathOrDir;
            } else { 
                basePath = std::filesystem::current_path();
            }
        } else { 
            basePath = std::filesystem::current_path();
        }

        if (!std::filesystem::exists(basePath) || !std::filesystem::is_directory(basePath)) {
             std::cerr << "Playlist base path is not a valid directory: " << basePath.string() << std::endl;
             if(!targetFileToFind.empty() && std::filesystem::exists(targetFileToFind) && std::filesystem::is_regular_file(targetFileToFind)){
                gImagePlaylist.push_back(targetFileToFind);
             }
            return;
        }

        for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(),
                               [](unsigned char c){ return std::tolower(c); });
                if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp" ||
                    ext == ".gif" || ext == ".tga" || ext == ".webp" || ext == ".tif" || ext == ".tiff") {
                    gImagePlaylist.push_back(entry.path().string());
                }
            }
        }
        if (!gImagePlaylist.empty()) std::sort(gImagePlaylist.begin(), gImagePlaylist.end());
        
        gCurrentImageIndex = -1; 
        if(!targetFileToFind.empty()){ 
            auto it = std::find(gImagePlaylist.begin(), gImagePlaylist.end(), targetFileToFind);
            if (it != gImagePlaylist.end()) { 
                gCurrentImageIndex = std::distance(gImagePlaylist.begin(), it);
            } else { 
                 if(std::filesystem::exists(targetFileToFind) && std::filesystem::is_regular_file(targetFileToFind)){
                     bool found_after_add = false;
                     for(size_t i = 0; i < gImagePlaylist.size(); ++i) { 
                        try { 
                            if(std::filesystem::equivalent(gImagePlaylist[i], targetFileToFind)) {
                                gCurrentImageIndex = i;
                                found_after_add = true;
                                break;
                            }
                        } catch (const std::filesystem::filesystem_error&) { /* Пропускаем */ }
                     }
                     if(!found_after_add) {
                        gImagePlaylist.insert(gImagePlaylist.begin(), targetFileToFind); 
                        std::sort(gImagePlaylist.begin(), gImagePlaylist.end()); 
                        it = std::find(gImagePlaylist.begin(), gImagePlaylist.end(), targetFileToFind);
                        if(it != gImagePlaylist.end()) gCurrentImageIndex = std::distance(gImagePlaylist.begin(), it);
                     }
                 } else if (!gImagePlaylist.empty()) { 
                    gCurrentImageIndex = 0;
                 }
            }
        } else if (!gImagePlaylist.empty()) { 
            gCurrentImageIndex = 0; 
        }

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error scanning directory " << basePath.string() << ": " << e.what() << std::endl;
         if(!targetFileToFind.empty() && std::filesystem::exists(targetFileToFind) && std::filesystem::is_regular_file(targetFileToFind) && gImagePlaylist.empty()){
            gImagePlaylist.push_back(targetFileToFind);
            gCurrentImageIndex = 0; 
        } else if (gImagePlaylist.empty()) {
            gCurrentImageIndex = -1; 
        }
    }
}

void navigateImage(int direction) { 
    if (gImagePlaylist.empty() || (direction == 0 && gCurrentImageIndex == -1) ) return;
    if (gImagePlaylist.size() == 1 && gCurrentImageIndex != -1) return; 

    int oldIndex = gCurrentImageIndex; 
    std::string oldPath = (oldIndex != -1 && oldIndex < static_cast<int>(gImagePlaylist.size())) ? gImagePlaylist[oldIndex] : "";


    if (gCurrentImageIndex == -1) { 
        gCurrentImageIndex = (direction > 0) ? 0 : (gImagePlaylist.empty() ? -1 : static_cast<int>(gImagePlaylist.size()) - 1);
    } else {
        gCurrentImageIndex += direction;
    }

    if (gCurrentImageIndex < 0) {
        gCurrentImageIndex = gImagePlaylist.size() - 1;
    } else if (gCurrentImageIndex >= static_cast<int>(gImagePlaylist.size())) {
        gCurrentImageIndex = 0;
    }

    if(gCurrentImageIndex >=0 && gCurrentImageIndex < static_cast<int>(gImagePlaylist.size())) {
      if (!loadImage(gImagePlaylist[gCurrentImageIndex])) {
          if (oldIndex != -1 && !oldPath.empty()) { 
            gCurrentImageIndex = oldIndex;
            if(gCurrentImagePath != oldPath || !gImageTexture) {
                loadImage(oldPath); 
            }
          } else { 
              gCurrentImageIndex = -1; 
              gCurrentImagePath = "Error: Could not navigate."; 
          }
      }
    } else {
        gCurrentImageIndex = -1; 
        gCurrentImagePath = "Error: Navigation failed.";
    }
}

void applyZoom(float factorChange, int mouseX = -1, int mouseY = -1) {
    if (!gImageTexture || gImageWidth == 0 || gImageHeight == 0) return;

    float oldZoom = gZoomFactor;
    gZoomFactor *= factorChange;

    gZoomFactor = std::max(0.05f, gZoomFactor); 
    gZoomFactor = std::min(20.0f, gZoomFactor); 

    if (std::abs(factorChange - 1.0f) > 0.001f) gFitToWindow = false; 

    SDL_FPoint zoomCenter;
    if (mouseX != -1 && mouseY != -1) {
        zoomCenter = {(float)mouseX, (float)mouseY};
    } else {
        zoomCenter = {(float)gWindowWidth / 2.0f, (float)gWindowHeight / 2.0f};
    }

    float imageX_at_zoom_center = (zoomCenter.x - gViewOffset.x) / oldZoom;
    float imageY_at_zoom_center = (zoomCenter.y - gViewOffset.y) / oldZoom;

    gViewOffset.x = zoomCenter.x - (imageX_at_zoom_center * gZoomFactor);
    gViewOffset.y = zoomCenter.y - (imageY_at_zoom_center * gZoomFactor);

    float zoomedWidth = gImageWidth * gZoomFactor;
    float zoomedHeight = gImageHeight * gZoomFactor;

    if (zoomedWidth < gWindowWidth) {
        gViewOffset.x = (gWindowWidth - zoomedWidth) / 2.0f;
    } else {
        gViewOffset.x = std::min(0.0f, gViewOffset.x);
        gViewOffset.x = std::max((float)gWindowWidth - zoomedWidth, gViewOffset.x);
    }

    if (zoomedHeight < gWindowHeight) {
        gViewOffset.y = (gWindowHeight - zoomedHeight) / 2.0f;
    } else {
        gViewOffset.y = std::min(0.0f, gViewOffset.y);
        gViewOffset.y = std::max((float)gWindowHeight - zoomedHeight, gViewOffset.y);
    }
}

void toggleFitToWindow() {
    gFitToWindow = !gFitToWindow;
    calculateInitialZoomAndOffset(); 
}

void close() {
    if (gImageTexture) SDL_DestroyTexture(gImageTexture);
    if (gFontInfo) TTF_CloseFont(gFontInfo);
    if (gFontButton) TTF_CloseFont(gFontButton);
    TTF_Quit();
    IMG_Quit();
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void handleButtonAction(ButtonAction action) {
    switch (action) {
        case ButtonAction::PREV_IMG:    navigateImage(-1); break;
        case ButtonAction::NEXT_IMG:    navigateImage(1); break;
        case ButtonAction::ZOOM_IN:     applyZoom(1.2f); break;
        case ButtonAction::ZOOM_OUT:    applyZoom(1.0f/1.2f); break;
        case ButtonAction::TOGGLE_FIT:  toggleFitToWindow(); break;
        case ButtonAction::RESET_VIEW:  resetView(); break;
        case ButtonAction::OPEN_FILE:   std::cout << "Open File clicked (not implemented)\n"; break;
        default: break;
    }
}


int main(int argc, char* argv[]) {
    if (!init()) { 
        std::cerr << "Failed to initialize!" << std::endl;
        close();
        return 1;
    }

    std::string fileToOpenArg = ""; 
    if (argc > 1) {
        fileToOpenArg = argv[1];
    }
    
    bool initialLoadSuccess = false;
    if (!fileToOpenArg.empty()) {
        if (loadImage(fileToOpenArg)) { 
            initialLoadSuccess = true;
        } else {
             try { 
                 gCurrentImagePath = std::string("Error loading argument: ") + std::filesystem::path(fileToOpenArg).filename().string();
             } catch (const std::exception& e) { 
                 gCurrentImagePath = std::string("Error with argument path: ") + e.what();
             }
        }
    }
    
    loadImagePlaylist(initialLoadSuccess ? gCurrentImagePath : (fileToOpenArg.empty() ? std::filesystem::current_path().string() : fileToOpenArg));
    
    if (!gImageTexture && !gImagePlaylist.empty()) {
         if (gCurrentImageIndex != -1 && gCurrentImageIndex < static_cast<int>(gImagePlaylist.size())) {
            // Ничего не делаем, ошибка уже должна быть в gCurrentImagePath
         } else if (loadImage(gImagePlaylist[0])) { 
            gCurrentImageIndex = 0;
         }
    }
    
    bool quit = false;
    SDL_Event e;

    Uint32 lastClickTime = 0;
    ButtonAction lastClickedAction = ButtonAction::NONE;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    SDL_GetWindowSize(gWindow, &gWindowWidth, &gWindowHeight);
                    setupUIButtons(); 
                    if (gImageTexture && gFitToWindow) { 
                        calculateInitialZoomAndOffset();
                    } else if (gImageTexture) { 
                         applyZoom(1.0f); 
                    }
                }
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q: quit = true; break;
                    case SDLK_LEFT:  handleButtonAction(ButtonAction::PREV_IMG); break;
                    case SDLK_RIGHT: handleButtonAction(ButtonAction::NEXT_IMG); break;
                    case SDLK_EQUALS: case SDLK_PLUS: case SDLK_KP_PLUS: handleButtonAction(ButtonAction::ZOOM_IN); break;
                    case SDLK_MINUS: case SDLK_KP_MINUS: handleButtonAction(ButtonAction::ZOOM_OUT); break;
                    case SDLK_0: case SDLK_KP_0: handleButtonAction(ButtonAction::TOGGLE_FIT); break;
                    case SDLK_r: handleButtonAction(ButtonAction::RESET_VIEW); break;
                    case SDLK_f: 
                        {
                            Uint32 fsFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
                            bool isFs = (SDL_GetWindowFlags(gWindow) & fsFlag) != 0; 
                            SDL_SetWindowFullscreen(gWindow, isFs ? 0 : fsFlag);
                            SDL_GetWindowSize(gWindow, &gWindowWidth, &gWindowHeight); 
                            setupUIButtons(); 
                             if (gImageTexture && gFitToWindow) calculateInitialZoomAndOffset();
                             else if (gImageTexture) applyZoom(1.0f); 
                        }
                        break;
                }
            } else if (e.type == SDL_MOUSEWHEEL) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (e.wheel.y > 0) applyZoom(1.2f, mouseX, mouseY);
                else if (e.wheel.y < 0) applyZoom(1.0f / 1.2f, mouseX, mouseY);
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                 if (e.button.button == SDL_BUTTON_LEFT) {
                    SDL_Point mousePoint = {e.button.x, e.button.y}; 
                    bool button_clicked = false;
                    for (const auto& btn : gButtons) {
                        if (SDL_PointInRect(&mousePoint, &btn.rect)) { 
                            handleButtonAction(btn.action);
                            button_clicked = true;
                            if(btn.action == ButtonAction::ZOOM_IN || btn.action == ButtonAction::ZOOM_OUT) {
                                lastClickTime = SDL_GetTicks();
                                lastClickedAction = btn.action;
                            }
                            break;
                        }
                    }
                    if(!button_clicked && gImageTexture){
                        gIsPanning = true;
                        gPanStartMouse = {e.button.x, e.button.y};
                        gPanStartOffset = gViewOffset;
                    }
                }
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    gIsPanning = false;
                    lastClickedAction = ButtonAction::NONE; 
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                SDL_Point motionMousePoint = {e.motion.x, e.motion.y}; 
                for (auto& btn : gButtons) { 
                    btn.hovered = SDL_PointInRect(&motionMousePoint, &btn.rect); 
                }
                if (gIsPanning && gImageTexture) {
                    gViewOffset.x = gPanStartOffset.x + (e.motion.x - gPanStartMouse.x);
                    gViewOffset.y = gPanStartOffset.y + (e.motion.y - gPanStartMouse.y);
                    
                    float zoomedWidth = gImageWidth * gZoomFactor;
                    float zoomedHeight = gImageHeight * gZoomFactor;
                    if (zoomedWidth < gWindowWidth) gViewOffset.x = (gWindowWidth - zoomedWidth) / 2.0f;
                    else { gViewOffset.x = std::min(0.0f, std::max((float)gWindowWidth - zoomedWidth, gViewOffset.x));}
                    if (zoomedHeight < gWindowHeight) gViewOffset.y = (gWindowHeight - zoomedHeight) / 2.0f;
                    else {gViewOffset.y = std::min(0.0f, std::max((float)gWindowHeight - zoomedHeight, gViewOffset.y));}
                }
            }
        }

        if (lastClickedAction == ButtonAction::ZOOM_IN || lastClickedAction == ButtonAction::ZOOM_OUT) {
            if (SDL_GetTicks() - lastClickTime > 200) { 
                 int mx, my; SDL_GetMouseState(&mx, &my);
                 SDL_Point currentMousePos = {mx,my}; 
                 bool still_on_button = false;
                 for(const auto& btn : gButtons) {
                     if (btn.action == lastClickedAction && SDL_PointInRect(&currentMousePos, &btn.rect)) { 
                         still_on_button = true; break;
                     }
                 }
                 if(still_on_button) handleButtonAction(lastClickedAction);
                 else lastClickedAction = ButtonAction::NONE; 
                 lastClickTime = SDL_GetTicks() - 150; 
            }
        }

        SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
        SDL_RenderClear(gRenderer);

        if (gImageTexture) {
            SDL_FRect dstRect; 
            dstRect.w = gImageWidth * gZoomFactor;
            dstRect.h = gImageHeight * gZoomFactor;
            dstRect.x = gViewOffset.x;
            dstRect.y = gViewOffset.y;
            SDL_RenderCopyF(gRenderer, gImageTexture, nullptr, &dstRect);
        } else {
             std::string msgToShow = gCurrentImagePath.empty() ? "No image. Open an image or use arrows." : gCurrentImagePath;
             renderText(msgToShow , 20 , gWindowHeight / 2 - FONT_SIZE_INFO, gFontInfo, COLOR_TEXT, true, gWindowWidth - 40);
        }
        
        drawUI(); 

        SDL_RenderPresent(gRenderer);
        SDL_Delay(16); 
    }

    close();
    return 0;
}
