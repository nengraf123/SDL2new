#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include "../common/common.h"
#include "../biblioteki/tinyfiledialogs.h"
#include <string>
#include <vector>

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();
    void init(const std::string& initialMusicPath, const std::string& initialFolderPath);
    void handleEvents(SDL_Event& event, SDL_Renderer* renderer, TTF_Font* font, TTF_Font* trackFont, int mx, int my, bool& running, int& scene);
    void update(SDL_Renderer* renderer, TTF_Font* font);
    void render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my);

private:
    std::string musicPath;
    std::string folderPath;
    std::string currentTrack;
    std::string coverPath;
    std::vector<std::string> musicFiles;
    std::vector<SDL_Texture*> musicFileTextures;
    std::vector<SDL_Rect> musicSquares;
    Mix_Music* bgm;
    int currentTrackIndex;
    bool musicStarted;
    SDL_Texture* trackText;
    SDL_Texture* currentTimeText;
    SDL_Texture* totalTimeText;
    SDL_Texture* hoverTimeText;
    SDL_Texture* coverTexture;
    double musicDuration;
    bool needsScrolling;
    int textOffset;
    Uint32 lastTextUpdate;
    SDL_Rect coverRect;
    SDL_Rect knopka1;
    SDL_Rect knopka2;
    SDL_Rect knopka11;
    SDL_Rect backButton;
    SDL_Rect sliderTrack;
    SDL_Rect sliderHandle;
    bool isDraggingSlider;
    SDL_Rect musicScrollTrack;
    SDL_Rect musicScrollHandle;
    bool isDraggingMusicScroll;
    size_t musicScrollOffset;
    size_t maxVisibleSquares;
    SDL_Color textColor;
    SDL_Color shadowColor;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;
    SDL_Color borderColor;
    SDL_Color sliderTrackColor;
    SDL_Color sliderHandleColor;
    SDL_Color sliderActiveColor;
    bool isMouseOnButton(int mx, int my, const SDL_Rect& button);
};

#endif
