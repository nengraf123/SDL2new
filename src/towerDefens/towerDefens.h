#ifndef TOWERDEFENS_H
#define TOWERDEFENS_H
#include "../common/common.h"
#include <vector>
#include <string>

class TowerDefens {
public:
    TowerDefens();
    ~TowerDefens();
    void init();
    void handleEvents(SDL_Event& event, int mx, int my, int& scene);
    void update(SDL_Renderer* renderer, TTF_Font* font);
    void render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my);

private:
    struct Enemy {
        float x, y;
        float speed;
        int health;
        size_t pathIndex;
        bool active;
        int type;
    };
    struct Tower {
        int x, y;
        int range;
        int damage;
        float fireRate;
        Uint32 lastShot;
        bool active;
        int type;
    };
    struct Projectile {
        float x, y;
        float speed;
        int damage;
        Enemy* target;
        bool active;
    };
    Uint32 lastEnemySpawn;
    Uint32 enemySpawnInterval;
    int playerHealth;
    int playerMoney;
    int towerCost;
    SDL_Rect backButton;
    SDL_Texture* healthText;
    SDL_Texture* moneyText;
    std::vector<Enemy> enemies;
    std::vector<Tower> towers;
    std::vector<Projectile> projectiles;
    std::vector<SDL_Point> enemyPath;
    int selectedTowerType;
    SDL_Rect previewTower;
    bool isPlacingTower;
    SDL_Texture* enemyTexture;
    SDL_Texture* towerTexture;
    const int ENEMY_TYPES;
    const int TOWER_TYPES;
    float enemySpeeds[10];
    int enemyHealths[10];
    int towerRanges[10];
    int towerDamages[10];
    float towerFireRates[10];
    std::string towerNames[10];
    std::vector<SDL_Rect> towerCards;
    SDL_Color textColor;
    SDL_Color pathColor;
    SDL_Color enemyColor;
    SDL_Color towerColor;
    SDL_Color projectileColor;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;
    SDL_Color borderColor;
    SDL_Color validPlacementColor;
    SDL_Color invalidPlacementColor;
    bool isMouseOnButton(int mx, int my, const SDL_Rect& button);
    bool inRange(Tower& tower, float px, float py);
    bool isValidPlacement(int x, int y, const std::vector<Tower>& towers, int towerSize = 50);
    void renderCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
};

#endif
