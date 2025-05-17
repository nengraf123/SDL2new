#include "musicPlayer.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

MusicPlayer::MusicPlayer() : musicPath("music/muzika.mp3"), bgm(nullptr), currentTrackIndex(0), musicStarted(false),
    trackText(nullptr), currentTimeText(nullptr), totalTimeText(nullptr), hoverTimeText(nullptr),
    coverTexture(nullptr), musicDuration(0.0), needsScrolling(false), textOffset(0), lastTextUpdate(0),
    coverRect({300, 100, 200, 200}), knopka1({0, 0, 200, 75}), knopka2({0, 75, 200, 75}),
    knopka11({340, 550, 120, 75}), backButton({650, 650, 120, 60}),
    sliderTrack({300, 500, 200, 10}), sliderHandle({300, 495, 10, 20}),
    isDraggingSlider(false), musicScrollTrack({790, 50, 10, 385}), musicScrollHandle({790, 50, 10, 20}),
    isDraggingMusicScroll(false), musicScrollOffset(0), maxVisibleSquares(7),
    textColor({200, 200, 200, 255}), shadowColor({50, 50, 50, 100}),
    buttonColor({40, 40, 60, 255}), buttonHoverColor({60, 60, 90, 255}),
    borderColor({100, 100, 100, 255}), sliderTrackColor({100, 100, 100, 255}),
    sliderHandleColor({150, 150, 150, 255}), sliderActiveColor({80, 80, 120, 255}) {}

MusicPlayer::~MusicPlayer() {
    if (bgm) Mix_FreeMusic(bgm);
    if (trackText) SDL_DestroyTexture(trackText);
    if (currentTimeText) SDL_DestroyTexture(currentTimeText);
    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
    if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
    if (coverTexture) SDL_DestroyTexture(coverTexture);
    for (auto& texture : musicFileTextures) {
        if (texture) SDL_DestroyTexture(texture);
    }
}

void MusicPlayer::init(const string& initialMusicPath, const string& initialFolderPath) {
    musicPath = initialMusicPath;
    folderPath = initialFolderPath;
    if (!folderPath.empty() && fs::exists(folderPath)) {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav") {
                musicFiles.push_back(entry.path().string());
                if (entry.path().string() == musicPath) {
                    currentTrackIndex = musicFiles.size() - 1;
                }
            }
        }
    }
    bgm = Mix_LoadMUS(musicPath.c_str());
    if (!bgm) {
        cerr << "Ошибка загрузки музыки: " << Mix_GetError() << endl;
    }
    musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
    currentTrack = fs::path(musicPath).filename().string();
    needsScrolling = currentTrack.length() > 15;
    coverPath = "img/cover_" + fs::path(musicPath).stem().string() + ".png";
}

void MusicPlayer::handleEvents(SDL_Event& event, SDL_Renderer* renderer, TTF_Font* font, TTF_Font* trackFont, int mx, int my, bool& running, int& scene) {
    bool MouseOnKnopka1 = isMouseOnButton(mx, my, knopka1);
    bool MouseOnKnopka2 = isMouseOnButton(mx, my, knopka2);
    bool MouseOnKnopka11 = isMouseOnButton(mx, my, knopka11);
    bool MouseOnBack = isMouseOnButton(mx, my, backButton);
    bool MouseOnSlider = isMouseOnButton(mx, my, sliderHandle);
    bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
    bool MouseOnMusicScroll = isMouseOnButton(mx, my, musicScrollHandle);
    bool MouseOnCover = isMouseOnButton(mx, my, coverRect);
    vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
    for (size_t i = 0; i < musicSquares.size(); ++i) {
        MouseOnMusicSquare[i] = isMouseOnButton(mx, my, musicSquares[i]);
    }

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_1 && bgm && !musicStarted) {
            if (Mix_PlayMusic(bgm, -1) == -1) {
                cerr << "Ошибка воспроизведения музыки: " << Mix_GetError() << endl;
            } else {
                musicStarted = true;
            }
        } else if (event.key.keysym.sym == SDLK_SPACE) {
            if (Mix_PausedMusic()) {
                Mix_ResumeMusic();
            } else {
                Mix_PauseMusic();
            }
        } else if (event.key.keysym.sym == SDLK_UP && !musicFiles.empty()) {
            if (currentTrackIndex > 0) {
                currentTrackIndex--;
            } else {
                currentTrackIndex = musicFiles.size() - 1;
            }
            musicPath = musicFiles[currentTrackIndex];
            if (musicStarted) {
                Mix_HaltMusic();
                musicStarted = false;
            }
            if (bgm) {
                Mix_FreeMusic(bgm);
            }
            bgm = Mix_LoadMUS(musicPath.c_str());
            if (!bgm) {
                cerr << "Ошибка загрузки новой музыки: " << Mix_GetError() << endl;
            } else {
                if (Mix_PlayMusic(bgm, -1) == -1) {
                    cerr << "Ошибка воспроизведения музыки: " << Mix_GetError() << endl;
                } else {
                    musicStarted = true;
                }
            }
            if (trackText) SDL_DestroyTexture(trackText);
            currentTrack = fs::path(musicPath).filename().string();
            trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
            needsScrolling = currentTrack.length() > 15;
            textOffset = 0;
            if (totalTimeText) SDL_DestroyTexture(totalTimeText);
            musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
            totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
            if (coverTexture) SDL_DestroyTexture(coverTexture);
            coverPath = "img/cover_" + fs::path(musicPath).stem().string() + ".png";
            if (fs::exists(coverPath)) {
                SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                if (coverSurface) {
                    coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                    SDL_FreeSurface(coverSurface);
                }
            } else {
                SDL_Surface* defaultCover = IMG_Load("img/ZnakMuziki.png");
                if (defaultCover) {
                    coverTexture = SDL_CreateTextureFromSurface(renderer, defaultCover);
                    SDL_FreeSurface(defaultCover);
                }
            }
            ofstream outFile("save/music_path.txt");
            if (outFile.is_open()) {
                outFile << musicPath << "\n" << folderPath;
                outFile.close();
            }
        } else if (event.key.keysym.sym == SDLK_DOWN && !musicFiles.empty()) {
            if (currentTrackIndex < static_cast<int>(musicFiles.size()) - 1) {
                currentTrackIndex++;
            } else {
                currentTrackIndex = 0;
            }
            musicPath = musicFiles[currentTrackIndex];
            if (musicStarted) {
                Mix_HaltMusic();
                musicStarted = false;
            }
            if (bgm) {
                Mix_FreeMusic(bgm);
            }
            bgm = Mix_LoadMUS(musicPath.c_str());
            if (!bgm) {
                cerr << "Ошибка загрузки новой музыки: " << Mix_GetError() << endl;
            } else {
                if (Mix_PlayMusic(bgm, -1) == -1) {
                    cerr << "Ошибка воспроизведения музыки: " << Mix_GetError() << endl;
                } else {
                    musicStarted = true;
                }
            }
            if (trackText) SDL_DestroyTexture(trackText);
            currentTrack = fs::path(musicPath).filename().string();
            trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
            needsScrolling = currentTrack.length() > 15;
            textOffset = 0;
            if (totalTimeText) SDL_DestroyTexture(totalTimeText);
            musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
            totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
            if (coverTexture) SDL_DestroyTexture(coverTexture);
            coverPath = "img/cover_" + fs::path(musicPath).stem().string() + ".png";
            if (fs::exists(coverPath)) {
                SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                if (coverSurface) {
                    coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                    SDL_FreeSurface(coverSurface);
                }
            } else {
                SDL_Surface* defaultCover = IMG_Load("img/ZnakMuziki.png");
                if (defaultCover) {
                    coverTexture = SDL_CreateTextureFromSurface(renderer, defaultCover);
                    SDL_FreeSurface(defaultCover);
                }
            }
            ofstream outFile("save/music_path.txt");
            if (outFile.is_open()) {
                outFile << musicPath << "\n" << folderPath;
                outFile.close();
            }
        } else if (event.key.keysym.sym == SDLK_LEFT && bgm && musicStarted) {
            double currentPosition = Mix_GetMusicPosition(bgm);
            double newPosition = max(0.0, currentPosition - 5.0);
            Mix_SetMusicPosition(newPosition);
        } else if (event.key.keysym.sym == SDLK_RIGHT && bgm && musicStarted) {
            double currentPosition = Mix_GetMusicPosition(bgm);
            double musicDuration = Mix_MusicDuration(bgm);
            double newPosition = min(musicDuration, currentPosition + 5.0);
            Mix_SetMusicPosition(newPosition);
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (MouseOnKnopka1) {
            const char* selectedFolder = tinyfd_selectFolderDialog("Выберите папку с музыкой", "");
            if (selectedFolder) {
                folderPath = selectedFolder;
                musicFiles.clear();
                musicSquares.clear();
                for (auto& texture : musicFileTextures) {
                    if (texture) SDL_DestroyTexture(texture);
                }
                musicFileTextures.clear();
                currentTrackIndex = 0;
                for (const auto& entry : fs::directory_iterator(folderPath)) {
                    if (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav") {
                        musicFiles.push_back(entry.path().string());
                        string filename = fs::path(entry.path()).filename().string();
                        SDL_Texture* textTexture = createTextTexture(renderer, font, filename, textColor, 130);
                        musicFileTextures.push_back(textTexture);
                    }
                }
                musicScrollOffset = 0;
                musicSquares.clear();
                for (size_t i = 0; i < musicFiles.size() && i < maxVisibleSquares; ++i) {
                    musicSquares.push_back({650, static_cast<int>(50 + i * 55), 140, 50});
                }
                if (!musicFiles.empty()) {
                    musicPath = musicFiles[0];
                    if (musicStarted) {
                        Mix_HaltMusic();
                        musicStarted = false;
                    }
                    if (bgm) {
                        Mix_FreeMusic(bgm);
                    }
                    bgm = Mix_LoadMUS(musicPath.c_str());
                    if (trackText) SDL_DestroyTexture(trackText);
                    currentTrack = fs::path(musicPath).filename().string();
                    trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
                    needsScrolling = currentTrack.length() > 15;
                    textOffset = 0;
                    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                    musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
                    totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                    if (coverTexture) SDL_DestroyTexture(coverTexture);
                    coverPath = "img/cover_" + fs::path(musicPath).stem().string() + ".png";
                    if (fs::exists(coverPath)) {
                        SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                        if (coverSurface) {
                            coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                            SDL_FreeSurface(coverSurface);
                        }
                    } else {
                        SDL_Surface* defaultCover = IMG_Load("img/ZnakMuziki.png");
                        if (defaultCover) {
                            coverTexture = SDL_CreateTextureFromSurface(renderer, defaultCover);
                            SDL_FreeSurface(defaultCover);
                        }
                    }
                }
                ofstream outFile("save/music_path.txt");
                if (outFile.is_open()) {
                    outFile << musicPath << "\n" << folderPath;
                    outFile.close();
                }
            }
        } else if (MouseOnKnopka2) {
            running = false;
        } else if (MouseOnKnopka11) {
            if (Mix_PausedMusic()) {
                Mix_ResumeMusic();
            } else {
                Mix_PauseMusic();
            }
        } else if (MouseOnBack) {
            scene = -1; // Вернуться в главное меню
        } else if (MouseOnSlider) {
            isDraggingSlider = true;
        } else if (MouseOnMusicScroll) {
            isDraggingMusicScroll = true;
        } else if (MouseOnSliderTrack && bgm) {
            double musicDuration = Mix_MusicDuration(bgm);
            if (musicDuration > 0) {
                float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
                double newPosition = progress * musicDuration;
                Mix_SetMusicPosition(newPosition);
            }
        } else if (MouseOnCover) {
            const char* selectedImage = tinyfd_openFileDialog("Выберите обложку", "", 0, nullptr, nullptr, 0);
            if (selectedImage) {
                SDL_Surface* newCoverSurface = IMG_Load(selectedImage);
                if (newCoverSurface) {
                    if (coverTexture) SDL_DestroyTexture(coverTexture);
                    coverTexture = SDL_CreateTextureFromSurface(renderer, newCoverSurface);
                    coverPath = "img/cover_" + fs::path(musicPath).stem().string() + ".png";
                    IMG_SavePNG(newCoverSurface, coverPath.c_str());
                    SDL_FreeSurface(newCoverSurface);
                }
            }
        } else {
            for (size_t i = 0; i < musicSquares.size(); ++i) {
                if (MouseOnMusicSquare[i] && i + musicScrollOffset < musicFiles.size()) {
                    currentTrackIndex = i + musicScrollOffset;
                    musicPath = musicFiles[currentTrackIndex];
                    if (musicStarted) {
                        Mix_HaltMusic();
                        musicStarted = false;
                    }
                    if (bgm) {
                        Mix_FreeMusic(bgm);
                    }
                    bgm = Mix_LoadMUS(musicPath.c_str());
                    if (!bgm) {
                        cerr << "Ошибка загрузки новой музыки: " << Mix_GetError() << endl;
                    } else {
                        if (Mix_PlayMusic(bgm, -1) == -1) {
                            cerr << "Ошибка воспроизведения музыки: " << Mix_GetError() << endl;
                        } else {
                            musicStarted = true;
                        }
                    }
                    if (trackText) SDL_DestroyTexture(trackText);
                    currentTrack = fs::path(musicPath).filename().string();
                    trackText = createTextTexture(renderer, trackFont, currentTrack.length() > 15 ? currentTrack.substr(0, 15) + "..." : currentTrack, textColor);
                    needsScrolling = currentTrack.length() > 15;
                    textOffset = 0;
                    if (totalTimeText) SDL_DestroyTexture(totalTimeText);
                    musicDuration = bgm ? Mix_MusicDuration(bgm) : 0.0;
                    totalTimeText = createTextTexture(renderer, font, formatTime(musicDuration), textColor);
                    if (coverTexture) SDL_DestroyTexture(coverTexture);
                    coverPath = "img/cover_" + fs::path(musicPath).stem().string() + ".png";
                    if (fs::exists(coverPath)) {
                        SDL_Surface* coverSurface = IMG_Load(coverPath.c_str());
                        if (coverSurface) {
                            coverTexture = SDL_CreateTextureFromSurface(renderer, coverSurface);
                            SDL_FreeSurface(coverSurface);
                        }
                    } else {
                        SDL_Surface* defaultCover = IMG_Load("img/ZnakMuziki.png");
                        if (defaultCover) {
                            coverTexture = SDL_CreateTextureFromSurface(renderer, defaultCover);
                            SDL_FreeSurface(defaultCover);
                        }
                    }
                    ofstream outFile("save/music_path.txt");
                    if (outFile.is_open()) {
                        outFile << musicPath << "\n" << folderPath;
                        outFile.close();
                    }
                    break;
                }
            }
        }
    } else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        if (isDraggingSlider) {
            isDraggingSlider = false;
            if (bgm && musicStarted) {
                double musicDuration = Mix_MusicDuration(bgm);
                if (musicDuration > 0) {
                    float progress = static_cast<float>(sliderHandle.x - sliderTrack.x) / (sliderTrack.w - sliderHandle.w);
                    double newPosition = progress * musicDuration;
                    Mix_SetMusicPosition(newPosition);
                }
            }
        } else if (isDraggingMusicScroll) {
            isDraggingMusicScroll = false;
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        if (isDraggingSlider) {
            int newX = mx - sliderHandle.w / 2;
            if (newX < sliderTrack.x) newX = sliderTrack.x;
            if (newX > sliderTrack.x + sliderTrack.w - sliderHandle.w) newX = sliderTrack.x + sliderTrack.w - sliderHandle.w;
            sliderHandle.x = newX;
        } else if (isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
            int newY = my - musicScrollHandle.h / 2;
            if (newY < musicScrollTrack.y) newY = musicScrollTrack.y;
            if (newY > musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h) newY = musicScrollTrack.y + musicScrollTrack.h - musicScrollHandle.h;
            musicScrollHandle.y = newY;
            float progress = static_cast<float>(musicScrollHandle.y - musicScrollTrack.y) / (musicScrollTrack.h - musicScrollHandle.h);
            musicScrollOffset = static_cast<size_t>(progress * (musicFiles.size() - maxVisibleSquares));
            musicSquares.clear();
            for (size_t i = musicScrollOffset; i < musicFiles.size() && i < musicScrollOffset + maxVisibleSquares; ++i) {
                musicSquares.push_back({650, static_cast<int>(50 + (i - musicScrollOffset) * 55), 140, 50});
            }
        }
    }
}

void MusicPlayer::update(SDL_Renderer* renderer, TTF_Font* font) {
    if (bgm && musicStarted && !isDraggingSlider) {
        double currentPosition = Mix_GetMusicPosition(bgm);
        if (musicDuration > 0) {
            float progress = static_cast<float>(currentPosition) / musicDuration;
            sliderHandle.x = sliderTrack.x + static_cast<int>(progress * (sliderTrack.w - sliderHandle.w));
        }
        if (currentTimeText) SDL_DestroyTexture(currentTimeText);
        currentTimeText = createTextTexture(renderer, font, formatTime(currentPosition), textColor);
    }
    if (needsScrolling) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastTextUpdate >= 50) {
            textOffset++;
            int textW, textH;
            SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
            if (textOffset >= textW - 300) {
                textOffset = 0;
            }
            lastTextUpdate = currentTime;
        }
    } else {
        textOffset = 0;
    }
    if (!isDraggingMusicScroll && musicFiles.size() > maxVisibleSquares) {
        float progress = static_cast<float>(musicScrollOffset) / (musicFiles.size() - maxVisibleSquares);
        musicScrollHandle.y = musicScrollTrack.y + static_cast<int>(progress * (musicScrollTrack.h - musicScrollHandle.h));
    }
}

void MusicPlayer::render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my) {
    bool MouseOnKnopka1 = isMouseOnButton(mx, my, knopka1);
    bool MouseOnKnopka2 = isMouseOnButton(mx, my, knopka2);
    bool MouseOnKnopka11 = isMouseOnButton(mx, my, knopka11);
    bool MouseOnBack = isMouseOnButton(mx, my, backButton);
    bool MouseOnSliderTrack = (mx >= sliderTrack.x && mx <= sliderTrack.x + sliderTrack.w && my >= sliderTrack.y && my <= sliderTrack.y + sliderTrack.h);
    bool MouseOnMusicScroll = isMouseOnButton(mx, my, musicScrollHandle);
    vector<bool> MouseOnMusicSquare(musicSquares.size(), false);
    for (size_t i = 0; i < musicSquares.size(); ++i) {
        MouseOnMusicSquare[i] = isMouseOnButton(mx, my, musicSquares[i]);
    }

    SDL_Rect shadowRect = {coverRect.x + 5, coverRect.y + 5, coverRect.w, coverRect.h};
    SDL_SetRenderDrawColor(renderer, shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a);
    SDL_RenderFillRect(renderer, &shadowRect);
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &coverRect);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &coverRect);
    if (coverTexture) {
        SDL_RenderCopy(renderer, coverTexture, nullptr, &coverRect);
    }
    SDL_SetRenderDrawColor(renderer, MouseOnKnopka1 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka1 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka1 ? buttonHoverColor.b : buttonHoverColor.b, 255);
    SDL_Rect scaledKnopka1 = {knopka1.x - (MouseOnKnopka1 ? 5 : 0), knopka1.y - (MouseOnKnopka1 ? 5 : 0),
        knopka1.w + (MouseOnKnopka1 ? 10 : 0), knopka1.h + (MouseOnKnopka1 ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledKnopka1);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledKnopka1);
    SDL_Texture* btn1Text = createTextTexture(renderer, font, "Выбрать папку", textColor, 180);
    if (btn1Text) {
        int tw, th;
        SDL_QueryTexture(btn1Text, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledKnopka1.x + (scaledKnopka1.w - tw) / 2, scaledKnopka1.y + (scaledKnopka1.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(btn1Text, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(btn1Text, shadowColor.a);
        SDL_RenderCopy(renderer, btn1Text, nullptr, &shadowTr);
        SDL_SetTextureColorMod(btn1Text, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(btn1Text, 255);
        SDL_RenderCopy(renderer, btn1Text, nullptr, &tr);
        SDL_DestroyTexture(btn1Text);
    }
    SDL_SetRenderDrawColor(renderer, MouseOnKnopka2 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka2 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka2 ? buttonHoverColor.b : buttonHoverColor.b, 255);
    SDL_Rect scaledKnopka2 = {knopka2.x - (MouseOnKnopka2 ? 5 : 0), knopka2.y - (MouseOnKnopka2 ? 5 : 0),
        knopka2.w + (MouseOnKnopka2 ? 10 : 0), knopka2.h + (MouseOnKnopka2 ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledKnopka2);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledKnopka2);
    SDL_Texture* btn2Text = createTextTexture(renderer, font, "Выход", textColor, 180);
    if (btn2Text) {
        int tw, th;
        SDL_QueryTexture(btn2Text, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledKnopka2.x + (scaledKnopka2.w - tw) / 2, scaledKnopka2.y + (scaledKnopka2.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(btn2Text, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(btn2Text, shadowColor.a);
        SDL_RenderCopy(renderer, btn2Text, nullptr, &shadowTr);
        SDL_SetTextureColorMod(btn2Text, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(btn2Text, 255);
        SDL_RenderCopy(renderer, btn2Text, nullptr, &tr);
        SDL_DestroyTexture(btn2Text);
    }
    SDL_SetRenderDrawColor(renderer, MouseOnKnopka11 ? buttonHoverColor.r : buttonColor.r, MouseOnKnopka11 ? buttonHoverColor.g : buttonColor.g, MouseOnKnopka11 ? buttonHoverColor.b : buttonHoverColor.b, 255);
    SDL_Rect scaledKnopka11 = {knopka11.x - (MouseOnKnopka11 ? 5 : 0), knopka11.y - (MouseOnKnopka11 ? 5 : 0),
        knopka11.w + (MouseOnKnopka11 ? 10 : 0), knopka11.h + (MouseOnKnopka11 ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledKnopka11);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledKnopka11);
    SDL_Texture* btn11Text = createTextTexture(renderer, font, Mix_PausedMusic() ? "Играть" : "Пауза", textColor, 100);
    if (btn11Text) {
        int tw, th;
        SDL_QueryTexture(btn11Text, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledKnopka11.x + (scaledKnopka11.w - tw) / 2, scaledKnopka11.y + (scaledKnopka11.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(btn11Text, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(btn11Text, shadowColor.a);
        SDL_RenderCopy(renderer, btn11Text, nullptr, &shadowTr);
        SDL_SetTextureColorMod(btn11Text, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(btn11Text, 255);
        SDL_RenderCopy(renderer, btn11Text, nullptr, &tr);
        SDL_DestroyTexture(btn11Text);
    }
    SDL_SetRenderDrawColor(renderer, MouseOnBack ? buttonHoverColor.r : buttonColor.r, MouseOnBack ? buttonHoverColor.g : buttonColor.g, MouseOnBack ? buttonHoverColor.b : buttonHoverColor.b, 255);
    SDL_Rect scaledBackButton = {backButton.x - (MouseOnBack ? 5 : 0), backButton.y - (MouseOnBack ? 5 : 0),
        backButton.w + (MouseOnBack ? 10 : 0), backButton.h + (MouseOnBack ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledBackButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledBackButton);
    SDL_Texture* backText = createTextTexture(renderer, font, "Назад", textColor, 100);
    if (backText) {
        int tw, th;
        SDL_QueryTexture(backText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledBackButton.x + (scaledBackButton.w - tw) / 2, scaledBackButton.y + (scaledBackButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(backText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(backText, shadowColor.a);
        SDL_RenderCopy(renderer, backText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(backText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(backText, 255);
        SDL_RenderCopy(renderer, backText, nullptr, &tr);
        SDL_DestroyTexture(backText);
    }
    if (trackText) {
        int textW, textH;
        SDL_QueryTexture(trackText, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = {300 - textOffset, 350, min(textW, 300), textH};
        SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textRect.w, textRect.h};
        SDL_Rect clipRect = {300, 350, 300, textH};
        SDL_RenderSetClipRect(renderer, &clipRect);
        SDL_SetTextureColorMod(trackText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(trackText, shadowColor.a);
        SDL_RenderCopy(renderer, trackText, nullptr, &shadowRect);
        SDL_SetTextureColorMod(trackText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(trackText, 255);
        SDL_RenderCopy(renderer, trackText, nullptr, &textRect);
        SDL_RenderSetClipRect(renderer, nullptr);
    }
    SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
    SDL_RenderFillRect(renderer, &sliderTrack);
    int handlePos = sliderHandle.x - sliderTrack.x;
    SDL_Rect activePart = {sliderTrack.x, sliderTrack.y, handlePos + sliderHandle.w / 2, sliderTrack.h};
    SDL_SetRenderDrawColor(renderer, sliderActiveColor.r, sliderActiveColor.g, sliderActiveColor.b, sliderActiveColor.a);
    SDL_RenderFillRect(renderer, &activePart);
    SDL_SetRenderDrawColor(renderer, sliderHandleColor.r, sliderHandleColor.g, sliderHandleColor.b, sliderHandleColor.a);
    SDL_RenderFillRect(renderer, &sliderHandle);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &sliderHandle);
    if (currentTimeText) {
        int textW, textH;
        SDL_QueryTexture(currentTimeText, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = {sliderTrack.x - textW - 5, sliderTrack.y - textH / 2, textW, textH};
        SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
        SDL_SetTextureColorMod(currentTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(currentTimeText, shadowColor.a);
        SDL_RenderCopy(renderer, currentTimeText, nullptr, &shadowRect);
        SDL_SetTextureColorMod(currentTimeText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(currentTimeText, 255);
        SDL_RenderCopy(renderer, currentTimeText, nullptr, &textRect);
    }
    if (totalTimeText) {
        int textW, textH;
        SDL_QueryTexture(totalTimeText, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = {sliderTrack.x + sliderTrack.w + 5, sliderTrack.y - textH / 2, textW, textH};
        SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
        SDL_SetTextureColorMod(totalTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(totalTimeText, shadowColor.a);
        SDL_RenderCopy(renderer, totalTimeText, nullptr, &shadowRect);
        SDL_SetTextureColorMod(totalTimeText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(totalTimeText, 255);
        SDL_RenderCopy(renderer, totalTimeText, nullptr, &textRect);
    }
    if (MouseOnSliderTrack && bgm) {
        if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
        double musicDuration = Mix_MusicDuration(bgm);
        if (musicDuration > 0) {
            float progress = static_cast<float>(mx - sliderTrack.x) / sliderTrack.w;
            double hoverPosition = progress * musicDuration;
            hoverTimeText = createTextTexture(renderer, font, formatTime(hoverPosition), textColor);
        }
    } else {
        if (hoverTimeText) SDL_DestroyTexture(hoverTimeText);
        hoverTimeText = nullptr;
    }
    if (hoverTimeText) {
        int textW, textH;
        SDL_QueryTexture(hoverTimeText, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = {mx - textW / 2, my - textH - 5, textW, textH};
        SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
        SDL_SetTextureColorMod(hoverTimeText, shadowColor.r, shadowColor.g, shadowColor.b);
        SDL_SetTextureAlphaMod(hoverTimeText, shadowColor.a);
        SDL_RenderCopy(renderer, hoverTimeText, nullptr, &shadowRect);
        SDL_SetTextureColorMod(hoverTimeText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(hoverTimeText, 255);
        SDL_RenderCopy(renderer, hoverTimeText, nullptr, &textRect);
    }
    SDL_SetRenderDrawColor(renderer, sliderTrackColor.r, sliderTrackColor.g, sliderTrackColor.b, sliderTrackColor.a);
    SDL_RenderFillRect(renderer, &musicScrollTrack);
    SDL_SetRenderDrawColor(renderer, MouseOnMusicScroll ? sliderActiveColor.r : sliderHandleColor.r, MouseOnMusicScroll ? sliderActiveColor.g : sliderHandleColor.g, MouseOnMusicScroll ? sliderActiveColor.b : sliderHandleColor.b, 255);
    SDL_RenderFillRect(renderer, &musicScrollHandle);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &musicScrollHandle);
    for (size_t i = 0; i < musicSquares.size(); ++i) {
        SDL_SetRenderDrawColor(renderer, MouseOnMusicSquare[i] ? buttonHoverColor.r : buttonColor.r, MouseOnMusicSquare[i] ? buttonHoverColor.g : buttonColor.g, MouseOnMusicSquare[i] ? buttonHoverColor.b : buttonHoverColor.b, 255);
        SDL_Rect scaledSquare = {musicSquares[i].x - (MouseOnMusicSquare[i] ? 5 : 0), musicSquares[i].y - (MouseOnMusicSquare[i] ? 5 : 0),
            musicSquares[i].w + (MouseOnMusicSquare[i] ? 10 : 0), musicSquares[i].h + (MouseOnMusicSquare[i] ? 10 : 0)};
        SDL_RenderFillRect(renderer, &scaledSquare);
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(renderer, &scaledSquare);
        if (i + musicScrollOffset < musicFileTextures.size() && musicFileTextures[i + musicScrollOffset]) {
            int textW, textH;
            SDL_QueryTexture(musicFileTextures[i + musicScrollOffset], nullptr, nullptr, &textW, &textH);
            SDL_Rect textRect = {scaledSquare.x + 5, scaledSquare.y + (scaledSquare.h - textH) / 2, textW, textH};
            SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, textW, textH};
            SDL_Rect clipRect = {scaledSquare.x + 5, scaledSquare.y, 130, scaledSquare.h};
            SDL_RenderSetClipRect(renderer, &clipRect);
            SDL_SetTextureColorMod(musicFileTextures[i + musicScrollOffset], shadowColor.r, shadowColor.g, shadowColor.b);
            SDL_SetTextureAlphaMod(musicFileTextures[i + musicScrollOffset], shadowColor.a);
            SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &shadowRect);
            SDL_SetTextureColorMod(musicFileTextures[i + musicScrollOffset], textColor.r, textColor.g, textColor.b);
            SDL_SetTextureAlphaMod(musicFileTextures[i + musicScrollOffset], 255);
            SDL_RenderCopy(renderer, musicFileTextures[i + musicScrollOffset], nullptr, &textRect);
            SDL_RenderSetClipRect(renderer, nullptr);
        }
    }
}

bool MusicPlayer::isMouseOnButton(int mx, int my, const SDL_Rect& button) {
    SDL_Rect cursor = {mx, my, 2, 2};
    return SDL_HasIntersection(&cursor, &button);
}
